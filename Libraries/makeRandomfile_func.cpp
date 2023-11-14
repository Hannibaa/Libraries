#include <iostream>
#include <MyLib/opendialogfile.h>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>




int main()
{
	auto file_name = opendialog::OpenFile(L"get any valide file");

	fs::path file_path{ file_name };

	print_ << "file : " << COLOR(color::Green, file_path.string()) << end_;
	print_ << "file name : " << COLOR(color::DarkGreen, file_path.stem().string()) << end_;
	wait_;


	fs::path new_file = fs::path(opendialog::OpenFolder(L"")).string() + "\\Random_file.txt";

	print_ << "new file : " << COLOR(color::Red, new_file.string()) << end_;
	wait_;

	File::makeRandomFile(new_file, 1000);

	std::cin.get();
	return 0;
}