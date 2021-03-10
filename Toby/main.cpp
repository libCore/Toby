#include "Toby.hh"

#include <iostream>

int main(void)
{

	try {
		libCore::Toby::Toby toby("test.toby");
		
		std::cout << std::any_cast<std::string>(toby.Get()["Main"]["a"]) << std::endl;
		std::cout << std::any_cast<std::string>(toby.Get()["Second"]["c"]) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Main: " << e.what() << std::endl;
	}

	return 0;
}
