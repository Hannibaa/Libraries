#include <iostream>
#include <string_view>
#include <thread>
#include "loacal_console_game_lib.h"




int main()
{

	INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
	WINIT_CURSOR;                                          // hide the cursor.
	std::chrono::milliseconds game_elapsetime_ms = 70ms;   // timing and speed.
	wchar_t title[100]{};                                  // title console.
	//std::wstringstream wss;



	//  ProgressBarH(const Pint& position, const std::wstring& title,
	//  int length, int color_bar, int color_text = 15)

	ProgressBar bar({ 10,10 }, L"File Copy", 36, 220);		 // vertical bar
															 
	ProgressBarH  hbar{ { 100,10 }, L"File Copy", 10 ,9 };  // horizontal bar
	hbar.set_value(5);
	ProgressBarH  hbar2{ { 70,15 }, L"WOP Inc", 9 ,5 };  // horizontal bar
	hbar2.set_value(7);



	Elapsed_Time timer;
	float frequency{ 1.f };
	float x{5};

	while (1) {
		std::this_thread::sleep_for(game_elapsetime_ms);
		esc::wcls();

		// Title of Console 
		swprintf_s(title, L"  Game Moving Frame per sec [%5.3f] |Time[%d]|PosX[%3d]|PosY[%3d] | Collision Times[%5d]",
			frequency, 1, 1, 1, 1);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);


		// Drawing 
		bar.progress(0.3f);
		bar.draw();
		x += 1.f / frequency;
		hbar.set_value(x);
		hbar.draw();
		hbar2.draw();
		// Dawing snakes

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
			wprint_ << MOVETO(1, 25)
				<< wCOLOR(color::Green, "set percent of progress bar :");
			float p{};
			std::wcin >> p;
			bar.set_value(p);
		}
		// set new title.
		if (KeyPressed(_u('T'))) {
			wprint_ << MOVETO(1, 23)
				<< wCOLOR(color::Green, "set title for progress bar : ");
			std::wstring p;
			std::getline(std::wcin, p);
			//std::wcin >> p;
			bar.setTitle(p);
		}

		// strategy of Game



		frequency = 1.f / timer();
	}



	wprint_ << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}