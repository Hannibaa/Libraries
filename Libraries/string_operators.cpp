#include <iostream>
#include "string_with_operators.hpp"

#include "MyLib/Console_Library/escape_code.h"

/* 
    Test for operator - in string 
	will generalize for basic_string
*/

using namespace std::string_literals;

int main() {

	Str::SString  str("hello1world1;;;;;");
	Str::SString  str2(10, 'A');

	std::string s1{ "helloaabbccabbc!" };
	std::string s2{ "world hello world23 and than this is itis at?" };
	std::string s3{ "is" };

	print_ << s2 << end_;
	print_ << s2 - "is" << end_;
	print_ << "is" - s2 << end_;

	print_ << s1 - "ddssd" << end_;
	print_ << "ddef" - s2 << end_;

	print_ << "hello234234ccddd" - s1 << end_;
	print_ << "this is one of oasis"s - "is"s << end_;
	print_ << "this is one of oasis"s / "is"s << end_;

	//print_ << "s1 = " << s1 << end_ << end_;
	//print_ << "s2 = " << s2 << end_ << end_;


	//print_ << "s1 + s2 " << s1 + s2 << end_;

	//print_ << "s1 =     " << s1 << end_;
	//print_ << "s1 - abb " << s1 - std::string("abb") << end_;
	//print_ << "s1 - abb " << (s1 - "abb") - "abb" << end_;
	//print_ << "s1 - s2  " << s1 - s2 << end_;
	//print_ << "s1 - aaccbb : " << s1 - "aaccbb" << end_;
	//print_ << "s1 - nullstring " << s1 - "" << end_;
	//print_ << "there is time - s3 " << "there is a time " - s3 << end_;


	wait_;
	return 0;
}


