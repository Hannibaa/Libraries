/**********************************************************************************
 *
 * Copyright (c) 2022-2023 KADDA Aoues
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **********************************************************************************/

 /*
  *****************************************************************************
  *                                                                           *
  *                          Platform Independent                             *
  *                     Progress Console Bars Library                         *
  *                                                                           *
  * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
  * Date  : 11 / 28 / 2023                                                    *
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


#pragma once
#include <algorithm>
#include <cmath>
#include <MyLib/Console_Library/escape_code.h>

// using also namespace cui = User_Interface;
namespace cui {

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    PROGRESS BAR Interface and Data Interface
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Abstract Interface 
	class IProgressBar {
	public:
		virtual void draw() = 0;
		virtual void clean(int) const = 0;
		virtual void set_title(const std::wstring_view title) = 0;

		virtual ~IProgressBar() {}
	};

	// Data interface ;
	class DProgressBar {
	public:
		// data :
		Pint                 _position;  // position of bar
		const std::wstring   bar_title;	  // title of bar
		int                  _length;	  // length of progress bar
		int                  _width;     // width of progress bar
		int                  _color;     // color of progress bar.
		int                  bg_color;   // bar background color show total 100% bar.
		float                l_100;      // percentage from length.
		int                  l;          // indicator of active position bar length

		// associated value that represented ;
		float              v_min;        // value minimum 
		float              v_max;		 // value maximum
		float              value;		 // value memorized

		virtual ~DProgressBar() {}

		DProgressBar(int x, int y, const std::wstring& title, int length
			, float min, float max, int colour, int _bg_color = 238)
			:_position(x, y)
			, bar_title{ title }
			, _length{ length }
			, bg_color{_bg_color}
			, _color{colour}
			, v_min{ min }
			, v_max{ max }
			, value{ min }
			, l_100{}
			, l{}
		{}

	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Horizontal Progress Bar ;
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ProgressBar : private DProgressBar, public IProgressBar {

		size_t                title_size;
		bool                  enable_value;    // enable show value
		std::wstring          _title;       // this one is constante

	public:
		ProgressBar() = default;

		ProgressBar(int x, int y, const std::wstring& title,
			        int length,float min, float max,  int colour, int bg_color)
			:DProgressBar(x, y, title, length, min, max, colour, bg_color)
			, enable_value{ true }
		{
			_title = bar_title;
			title_size = _title.size();
		}


		virtual void set_title(const std::wstring_view title) override {
			_title = title;
			title_size = _title.size();
		}

		void display_value( const std::wstring& superator = L"|") {
			_title = bar_title + superator +
				std::to_wstring(value).substr(0, 3 + std::to_wstring(value).find(L'.')) + L" ";
		}

		Pint getPosition() const {
			return _position;
		}

		void set_option(bool _show_value) {
			enable_value = _show_value;
		}


		void set_value(float _value) {
			// set the value 
			value = std::clamp(_value, v_min, v_max);
			// calculate l
			float _l = float(_length) * float(value - v_min) / float(v_max - v_min);
			l = std::clamp(int( std::round(_l) ), 0, _length) ;
			// calculate l_100
			l_100 = std::clamp(100.f * _l / float(_length), 0.f, 100.f);
			//wprint_ << "l100 " << l_100 << wend_;
		}

		float get_value() const {
			return value;
		}

		virtual void draw() override {
			std::wstring l_str = std::to_wstring(int(std::round(l_100)));
			std::wstring strbar = _title + std::wstring( _length - _title.size() , L' ');

			if (l > _title.size() + 3) {
				if (l < _length - 1)
					strbar.insert(l, l_str);
			}
			else
				strbar.insert(_title.size() + 4, l_str);
		
			strbar = strbar.substr(0, _length);

			wprint_ << MOVETO(_position.x, _position.y)
				<< _wCOLOR_BG256(_color) << strbar.substr(0, l)
				<< _wCOLOR_BG256(bg_color)
				<< strbar.substr(l)
				<< RESETMODE;
			
			if ( l > _length - 2)
				wprint_ << l_str;

			_title = _title.substr(0, title_size);
		}

		virtual void clean(int _col) const override {
			wprint_ << MOVETO(_position.x, _position.y)
				    << _wCOLOR_BG256(_col)
				    << WREPEAT(_length, L' ')
				    << RESETMODE;
		}
	};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    Vertical Progress Bar ;
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	class VProgressBar : private DProgressBar, public IProgressBar {

		int            _text_color;
		int            _text_bg_color;
		Pint           _delta_tx;
		std::wstring   _title;
		// TODO   set max_length_bar as static or as template pas to static constexpr.

	public:
		VProgressBar() = default;

		VProgressBar(int x, int y, const std::wstring& title, int length, int width,
			float min,float max,
			int color_bar, int _bg_color = 16)
			: DProgressBar(x , y, title, length , min, max, color_bar, _bg_color)
			, _text_color{ color::White }
			, _text_bg_color{color::Grey19}
			, _delta_tx{}
		{
			_width = width;
			_title = bar_title;
			// check if length of bar and screen with coordinate fit 
			if (_length > _position.y - 2) _length = _position.y - 1;
		}

		virtual void set_title(const std::wstring_view title) override {
			_title = title;
		}

		void set_width(int width) {
			_width = width;
		}

		// the value here is percentage
		void set_value(float _value) {
			// set the value 
			value = std::clamp(_value, v_min, v_max);
			// calculate l
			float _l = float(_length) * float(value - v_min) / float(v_max - v_min);
			l = std::clamp(int(std::round(_l)), 0, _length);
			// calculate l_100
			l_100 = std::clamp(100.f * _l / float(_length), 0.f, 100.f);
			//wprint_ << "l100 " << l_100 << wend_;
		}

		float get_value() const {
			return value;
		}

		void display_value() {
			std::wstring value_str = std::to_wstring(value).substr(0, 3 + std::to_wstring(value).find(L'.'));
			int x_shifting = std::abs(_width - int(value_str.size())) / 2;
			wprint_ << WMOVETO(_position.x - x_shifting, _position.y - l)
				    << _wCOLOR_FG256(_color)
				    << value_str
				    << RESETMODE;
		}

		void adjust_title(int x0 = 0, int y0 = 0, bool enable_adjustement = true) {
			if (enable_adjustement)
				_delta_tx.x = std::abs(_width - int(_title.size())) / 2 + x0;
			else
				_delta_tx.x = x0;

			_delta_tx.y = y0;
		}

		virtual void draw() override {
			wprint_ << WMOVETO(_position.x - _delta_tx.x, _position.y + 1 + _delta_tx.y)
				<< WTEXT_COLOR(_text_color, _text_bg_color, _title);

			for (int i = 0; i < l; ++i) {
				wprint_ << WMOVETO(_position.x, _position.y - i)
					<< _wCOLOR_BG256(_color)
					<< std::wstring(_width, L' ')
					<< RESETMODE;

			}
		}

		virtual void clean(int _col = 0) const override {
			for(int i = 0; i != _length ;++i)
				wprint_ << WMOVETO(_position.x , _position.y - i)
				        << _wCOLOR_BG256(_col) 
				        << std::wstring(_width, L' ')
				        << RESETMODE;
		}

		void set_text_color(int bg, int fg = color::White) {
			_text_bg_color = bg;
			_text_color = fg;
		}

		Pint getPosition() const {
			return _position;
		}

		Pint getEndBarPosition() const {
			return Pint{ _position.x, _position.y - l };
		}
	};


}

