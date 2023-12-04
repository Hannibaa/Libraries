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
#include <cstdlib>
#include "MyLib/random_vector.h"
#include "MyLib/container_utility.h"
#include "Progress_bar.h"
#include "scale.h"



namespace Histogram {

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


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Histogram of bars 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class Histogram_bar {

		// general histo info :
		std::vector<T>   _data;
		T                _max;
		T                _min;
		std::wstring _title ;
		Pint         _title_pos;
		int          _title_color;

		std::wstring _titleX ;
		std::wstring _titleY ;

		Pint         _pos;
		
		int          _length ;
		int          _width ;
		bool         _enable_label;
		bool         _enable_multicolor;
	
		// general bars info :
		int           bar_width;
		std::vector<cui::VProgressBar> vbars;

		// Scale x and y;
		std::map<int, T>          _map_data;
		std::map<int, size_t>     _map_freq;

		// thread parameter
		bool          bthread_executed;
		int           index{};
		int           index_r{};


	public:
		Histogram_bar(int x, int y, const std::vector<T>& data,
			int length, int width, const std::wstring& title, int title_color)
			:_pos(x, y)
			, _data(data)
			, _length{ length }
			, _width{ width }
			, _title{ title }
			, _title_color{ title_color }
			, _enable_label{false}
			, _enable_multicolor{true}
			,  bthread_executed{true}
			, _map_data{}
			, _map_freq{}
		{
			// get max and min
			if (_data.empty()) {
				Print_(color::Red, "data Error....");
				abort();
			}
            // min and max of data
			_min = *std::min_element(_data.begin(), _data.end());
			_max = *std::max_element(_data.begin(), _data.end());
			// calculate width of bars and total width
			bar_width = _width / int(_data.size());
			if (bar_width < 2) {
				//Print_(color::Red, "bar_width is minimum") << end_;
				bar_width = 1;
				_width = bar_width * _data.size();
			}
		}

		// no need to set_title title of axis
		void set_title_Xaxis(const std::wstring_view titleX) {
			_titleX = titleX;
		}
		void set_title_Yaxis(const std::wstring_view titleY) {
			_titleY = titleY;
		}
		// set bar width equivalent to set length
		void set_bar_width(int _bar_width) {
			bar_width = _bar_width;
			_width = bar_width * int(_data.size());
		}

		// we need some time to set minmax manually
		void set_minmax(T min, T max) {
			_min = min;
			_max = max;
		}

		void enable_label() {
			_enable_label = !_enable_label;
		}

		// Initialization of all bars according to data/
		void init_bars() {
			int k{};

			// put data in Y axis
			_map_data[0] = T{};
			_map_data[_length] = _max;

			// put freq in X axis
			_map_freq[0] = 0;
			_map_freq[_width] = _data.size();

			auto intensity = [=](T value, int c, int c0)->float {
				return float(c0) + (float(c) *( (value - _min) / (_max - _min)));
				};

			for (const auto& v : _data) {
				// take label for x axis 
				std::wstring tx = std::to_wstring(k+1) + std::wstring(bar_width,L' ');
				tx = tx.substr(0, bar_width);

				if (!_enable_label) tx = L"";

				int color_ = color::Green;
				
				// todo set color du to intensity of data value.
				// as lambda intensity(T value,min,max, int[range]) -> int {}
				if (_enable_multicolor) {
					//color_ = k % 15 + 235;
					color_ = intensity(v, 15, 235);
				}


				vbars.emplace_back(_pos.x + bar_width * k, _pos.y, tx, _length, 
					bar_width, float(_min), float(_max), color_);

				vbars[vbars.size() - 1].set_value(float(v));
				// alternate coordinate color in x axis 
				int bg_color = k % 2 ? color::Green : color::Red;
				vbars[vbars.size() - 1].set_text_color(bg_color);

				++k;
			}

		}

		void set_value(int _number_bar, T v) {
			if (_number_bar < vbars.size()) {
				vbars[_number_bar].set_value(float(v));
				vbars[_number_bar].clean();
				vbars[_number_bar].draw();
			}
		}

		void draw_bars() {

			for (auto& b : vbars) {
				b.draw();
			}
		}

		void thread_show_value() {

			while (true) {

				if (KeyReleased(VK_UP)) {
					index_r = index;
					++index;
				}

				if (KeyReleased(VK_DOWN)) {
					index_r = index;
					--index;
				}
				// break:
				if (KeyPressed(VK_ESCAPE)) {
					bthread_executed = false;
					break;
				}
			}

		}

		void draw() {
			draw_bars();

			std::thread thread_(&Histogram_bar<T>::thread_show_value, this);

			// position of main title
			_title_pos.x = _pos.x + _width / 2 - int(_title.size()) / 2;
			_title_pos.y = _pos.y - _length - 1;

			esc::put_string_at(_title_pos.x, _title_pos.y, _title, _title_color);


			cui::ScaleX X(_pos.x, _pos.y + 2, _titleX, _width, color::Red, color::Green, _map_freq);
			cui::ScaleY Y(_pos.x - 3, _pos.y, _titleY, _length, color::Blue, color::Fuchsia, _map_data);

			X.draw();
			Y.draw();

			while (bthread_executed) {
				// put arraw
				index = std::clamp(index, 0, int(_data.size()) - 1);

				esc::put_char_at(vbars[index].getEndBarPosition().x, 
					vbars[index].getEndBarPosition().y, '\x1f', color::Red);
				esc::put_char_at(vbars[index_r].getEndBarPosition().x, 
					vbars[index_r].getEndBarPosition().y, '\x1f', color::Black);

			}

			thread_.detach();
		}

	};
}