#include <iostream>
#include <string>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/random_generator.h>

/* 
            Test For Generate Random Object ?
			
*/

template<typename Type,typename...Option, typename GeneratorType>
Type generate_type(const Option&...args, GeneratorType generator) {
	return generator(args...);
}



int main()
{
	// generate int 

	RNG::iRG<int> int_rand;

	for (int i = 0; i < 10; ++i) {

	  auto f = generate_type<std::string,int,int>(int_rand(0,5), int_rand(5,12), [](int a, int b)->std::string
	       	{ return std::string("hello world").substr(a, b); });
	  print_ << "string behavior [" << f <<"]" << end_;

	}

	for (int j = 0; j < 10; ++j) {
		auto str_gen = [](int a, int b, std::string_view str) { return std::string(str).substr(a, b); };
		auto str = str_gen(int_rand(0, 5), int_rand(5, 12), "hello world there");
		print_ << "string 2 : [" << str << ']' << end_;
	}

	auto i = generate_type<int,int,int>(20, 10, [&](int i_max, int i_min)->int 
		      {return int_rand(i_min,i_max); });

	print_ << "integer generated " << i << end_;


	std::cin.get();
	return 0;
}
