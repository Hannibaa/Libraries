#include <iostream>
#include "c:\Users\Acer\source\MyLib/Console_Library/escape_code.h"
#include <MyLib/chrono/to_day.h>
#include <MyLib/stringfunctionhelper.h>

/*
             KADDA Aoues 
			 Date : 1 / 11 /2023
			 1. Add static function Static
			 2. Add function removeUnusefullChar in string lib

*/


int main()
{
	print_ << ToDay::date();

	newline_;
	
	print_ << ToDay::String() << end_;

	auto date = Str::removeUnusefullCharAny(ToDay::String(),":- ");

	newline_;
	print_ << "date iss : " << date << end_;

	std::cin.get();
	return 0;
}