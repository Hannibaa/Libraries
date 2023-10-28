#include <iostream>
#include <vector>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/function_utility.h>


//           Type comparing functions and mesure 
using namespace std::literals;

int main()
{


	print_ << "compare two size (int) > (double)    : " << Function::compareSize(33, 7.5,
		[](auto x1, auto x2) {return sizeof x1 > sizeof x2; }) << end_;
	print_ << "compare two size (string) > (double) : " << Function::compareSize("hello"s, 7.5,
		[](auto x1, auto x2) {return sizeof x1 > sizeof x2; }) << end_;

	newline_;

	print_ << "size of (int)    : " << Function::SizeOf(4444) << end_;
	print_ << "size of (double) : " << Function::SizeOf<double>() << end_;
	print_ << "size of (string) : " << Function::SizeOf<std::string>() << end_;
	print_ << "size of (vector) : " << Function::SizeOf<std::vector<int>>() << end_;

	newline_;

	print_ << "test Size_of structure : " << end_;
	print_ << "size of (wchar_t) : " << Function::Size_Of<wchar_t>::size << end_;
	print_ << "size of (void*)   : " << Function::Size_Of<void*>{}() << end_;   // create object function in place;

	std::cin.get();
	return 0;
}