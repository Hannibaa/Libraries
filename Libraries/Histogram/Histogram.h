/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                     ANSI Escape Code VT100 Library                        *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 *                                                                           *
 * URL :                                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/

/*
    From : https://statistics.laerd.com/statistical-guides/understanding-histograms

    What is a histogram?
	   A histogram is a plot that lets you discover, and show, the underlying frequency 
	   distribution(shape) of a set of continuous data. This allows the inspection of 
	   the data for its  underlying distribution(e.g. normal distribution). outliers
	   skewness, etc.
	   we have a data of some thing{title} : 

	   _data[N];

	   bins -> {... range of _data[]: _from, _to };

	   frequency[] -> number of occurence of range bins of data( _from , _to ); 

	   _data[]{11, 15,24,25,25,29,31,34,34,38,44,45,47,43,48,55,56,57,79}
	   Bins have 7, frequency matrix 7; need function to create this data.
	   --------------------------------------------------------------------------------
	   Bin           Frequency               Scores Included in Bin
	   --------------------------------------------------------------------------------
	   00-20			2                          11, 15
	   20-30			4						 24,25,25,29
	   30-40			4						 31,34,34,38
	   40-50			5						44,45,47,43,48
	   50-60			3						   55,56,57
	   60-70			0						     ..
	   70-..			1						     79
	   ---------------------------------------------------------------------------------

	   We create some usefull functions that can manage these data
	   template<typename T>
	   using Bin = std::pair<T,T>;

	   struct Bin { T first, T second}; 
	   vector<Bin> vbins;
	   histo_frequency(Bin
*/

#pragma once

#include <thread>
#include <set>
#include <map>
#include <cmath>
#include "MyProject\Libraries\Libraries\loacal_console_game_lib.h"
#include "MyLib/random_vector.h"
#include "MyLib/container_utility.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    function and data to manage histogram
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
using bin = std::pair<T, T>;

template<typename T>
using vbins = std::vector<bin<T>>;

template<typename T>
using histo_type = std::pair<bin<T>, size_t>;

namespace Histogram {

	// make range equi-distance ; with min and max value
	template<typename T>
	std::vector<bin<T>> histo_make_ranges(const std::vector<T>& _data, size_t n, T min = T{}, T max = T{}) {

		if (n == 0 || n == -1) n = 2;

		std::vector<bin<T>> vbin;

		if (min == max && max == T{})
		{
			min = *std::min_element(_data.begin(), _data.end());
			max = *std::max_element(_data.begin(), _data.end());
		}

		T h = (max - min) / static_cast<T>(n);

		for (size_t k = 0; k != n - 1; ++k) {
			vbin.emplace_back(min + T(h * k), min + T(h * (k + 1ull)));
		}

		vbin.emplace_back(min + T(h * (n - 1)), max);

		return vbin;
	}

	// function take scale line and data and associate this scale to data range
	/*
	* exemple: scale length 30, value 79 - 11)/3 = 22
			0  ...     10         20            30
			|----------|----------|-------------|
			11         33         55            79    (55+22=77 but round it to max value 79)

			create map of (0,11) (10,33) (20,55) (30,79)
			for facilite drawing.
	*/
	template<typename T, typename Int = int>
	std::map<Int, T> histo_make_map(Int length, T v_min, T v_max, Int n_intervals)
	{
		Int h = length / n_intervals;
		T H = (v_max - v_min) / T(n_intervals);

		std::map<Int, T> _map;

		for (Int t = 0; t != n_intervals; ++t) {
			_map[t * h] = v_min + H * T(t);
		}

		_map[length] = v_max;

		return _map;
	}


	template<typename T>
	std::map<int, T>  histo_make_map_range(int length, const std::vector<bin<T>>& _bins)
	{
		int number_section = int(_bins.size()); // number of devided section
		int h = length / number_section;         // each segment have h unit

		std::map<int, T> _map;                   // map to store every position in scale value associated

		for (int k = 0; k != number_section; ++k) {
			_map[k * h] = _bins[k].first;
		}

		_map[length] = _bins[number_section - 1].second;

		return _map;
	}


