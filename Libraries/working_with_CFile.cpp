#include <iostream>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>

/*
     test name(), save(), and destroctor() action
*/

int main()
{
	File::CFile file;
	std::string file_name  ;

	print_ << "file name " << file.name() << end_;
	print_ << "file full name : " << file.path() << end_;
	print_ << "file size is " << file.size() << end_;

	file.add({ 'a','b' });
	file.setName("text.txt");


	print_ << "file size after add is " << file.size() << end_;
	print_ << "file name " << file.name() << end_;
	file.save();

	std::cin.get();
	return 0;
}