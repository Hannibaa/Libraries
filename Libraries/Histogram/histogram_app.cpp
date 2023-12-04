#include <iostream>
#include "MyLib/Console_Library/Event_Windows.h"
#include "histogram_bar.h"





int main() {

	std::vector<int> vi{ 10,20,40,100 };

	std::vector<float> vff;  // this cause data error call abort() ;

	auto vf = vu::makeRandomContainer<std::vector>(20.5f, 75.7f, 124);

	Histogram::Histogram_bar  histo(17, 27, vf, 20, 100, L"Drilling Parameter", color::Green);
	//histo.enable_label();
	histo.set_title_Xaxis(L"index of data");
	histo.set_title_Yaxis(L"ROP[ft/h]");

	histo.set_bar_width(1);
	histo.init_bars();

	INIT_WCHAR_TEXT;
	WINIT_CURSOR;


		histo.draw();
	//while (true) {

	//	wprint_ << MOVETO(1, 1)
	//		<< L"Give number of line to be changed : ";
	//	int n{};
	//	std::wcin >> n;
	//	esc::wclear_line(1, 1);
	//	wprint_ << L"Give a new value for line [" << n << L"] : ";
	//	float v{};
	//	std::wcin >> v;

	//	histo.set_value(n, v);




	//	if (KeyPressed(VK_ESCAPE)) break;
	//}


	std::wcin.get();
	return 0;
}