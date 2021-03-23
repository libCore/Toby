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
		// There is several ways to write into a file.
		// In here we will cover the most common way.

		libCore::Toby::Toby config("example.toby");

		config._data["Main"]["a"] = "We change the value";

		/*
		* In toby there is 4 ways to write into a file.
		* 
		* 1- **Re-write** the file.
		* 2- **Re-write** the file but, with **different** data.
		* 3- Write into **another** file but, with the **same** data.
		* 4- Write into **another** file but, with **different** data
		*/

		config.Write(); // We are applying the 1 rule.
		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}