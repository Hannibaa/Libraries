#include <iostream>
#include <sstream>
#include <vector>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/function_utility.h"

template<typename Char>
void print_wchar_chart(Char from = 14i16, Char to = Fn::max_of<Char>, short char_in_line = 15i16, short max_char = 150i16)
{
	for (int s = from; s < to; ++s) {

		Char c = static_cast<Char>(s);

		wprint_ << std::hex << s << '|' << c << L"  ";

		if (s % char_in_line == 0) wprint_ << end_;
		std::wcin.clear();
		if (s % max_char == 0) wwait_;
		std::wcin.clear();
	}
}



int main()
{
	esc::init_wchar; 

	print_wchar_chart<char>();


	std::cin.get();
	return 0;
}