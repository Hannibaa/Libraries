#include <iostream>
#include <sstream>
#include <array>
#include <thread>
#include "loacal_console_game_lib.h"

/*
          random move of snakes
		  detect collision 
		  radii of collision
*/



int main()
{
	INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
	WINIT_CURSOR;                                          // hide the cursor.
	std::chrono::milliseconds game_elapsetime_ms = 100ms;   // timing and speed.
	wchar_t title[100]{};                                  // title console.
	std::wstringstream wss;

	// minimum radii 
	int R_min{ 2 };
	int collision_times{};
	bool enable_waiting{ true };

	float x{ 10.f }, y{ 10.f };
	Snake_1<12> snake(x,_width, 1.1f, y, _height, 1.1f);

	std::vector<Snake_1<12>> snakes(3, Snake_1<12>{ x,_width, 1.1f, y, _height, 1.1f });

	for (auto& s : snakes) s.setPosition(float(rand() % 145), float(rand() % 35));

	Elapsed_Time timer;
	float frequency{ 1.f };


	while (1) {
		//std::this_thread::sleep_for(game_elapsetime_ms);
		esc::wcls();

		// Title of Console 
		swprintf_s(title, L"  Game Moving Frame per sec [%5.3f] |Time[%d]|PosX[%3d]|PosY[%3d] | Collision Times[%5d]",
			frequency, snakes.size(), snake.getPosition()[0], snake.getPosition()[1], collision_times);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);
		put_string_at(1, 33, wss.str(), color::Green);
		wss.str(L"");


		// Drawing 
		snake.update();
		put_string_at(1+snake.getPosition()[0], 1+snake.getPosition()[1], L"\x2542", color::Red);

		// Dawing snakes
		for (auto& s : snakes) {
			s.update();
		}

		if (KeyPressed(VK_ESCAPE)) break;

		// Menu of console
		if (KeyPressed(VK_SPACE)) {
			put_string_at(0, 2, L"Press up to add element falling");
			put_string_at(0, 3, L"Press down to remove element");
			put_string_at(0, 4, L"Press A to change game parameter");
			put_string_at(0, 5, L"Press left  N\\A");
			wwait_;
		}

		// add new parameter
		if (KeyPressed(_u('A'))) {
			int temp = R_min;
			wprint_ << MOVETO(1, 29);
			wprint_ << L"previews value R_min[" << R_min << L"] enable_waiting[" << enable_waiting 
				    << L"]" << wend_;
			WPrint_(color::Green, L"enter radius of collision R_min :");
			std::wcin.clear();
			std::wcin >> R_min;
			if (R_min == 0) R_min = temp;
			WPrint_(color::Green, L"Desable/Enable waiting in collision :");
			std::wcin >> enable_waiting;
		}

		// strategy of Game
		

		// Collision effect: 
		for (auto& s : snakes) {
			int dist = sqrt_distance(snake.getPosition(), s.getPosition());
			int lmin = 4 * R_min * R_min;
			wss << L"distance[" << dist << L"]| lmin[" << lmin << L"]\x2588\x2588";
			if ( dist < lmin) {
				++collision_times;
				put_string_at(snake.getPosition()[0], snake.getPosition()[1],
					L"COLLISION", color::Red);
				if ( enable_waiting ) wwait_;
			}
			
		}

		
		
		frequency = 1.f / timer();
	}



	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}