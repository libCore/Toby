/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: GNU GPLv2
*/

#include "../Toby.hh"
#include <iostream>
#include <thread>
#include <chrono>

int main(void)
{
	// Toby parser should be always* in a try block.
	try
	{
		auto start = std::chrono::system_clock::now();

		// We don't need to call any other function.
		// The constructor reads the file automatically.
		// In the v2 you'll be able to call the contructor WITHOUT reading the file.
		libCore::Toby::Toby config("Path/To/bench.toby");

		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> diff = end - start;

		std::cout << diff.count() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;

}