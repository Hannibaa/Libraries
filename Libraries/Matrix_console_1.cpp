#include <iostream>
#include <sstream>
#include <array>
#include <thread>
#include "loacal_console_game_lib.h"




int main()
{
	INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
	WINIT_CURSOR;                                          // hide the cursor.
	std::chrono::milliseconds game_elapsetime_ms = 100ms;   // timing and speed.
	wchar_t title[100]{};                                  // title console.



	std::vector<MMatrix> vMatrix(12, MMatrix{ 60.f,7.f });
	vMatrix.reserve(100);

	Elapsed_Time timer;
	float frequency{ 1.f };

	while (1) {
		//std::this_thread::sleep_for(game_elapsetime_ms);
		esc::wcls();

		swprintf_s(title, L"  Game Moving Frame per sec [%5.3f] |Time[%d]|elements[%3d]|color[%8d]",
			frequency, game_elapsetime_ms.count(), vMatrix.size(), 1.f);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);

		// Loop over matrix off falling latter.
		for (auto& element : vMatrix) element.update();

		if (KeyPressed(VK_ESCAPE)) break;

		if (KeyPressed(VK_UP)) { 
			if (vMatrix.size() < 99 )
			vMatrix.push_back(MMatrix{ 70.f,5.f });
		}

		if (KeyPressed(VK_DOWN)) { 
			if (!vMatrix.empty()) vMatrix.pop_back();
		}


		if (KeyPressed(VK_SPACE)) {
			put_string_at(0, 2, L"Press up to add element falling");
			put_string_at(0, 3, L"Press down to remove element");
			put_string_at(0, 4, L"Press right N\\A");
			put_string_at(0, 5, L"Press left  N\\A");
			wwait_;
		}

		// strategy of Game


		frequency = 1.f / timer();
	}



	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}