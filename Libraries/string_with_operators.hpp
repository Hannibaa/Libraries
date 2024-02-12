#pragma once

#include <string>

namespace Str {

	// Class of string 

	class SString : public std::string {

	public:
		using std::string::string;
		

	};



}


std::string operator - (const std::string& s1, const std::string& s2) {
	// check if s1 is longer than s2 otherwise will return s1;
	std::string s{};
	std::string::size_type position{};

	if (s1.size() < s2.size()) {
		position = s2.find(s1);
		s = s2;
		if (position != std::string::npos) {
			s.erase(position, s1.size());
		}

		return s;
	}

	// looking for first occurence of s2 in s1;
	if (s1.size() > s2.size()) {
	    position = s1.rfind(s2);
		s = s1;
		if (position != std::string::npos) {
			s.erase(position, s2.size());
		}

		return s;
	}

	// thirs case is when s1.size == s2.size

	if (s1 == s2) {
		return std::string{ "" };
	}

	for (size_t k = 0; k != s1.size(); ++k) {
		if (s1[k] != s2[k]) s.push_back(s1[k]);
	}

	return s;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//     Operation divide / as remove all substring 's2' from 's1'
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string operator / (std::string s1, const std::string& s2) {
	size_t sz2 = s2.size();
	if (s1.size() < sz2) {
		std::cout << "undifined operation \n";
		return {};
	}
	size_t pos{};
	while ( true ) {
		pos = s1.find(s2);
		if (pos == std::string::npos) break;
		s1.erase(pos, sz2);
		std::cout << "pos : " << pos << '\n';
		std::cout << "s1  : " << s1 << '\n';
	}

	return s1;
}

//template<typename Tchar>
//std::basic_string<Tchar> operator - (const std::basic_string<Tchar>& s1, 
//	const std::basic_string<Tchar>& s2) {
//	// check if s1 is longer than s2 otherwise will return s1;
//	std::basic_string<Tchar> s{};
//	size_t position{};
//
//	if (s1.size() < s2.size()) {
//		position = s2.find(s1);
//		s = s2;
//		if (position != std::string::npos) {
//			s.erase(position, s1.size());
//		}
//
//		return s;
//	}
//
//	// looking for first occurence of s2 in s1;
//	if (s1.size() > s2.size()) {
//	    position = s1.rfind(s2);
//		s = s1;
//		if (position != std::string::npos) {
//			s.erase(position, s2.size());
//		}
//
//		return s;
//	}
//
//	// thirs case is when s1.size == s2.size
//
//	if (s1 == s2) {
//		return std::string{ "" };
//	}
//
//	for (size_t k = 0; k != s1.size(); ++k) {
//		if (s1[k] != s2[k]) s.push_back(s1[k]);
//	}
//
//	return s;
//}


