#include <iostream>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/stringfunctionhelper.h>

/* 
               Test random function generating string
*/


int main()
{
	print_ << "get 10 random string " << end_;

	// first example
	for (int i = 0; i < 10; ++i)
		print_ << i << " string " << Str::getRandomString("A         ", 100) << end_;

	wait_; cls();
	for (int i = 0; i < 10; ++i)
		print_ << i << " string " << Str::getRandomString(10) << end_;

	wait_; cls();
	for (int i = 0; i < 10; ++i)
		print_ << i << " string " << Str::getRandomString(22, "--- ___ @@@_ ") << end_;

	wait_; cls();
	for (int i = 0; i < 10; ++i)
		print_ << i << " string " << Str::getRandomString("-- @@@\\@@@@\\@@ phone.") << end_;



	std::cin.get();
	return 0;
}