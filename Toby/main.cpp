// Toby.cpp : Defines the entry point for the application.
//

#include "Toby.hh"

#include <iostream>
int main()
{
	libCore::Toby::Toby toby("test.toby");
	std::cout << std::any_cast<std::string>(toby.Get()["Main"]["a"]) << std::endl;
	std::cout << std::any_cast<std::string>(toby.Get()["Second"]["a"]) << std::endl;
	return 0;
}
