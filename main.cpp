/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: BSD 2-Clause License
		Permisions: Commercial use, Distribution, Modification, Private use
		Conditions: License and copyright notice
		Limitations: Liability, Warranty
*/

/*
*	For examples check the `examples` folder. 
* 
* 
*	Feel free to use this file to playing around :^)
*/


#include "Toby.hh"
#include <iostream>
#include <thread>


int main(void)
{
	// Toby parser should be always* in a try block.
	try
	{
		libCore::Toby::Toby config("C:\\Users\\Alex\\Source\\Repos\\Toby\\examples\\example.toby");
	
		std::cout << std::any_cast<std::string>(config._data["Main"]["a"]);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;

}