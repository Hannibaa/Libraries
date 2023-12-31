#include <iostream>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/CFile.h>

/*
          Test funtionality of CFile class and library functions
*/


int main()
{
	fs::path file_name = "C:\\Users\\Acer\\source\\MyProject\\Libraries\\Libraries\\Asmbly_code.txt";

	std::string save_file;

	File::CFile file(file_name);

	if( !File::file_propierty(file_name) ) return 2;

	save_file = file_name.parent_path().string() + "\\" + "saved.txt";

	print_ << "saved in : " << end_;
	print_ << "do you like to save it y/n: " << end_;
	char ch{};
	std::cin >> ch;

	if (ch == 'n' || ch == 'N') goto __end;

	file.save_file(save_file);
	print_ << "file saved " << end_;

	save_file.clear();
	save_file = file_name.parent_path().string() + "\\" + "region.txt";

	file.write('C', 3);
	file.write('C', 4);

	file.save_region(save_file, 2, 7);
	print_ << "save region in action\n";

	return 1;

__end:
	print_ << "end -------- \n";

	// test save to file :
	save_file.clear();
	save_file = file_name.parent_path().string() + "\\" + "save_2.txt";
	auto vec = file.getdataAs<double>();
	std::vector<double> vec2(vec.begin(), vec.begin() + 100 );
	File::save_to_file(vec2, save_file);
	print_ << "file saved to : " << save_file << end_;

	// we make overloading of that function to treated 
	save_file.clear();
	save_file = file_name.parent_path().string() + "\\" + "save_3.txt";

	File::save_to_file(vec.begin(), vec.begin()+2, save_file);
	print_ << "file saved to : " << save_file << end_;

	std::cin.get();
	return 0;
}