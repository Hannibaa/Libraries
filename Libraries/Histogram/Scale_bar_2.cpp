#include <iostream>
#include "Histogram.h"

int main()
{

	auto vfloats = vu::makeRandomContainer<std::vector>(0, 355, 100);

	cu::print_container(vfloats,"value: ");

	INIT_WCHAR_TEXT;
	WINIT_CURSOR;

	// using function of histogram
	// 1. making vector of range
	auto ranges = histo_make_ranges(vfloats, 3);

	auto _map = histo_make_map_range(40, ranges);
	auto _map2 = histo_make_map_frequency(15, 100, 7);

	wprint_ << L"bins of data : \n";
	wprint_ << WREPEAT(10, L'-') << wend_;
	for (const auto& v : _map) wprint_ << v.first << L"|" << v.second << wend_;
	wprint_ << WREPEAT(10, L'-') << wend_;
	wprint_ << L"freqency intervals :\n";
	wprint_ << WREPEAT(10, L'-') << wend_;
	for (const auto& v : _map2) wprint_ << v.first << L"|" << v.second << wend_;
	wprint_ << WREPEAT(10, L'-') << wend_;

	auto vhisto = histo_get_frequency(ranges, vfloats);
	wnewline_;

	wprint_ << "table of bins/frequency :\n";
	histo_print_frequency_table(vhisto);

	std::sort(vfloats.begin(), vfloats.end());

	ScaleY  scaley(80,30, L"ROP drilling", 15, 2, color::Fuchsia, color::Green, _map2);
	ScaleX  scalex({ 81, 30 }, L"WOB drilling", 40, 3, color::Fuchsia, color::Green, _map);

	scaley.draw();
	scalex.draw();
	std::wcin.get();
	return 0;
}