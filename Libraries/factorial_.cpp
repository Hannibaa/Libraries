#include <iostream>
#include <vector>
#include <MyLib/function_utility.h>




int main() {
	Print_(color::Green, "Testing Factorial , Run Time and Compile Time ") << end_;
	print_ << "factorial of 0 " << Function::Factorial<0>::value << end_;
	print_ << "factorial of 1 " << Function::Factorial<1>::value << end_;
	print_ << "factorial of 6 " << Function::Factorial<10>::value << end_;

	const int N = 4;
	newline_;
	print_ << "factorial of N " << Function::Factorial<N>::value << end_; // working for const and constexpr
	newline_;
	//for (int i = 0; i < 10; ++i)  // this loop not working 
	//	print_ << "factorial of (" << i << "!) = " << Function::Factorial<i>::value << end_;
	for (int i = 0; i < 10; ++i)
		print_ << "factorial of (" << i << "!) = " << Function::factorial(i) << end_;

	Print_(color::Red, "Test Run time factorial") << end_;

	print_ << "factorial of 3 " << Function::factorial(3) << end_;



	wait_;
	return 1;
}