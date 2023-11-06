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

const size_t MAX_FILES_GEN = 20;

void splite_file(const fs::path& file_name, size_t Size, fs::path folder = std::string{}) {

	// Here we suppose file_name well defined and Size well defined
	// we create object CFile
	
	File::CFile file{ file_name };

	// will create folder at file position if there are no one:
	if (folder.empty()) {
		folder = file_name.parent_path().string() + "_" + Time::get_serial_at_time();
		fs::create_directory(folder);
	}

	// calculate number of file will be generated 
	// and rest file :
	size_t n_files = file.size() / Size;
	size_t rest_file = file.size() - n_files * Size;

	// create a files in folder.

	file.Splite_In(folder, Size, "splited");

}

void assemble_files(const fs::path& directory) {

}


int main() {
	Print_(color::Yellow, "******  KADDA Aoues sofware ware presente ******") << end_;
	Print_(color::Yellow, "******  spliter version v 2.0 *****") << end_;

	// here we load file, check file existence and sizing
	auto file_name = opendialog::OpenFile(L"open file to split it");

	fs::path file_name_{ file_name };
	

	Print_(color::Green, "file name : "); Print_(color::Yellow, file_name_) << end_;
	Print_(color::Green, "file size : "); Print_(color::Yellow, fs::file_size(file_name_)) << end_;

	newline_;
	Print_(color::Aqua, "did you like to splite file y/n ") << end_;
	char yn{};
	std::cin >> yn;
	if (yn == 'n' || yn == 'N') return;  // end of exicution

	size_t sz{};
	Print_(color::Aqua, "enter the size to be spliting ") << end_;
	std::cin >> sz;

    

	// here check directory existing and splites files existing and appropriate names for original
	// file.

	wait_;
	return 0;
}