#include <iostream>
#include <MyLib/opendialogfile.h>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>



int main()
{
	File::CFile file;
	file.setName("data.bin");
	file.add<double>({ 100.24, 500.789 }, 0);  
	file.add({ 'a','b','c' }, file.size());
	file.add<double>({ 100.24, 500.789 }, file.size());
	file.save();

	print_ << "file name : " << file.name() << end_;
	print_ << "file size : " << file.size() << end_;

	

	std::cin.get();
	return 0;
}