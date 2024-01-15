#include <iostream>
#include <array>

#include "MyLib/Console_Library/escape_code.h"
//#include "MyLib/BitMaskFunction.h"
//#include "MyLib/Bits_operation.h"
//#include "MyLib/bitwisefunction.h"
#include "MyLib/bit_utility.h"

#define _Int(x)   int##x##_t 

template<typename Array>
void print_result(const Array& ar, std::string_view comment ="") {
	int i{};
	std::cout << comment << '\n';
	std::cout << "------------------------------------\n";
	for (const auto& e : ar) {
		if constexpr (std::is_integral_v<typename Array::value_type>)
			std::cout << i++ << "T : " << std::hex 
			<< (uint64_t)e << '\n';
		else
			std::cout << i++ << "[" << e << "]\n";
	}

	std::cout << "------------------------------------\n";
}


struct char3 {
	char a;
	char b;
	char c;
};

std::ostream& operator << (std::ostream& os, const char3 c3) {
	os << std::hex << (int)c3.a << " , " << (int)c3.b << " , " << (int)c3.c;
	return os;
}

struct mix3 {
	uint64_t  ui;
	float     f;
	char      c;
};

std::ostream& operator << (std::ostream& os, const mix3& m) {
	os << "{ " << m.ui << " , " << m.f << " , " << m.c << " }";
	return os;
}



int main() {

	// 16 bytes size struct :
	mix3 m{
	0xffaaccbbeeui64, 3.1415f, 'z'
	};

	std::string  str  = "hello ";
	std::wstring wstr = L"hello how are you?";

	// loaded to vector of bytes : 
	auto vec = Bit::load_toVector(m);

	std::array<byte, 16> arr;

	std::memcpy(arr.data(), vec.data(), sizeof(byte) * vec.size());

	print_result(vec, "vector");
	print_result(arr, "array");

	auto farr  = Bit::make_data_from<float>(arr);
	auto fvec  = Bit::make_data_from<float>(vec);
	auto fstr  = Bit::make_data_from<float>(str);
	auto mm = Bit::make_data_from<mix3>(vec, 0);
	std::cout  << " mm = " << mm << end_;
	auto mm2 = Bit::make_data_from<mix3>(str);
	// auto fwstr = Bit::make_data_from<float>(wstr); // because sizeof(wchar_t) = 2;

	print_result(farr, "array of float");
	print_result(fvec, "vector of float");
	print_result(fstr, "string of float");

	wait_;
	return 0;
}








//int main() {
//	// 16 bytes size struct :
//	mix3 m{
//	0xffaaccbbeeui64, 3.1415f, 'z'
//	};
//
//	// loaded to vector of bytes : 
//	auto vec = Bit::load_toVector(m);
//
//	std::array<byte, 16> Ar;
//	std::memcpy(Ar.data(), vec.data(), 16);
//
//	print_ << "size of vec : " << vec.size() << end_;
//	print_result(vec, "element of vector bytes : ");
//	print_result(Ar, "element of Array bytes : ");
//
//	// we need to make type of char 3 from vec from position 2 : 
//	char3 c3 = Bit::make_data_from<char3>(vec, 4);
//
//	float pii = Bit::make_data_from<float>(vec, 8);
//
//	auto vec_shorts = Bit::make_data_from<short>(vec);
//
//	print_ << "char3 : " << c3 << end_;
//	print_ << "float : pii : " << pii << end_;
//	print_result(vec_shorts, "vector of short integer value :");
//
//	wait_;
//	return 0;
//}





//int main() {
//
//	mix3 m{
//		0xffaaccbbeeui64, 3.1415f, 'z'
//	};
//
//	std::cout <<"m = " << m << end_;
//
//	// we going to load this type object in vector bytes
//
//	auto vec = load_toVector(m);
//	print_ << "size of vector " << vec.size() << end_;
//	for (const auto& e : vec) print_ << e << " ";
//
//	newline_;
//	print_ << "float from : " << Bit::_getSubType<float>(m,8) << end_;
//	print_ << "char from : " << Bit::_getSubType<char>(m,12) << end_;
//	print_ << "long int : " << std::hex << Bit::_getSubType<uint64_t>(m) << end_;
//
//	std::cin.get();
//	return 0;
//}



//
//int main()
//{
//	int x = 0xfaf0f3aa;
//
//	char3 c3{ 0xf1, 0xf2, 0xf3 };
//
//	uint64_t y = 0xaabbccdd'eeff9977;
//
//	std::cout << std::hex << " x " << x << '\n';
//
//	auto vecx  = Bit::getSubType<char>(x);
//	auto vecxi = Bit::getSubType<unsigned short>(x);
//	auto vc    = Bit::getSubType<unsigned char>(y);
//	auto v3c   = Bit::getSubType<short>(c3);
//
//	print_result(vc);
//	print_result(vecx);
//	print_result(vecxi);
//	std::cin.get();
//	return 0;
//}