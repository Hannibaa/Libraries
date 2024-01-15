#include <iostream>
#include <thread>
#include "MyLib/opendialogfile.h"
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/CFile.h"
#include "MyLib/random_generator.h"

/*
      Author :	KADDA Aoues
	  Date   :  13 / 01 / 2024
	  App    :  Deleting file for unrecovered

	  Abstract : we open file after, rewritten in it a random 
*/

const char* title = R"(******************************************************************
******************* KADDA AOUES SMALL-PROGRAM ********************
* THIS PROGRAM REPLACE ALL BYTES OF FILE BY RANDOM BYTE IN AIME  *
*   TO REPLACE ALL FILE BY RANDOM BYTE FOR UNRECOVED REASON      *
******************************************************************)";

const char* attention = R"(* -------------------------- ATTENTION ------------------------- *
*        THE FILE IS UN-RECOVERED AFTER SUCCESS OPERATION        *
* -------------------------------------------------------------- *
)";


int main()
{
	Print_(color::Lime, title) << end_;
	Print_(color::Red, attention) << end_;
	newline_; 

	print_ << "press entry to continue" << end_;
	std::cin.get();

	rng::RG<char> _byte;
	char yn{};
	fs::path file = opendialog::OpenFile(L"get any file");

	//fs::path file = R"(C:\Users\Acer\Documents\files.txt)";

	if (file.empty()) {
		Print_(color::Red, "Error in opening file") << end_;
		return -1;
	}


	Print_(color::Green, "file path : ") << file.string() << end_;

_yes_or_no:
	Print_(color::Green, "do you like to unrecovered file Y/N : ");

	std::cin >> yn;

	if (yn == 'N' || yn == 'n') {
		Print_(color::Red, "File not unrecovered...end") << end_;
		return 1;
	} 
	else if (yn != 'Y' && yn != 'y') {
		goto _yes_or_no;
	}

	// open file in mode read write
	std::fstream  _file{ file, std::ios::binary | std::ios::in | std::ios::out };

	if (!_file.is_open()) {
		Print_(color::Red, "Error in opening file...") << end_;
		return -1;
	}

	// read first 10 character : 
	std::cin.get();

	_file.seekg(0, std::ios::end);
	size_t length = _file.tellg();
	Print_(color::Green, "size : ") << length << end_;

	_file.seekg(0 , std::ios::beg);

	while (--length) {
		_file.put(_byte());
	}

	print_ << end_;
	_file.close();
	
	Print_(color::Red, "The File is -- UNRECOVER --") << end_;

	Print_(color::Green, "End ...") << end_;

	std::cin.get();
	return 0;
}