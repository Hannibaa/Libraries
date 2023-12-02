#include <iostream>
#include <string_view>
#include <thread>
#include <algorithm>
#include "Histogram.h"



float v{};
int   index{}, index_r{};
//std::vector<float> values = vu::makeRandomVector<float>(10.f, 200.f, 50);// deprecated
auto values = vu::makeRandomContainer<std::vector>(10.f, 200.f, 50);
wchar_t title[100]{};                                  // title console.

void menu() {
	
	while (1) {

		// Menu of console
		if (KeyPressed(VK_SPACE)) {
			esc::put_string_at(0, 2, L"Press up to add element falling");
			esc::put_string_at(0, 3, L"Press down to remove element");
			esc::put_string_at(0, 4, L"Press A to change game parameter");
			esc::put_string_at(0, 5, L"Press left  N\\A");
			wwait_;

		}

		// break
		if (KeyPressed(VK_ESCAPE)) {
			break;
		}

		// reading the value of vector 
		if (KeyReleased(VK_UP)) {
			if (!values.empty()) {
				index_r = index;
				index = std::clamp(++index,0,(int)values.size());
				if (index < values.size() && index >=0 )
				v = values[index];
			}
		}
		if (KeyReleased(VK_DOWN)) {
			if (!values.empty()) {
				index_r = index;
				index = std::clamp(--index,0,(int)values.size());
				if (index < values.size() && index >= 0)
				v = values[index];
			}
		}
	}
}

int main()
{

	std::thread   thread_(menu);
	INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
	WINIT_CURSOR;                                          // hide the cursor.
	std::chrono::milliseconds game_elapsetime_ms = 70ms;   // timing and speed.
	
	// bar to show the value 
	std::wstring bar_text;
	Pint         bar_position{ 2,2 };
	const int    bar_length{ 50 };
	int          bar_color{ color::Fuchsia };

	// set the constante of histogram:
	const int histoX{25};                               //
	const int histoY{28};							   //
	const int histo_bar_width{ 2 };					   //
	const int histo_bar_length{ 25 };				   //
    int       histo_bar_color{ 10 };				   //
    bool      set_dif{ true };                       // set if we get difirent color for bars
	const int histo_text_color{ 1 };				   //
	const int histo_max_bars{ 50 };					   //
	const std::wstring histo_title_X{ L"exemple 1" };   //
	const std::wstring histo_title_Y{ L"Frequency 1" }; // text
	const int histo_title_Xx{histoX + (histo_max_bars * histo_bar_width / 2) 
		                 - (int(histo_title_X.size()) / 2) };
	const int histo_title_Xy{histoY + 4 };

	const int histo_title_Yy{ histoY - (histo_bar_length / 2) + int(histo_title_Y.size()) };
	const int histo_title_Yx{ histoX - 5 };


	// START CONSTRUCTION OF Histrogram 
	std::vector<ProgressBarH> bars;
	float value_max = *std::max_element(values.begin(),values.end());

	for (int i = 0; i != histo_max_bars; ++i) {

		std::wstring tx = std::to_wstring(i)+ L"  "; // for coordinate indication X
		tx = tx.substr(0, 2);
		float v_percent = 100.f * values[i] / value_max; // calculate percent 
		Pint p(histoX + histo_bar_width * i, histoY);    // position of bars of histogram
		// set different color for bar
		if (set_dif) {
			histo_bar_color = int(v_percent) % 15 + 232;  // we can also put function intensity.
		}

		bars.emplace_back(p, L"", histo_bar_length, histo_bar_color, histo_text_color);
		bars[bars.size() - 1].set_width(histo_bar_width);
		bars[bars.size() - 1].set_value(v_percent);
		int col = i % 2 ? 237 : color::Yellow;
		bars[bars.size() - 1].setBackground_color(col);
	}


	//  ProgressBarH(const Pint& position, const std::wstring& title,
	//  int length, int color_bar, int color_text = 15)
	ProgressBar  barr( bar_position, bar_text, bar_length, bar_color);
	barr.set_value(99);

	Pint p{ histoX, histoY + 2 };
	ScaleX<int>   scaley(p, L"exemples ...", histo_max_bars * histo_bar_width, 5, 
		color::White, color::Green);

draw_loop:

	// Y axe title
	// put_string_horizontal_at(histo_title_Yx, histo_title_Yy, L"Example X 1", color::Fuchsia);
	// X axe title
	//put_string_at(histo_title_Xx, histo_title_Xy, L"Example Y 1", color::Red);

	// Draw Histogram :
	for (auto& b : bars) b.draw();
	// Draw barr indicators
	barr.draw();
	// Draw Scale y
	scaley.draw();

	while (1) {

		std::this_thread::sleep_for(100ms);
		esc::wclear_line(0, 0);
		// Title of Console 
		swprintf_s(title, L"Histogram v.1 vector[%d][%5.2f] |",
			index, v);
		put_string_at(30, 0, title, color::Red);
		TITLE(title);		



		// triangle indication of value:
		if (index > -1 && index < bars.size()) {
			barr.set_value(bars[index].get_value());
			barr.setTitle(std::to_wstring(values[index]));
			esc::wclear_line(barr.getPosition().x,barr.getPosition().y);
			barr.draw();
			put_char_at(bars[index].getPosition().x, bars[index].getPosition().y, '\x1f', color::Red);
		}
		if (index_r > -1 && index_r < bars.size())
		put_char_at(bars[index_r].getPosition().x, bars[index_r].getPosition().y, '\x1f', color::Black);

		// break Escape
		if (KeyPressed(VK_ESCAPE)) {
			break;
		}
	}



	//wprint_ << _wCOLOR_BG256(12) << "Exit Game..." << wend_;
	//std::wcout << RESETMODE;
	thread_.join();
	std::cin.get();
	return 0;
}