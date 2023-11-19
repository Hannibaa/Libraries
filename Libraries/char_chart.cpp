#include <iostream>
#include <sstream>
#include <vector>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"



int main()
{
	esc::init_wchar; 

	esc::print_CharType_chart<char>();


	std::cin.get();
	return 0;
}