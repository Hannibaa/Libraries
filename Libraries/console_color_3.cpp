#include <iostream>
#include <sstream>
#include <array>
#include <thread>
#include "loacal_console_game_lib.h"

class FLetter_ {

	std::wstring      text;
	float             x, y;
	float             Xstep, Ystep;
	color             _color;
	RNG::RG<int>      i;
	int               _k;
public:

	FLetter_(float _x, float _y, int clr, float sx = 1.5f, float sy = 1.0f)
		:text{ L"ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
		x{ _x },
		y{ _y },
		Xstep{ sx },
		Ystep{ sy },
		_color{ static_cast<color>(clr) },
		i{ 0,5 }
	{
		_k = RNG::Random::rand() % 36;
	}


	void setValue(float a, float b) {
		x = a;
		y = b;
	}

	void setText(std::wstring_view _text) {
		text = _text;
	}

	void setText(const wchar_t w) {
		text.push_back(w);
	}

	void update() {
		//y += Ystep;
		//y = std::clamp<float>( y, 1, _height);
		int _x = x; int _y = y;
		wprint_ << MOVETO(_x, _y) << _wCOLOR_FG6(i(), _k) << text << RESETMODE;
	}


};



int main()
{
	    std::map<int, int>  _ansi_color;         
		esc::make_color_map(_ansi_color, esc::_rgb_colors, 256);           
		esc::InterContainer rgb2ansi(&_ansi_color);    


	INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
	WINIT_CURSOR;                                          // hide the cursor.
	std::chrono::milliseconds game_elapsetime_ms = 100ms;   // timing and speed.
	wchar_t title[100]{};                                  // title console.


	swprintf_s(title, L"  Game Moving Text number [%4d]| time ms [%d]%3.3f|%3.3f",
		100, game_elapsetime_ms.count(), 10, 10);
	put_string_at(30, 0, title, color::Red);
	TITLE(title);

	// checking colors: 

	
	

	int k{};

	while (1) {
		std::this_thread::sleep_for(game_elapsetime_ms);
		esc::wcls();

		 // RNG::Random::rand() % int(0xffffff);
		k += 1000;

		if (k > 0xffffff) k = 0;

		int color = rgb2ansi[k];

		WPrint_(color, "Hello World") << k ;


		if (KeyPressed(VK_ESCAPE)) break;

		if (KeyPressed(VK_CONTROL)) {
			put_string_at(0, 2, L"Press up to move up");
			put_string_at(0, 3, L"Press down to move down");
			put_string_at(0, 4, L"Press right to move right");
			put_string_at(0, 5, L"Press left to move left");
			wwait_;
		}

		// strategy of Game


		//std::this_thread::sleep_for(game_elapsetime_ms);
	}



	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}