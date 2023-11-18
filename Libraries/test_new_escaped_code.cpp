#include <iostream>
#include <sstream>
#include <vector>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/stringfunctionhelper.h"




int main()
{
	esc::init_wchar;

	std::wstring text = L"hello world, this paragrapphe is use to demostrate std::vector<string> typing in box";
	
    std::wstring text2 = L"hello first line\nsecond line ----\nthird line ++++++\n" ;
	
	Str::replace_inplace(text2, L'\n', L' ');
	esc::print_text(text, 10, 15, 15);
	esc::customize(UNDERLINE, esc::print_text<wchar_t>, text, 14, 70, 20);
	esc::_coloring(color::Red, esc::print_text<wchar_t>, text2, 10, 100, 5);
	esc::print_text(text2, 10, 50, 15);


	std::cin.get();
	return 0;
}