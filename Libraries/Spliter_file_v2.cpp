#include <iostream>
#include <MyLib/opendialogfile.h>                // using opendialog windows
#include <MyLib/Console_Library/escape_code.h>   // for text coloring
#include <MyLib/CFile.h>						 // using class CFile
#include <MyLib/chrono/to_day.h>                 // using to day class to generate date.

/*
                Author : KADDA Aoues 
				Date   : 3 / 11 / 2023
				Title  : version n 2 of spliter.assembler file.

*/


void assemble_files(const fs::path& directory) {

}

fs::path get_file_and_check_size(size_t& _size) {
__another:
	// here we load file, check file existence and sizing
	auto string_file = opendialog::OpenFile(L"open file to split it");
	char yn{};

	fs::path file_name{ string_file };

	if (!File::file_propierty(file_name)) {
		Print_(color::Red, "file not exist or failure to open") << end_;
		Print_(color::Green, "did you like another file (y/n)") << end_;

		std::cin >> yn;
		if (yn == 'y' || yn == 'Y') goto __another;

		return {};
	}

	size_t file_size = fs::file_size(file_name);

	// checking and simulate spliting of file

	size_t n_files{};
	size_t rest_file{};

	Print_(color::Aqua, "enter the size to be spliting ") << end_;
	std::cin >> _size;


	if (_size > file_size) {
		Print_(color::Red, "there problemes of size spliting files") << end_;
		goto __end;
	}

	n_files = file_size / _size;
	rest_file = file_size - _size * n_files;

	if (rest_file == 0) print_ << "number of file out : " << n_files << end_;
	else print_ << "number of file out : " << n_files + 1 << end_;


__end:
	return file_name;
}


int main() {
	Print_(color::Yellow, "******  KADDA Aoues sofware ware presente ******") << end_;
	Print_(color::Yellow, "******  spliter version v 2.0             ******") << end_;


	size_t _size{};
	auto file_name = get_file_and_check_size(_size);

	if (file_name.empty()) {
		Print_(color::Red, "is not valide file name") << end_;
		return -1;
	}

	Print_(color::Green, "file : ") << COLOR(color::Red, file_name.string()) << end_;

	// calling of function 
	File::splite_file(file_name, _size);
	Print_(color::Green, "spliting finish") << end_;

	// we should print file and their size to screen


	wait_;
	return 0;
}