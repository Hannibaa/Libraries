#include <iostream>
#include <thread>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/random_generator.h"

using namespace std::chrono_literals;

void _hline(int n) {
	for(int i = 0 ; i != n; ++i)
	wprint_ << Unicode::hLine;
}

void put_char_at(int x, int y, wchar_t w, color _color = color::White) {
	wprint_ << MOVETO(x, y);
	//wprint_ << w;
	WPrint_(_color, w);
}

void put_string_at(int x, int y, const std::wstring& wstr, color _color = color::White) {
	wprint_ << MOVETO(x, y);
	//wprint_ << wstr;
	WPrint_(_color, wstr);

}

int main()
{
	SETMODE_WTTEXT;
	RNG::RG<int> x(1, 100);
	RNG::RG<int> y(1, 25), clr(0,16);
	int dist_min = 100;
	int count{};
	int count_colusion{};
	int fr{ 1 };
	ESC::winit_cursor;
	while (1) {

		++count;
		if (count % fr == 0) {
			wcls();
			count = 0;
		}
		int _x = x(), _y = y();
		int _X = x(), _Y = y();
		int d = (_x - _X) * (_x - _X) + (_y - _Y) * (_y - _Y); 

		put_string_at(30, 0, L"number of colusion " + std::to_wstring(count_colusion) + 
			L"        " + std::to_wstring(_X) + L"|" + std::to_wstring(_Y) +
			L"        " + std::to_wstring(_x) + L"|" + std::to_wstring(_y) +
			L"        |" + std::to_wstring(d) +L"| press space to see menu"
			, color::Red);


		std::wstring wstr = L"(" + std::to_wstring(_X) + L"|" + std::to_wstring(_Y) + L")" ;
		put_string_at(_X, _Y, wstr , static_cast<color>(clr()));

	       put_char_at(_x, _y, Unicode::uprc, static_cast<color>(fr));
		   wprint_ << _x << L"|" << _y;
		   wprint_ << L"|KADDA|" << fr;
		   if (KeyPressed(VK_ESCAPE)) break;

		   if (KeyOn((unsigned)'A')) put_char_at(30, 30, Unicode::vLine);
		   if (KeyPressed((unsigned)'A')) put_char_at(30, 30, Unicode::vLine);
		   if (KeyReleased((unsigned)'A')) put_char_at(30, 30, Unicode::vLine);

		   if (KeyPressed(VK_SPACE)) {
			   put_string_at(0, 2, L"Press 'A' to see some effect KeyOn() function");
			   put_string_at(0, 3, L"Press  up_arrow to raise occurence ");
			   put_string_at(0, 4, L"Press  down_arrow to decrease occurence");
			   put_string_at(0, 5, L"Press  entry to continue...");
			   wwait_;
		   }

		   if (KeyPressed(VK_UP)) {
			   ++fr;
		   }
		   if (KeyPressed(VK_DOWN)) {
			   fr > 2 ? --fr : fr;
		   }

		   // strategy of Game

		   if (d < dist_min) {
			   wwait_;
			   wclear_line();
			   ++count_colusion;
		   }

		   std::this_thread::sleep_for(500ms);
	}

	std::wcout << _wCOLOR_BG256(12) << "hello world" << end_;
	std::wcout << RESETMODE;

	SETMODE_TEXT;
	std::cin.get();
	return 0;
}