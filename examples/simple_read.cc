/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: BSD 2-Clause License
		Permisions: Commercial use, Distribution, Modification, Private use
		Conditions: License and copyright notice
		Limitations: Liability, Warranty
*/

// Your path to the toby header.
#include "../Toby.hh"

int simple(void)
{
	// Toby parser should be always* in a try block.
	try  
	{
		libCore::Toby::Toby config("Your path");

		// We get our info.
		auto& config_map = config.Get();

		// We need to use the any_cast, it always returns an any type variable.
		std::string value = std::any_cast<std::string>(config_map["Main"]["a"]);

		std::cout << value << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}