#include <iostream>
#include <sstream>
#include <vector>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"


int main()
{
	esc::init_wchar;

	esc::print_wchar_chart(0x1fff, 0x2fff);


	std::cin.get();
	return 0;
}