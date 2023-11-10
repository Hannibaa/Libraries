#include <iostream>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/function_utility.h>

/*
       Test a 'clamp function' and template version of clamp.
*/


int main()
{
	for (float f = 0.f; f < 10.f; f += 0.5f) {
		// template one.
		print_ << "clamp<2.4f, 7.1f>[" << f << "] = " << Fn::clamp<2.4f, 7.1f>(f) << end_;
		// all argument is variable in second overloading
		print_ << "clamp the function " << Fn::clamp(f, f-0.1f , f+0.1f) << end_; 
	}

	Fn::clamp<23, 5>(4);

	

	std::cin.get();
	return 0;
}