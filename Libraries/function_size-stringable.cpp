#include <iostream>
#include "MyLib/function_utility.h"
#include "MyLib/Console_Library/escape_code.h"


int main()
{
	auto f = 1002232.3434f;
	auto size = Fn::_size<char>(f);
	
	print_ << f << " size of number " << size << end_;

	std::string str{ "hllo" };
	print_ << f << " size of number " << Fn::_size<char>(str) << end_;

	std::cin.get();
	return 0;
}