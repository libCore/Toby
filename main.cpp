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
#include <thread>

void write_file(libCore::Toby::data_t d)
{
	libCore::Toby::Toby conf("out.toby");
	
	conf.Write(d);
}

int main(void)
{
	// Toby parser should be always* in a try block.
	try
	{
		libCore::Toby::Toby config("C:\\Users\\Alex\\Source\\Repos\\Toby\\examples\\example.toby");
	
		std::thread t(write_file, config._data);

		t.join();

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;

}