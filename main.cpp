/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: BSD 2-Clause License
		Permisions: Commercial use, Distribution, Modification, Private use
		Conditions: License and copyright notice
		Limitations: Liability, Warranty
*/

// Your path to the toby header.
#include "Toby.hh"
#include <iostream>

int main(void)
{
	// Toby parser should be always* in a try block.
	try
	{
		libCore::Toby::Toby config("examples\\example.toby");

		// We get our info.
		auto& config_map = config._data;

		// We need to use the any_cast, it always returns an any type variable.
		std::string value = std::any_cast<std::string>(config_map["main"]["a"]);

		std::cout << value << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;

}