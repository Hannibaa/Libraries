/*
                   KADDA Aoues 

				   1. file spliter and concataner
				   2. 1 / 11 / 2023

*/

#include <iostream>
#include <MyLib/opendialogfile.h>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/CFile.h>
#include <MyLib/chrono/to_day.h>   // using to day class to generate date.



void generate_splite_file(File::CFile& file, size_t size) {

	// the size shoud be inferieur of file.size;
	if (size > file.size()) {
		Print_(color::Red, "the size not appropriate") << end_;
		return;
	}

	// make a name for file output 
	std::string file_name = file.name() + "_" + Str::removeUnusefullCharAny(ToDay::String(), ":- ") + "_";

	// create temperary temp_file from file
	File::CFile temp_file(file,size);

	temp_file.save_file(file.path() + "\\"+ file_name + "1");
	Print_(color::Green, "file saved :") << temp_file.name() << end_;
}




int main() {
	Print_(color::Green, "*****************************************************************") << end_;
	Print_(color::Green, "************* File Spliter Edited By KADDA Aoues ****************") << end_;
	Print_(color::Green, "*****************************************************************") << end_;

	newline_;
	Print_(color::Yellow, "Please press Entry to chose a file to be splited!") << end_;

	// file name in wchar_t 
	auto filename = opendialog::OpenFile(L"chose file to be splited");

	File::CFile file(filename);

	Print_(color::Red, "file name : ") << file.name() << end_;
	Print_(color::Red, "size      : ") << file.size() << end_;

	newline_;
	// chosing option
	Print_(color::Green, "Chose option 1 or 2 :") << end_;
	Print_(color::Green, "1. Maximum bytes do you want in each file.") << end_;
	Print_(color::Green, "2. Number of files splited do you want generated.") << end_;

	int chose{};

re_chose:

	std::cin >> chose;

	if (chose == 1) {
		// how much maximum size of output files
		Print_(color::Yellow, "Enter the size of output files :") << end_;
		size_t sz{};
		std::cin >> sz;

		// put condition on sz!

		generate_splite_file(file, sz);
	}
	else if (chose == 2) {
		// how much number of file do you like to generated
		Print_(color::Yellow, "Enter a number of files do you like to generated :") << end_;
		size_t number_file{};
		std::cin >> number_file;
		// put condition on number_file!

		size_t sz = file.size() / number_file;

		generate_splite_file(file, sz);
	}
	else {
		print_ << "Error please chose 1 or 2\n";
		chose = 0;
		goto re_chose;
	}





	wait_;
	return 0;
}