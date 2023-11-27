#include <iostream>
#include <string_view>
#include <thread>
#include <algorithm>
#include "loacal_console_game_lib.h"
#include "MyLib/random_vector.h"


void put_string_horizontal_at(int x, int y, const std::wstring& str, int color) {
	
	wprint_ << SAVECURSORPOSITION;
	for (int k = 0; k != str.size(); ++k) {
		wprint_ << MOVETO(x,y - k)
			    << wCOLOR(color, str[k]);
	}
	wprint_ << RESTORCUR_SAVED_POS;
}

int main()
{

	INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
	WINIT_CURSOR;                                          // hide the cursor.
	std::chrono::milliseconds game_elapsetime_ms = 70ms;   // timing and speed.
	wchar_t title[100]{};                                  // title console.
	

	
	// Title of Console 
	swprintf_s(title, L"  Game Moving Frame per sec [%5.3f] |Time[%d]|PosX[%3d]|PosY[%3d] | Collision Times[%5d]",
		  1.f, 1, 1, 1, 1);
	put_string_at(30, 0, title, color::Red);
	TITLE(title);

	// set the constante of histogram:
	const int histoX{13};                               //
	const int histoY{30};							   //
	const int histo_bar_width{ 2 };					   //
	const int histo_bar_length{ 25 };				   //
	const int histo_bar_color{ 10 };				   //
	const int histo_text_color{ 1 };				   //
	const int histo_max_bars{ 50 };					   //
	const std::wstring histo_title_X{ L"exemple 1" };   //
	const std::wstring histo_title_Y{ L"Frequency 1" }; // text
	const int histo_title_Xx{histoX + (histo_max_bars * histo_bar_width / 2) 
		                 - (int(histo_title_X.size()) / 2) };
	const int histo_title_Xy{histoY + 2 };

	const int histo_title_Yy{ histoY - (histo_bar_length / 2) + int(histo_title_Y.size()) };
	const int histo_title_Yx{ histoX - 4 };

	std::vector<ProgressBarH> bars;
	std::vector<float> values = vu::makeRandomVector<float>(10.f, 200.f, histo_max_bars);
	float value_max = *std::max_element(values.begin(),values.end());

	for (int i = 0; i != histo_max_bars; ++i) {

		std::wstring tx = std::to_wstring(i);
		tx = tx.substr(0, 2);
		Pint p(histoX + histo_bar_width * i, histoY);
		bars.emplace_back(p, tx, histo_bar_length,	histo_bar_color, histo_text_color);
		bars[bars.size() - 1].set_width(histo_bar_width);
		float v_percent = 100.f * values[i] / value_max;
		bars[bars.size() - 1].set_value(v_percent);
	}


	//  ProgressBarH(const Pint& position, const std::wstring& title,
	//  int length, int color_bar, int color_text = 15)
	ProgressBar  barr({ 2,2 }, L"hello", 50, color::Red);
	barr.set_value(99);
draw_loop:
	put_string_horizontal_at(histo_title_Yx, histo_title_Yy, L"Example X 1", color::Fuchsia);

	put_string_at(histo_title_Xx, histo_title_Xy, L"Example Y 1", color::Red);

	for (auto& b : bars) b.draw();
	barr.draw();


	// Menu of console
	if (KeyPressed(VK_SPACE)) {
		put_string_at(0, 2, L"Press up to add element falling");
		put_string_at(0, 3, L"Press down to remove element");
		put_string_at(0, 4, L"Press A to change game parameter");
		put_string_at(0, 5, L"Press left  N\\A");
		wwait_;
		goto draw_loop;
	}




	//wprint_ << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	//std::wcout << RESETMODE;

	std::cin.get();
	return 0;
}