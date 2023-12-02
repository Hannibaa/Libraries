#include <iostream>
#include "Histogram/Progress_bar.h"

void _print_ctext(const esc::sCONSOLE_TEXT<wchar_t>& text) {
	wprint_ << WMOVETO(text.x, text.y)
		<< _wCOLOR_BG256(text.bg_color)
		<< _wCOLOR_FG256(text.fg_color)
		<< text.text
		<< RESETMODE;

}

int main()
{
	INIT_WCHAR_TEXT;
	WINIT_CURSOR;

	float _max = 80.5f;
	float _min = 25.67f;

	ProgressBar<float>  p(10 ,10, L"Hello", 25, _min, _max, color::Red);

	p.set_value(57.55f);
	p.setTitle(L"Hello" + std::to_wstring(57.55f));

	p.draw();

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