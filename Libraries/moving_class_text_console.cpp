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

	std::wstring update() {
		std::wstringstream str;
		int _x = x; int _y = y;
		str << MOVETO(_x, _y) << _wCOLOR_FG256(_color) << text << RESETMODE;
		return str.str();
	}

	 operator std::wstring () noexcept {
		return update();
	}
};





int main()
{
	SETMODE_WTTEXT;

	// wprint_ << SET_MAX_LENGTH(120) << SET_MAX_LINES(35);
	// wprint_ << DOUBLE_HBHalf;
	// wprint_ << LED(4);

	std::vector<Text> vtext;
	RNG::RG<float> speed(1.0f, 2.2f);
	RNG::RG<float> value(10.f, 30.f);
	RNG::RG<int>  icolor(0, 12);

	bool no_text = true;

	Text text(0.f, 120.f, 1.9f, 0.f, 25.f, 1.9f, 6);
	text.setText(L"Kadda");
	
	wchar_t title[100]{};

	while (1) {
		int _color = 13;

		esc::wcls();
		swprintf_s(title, L"  Game Moving Text number [%4d]| distance []", vtext.size());
		put_string_at(30, 0, title , color::Red);


		if ( KeyPressed(unsigned('A')) ) {
			std::wstring text1;
			wprint_ << MOVETO(0, 0) << "add a text : ";
			std::wcin >> text1;


			Text t{ 0.f, 120.f,(float)speed(), 0.f, 30.f, (float)speed(), icolor()};
			vtext.push_back(t);
			vtext.at(vtext.size() - 1).setText(text1);
			vtext.at(vtext.size() - 1).setStarValue(value(), value());
			wwait_; no_text = false;
		}

		for (auto& txt : vtext) 
		      wprint_ << txt.update();

		if (KeyPressed(VK_ESCAPE)) break;

		if (KeyPressed(VK_SPACE)) {
			put_string_at(0, 2, L"Press 'A' to see some effect KeyOn() function");
			put_string_at(0, 3, L"Press  up_arrow to raise occurence ");
			put_string_at(0, 4, L"Press  down_arrow to decrease occurence");
			put_string_at(0, 5, L"Press  entry to continue...");
			wwait_;
		}

		// strategy of Game

		std::this_thread::sleep_for(300ms);
	}

	std::wcout << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	std::wcout << RESETMODE;

	SETMODE_TEXT;
	std::cin.get();
	return 0;
}