#include <iostream>
#include <vector>
#include <array>
#include <MyLib/container_utility.h>
#include "MyLib/Console_Library/escape_code.h"


int main()
{
	float a[5]{ 1.f,2.f,3.f,4.f,5.f };
	float b[5]{ 1.f,2.f,3.f,4.f,5.f };
	std::vector<int> vi{ 1,2,3,4,5,6 };
	std::array<char, 4> vchar{ 'a','b','c','d' };

	Container::print_container(vi, "vector");
	Container::print_container(vchar,"array of char");
	Container::print_container(a,"c type array");

	cu::rotate_array_to_value<5>(100.f, a);
	cu::rotate_container_to_value(2000, vi);
	cu::rotate_container_to_value('k', vchar);

	Container::print_container(vchar,"array of char after rotate");
	Container::print_container(a, "after rotation and add value");
	Container::print_container(vi,"vector of char after rotate");

	std::cin.get();
	return 0;
}