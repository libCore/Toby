#pragma once

/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: GNU GPLv2
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

		enum class EPreProc
		{
			VERSION,
			DEFINE
		};

		enum class EComment
		{
			SEMICOLON,
			HASH
		};

		enum class EChildSeparator
		{
			DOT,
			SLASH
		};
		
		typedef std::map<std::string, std::map<std::string, std::any>> data_t;
		typedef std::map<std::string, std::any> pair_t;

		class Toby
		{

		public:
			Toby() {}
			Toby(std::string path)
			{
				sPath = path;

				Read();
			}

			int version() { return _ver; }

			// Writes the file from the path especified with custom data.
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
			// Write the file from the path especified, with the local data
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
			// Write the file from the constructor with custom data.
			bool Write(data_t data)
			{
				std::lock_guard<std::mutex> lock(_data_mutex);

				std::ofstream file(sPath, std::ios::out);

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
			// Write the file from the constructor
			bool Write()
			{
				std::lock_guard<std::mutex> lock(_data_mutex);

				std::ofstream file(sPath, std::ios::out);
			
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

			std::map<EPreProc, std::map<std::string, std::any>> GetPreproc() { return _preproc_list; }


		public:
			data_t data;
			std::string sPath;
			char czComment = ';';
		private:

			bool Read()
			{
				std::string sData;
				std::ifstream ifsFile(sPath, std::ios_base::in);

				if (!ifsFile.is_open())
					throw std::exception("Cannot open the file.");

				while (std::getline(ifsFile, sData))
				{
					if (sData[0] == '#')
					{
						if (!set_preproc(sData))
							throw std::exception("Can't get the preprocs..");

						std::any ver = _preproc_list[EPreProc::VERSION]["ver"];

						if (std::stoi(std::any_cast<std::string>(ver)) != LIBCORE_TOBY_VERSION)
							throw std::exception("Version not implemented or supplied.");
					}
					else
					{
						if (parse(sData) == -1)
							throw std::exception("Can't parse.");
					}
				}
				ifsFile.close();
				return true;
			}

			/// <summary>
			/// Makes a field.
			/// </summary>
			/// <param name="k">The key of the field.</param>
			/// <param name="d">The data of the field.</param>
			/// <returns>The field ready to insert into the file.</returns>
			std::string make_field(std::string k, std::any d)
			{
				return k + "=" + std::any_cast<std::string>(d);
			}
			/// <summary>
			/// Makes a section.
			/// </summary>
			/// <param name="s">Name of the section</param>
			/// <returns>Section formatted.</returns>
			std::string make_section(std::string s)
			{
				
				return "[" + s + "]";
			}
			/// <summary>
			/// Checks if the string is a section
			/// </summary>
			/// <param name="sec">the line.</param>
			/// <returns>True if it's a section.</returns>
			bool is_section(std::string sec)
			{
				auto size_sec = sec.size() - 1;
				return (sec[0] == '[' && sec[size_sec] == ']');
			}

			/// <summary>
			/// Removes the brackets of a section.
			/// </summary>
			/// <param name="sec">The string.</param>
			/// <returns>The name of the section.</returns>
			std::string clean_section(std::string sec)
			{
				std::string _sec = sec;
				_sec.erase(_sec.begin());
				_sec.erase(_sec.end() - 1);
				return _sec;
			}
			
			/// <summary>
			/// Removes the white chars of a line.
			/// </summary>
			/// <param name="s">The string.</param>
			/// <returns>The string without white chars.</returns>
			std::string remove_white(std::string s)
			{
				s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
				return s;
			}

			/// <summary>
			/// Removes the first white chars of a string.
			/// </summary>
			/// <param name="s">The string.</param>
			/// <returns>The line without the first white characters.</returns>
			std::string remove_first_whites(std::string s)
			{
				for (size_t i = 0; i < s.length(); i++)
				{
					if (isspace(s[0]))
						s.erase(s.begin());
					else
						break;
				}
				return s;
			}

			/// <summary>
			/// Main function.
			/// </summary>
			/// <param name="line">The line.</param>
			/// <returns>The status.</returns>
			int parse(std::string line)
			{
				// We check if the line is a comment. If it is, we go back into the loop.
				if (line[0] == czComment || line == "") { return 1; }
				// We check if the line is a section. If it is, we are going store the section.
				if (is_section(remove_white(line))) { _scope = clean_section(remove_white(line)); return 1; }

				// Parses the data. Self explanatory.
				auto parsed_data = split(line, '=');
				parsed_data[0] = remove_white(parsed_data[0]);
				parsed_data[1] = remove_first_whites(parsed_data[1]);
				auto pair = std::make_pair(parsed_data[0], std::make_any<std::string>(parsed_data[1]));

				const std::lock_guard<std::mutex> lock(_data_mutex);

				data[_scope].insert(pair);

				return 0;
			}

			/// <summary>	
			/// /!\ Change the name of the function in future versions.
			/// Allows to parse and sture the `preprocs`
			/// </summary>
			/// <param name="line">Line what we got from the main loop</param>
			/// <returns>True if success</returns>
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
						_preproc_list[EPreProc::VERSION].insert(std::make_pair<std::string, std::any>("ver", std::make_any<std::string>(value_splitted[1])));

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
						_preproc_list[EPreProc::DEFINE].insert(std::make_pair<std::string, std::any>(value_splitted[1].c_str(), std::make_any<std::string>(value_splitted[2])));
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


			public:
			
			/// <summary>
			/// Util function. Allows split a string.
			/// </summary>
			/// <param name="s">String to split</param>
			/// <param name="delimiter">Token to split</param>
			/// <returns>Vector of strings</returns>
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
			int _ver;
			std::string _scope;
			std::map<EPreProc, std::map<std::string, std::any>> _preproc_list;
			std::mutex _data_mutex;
		};

	}


}
#endif // !LIBCORE_TOBY