// Toby.cpp : Defines the entry point for the application.
//

#include "Toby.hh"

#include <iostream>
int main()
{
	libCore::Toby::Toby toby("test.toby");
	std::cout << toby << std::endl;
	return 0;
}
