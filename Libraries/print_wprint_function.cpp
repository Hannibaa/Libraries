#include <iostream>
#include "MyLib/Console_Library/escape_code.h"

template<typename T, typename St = std::ostream>
St _print;

template<typename St>
St _print<char, St> = std::cout;

// TODO    need to fix this 
template<typename st>
st _print<wchar_t, st>  =  std::wcout;

int main()
{
	print_ << "hello" << end_;

	wprint_ << L"Hello\x2588" << wend_;

	_print<char> << "hello new template stream" << end_;

	_print<wchar_t, std::wostream> << L"hello" << end_;

	std::cin.get();
	return 0;
}