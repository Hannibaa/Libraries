#include <iostream>
#include <MyLib/opendialogfile.h>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>

/*
           Auture : KADDA Aoues 
		      Exemple for filesystem, and using opendialgue folder box, 
			  and test making random file text and binary.
*/


int main()
{

	fs::path folder = fs::path(opendialog::OpenFolder(L""));

	if (!fs::exists(folder)) {
		Print_(color::Red, "this folder : ") << folder.string() << COLOR(color::Green, "not exist") << end_;
		return -1;
	}
	else {
		Print_(color::Green, "folder : ") << folder.string() << end_;
	}

	fs::path file_random_text = folder.string() + "\\Random_text.txt";
	fs::path file_random_binary = folder.string() + "\\Random_binary.bin";

	print_ << "text file   : " << COLOR(color::Red, file_random_text.string()) << end_;
	print_ << "binary file : " << COLOR(color::Red, file_random_binary.string()) << end_;
	wait_;

	// checking if file exist otherwise will not forward operation

	if (!fs::exists(file_random_text)) {
		Print_(color::Red, "file not exit ok!") << end_;
	    File::makeRandomTextFile(file_random_text,100, 100 ,114, Str::getRandomString, "A  ", 99ull);
	}
	else {
		Print_(color::Red, "file exist do nothing") << end_;
	}

	if (!fs::exists(file_random_binary)) {
		Print_(color::Red, "file not exit ok!") << end_;
	    File::makeRandomFile(file_random_binary, 1ull << 7ull);
	}
	else {
		Print_(color::Red, "file exist do nothing") << end_;
	}

	std::cin.get();
	return 0;
}