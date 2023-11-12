#include <iostream>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>

/*
          Test funtionality of CFile class and library functions
*/


int main()
{
	fs::path file_name = "C:\\Users\\Acer\\source\\MyProject\\Libraries\\Libraries\\Asmbly_code.txt";

	std::string save_file;

	File::CFile file(file_name);

	if( !File::file_propierty(file_name) ) return 2;

	save_file = file_name.parent_path().string() + "\\" + "saved.txt";

	print_ << "saved in : " << end_;
	print_ << "do you like to save it y/n: " << end_;
	char ch{};
	std::cin >> ch;
	if (ch == 'n' && ch == 'N') goto __end;

	file.save_file(save_file);
	print_ << "file saved " << end_;
	return 1;

__end:

	std::cin.get();
	return 0;
}