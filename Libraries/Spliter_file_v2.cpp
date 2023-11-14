#include <iostream>
#include <MyLib/opendialogfile.h>                // using opendialog windows
#include <MyLib/Console_Library/escape_code.h>   // for text coloring
#include <MyLib/CFile.h>						 // using class CFile

/*
                Author : KADDA Aoues 
				Date   : 3 / 11 / 2023
				Title  : version n 2 of spliter.assembler file.

*/


void assemble_files(const fs::path& directory, const std::string& name_of_file) {

	auto vec_paths = File::get_files_directory(directory);

	File::concate_files(vec_paths, directory.string() + "\\" + name_of_file);
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

	newline_;

	Print_(color::Green, "[+1] splite file to many files.") << end_;
	Print_(color::Green, "[+2] assemble a files in one file.") << end_;
	newline_;

__start:

	Print_(color::Green, "[+] chose option : ") << end_;
	int option{};
	std::cin >> option;

	if (option == 1) {

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

		wait_;
		return 1;
	}
	else if (option == 2) {
__assembly:
		auto _folder = opendialog::OpenFolder(L"chose folder where there splited files");

		fs::path folder(_folder);

		// check if is it folder and exist 
		if (!fs::is_directory(folder)) {
			Print_(color::Red, "this is not folder, chose another or exit :(y = another file/ n = exit") << end_;
			char ch{};
			std::cin >> ch;
			if (ch == 'y' || ch == 'Y') goto __assembly;
			return -1;
		}

		assemble_files(folder, "_Asm_files.as");
		Print_(color::Green, "files is assembled, exit.") << end_;
		return 2;
	}
	else {
		Print_(color::Red, "Chose only 1 or 2, re-entry : ") << end_;
		goto __start;
	}

	return 0;
}