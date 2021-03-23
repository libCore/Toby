/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: GNU GPLv2
*/

// Your path to the toby header.
#include <LibCore/Toby>

int simple(void)
{
	// Toby parser should be always* in a try block.
	try  
	{
		libCore::Toby::Toby config("example.toby");

		// We get our info.
		auto& config_map = config._data;

		// We need to use the any_cast, it always returns an any type variable.
		std::string value = std::any_cast<std::string>(config_map["Main"]["a"]);

		std::cout << value << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}