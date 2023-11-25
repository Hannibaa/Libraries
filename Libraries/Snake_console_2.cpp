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

	float x{ 10.f }, y{ 10.f };
	Snake_1<12> snake(x,_width, 1.1f, y, _height, 1.1f);

	std::vector<Snake_1<12>> snakes(12, Snake_1<12>{ x,_width, 1.1f, y, _height, 1.1f });

	for (auto& s : snakes) s.setPosition(float(rand() % 111), float(rand() % 15));

	Elapsed_Time timer;
	float frequency{ 1.f };


	while (1) {
		//std::this_thread::sleep_for(game_elapsetime_ms);
		esc::wcls();

		// Title of Console 
		swprintf_s(title, L"  Game Moving Frame per sec [%5.3f] |Time[%d]|PosX[%3d]|PosY[%3d]",
			frequency, snakes.size(), snake.getPosition()[0], snake.getPosition()[1]);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);

		// Drawing 
		snake.update();

		// Dawing snakes
		for (auto& s : snakes) s.update();


		if (KeyPressed(VK_ESCAPE)) break;

		// Menu of console
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