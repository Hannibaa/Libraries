#pragma once

#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/random_variable.h"
#include "MyLib/Console_Library/escape_code.h"

using namespace std::chrono_literals;

constexpr int _width = 145;
constexpr int _height = 35;


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
	std::array<std::wstring, 4>  _shapes;
	float             x, y;
	float         _vx, _vy;
	color           _color;
	int i{};
	int up, down, right, left, select_key;

	void moving(float& x, float& y, float speedX, float speedY) {
		if (KeyPressed(up))    y -= speedY;
		if (KeyPressed(down))  y += speedY;
		if (KeyPressed(right)) x += speedX;
		if (KeyPressed(left))  x -= speedX;

		x = std::clamp<float>(x, 0.f, _width);
		y = std::clamp<float>(y, 0.f, _height);
	}

	void select_shape() {
		++i;
		i = i % 4;
		if (KeyPressed(select_key))
			if (i == 0 || i == 1 || i == 2 || i == 3) text = _shapes[i];
	}

public:

	Text_(float _x, float _y, int clr, const float(&v)[2])
		:text{},
		x{ _x },
		y{ _y },
		_vx{ v[0] },
		_vy{ v[1] },
		up{ VK_UP },
		down{ VK_DOWN },
		right{ VK_RIGHT },
		left{ VK_LEFT },
		select_key{ VK_SPACE },
		_color{ static_cast<color>(clr) }
	{}

	void define_control(int _up, int _down, int _right, int _left, int _select_key) {
		up = _up;
		down = _down;
		right = _right;
		left = _left;
		select_key = _select_key;
	}

	void insert_shape(const std::wstring(&shape)[3]) {
		_shapes[1] = shape[1];
		_shapes[2] = shape[2];
		_shapes[3] = shape[0];
	}

	void setX(float a) {
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
		_shapes[0] = text;
	}

	void setText(const wchar_t w) {
		text.push_back(w);
		_shapes[0] = text;
	}

	std::wstring update() {
		moving(x, y, _vx, _vy);
		select_shape();
		std::wstringstream str;
		int _x = x; int _y = y;
		str << MOVETO(_x, _y) << _wCOLOR_FG256(_color) << text << RESETMODE;
		return str.str();
	}

	operator std::wstring() noexcept {
		return update();
	}
};



class MMatrix {

	std::wstring      text;
	float             x, y;
	float             Xstep, Ystep;
	color             _color;
	RNG::RG<int>      i;

public:

	MMatrix(float _x, float _y, int clr, float sx = 1.5f, float sy = 1.3f)
		:text{ L"ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
		x{ _x },
		y{ _y },
		Xstep{ sx },
		Ystep{ sy },
		_color{ static_cast<color>(clr) },
		i{ 0,26 }
	{}


	void setValue(float a, float b) {
		x = a;
		y = b;
	}

	void setSpeedY(float vy) {
		Ystep = vy;
	}

	void setText(std::wstring_view _text) {
		text = _text;
	}

	void setText(const wchar_t w) {
		text.push_back(w);
	}

	void update(int _crgb = 0) {
		y += Ystep;
		y = std::clamp<float>( y, 1, _height);
		int _x = x; int _y = y;
		if (_crgb == 0) _crgb = _color;
		if (_crgb > 254) {
			y = RNG::Random::rand() % 10;
			x = RNG::Random::rand() % 144;
		}

		wprint_ << MOVETO(_x, _y) << _wCOLOR_FG256(_crgb) << text[i()] << RESETMODE;
		wprint_ << MOVETO(_x, _y - 1) << _wCOLOR_FG256(_crgb - 2) << text[i()] << RESETMODE;
		wprint_ << MOVETO(_x, _y - 2) << _wCOLOR_FG256(_crgb - 4) << text[i()] << RESETMODE;
		wprint_ << MOVETO(_x, _y - 3) << _wCOLOR_FG256(_crgb - 6) << text[i()] << RESETMODE;
	}


};


class Elapsed_Time {

	std::chrono::system_clock::time_point _start;
	std::chrono::system_clock::time_point _end;
	std::chrono::duration<float> _duration;

public:

	Elapsed_Time()
		: _start{std::chrono::system_clock::now()}
		, _end{}
		, _duration{}
	{}

	float operator()() {
		_duration =  std::chrono::system_clock::now() - _start;
		_start = std::chrono::system_clock::now();
		return _duration.count();
	}
};