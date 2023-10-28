#include <iostream>
#include <MyLib/stringfunctionhelper.h>
#include "MyLib/Console_Library/escape_code.h"

using namespace std;


int main()
{
	string text = "hello the repeated qualification std it's tedious and distracting";

	auto v_words = Str::StringToWords(text);

	Str::PrintWords2(v_words,60,'\n');


	cin.get();
	return 0;
}