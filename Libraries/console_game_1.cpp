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

	std::wstring    text;
	RV::SRV<float>  x, y;
	color           _color;

public:

	Text(float _x0, float _y0, float _s1, float _x1, float _y1, float _s2, int clr)
		:text{},
		x{ _x0,_y0,_s1 },
		y{ _x1,_y1,_s1 },
		_color{ static_cast<color>(clr) }
	{}


	void setStarValue(float a, float b) {
		x.start_value(a);
		y.start_value(b);
	}

	void setText(std::wstring_view _text) {
		text = _text;
	}

	void setText(const wchar_t w) {
		text.push_back(w);
	}

	std::wstring update() {
		std::wstringstream str;
		int _x = x; int _y = y;
		str << MOVETO(_x, _y) << _wCOLOR_FG256(_color) << text << RESETMODE;
		return str.str();
	}

	operator std::wstring() noexcept {
		return update();
	}
};

class Text_ {

	std::wstring    text;
	float  x, y;
	color           _color;

public:

	Text_( float _x, float _y, int clr)
		:text{},
		x{ _x },
		y{ _y },
		_color{ static_cast<color>(clr) }
	{}

	void setX(float a ) {
		x = a;
	}

	void setY(float b) {
		y = b;
	}

	void setText(std::wstring_view _text) {
		text = _text;
	}

	void setText(const wchar_t w) {
		text.push_back(w);
	}

	std::wstring update() {
		std::wstringstream str;
		int _x = x; int _y = y;
		str << MOVETO(_x, _y) << _wCOLOR_FG256(_color) << text << RESETMODE;
		return str.str();
	}

	operator std::wstring() noexcept {
		return update();
	}
};




int main()
{

	ESC::winit_cursor;
	esc::init_wchar;

	std::chrono::milliseconds _ms = 70ms;   // timing and speed

	bool no_text = true;

	Text_ text(20.f,45.f, 10);
	text.setText(Unicode::solid[9]);
	text.setText(Unicode::solid[9]);
	text.setText(Unicode::solid[9]);

	wchar_t title[100]{};

	float x{}, y{};

	while (1) {
		int _color = 13;

		esc::wcls();
		swprintf_s(title, L"  Game Moving Text number [%4d]| time ms [%d]%3.3f|%3.3f", 
			              100 , _ms.count(),x,y);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);


		if (KeyPressed(VK_UP))    y-=1.f;
		if (KeyPressed(VK_DOWN))  y+=1.f;
		if (KeyPressed(VK_RIGHT)) x+=2.3f;
		if (KeyPressed(VK_LEFT))  x-=2.3f;

		text.setX(x); text.setY(y);
		wprint_ << text.update();
		

		if (KeyPressed(VK_ESCAPE)) break;

		if (KeyPressed(VK_SPACE)) {
			put_string_at(0, 2, L"Press 'A' to see some effect KeyOn() function");
			put_string_at(0, 3, L"Press  up_arrow to raise occurence ");
			put_string_at(0, 4, L"Press  down_arrow to decrease occurence");
			put_string_at(0, 5, L"Press  entry to continue...");
			wwait_;
		}

		// strategy of Game

		std::this_thread::sleep_for(_ms);
	}

	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}