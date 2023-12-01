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

	template<typename T>
	class DProgressBar {
	public:
		// data :
		Pint           _position;  // position of bar
		std::wstring   _title;	  // title of bar
		int            _length;	  // length of progress bar
		int            _color;     // color of progress bar.
		float          l_100;      // percentage from length.

		// associated value that represented ;
		T              v_min;
		T              v_max;
		T              value;

		virtual ~DProgressBar() {}

		DProgressBar(int x, int y, const std::wstring& title, int length, T max, T min,int colour)
			:_position(x, y)
			, _title{ title }
			, _length{ length }
			, _color{ colour }
			, v_min{ min }
			, v_max{ max }
			, value{ min }
			, l_100{}
		{}

		virtual ~DProgressBar() {}
	};



	template<typename T>
	class ProgressBar : private DProgressBar<T>, public IProgressBar {

		int       l;
		size_t    title_size;
		bool      enable_value;    // enable show value

	public:
		ProgressBar() = default;

		ProgressBar(int x, int y, const std::wstring& title, int length,T min, T max,  int colour)
			:DProgressBar<T>(x, y, title, length, min, max, colour)
			, l{}
			, enable_value{ true }
		{
			title_size = _title.size();
		}

		virtual void setTitle(const std::wstring_view title) {
			_title = title;
			title_size = _title.size();
		}

		Pint getPosition() const {
			return _position;
		}

		void set_option(bool _show_value) {
			enable_value = _show_value;
		}


		void set_value(T _value) {
			// set the value 
			value = std::clamp(_value, v_min, v_max);
			// calculate l
			float _l = float(_length) * float(value - v_min) / float(v_max - v_min);
			l = std::round(_l);
			// calculate l_100
			l_100 = std::clamp(100.f * _l / float(_length), 0.f, 100.f);
			//wprint_ << "l100 " << l_100 << wend_;
		}

		T get_value() const {
			return value;
		}

		virtual void draw() override {
			// calculate percent of progression bar
			int l_percent = int(std::round(l_100));


			if (enable_value) {
				int X = _position.x + l;
				X = X < int(_title.size() + 10) ? int(_title.size()) + 10 : X; // this for writing percent 
				wprint_ << MOVETO(X, _position.y)                           // inside colored bar or
					<< std::to_wstring(l_percent);                            // at the end of bar 
			}
			else {
				// printing title and value
				_title += L"   " + std::to_wstring(value);
			}

			wprint_ << MOVETO(_position.x, _position.y)
				    << _title;

			size_t _size = _title.size();

			wprint_ << MOVETO(_position.x, _position.y)
				<< _wCOLOR_BG256(_color);
			if (l > _size)
				wprint_ << _title
				<< REPEAT(l - _size, L' ')
				<< RESETMODE;
			else
				wprint_ << _title.substr(0, l)
				<< RESETMODE;

			_title = _title.substr(0, title_size);
		}
	};


}