#include <iostream>
#include <sstream>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"


int main()
{
	// print_ << LED(2);
	//print_ << SINGLE_WSH6 ;
	std::string cur;
	std::stringstream stream;

	TITLE(L"hello this my first title here ");

	print_ << "Hello " << end_;

	print_ << BLINKING ;

	print_ << "Hello " << end_;

	print_ << "this one is " << end_;
	stream << REQUES_CUR_POS;
	print_ << "the coordinate of actual cursor is : " << stream.str();
	print_ << RESETMODE;
	// print_ << LEDOFF;

	std::cin.get();
	return 0;
}