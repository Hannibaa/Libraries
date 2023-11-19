#include <iostream>
#include <sstream>
#include <thread>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/random_variable.h"
#include "MyLib/Console_Library/escape_code.h"

using namespace std::chrono_literals;

int _width = 145;
int _height = 35;


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

	std::wstring      text;
	float             x, y;
	float         _vx, _vy;
	color           _color;

	int up, down, right, left;

	void moving(float& x, float& y, float speedX, float speedY) {
		if (KeyPressed(up))    y -= speedY;
		if (KeyPressed(down))  y += speedY;
		if (KeyPressed(right)) x += speedX;
		if (KeyPressed(left))  x -= speedX;

		x = std::clamp<float>(x, 0.f, _width);
		y = std::clamp<float>(y, 0.f, _height);
	}

public:

	Text_( float _x, float _y, int clr , const float (&v)[2] )
		:text{},
		x{ _x },
		y{ _y },
		_vx{v[0]},
		_vy{v[1]},
		up{VK_UP},
		down{VK_DOWN},
		right{VK_RIGHT},
		left{VK_LEFT},
		_color{ static_cast<color>(clr) }
	{}

	void define_control(int _up, int _down, int _right, int _left) {
		up = _up;
		down = _down;
		right = _right;
		left = _left;
	}

	void setX(float a ) {
		x = a;
	}

	void setY(float b) {
		y = b;
	}

	void setVelocity(float vx, float vy) {
		_vx = vx; 
		_vy = vy;
	}

	void setText(std::wstring_view _text) {
		text = _text;
	}

	void setText(const wchar_t w) {
		text.push_back(w);
	}

	std::wstring update() {
		moving(x, y, _vx, _vy);
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
	INIT_WCHAR_TEXT;
	WINIT_CURSOR;
    
	std::chrono::milliseconds _ms = 70ms;   // timing and speed


	Text_ text(20.f,10.f, 10 ,{3.3f,1.3f});
	text.setText(Unicode::solid[9]);
	text.setText(Unicode::solid[9]);
	text.setText(Unicode::solid[9]);

	Text_ text2(60.f,10.f, 10 ,{3.3f,1.3f});
	text2.setText(Unicode::solid[9]);
	text2.setText(Unicode::solid[9]);
	text2.setText(Unicode::solid[9]);
	text2.define_control(_u('W'), _u('S'), _u('A'), _u('D'));

	wchar_t title[100]{};

	while (1) {

		std::this_thread::sleep_for(_ms);
		esc::wcls();

		// title for widows console and inside console application
		swprintf_s(title, L"  Game Moving Text number [%4d]| time ms [%d]%3.3f|%3.3f", 
			              100 , _ms.count(),10,10);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);


		wprint_ << text.update();
		wprint_ << text.update();
		wprint_ << text.update();
		wprint_ << text2.update();
		

		if (KeyPressed(VK_ESCAPE)) break;

		if (KeyPressed(VK_SPACE)) {
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