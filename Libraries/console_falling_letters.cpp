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

	// variable and object.
	FLetter letter(10.f, 20.f, 5);


	while (1) {

		std::this_thread::sleep_for(game_elapsetime_ms);
		esc::wcls();

		// title for widows console and inside console application
		swprintf_s(title, L"  Game Moving Text number [%4d]| time ms [%d]%3.3f|%3.3f",
			100, game_elapsetime_ms.count(), 10, 10);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);

		// GAME STARTING 


		letter.update();



		if (KeyPressed(VK_ESCAPE)) break;

		if (KeyPressed(VK_CONTROL)) {
			put_string_at(0, 2, L"Press up to move up");
			put_string_at(0, 3, L"Press down to move down");
			put_string_at(0, 4, L"Press right to move right");
			put_string_at(0, 5, L"Press left to move left");
			wwait_;
		}

		// strategy of Game

	}

	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}