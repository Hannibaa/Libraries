#include <iostream>
#include <sstream>
#include <thread>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/random_variable.h"
#include "MyLib/Console_Library/escape_code.h"

using namespace std::chrono_literals;



void put_string_at(int x, int y, const std::wstring& wstr, color _color = color::White) {
	wprint_ << MOVETO(x, y);
	WPrint_(_color, wstr);
}

class Text {
	float x0, y0;
	float x1, y1;
	float stepX, stepY;

	std::wstring text;

	RV::SRV<float> x, y;
	color _color;

public:

	Text(float _x0, float _y0, float _s1, float _x1, float _y1, float _s2, int clr)
		:x{_x0,_y0,_s1},
		 y{_x1,_y1,_s1},
		_color{static_cast<color>(clr)}
	{}

	void setStarValue(float a, float b) {
		x.start_value(a);
		y.start_value(b);
	}

	void setText(std::wstring_view _text) {
		text = _text;
	}

	operator std::wstring() {
		std::wstringstream str;
		str << MOVETO(x, y) << _wCOLOR_FG256(_color) << text << RESETMODE;
		return str.str();
	}
};

int main()
{
	SETMODE_WTTEXT;
	ESC::winit_cursor;

	RV::SRV<float> x(0.f, 120.f, 0.7f);
	x.start_value(30.f);
	RV::SRV<float> y(0.f, 30.f, 0.9f);
	y.start_value(10.f);
	
	RV::SRV<float> x1(0.f, 120.f, 0.7f);
	RV::SRV<float> y1(0.f, 30.f, 0.5f);

	bool no_text = true;
	int min_dist = 230;

	std::wstring text1 ;
	std::wstring text2 ;

	while (1) {
		int _color = 13;
		int _x1 = x;		int _x2 = x1;
		int _y1 = y;        int _y2 = y1;

		int d = (_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2);

		wcls();
		put_string_at(30, 0, L"Game Moving Text      | distance [" + std::to_wstring(d) + L"]",
			         color::Red);


		if (no_text) {
			wprint_ << MOVETO(5, 15) << "give me text 1: " ;
			std::wcin >> text1;
			wprint_ << MOVETO(5, 16) << "give me text 2: " ;
			std::wcin >> text2;
			wwait_; no_text = false;
		}


		auto xy1 = Unicode::dnlc + std::to_wstring(_x1) + L"|" + std::to_wstring(_y1) ;
		auto xy2 = Unicode::dnlc + std::to_wstring(_x2) + L"|" + std::to_wstring(_y2) ;

		put_string_at(_x1, _y1,xy1 + text1, static_cast<color>(_color));
		put_string_at(_x2, _y2,xy2 + text2, static_cast<color>(_color - 2));

		if (KeyPressed(VK_ESCAPE)) break;


		if (KeyPressed(VK_SPACE)) {
			put_string_at(0, 2, L"Press 'A' to see some effect KeyOn() function");
			put_string_at(0, 3, L"Press  up_arrow to raise occurence ");
			put_string_at(0, 4, L"Press  down_arrow to decrease occurence");
			put_string_at(0, 5, L"Press  entry to continue...");
			wwait_;
		}

		// strategy of Game
		if (d < min_dist) {
			put_string_at(0, 0, L"IS TOO CLOSE", color::Green);
			wwait_;
		}

		std::this_thread::sleep_for(500ms);
	}

	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	SETMODE_TEXT;
	std::cin.get();
	return 0;
}