	// this return frequency for on interval(range,bin), from data 
	template<typename T>
	size_t histo_get_frequency_in_bin(const bin<T>& _bin, const std::vector<T>& _data) {

		size_t count{};

		for (const auto& e : _data) {
			if (e < _bin.first || e > _bin.second) continue;
			++count;
		}

		return count;
	}

	// this return all frequencey according to range(bin) in vector data 
	template<typename T>
	std::vector<histo_type<T>>
		histo_get_frequency(const vbins<T>& _vbins, const std::vector<T>& _data)
	{
		std::vector<histo_type<T>> vhisto;

		for (const auto& r : _vbins) {
			size_t frq = histo_get_frequency_in_bin(r, _data);
			vhisto.emplace_back(r, frq);
		}

		return vhisto;
	}

	std::map<int, size_t> histo_make_map_frequency(int length, size_t freq_max, size_t number_section) {

		int h = length / number_section;         // each segment have h unit

		size_t fh = freq_max / number_section;

		std::map<int, size_t> _map;

		for (int k = 0; k != number_section; ++k) {
			_map[k * h] = fh * size_t(k);
		}

		_map[length] = freq_max;

		return _map;
	}

	template<typename T>
	void histo_print_frequency_table(const std::vector<histo_type<T>>& vhisto_types) {

		wprint_ << WREPEAT(40, L'-') << wend_;
		wprint_ << CELL(20, left, L"interval") << L"|| " << CELL(15, left, L"Frequency") << end_;
		wprint_ << WREPEAT(40, L'-') << wend_;

		for (const auto& data : vhisto_types) {

			std::wstringstream wss;
			wss << data.first.first << wCOLOR(color::Red, L"to") << data.first.second;
			wprint_ << CELL(32, left, wss.str()) << L"|| " << CELL(25, left, data.second) << end_;
		}
		wprint_ << WREPEAT(40, L'-') << wend_;

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Histogram data analysis in console.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	class IHistogram {
	public:
		virtual void draw() = 0;

		virtual ~IHistogram() {}
	};

	template<typename T>
	class DHistogram {
	public:
		Pint                _position;

		static_assert(std::is_arithmetic_v<T>, "Type should be an arithmetic");

		DHistogram(int x, int y)
			:_position{ x,y }
		{}

		virtual ~DHistogram() {}
	};

	template<typename T>
	class Histogram :private DHistogram<T>, public IHistogram {

		std::vector<T>    _data;
		float             v{};
		int               index{}, index_r{};
		wchar_t           title[100]{};
		std::wstring      _histo_title;
		int               _histo_title_y;  // coordinate for histogram title.
		int               _histo_title_x;  // coordinate for histogram title.

		std::chrono::milliseconds    _elapsetime_ms = 100ms;      // timing and speed.

		// Histogram data:

		const int histoX;                   // position of general histogram x
		const int histoY;			        // and y
		int       histo_max_bars;           // max bars numbers.
		int       histo_bar_width;			// element bar width
		const int histo_bar_length;		    // element bar length
		int       histo_length_x;             // histo total length
		int       histo_length_y;
		int       histo_bar_color;		    // general element bars colors
		bool      set_different_color;      // set if we get difirent color for bars
		const int histo_text_color;		    // histogram text color
		std::wstring histo_title_Y;         // text display on Y axis
		std::wstring histo_title_X;         // text display on X axis

		std::vector<ProgressBarH> _bars;    // bar vector.

		// bar to show data : 
		std::wstring bar_text;
		Pint         bar_position;
		int          bar_length;
		int          bar_color;

		// Y Scale data : 
		int number_section_x;    // number 
		int number_section_y;
		size_t freq_max{};

	public:
		Histogram(int x, int y, const std::vector<T>& data,
			int element_bar_width,
			int element_bar_length,
			int histo_color,
			int histo_text_color)
			:DHistogram<T>(x, y)
			, _data{ data }
			, histoX{ x }
			, histoY{ y }
			, histo_bar_width{ element_bar_width }
			, histo_bar_length{ element_bar_length }
			, histo_bar_color{ histo_color }
			, histo_text_color{ histo_text_color }
			, set_different_color{ true }
		{
			histo_max_bars = int(_data.size());
			histo_length_x = histo_max_bars * histo_bar_width;
			histo_length_y = histo_bar_length;

			// set default graduation scale number to 5,5
			set_graduation(5, 5);
		}

		// Title 
		void set_histo_title(const std::wstring& histo_title) {
			_histo_title = histo_title;
			_histo_title_x = histoX + histo_length_x / 2 - int(histo_title.size() / 2);
			_histo_title_y = 1;/*histoY - histo_bar_length - 2;*/
		}

		// set the graduation in scale x and y
		void set_graduation(int scale_x, int scale_y) {
			number_section_x = scale_x;
			number_section_y = scale_y;
		}

		// initialize bar data:
		void init_bar_data(int x, int y, const std::wstring& text, int length, int colour) {
			bar_text = text;
			bar_length = length;
			bar_color = colour;
			bar_position.x = x;
			bar_position.y = y;
		}


		// initialization of bars
		virtual void init_histogram_bars(const std::wstring& titleY, bool desable_text_y = true,
			bool enable_dif_bar_color = true)
		{
			histo_title_Y = titleY;

			set_different_color = enable_dif_bar_color;

			float value_max = *std::max_element(_data.begin(), _data.end());

			for (int i = 0; i != histo_max_bars; ++i) {

				std::wstring tx = std::to_wstring(i) + L"  "; // for coordinate indication X
				tx = tx.substr(0, 2);
				if (desable_text_y) tx = L"";

				float v_percent = 100.f * _data[i] / value_max;  // calculate percent 
				Pint p(histoX + histo_bar_width * i, histoY);    // position of bars of histogram
				// set different color for bar
				if (set_different_color) {
					histo_bar_color = int(v_percent) % 15 + 232;  // we can also put function intensity.
				}

				_bars.emplace_back(p, tx, histo_bar_length, histo_bar_color, histo_text_color);
				_bars[_bars.size() - 1].set_width(histo_bar_width);
				_bars[_bars.size() - 1].set_value(v_percent);
				int col = i % 2 ? 237 : color::Yellow;
				_bars[_bars.size() - 1].setBg_text_color(col);
			}
		}


		// initialization of bars version 2;
		void init_histogram_variable_bars(const std::wstring& titleY)
		{
			histo_title_Y = titleY;

			//text bars ignoring
			std::wstring tx = L"";

			//processing data first:
			auto _vbins = histo_make_ranges(_data, number_section_x);
			auto _bin_freqs = histo_get_frequency(_vbins, _data);
			auto comp_freq = [](const histo_type<T>& h1, const histo_type<T>& h2) ->bool {
				return h1.second < h2.second;
				};

			std::sort(_data.begin(), _data.end());

			// get maximum frequency
			freq_max = std::max_element(_bin_freqs.begin(), _bin_freqs.end(), comp_freq)->second;
			float value_max = float(freq_max);

			// redefine of bar width;
			histo_bar_width = histo_length_x / number_section_x;


			//histo_print_frequency_table(_bin_freqs);
			//wnewline_;


			// making bars for all bins (ranges)
			int k{}; // just counter
			for (auto& d : _bin_freqs) {
				// point for every bar freq.
				Pint p(histoX + histo_bar_width * k, histoY);

				// calculate percent of value 
				float v_percent = 100.f * d.second / value_max;
				//wprint_ << "vpercent : " << v_percent << wend_;
				// 
				// set different color for bar
				if (set_different_color) {
					histo_bar_color = int(v_percent) % 15 + 232;  // we can also put function intensity.
				}

				// initialization of bars
				_bars.emplace_back(p, tx, histo_bar_length, histo_bar_color, histo_text_color);
				size_t last = _bars.size() - 1;

				// initialization of all style
				_bars[last].set_width(histo_bar_width);
				_bars[last].set_value(v_percent);

				++k;
			}
		}

		// this menu thread.
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

				// reading the value of vector 
				if (KeyReleased(VK_UP)) {
					if (!_data.empty()) {
						index_r = index;
						index = std::clamp(++index, 0, (int)_data.size());
						if (index < _data.size() && index >= 0)
							v = _data[index];
					}
				}
				if (KeyReleased(VK_DOWN)) {
					if (!_data.empty()) {
						index_r = index;
						index = std::clamp(--index, 0, (int)_data.size());
						if (index < _data.size() && index >= 0)
							v = _data[index];
					}
				}
			}

		}


