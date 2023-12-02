#include <iostream>
#include <thread>
#include <MyLib/Console_Library/Event_Windows.h>
#include "Progress_bar.h"

void _print_ctext(const esc::sCONSOLE_TEXT<wchar_t>& text) {
	wprint_ << WMOVETO(text.x, text.y)
		<< _wCOLOR_BG256(text.bg_color)
		<< _wCOLOR_FG256(text.fg_color)
		<< text.text
		<< RESETMODE;

}


void _print_ctext(const csString& cstring) {


}

int main()
{
	INIT_WCHAR_TEXT;
	WINIT_CURSOR;

	float _max = 80.5f;
	float _min = 25.67f;
	float    v = 57.55f;
	int _length = 70;
	int l = 40;
	std::wstring title{ L" WOB " };

	auto colour = esc::ansi_color<3, 4, 7>();

	wprint_ << L"color " << colour << wend_;

	cui::ProgressBar  p(10, 10, title, 70, _min, _max, color::Red, 234);

	p.set_value(v);
	int k{5};
	// drawing
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		esc::wclear_line(10, 10);

		if (KeyReleased(VK_UP)) {
			++v; ++k;
		}

		if (KeyPressed(VK_DOWN)) {
			--v; --k;
		}

		if (KeyPressed(VK_SPACE)) break;

		p.set_value(v);

		p.display_value();
		p.draw();
	}

	//esc::sCONSOLE_TEXT<wchar_t> text;

	//text.text = L"hello world";
	//text.bg_color = color::DarkBlue;
	//text.fg_color = color::Yellow;
	//text.x = 60; 
	//text.y = 20;
	//
	//_print_ctext(text);

	//wnewline_;
	//// second example:
	//esc::cString<wchar_t> tx{ L" Wonderfule days ...     ] " };
	//tx.set_position(70, 7);
	//tx.set_color(color::Black ,color::Grey93);

	//wprint_ << tx;

	//wprint_ << WMOVETO(tx.get_position().x, tx.get_position().y)
	//	<< _wCOLOR_BG256(tx.get_backGroundColor())
	//	<< _wCOLOR_FG256(tx.get_foreGroundColor())
	//	<< tx
	//	<< RESETMODE;

	std::wcin.get();
	return 0;
}