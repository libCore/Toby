#pragma once

#define LIBCORE_TOBY_VERSION 1

#include <string>
#include <istream>
#include <fstream>
#include <any>
#include <utility>
#include <vector>
#include <sstream>
#include <map>
#include <any>

namespace libCore {

	namespace Toby {

		enum class pre_proc
		{
			version,
			define
		};

		class Toby
		{
		public:
			Toby(std::string path)
			{
				_path = path;

				std::string data;
				std::ifstream file(_path, std::ios_base::in);

				if (!file.is_open())
					throw std::exception("Cannot open the file.");

				while (std::getline(file, data))
				{
					if (data[0] == '#')
					{
						if (!set_preproc(data))							
							throw std::exception("Can't get the preprocs..");

						if (std::any_cast<int>(_preproc_list[pre_proc::version]["ver"]) != LIBCORE_TOBY_VERSION)
							throw std::exception("Version not implemented or supplied.");
					}
					else
					{
						if (parse(data) == -1)
							throw std::exception("Can't parse.");
					}
				}
			}
			int version() { return _ver; }
			std::map<std::string, std::map<std::string, std::any>> Get()
			{
				return _data;
			}
		private:
			bool is_section(std::string sec)
			{
				auto size_sec = sec.size();
				return (sec[0] == '[' && sec[size_sec-1] == ']');
			}

			std::string clean_section(std::string sec)
			{
				sec.erase(sec.begin());
				sec.erase(sec.end() - 1);
				return sec;
			}

			int parse(std::string line)
			{
				// main
				// We check if the line is a section. If it is, we are going store the section.
				if (is_section(line)) { _scope = clean_section(line); return 1; }

				auto parsed_data = split(line, '=');
				auto pair = std::make_pair(parsed_data[0], std::make_any<std::string>(parsed_data[1]));
				_data[_scope].insert(pair);

			}

			bool set_preproc(std::string line)
			{
				auto value_splitted = split(line, ' ');
				std::string token = value_splitted[0].c_str();
				token.erase(token.begin());
				if (token == "version")
				{
					try
					{
						_ver = std::stoi(value_splitted[1]);
						_preproc_list[pre_proc::version].insert(std::make_pair<std::string, std::any>("ver", std::make_any<std::string>(value_splitted[1])));

						return true;
					}
					catch (const std::exception& e)
					{
						throw e;
						return false;

					}
				}
				else if (token == "define")
				{
					try
					{
						_preproc_list[pre_proc::define].insert(std::make_pair<std::string, std::any>(value_splitted[1].c_str(), std::make_any<std::string>(value_splitted[2])));
						return true;

					}
					catch (const std::exception& e)
					{
						throw e;
						return false;
					}
				}
			}

			std::vector<std::string> split(const std::string& s, char delimiter)
			{
				std::vector<std::string> tokens;
				std::string token;
				std::istringstream tokenStream(s);
				while (std::getline(tokenStream, token, delimiter))
				{
					tokens.push_back(token);
				}
				return tokens;
			}

	

		private:
			std::string _path;
			int _ver;
			std::string _scope;
			std::map<pre_proc, std::map<std::string, std::any>> _preproc_list;
			std::map<std::string, std::map<std::string, std::any>> _data;
		};

	}


}