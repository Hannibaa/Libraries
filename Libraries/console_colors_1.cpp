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


	swprintf_s(title, L"  Game Moving Text number [%4d]| time ms [%d]%3.3f|%3.3f",
	                   100, game_elapsetime_ms.count(), 10, 10);
	put_string_at(30, 0, title, color::Red);
	TITLE(title);

	// checking colors: 
	wnewline_;
	for (int i = 0; i != 16; ++i) {
		wprint_ << "color " << i << " is : " << _wCOLOR_FG256(i) << "COLOR" <<
		   RESETMODE << wend_;
	}
	wwait_;

	for (int k = 0; k != 36 ; ++k) {
		wnewline_;
		for (int i = 0; i != 6; ++i) {
			wprint_ << "color " << i << " is : " << _wCOLOR_FG6(i,k) << "COLOR" <<
				RESETMODE << wend_;
		}
	//	wwait_;
	}

	wnewline_;
	for (int i = 232; i != 256; ++i) {
		wprint_ << "color " << i << " is : " << _wCOLOR_FG256(i) << "COLOR" <<
			RESETMODE << wend_;
	}
	wwait_;







	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}

