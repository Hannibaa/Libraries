#pragma once

#include "scale.h"
#include "Progress_bar.h"

std::wstring to_fwstring(float x, size_t npoint) {
	return std::to_wstring(x).substr(0, std::to_wstring(x).find(L'.') + npoint + 1);
}

namespace cui {

	class Mesured_value {
		cui::VProgressBar   _bar;
		Pint                _pos;

		std::wstring        _title;
		std::wstring        _unite;
		int                 _title_color;

		float              _value;
		float              _max;
		float              _min;
		/* 		VProgressBar(int x, int y, const std::wstring& title, int length, int width,
			float min,float max,
			int color_bar, int _bg_color = 16)
*/
	public:
	    Mesured_value(int x, int y, float min, float max, 
			const std::wstring& title,
			const std::wstring& unite,
		    int length, int width, int color_bar, int _bg_color = 16 )
			:_bar(x,y,L"", length, width, min, max, color_bar, _bg_color)
			,_pos(x,y)
			,_title{title}
			,_unite{unite}
			,_title_color{color::Yellow}
			,_min{min}
			,_max{max}
		{
			_value = (_max + _min) / 2.f;
		}



		void set_value(float value) {
			_value = value;
		}

		void set_color(int color) {
			_title_color = color;
		}

		void draw_graduation(int n) {
			int length = _bar.get_length();
			int width  = _bar.get_width();
			for (int i = 0; i != length; ++i) {
				wprintm_(_pos.x + width + 1, _pos.y - i) << L"\x2500";
				if ( i % n == 0) wprintm_(_pos.x + width+1, _pos.y - i) << L"\x2501\x2501";
			}
		}

		void draw() {
			_bar.set_value(_value);
			_bar.draw();
			draw_graduation(5);
			// todo put strings 
			/*
			         put title, and value of title and unit in this layout :
			              +-----[Flow]
			              |
						  +-[Value]-[Gal/min]
			*/
			wprintm_(_pos.x - 2, _pos.y + 1) << _wCOLOR_FG256(color::Red)
				                         << L"\x250f\x2501"
										 << WMOVETO(_pos.x - 2, _pos.y + 2)
										 << L"\x2516" << RESETMODE;
			
			wprintm_(_pos.x , _pos.y + 1) << _wCOLOR_FG256(color::Red) << L'['
				                          << _wCOLOR_FG256(_title_color) << _title
										  << wCOLOR(color::Red , L']')
				                          ;

			wprintm_(_pos.x - 1, _pos.y + 2) << _wCOLOR_FG256(color::Red) << L"["
				                     << _wCOLOR_FG256(_title_color) << to_fwstring(_value,2)
				                     << _wCOLOR_FG256(color::Red) << L"]\x2501["
									 << _wCOLOR_FG256(_title_color) << _unite
									 << wCOLOR(color::Red, L']');

		}
	};


}