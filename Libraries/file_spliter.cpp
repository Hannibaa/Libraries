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

void assemble_splite_files(const fs::path& directory) {

	// first get all file in this directory
	// check if files have same suffix number and identity for some file
	// generate a file : 
}

void generate_splite_file(File::CFile& file, size_t size) {

	const size_t file_size = file.size();
	// the size shoud be inferieur of file.size;
	if (size > file_size) {
		Print_(color::Red, "the size not appropriate") << end_;
		return;
	}

	// calculate number of files
	int n_files = file_size / size ;
	size_t rest_size = file_size - n_files * size;

	Print_(color::Green, "Number of files generated is : ") << n_files << end_;
	Print_(color::Green, "Last file should have : ") << rest_size << " bytes\n";

	if (n_files > 20) {
		Print_(color::Red, "Too much files generated, revisited input") << end_;
	}

	std::string str_time = Str::removeUnusefullCharAny(Time::ToDay::String(), ":- ");
	std::string file_name_ = file.name().string() + "_" + str_time + "_";

	fs::path new_path{};
	// making folder for files:
	if (fs::create_directory(file.path() + "\\Splite_" + file.name() + "_" + str_time)) {
		Print_(color::Green, "Success! Folder created for splited file") << end_;
		new_path = file.path() + "\\Splite_" + file.name() + "_" + str_time;
	}
	else {
		Print_(color::Red, "Failed?!!!, to creat folder splited") << end_;
		return;
	};

	// iteration number of generated file:
	for (int k = 0; k != n_files; ++k) {

		// make a name for file output 
		std::string file_name = file_name_ + std::to_string(k);

		// create temperary temp_file from file
		File::CFile temp_file(file, size , k * size);

		temp_file.save_file(new_path.string() + "\\" + file_name);
		Print_(color::Green, "file saved : ") <<COLOR(color::Red, file_name )<< end_;
	}

	if (rest_size != 0) {
	          File::CFile tm_file(file, rest_size, (n_files - 1) * size);
			  file_name_ += std::to_string(n_files);
	          tm_file.save_file(new_path.string() + "\\" + file_name_);
			  Print_(color::Green, "last file : ") << COLOR(color::Red, file_name_) << end_;
	}

	Print_(color::Yellow, "--------- End -------- End ---------- End ----------") << end_;
}




int main() {
	Print_(color::Green, "*****************************************************************") << end_;
	Print_(color::Green, "************* File Spliter Edited By KADDA Aoues ****************") << end_;
	Print_(color::Green, "*****************************************************************") << end_;

	newline_;
	Print_(color::Yellow, "Please press Entry to chose a file to be splited!") << end_;

	wait_;
	// file name in wchar_t 
	auto filename = opendialog::OpenFile(L"chose file to be splited");

	if (filename.empty()) {
		Print_(color::Red, "There no file, exit.") << end_;
	}

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