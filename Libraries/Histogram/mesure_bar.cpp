#include <iostream>
#include <thread>
#include "mesured_value.h"





int main()
{
	INIT_WCHAR_TEXT;
	WHIDE_CURSOR;

	cui::Gauge_bar  flow_bar(10 ,25, -10.5f,+11.6f, L"FlowIn",L"Gal/min" ,
		                          10,3,color::Fuchsia,color::Grey11);


	int count{ 3 };

	while (--count) {
		 float value = float(rand() % 10);
		 flow_bar.set_value(value);
	     flow_bar.draw();
		 wwait_;
		 std::this_thread::sleep_for(std::chrono::milliseconds(100));
		 esc::wcls();
	}



	std::wcin.get();
	return 0;
}