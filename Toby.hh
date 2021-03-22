#pragma once

/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: BSD 2-Clause License
		Permisions: Commercial use, Distribution, Modification, Private use
		Conditions: License and copyright notice
		Limitations: Liability, Warranty
*/

#ifndef LIBCORE_TOBY
#define LIBCORE_TOBY


// YOU MUST **NOT** CHANGE THIS
#define LIBCORE_TOBY_VERSION 1


// If you don't want includes, just define it.
#ifndef LIBCORE_NOINCLUDES
#include <string>
#include <istream>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <map>
#include <any>
#include <mutex>
#endif // !LIBCORE_NOINCLUDES

namespace libCore {

	namespace Toby {

		enum class pre_proc
		{
			version,
			define
		};
		
		typedef std::map<std::string, std::map<std::string, std::any>> data_t;

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

						std::any ver = _preproc_list[pre_proc::version]["ver"];

						if (std::stoi(std::any_cast<std::string>(ver)) != LIBCORE_TOBY_VERSION)
							throw std::exception("Version not implemented or supplied.");
					}
					else
					{
						if (parse(remove_white(data)) == -1)
							throw std::exception("Can't parse.");
					}
				}
				file.close();
			}
			int version() { return _ver; }
			/*
			std::map<std::string, std::map<std::string, std::any>> Read()
			{
				return _data;
			}
			*/
			// DumbWrite
			bool Write(std::string path, data_t data)
			{

				std::ofstream file(path, std::ios::out);

				if (!file.is_open())
				{
					return false;
					throw std::exception("Cannot open the file.");
				}

				file << "#version " << LIBCORE_TOBY_VERSION << std::endl;

				std::lock_guard<std::mutex> lock(_data_mutex);

				for (const auto& Fpair : data)
				{
					file << make_section(Fpair.first) << std::endl;
					for (const auto& Spair : Fpair.second)
					{
						file << make_field(Spair.first, Spair.second) << std::endl;
					}
				}

				file.close();
			}
			bool Write(std::string path)
			{

				std::ofstream file(path, std::ios::out);

				if (!file.is_open())
				{
					return false;
					throw std::exception("Cannot open the file.");
				}

				file << "#version " << LIBCORE_TOBY_VERSION << std::endl;

				std::lock_guard<std::mutex> lock(_data_mutex);

				for (const auto& Fpair : _data)
				{
					file << make_section(Fpair.first) << std::endl;
					for (const auto& Spair : Fpair.second)
					{
						file << make_field(Spair.first, Spair.second) << std::endl;
					}
				}

				file.close();
			}
			bool Write(data_t data)
			{
				std::lock_guard<std::mutex> lock(_data_mutex);

				std::ofstream file(_path, std::ios::out);

				if (!file.is_open())
				{
					return false;
					throw std::exception("Cannot open the file.");
				}

				file << "#version " << LIBCORE_TOBY_VERSION << std::endl;

				for (const auto& Fpair : data)
				{
					file << make_section(Fpair.first) << std::endl;
					for (const auto& Spair : Fpair.second)
					{
						file << make_field(Spair.first, Spair.second) << std::endl;
					}
				}

				file.close();
			}
			bool Write()
			{
				std::lock_guard<std::mutex> lock(_data_mutex);

				std::ofstream file(_path, std::ios::out);
			
				if (!file.is_open())
				{
					return false;
					throw std::exception("Cannot open the file.");
				}

				file << "#version " << LIBCORE_TOBY_VERSION << std::endl;
				
				for (const auto& Fpair : _data)
				{
					file << make_section(Fpair.first) << std::endl;
					for (const auto& Spair : Fpair.second)
					{
						file << make_field(Spair.first, Spair.second) << std::endl;
					}
				}

				file.close();
			}

			std::map<pre_proc, std::map<std::string, std::any>> GetPreproc() { return _preproc_list; }

			std::map<std::string, std::map<std::string, std::any>> _data;
			char _comment = ';';
		private:
			std::string make_field(std::string k, std::any d)
			{
				return k + "=" + std::any_cast<std::string>(d);
			}
			std::string make_section(std::string s)
			{
				return "[" + s + "]";
			}
			bool is_section(std::string sec)
			{
				auto size_sec = strlen(sec.c_str()) - 1;
				return (sec[0] == '[' && sec[size_sec] == ']');
			}

			std::string clean_section(std::string sec)
			{
				std::string _sec = sec;
				_sec.erase(_sec.begin());
				_sec.erase(_sec.end() - 1);
				return _sec;
			}

			std::string remove_white(std::string s)
			{
				s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
				return s;
			}

			int parse(std::string line)
			{
				// main
				// We check if the line is a section. If it is, we are going store the section.
				if (line[0] == _comment || line == "") { return 1; }
				if (is_section(line)) { _scope = clean_section(line); return 1; }

				auto parsed_data = split(line, '=');
				auto pair = std::make_pair(parsed_data[0], std::make_any<std::string>(parsed_data[1]));

				const std::lock_guard<std::mutex> lock(_data_mutex);

				_data[_scope].insert(pair);

				return 0;
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
				else
				{
					throw std::exception("Unknow preproc");
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
			std::mutex _data_mutex;
		};

	}


}
#endif // !LIBCORE_TOBY