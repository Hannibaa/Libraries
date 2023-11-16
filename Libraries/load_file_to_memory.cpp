#include <iostream>
#include <MyLib/opendialogfile.h>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>



int main()
{

	fs::path file_name = opendialog::OpenFile();

	if (file_name.empty()) return -1;else
	Print_(color::Green, "file : ") << COLOR(color::Yellow, file_name.string()) << end_; 

	char yn{};
	print_ << "did you like to continue to load it in memory (y/n) : ";
	std::cin >> yn;

	if (yn == 'n' || yn == 'N') {
		return -1;
	}

	auto file_memory = File::LoadFileToMemory<double>(file_name);

	print_ << "size of main vector : " << file_memory.first.size() << " of " <<
		typeid(file_memory.first[0]).name() << end_;
	print_ << "size of rest byte   : " << file_memory.second.size() << end_;



	std::cin.get();
	return 0;
}