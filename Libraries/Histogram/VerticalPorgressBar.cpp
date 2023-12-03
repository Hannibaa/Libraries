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
	int _length = 25;
	int _width = 4;
	int l = 40;
	std::wstring title{ L"TDS Torq" };



	cui::VProgressBar  p(10, 30, title, _length, _width, _min, _max, color::Green);

	// to remove text 
	p.set_title(L"");

	//p.adjust_title(0, 1,false);
	// drawing
	while (true) {
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		

		if (KeyReleased(VK_UP)) {
			++v; 
			esc::wcls();
		}

		if (KeyOn(VK_DOWN)) {
			--v; 
			esc::wcls();
		}

		if (KeyPressed(VK_ESCAPE)) break;

		p.set_value(v);

		//p.display_value();
		p.draw();
	}


	std::wcin.get();
	return 0;
}