		// this main function of drawing 
		virtual void draw() {
			std::thread  thread_(&Histogram<T>::menu, this);

			INIT_WCHAR_TEXT;                                       // initialization of wchar_t text.
			WINIT_CURSOR;                                          // hide the cursor.

			//auto _bins = histo_make_ranges( _data, number_section_y);
			//std::map<int, T> _mapy = histo_make_map_range(histo_length_y,_bins);

			//std::map<int, size_t> 
			//	_mapx = histo_make_map_frequency(histo_length_x, data_size, number_section_x);

			std::map<int, T> _mx = histo_make_map(histo_length_x, *_data.begin(), *(_data.end() - 1)
				, number_section_x);

			std::map<int, size_t> _my = histo_make_map(histo_length_y, size_t(0), freq_max
				, number_section_y);


			ProgressBar<float>  barr(bar_position, bar_text, bar_length, bar_color);
			barr.set_maxmin(0, freq_max);
			barr.set_value(freq_max / 2);

			Pint          p{ histoX, histoY + 2 };
			ScaleX   scalex(p, histo_title_Y, histo_length_x, number_section_x,
				color::White, color::Green, _mx);

			ScaleY   scaley(histoX - 3, histoY, histo_title_Y, histo_bar_length, number_section_y,
				color::Fuchsia, color::Red, _my);
		draw_loop:

			// Draw Histogram :
			for (auto& b : _bars) b.draw();
			// Draw barr indicators

			barr.draw();
			// Draw Scale y and x
			scaley.draw();
			scalex.draw();

			// Main Loop for data:
			while (1) {

				std::this_thread::sleep_for(_elapsetime_ms);
				esc::wclear_line(0, 0);
				// Title of Console 
				swprintf_s(title, L"Histogram v.1 {%s} [%d][%5.2f] |", _histo_title,
					index, v);
				TITLE(title);

				// histogram title //
				put_string_at(_histo_title_x, _histo_title_y, _histo_title, color::Red);

				// triangle indication of value:
				if (index > -1 && index < _bars.size()) {
					barr.set_value(_bars[index].get_value());               // this value is % of bars
					barr.setTitle(bar_text + std::to_wstring(_data[index]));// this real value.
					esc::wclear_line(barr.getPosition().x, barr.getPosition().y);
					barr.draw();
					put_char_at(_bars[index].getPosition().x, _bars[index].getPosition().y, '\x1f', color::Red);
				}
				if (index_r > -1 && index_r < _bars.size())
					put_char_at(_bars[index_r].getPosition().x, _bars[index_r].getPosition().y, '\x1f', color::Black);

				// break Escape
				if (KeyPressed(VK_ESCAPE)) {
					break;
				}
			}

			wprint_ << _wCOLOR_BG256(12) << "Exit ......." << wend_;
			std::wcout << RESETMODE;
			thread_.detach();
		}
	};



	template<typename T>
	class HistogramFrequency : public Histogram<T> {

	public:
		using Histogram<T>::Histogram;

		virtual void init_histogram_bars(const std::wstring& titleY, bool desable_text_y = true,
			bool enable_dif_bar_color = true) override
		{
		}

		virtual void draw() override {
		}
	};

}