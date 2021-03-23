/*
	libreCore or libCore - Toby config.

	Author: Alex. G. B. aka Zankuro

	License: GNU GPLv2
*/

/*
*	For examples check the `examples` folder. 
* 
* 
*	Feel free to use this file to playing around :^)
*/


#include "Toby.hh"
#include <iostream>


int main(void)
{
	// Toby parser should be always* in a try block.
	try
	{
		/*
		* Welcome to the playground!
		* 
		* On here is the minimal setup for use Toby.
		* I recomend get used to the api before adding Toby to your application.
		* Don't worry, it doesn't take so much time to learn.
		* 
		* Have fun! :^)
		*/

		libCore::Toby::Toby config("Path");

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;

}