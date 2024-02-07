#include <iostream>
#include <span>
#include <vector>
#include <valarray>
#include <array>
#include <set>
#include <forward_list>

#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/container_utility.h"




int main()
{
	auto coll_vector = cu::make_random_container<std::vector<int>>(0, 10, 10);
	auto coll_vector_gen = cu::make_random_container<std::vector<int>>(0, 15, 10,
		[](int min, int max) {return rand() % (max - min + 1) + min; });
	auto coll_array = cu::make_random_container<std::array<float, 4>>(-10.5f, 24.f);
	auto coll_set = cu::make_random_container<std::set<int>>(-1, 1, 10);
	auto coll_set_gen = cu::make_random_container<std::set<int>>(-10, 10, 10,
		[](int min, int max) {return rand() % (max - min);});
	auto coll_multset = cu::make_random_container<std::multiset<int>>(-1, 1, 10);
	auto coll_multset_gen = cu::make_random_container<std::multiset<int>>(-10, 10, 10 ,
		[](int min, int max) {return rand() % (min - max); });
	//auto coll_list = make_random_container<std::forward_list<char>>('a', 'k', 7);
	std::span<int> coll_span(coll_vector.begin() + 1, coll_vector.end() - 2);

	auto coll_array_gen = cu::make_random_container<std::array<int, 20>>(-5, 5,
		[](int min, int max) { return rand() % (max - min + 1) + min ; });

	cu::print_container(coll_vector, "random collection of vector int   :");
	cu::print_container(coll_array,  "random collection of array flaot  :");
	cu::print_container(coll_span, "random collection of span int  :");
	cu::print_container(coll_set, "random collection of int in set :");
	cu::print_container(coll_multset, "random collection of int in multset :");
	cu::print_container(coll_array_gen, "random collection with generating function : ");
	cu::print_container(coll_vector_gen, "random collection vector with generating function :");
	cu::print_container(coll_set_gen, "set with generating function : ");
	cu::print_container(coll_multset_gen, "multi-set with generating function : ");
	//cu::print_container(coll_list, "random collection of list char    :");

	std::cin.get();
	return 0;
}