#include <iostream>
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/containers.h"

template<typename T1,typename T2>
class A {
	T1* ptr;
	T2  value;

public:
	A(T1* _ptr, T2 _value)
		: ptr{_ptr},
		  value{_value}
	{
		Print_(color::Purple, "Calling A(T1*,T2)") << end_;
	}

	A(T1& _ref, T2 _value) 
		: A(&_ref, _value) 
	{
		Print_(color::Aqua, "Calling A(T1&,T2)") << end_;
	}

};

	template<typename T>
	A(T* p) -> A < T, decltype(std::string{}) > ;


int main()
{
	std::map<int,int> _m{ {2000,0},{4000,1}, {100,3}, {-100,6 } };

	A a(&_m, [](){});

	A b(_m, []() {});


	std::cin.get();
	return 0;
}