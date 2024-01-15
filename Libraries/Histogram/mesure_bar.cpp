#include <iostream>
#include <thread>
#include "MyLib/Console_Library/Event_Windows.h"
#include "mesured_value.h"





int main()
{
	INIT_WCHAR_TEXT;
	WHIDE_CURSOR;

	cui::Gauge_bar  flow_bar(10 ,25, -10.5f,+11.6f, L"FlowIn",L"Gal/min" ,
		                          10,3,color::Fuchsia,color::Grey11);

	cui::Gauge_bar  trip_tank(30, 25, 0.f, 80.f, L"Level", L"bls",
		                          10, 3, color::Purple, color::Grey11);

	cui::Gauge_bar  active_tank(50, 25, 0.f, 1300.f, L"Active", L"bls",
		                          10, 3, color::Red, color::Grey11);

	active_tank.set_value(1123.5f);

	int count{ 3 };

	float value{};

	while (true) {

		if (KeyOn('A')) {
			value += 0.5f;
		}

		if (KeyOn('Q')) {
			value -= 0.5f;
		}


		flow_bar.set_value(value);
		trip_tank.set_value(value);
		active_tank.draw();
		flow_bar.draw();
		trip_tank.draw();

		if (KeyPressed(VK_ESCAPE)) {
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		esc::wcls();
	}



	std::wcin.get();
	return 0;
}