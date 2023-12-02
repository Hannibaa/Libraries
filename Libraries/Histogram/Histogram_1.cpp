#include <iostream>
#include "Histogram.h"


int main()
{
	std::vector<int> vint = vu::make_equi_distance_container<std::vector<int>>(5,80,7);

	std::vector vint2 = vu::makeRandomContainer<std::vector>(5.f, 80.f, 70);

	// Initialization data for graph.
	Histogram histo(20, 29, vint2, 1, 25, 10, 1);
	histo.init_bar_data(2, 2, L"WOB para", 45, color::Blue); // to show data by arrow keyboard
	//histo.init_histogram_bars(L"Average ROP");             // initialization of bars. equidistance bars
	histo.set_graduation(6, 8);
	histo.init_histogram_variable_bars(L"Average RPM TORQ");
	histo.set_histo_title(L"Drilling Parameters");

	histo.draw();

	std::cin.get();
	return 0;
}