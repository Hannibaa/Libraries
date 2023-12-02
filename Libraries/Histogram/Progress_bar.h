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
#include <MyLib/Console_Library/escape_code.h>

// using also namespace cui = User_Interface;
namespace User_Interface {

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    PROGRESS BAR 
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Abstract Interface 
	class IProgressBar {
	public:
		virtual void draw() = 0;
		virtual void set_title(const std::wstring_view title) = 0;

		virtual ~IProgressBar() {}
	};

	class DProgressBar {
	public:
		// data :
		Pint                 _position;  // position of bar
		const std::wstring   bar_title;	  // title of bar
		int                  _length;	  // length of progress bar
		int                  _color;     // color of progress bar.
		int                  bg_color;   // bar background color show total 100% bar.
		float                l_100;      // percentage from length.

		// associated value that represented ;
		float              v_min;
		float              v_max;
		float              value;

		virtual ~DProgressBar() {}

		DProgressBar(int x, int y, const std::wstring& title, int length
			, float min, float max, int colour, int _bg_color = 238)
			:_position(x, y)
			, bar_title{ title }
			, _length{ length }
			, _color{ colour }
			, bg_color{_bg_color}
			, v_min{ min }
			, v_max{ max }
			, value{ min }
			, l_100{}
		{}

	};



	class ProgressBar : private DProgressBar, public IProgressBar {

		int                   l;
		size_t                title_size;
		bool                  enable_value;    // enable show value
		std::wstring          _title;       // this one is constante

	public:
		ProgressBar() = default;

		ProgressBar(int x, int y, const std::wstring& title,
			        int length,float min, float max,  int colour, int bg_color)
			:DProgressBar(x, y, title, length, min, max, colour, bg_color)
			, l{} 
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
	};


}

namespace cui = User_Interface;