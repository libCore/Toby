#pragma once

#define LIBCORE_TOBY_VERSION 0

#include <string>
#include <istream>
#include <fstream>
#include <any>
#include <utility>
#include <vector>
#include <sstream>

#include <iostream>

namespace libCore {

	namespace Toby {

		enum class pre_proc
		{
			version
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
					auto pair = get_preproc(data);
					if (pair.first != pre_proc::version || pair.second != LIBCORE_TOBY_VERSION)
						throw std::exception("Version not supplied.");
					break;
				}
			}
			int version() { return _ver; }
		private:
			std::pair<pre_proc, int> get_preproc(std::string line)
			{

				if (line[0] != '#')
					throw std::exception("Pre-processor not declared.");

				auto value_splitted = split(line, ' ');
				std::string token = value_splitted[0].c_str();
				token.erase(token.begin());
				if (token == "version")
				{
					try
					{
						_ver = std::stoi(value_splitted[1]);
						_preproc_list.push_back(std::make_pair<pre_proc, int>(pre_proc::version, std::stoi(value_splitted[1])));
						return std::make_pair<pre_proc, int>(pre_proc::version, std::stoi(value_splitted[1]));
					}
					catch (const std::exception& e)
					{
						throw e;
					}
					

				}

				//return std::make_pair()
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
			std::vector<std::pair<pre_proc, int>> _preproc_list;
		};

	}


}