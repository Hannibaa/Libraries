#pragma once
#include <MyLib/Console_Library/escape_code.h>


namespace cui {

	class IScale {
	public:
		virtual void draw() = 0;
		virtual void set_title(const std::wstring_view title) = 0;

		virtual ~IScale() {}
	};

	class DScale  {
	public:

		// data for every linear scale 
		Pint                 _position;        // position of bar
		const std::wstring   _scale_title;	  // title of bar
		int                  _title_x;       // coordinate of title x
		int                  _title_y;		 // coordinate of title y
		int                  _title_fg_color;
		int                  _title_bg_color;
		int                  _length;	      // length of progress bar
		int                  _color;          // color of scale lines.
		float                l_100;           // percentage from length.
		int                  l;               // is the position of value on scale
		

		// wchar_t glyph variable
		wchar_t _line{};
		wchar_t _line_end{} ;
		wchar_t _line_beg{} ;
		wchar_t _line_tee{} ;

		// wchar_t constante
		static const wchar_t corner_bline = 0x2517;
		static const wchar_t corner_eline = 0x251b;
		static const wchar_t corner_bline1 = 0x2515;
		static const wchar_t corner_eline1 = 0x2519;
		static const wchar_t tline1 = 0x2537;
		static const wchar_t tline = 0x253b;
		static const wchar_t bline = 0x2501;

		//glyph for downside;
		static const wchar_t corner_bline_dn = 0x250d;
		static const wchar_t corner_eline_dn = 0x2511;
		static const wchar_t tline_dn = 0x252f;

		//glyph for horizontal scale
		static const wchar_t hline = 0x2503;
		static const wchar_t hline_up = 0x2512;
		static const wchar_t hline_dn = 0x251a;
		static const wchar_t hline_t = 0x2528;

		//initialization 
		DScale(int x, int y, const std::wstring& title, int length, 
			     int colour, int text_color)
			:_position(x,y)
			,_scale_title{title}
			, _title_x{}
			, _title_y{}
			,_length{length}
			,_color{colour}
			,_title_fg_color{text_color}
			,_title_bg_color{color::Black}
			, l_100{}
			, l{}
		{}

		virtual void set_glyph(wchar_t, wchar_t, wchar_t, wchar_t) = 0;

		virtual ~DScale() {}
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    ScaleX horizontal class 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class ScaleX : private DScale, public IScale {

		std::map<int, T> _map;  // to representing value in scal:
		int _value_color;
		T    value;

	public:
		ScaleX(int x, int y, const std::wstring& title, int length,
			int colour, int text_color, const std::map<int,T>& map)
			:DScale(x, y, title, length, colour, text_color)
			,_map{map}
			, _value_color{color::White}
		{
			_title_x = _position.x + _length / 2 - int(_scale_title.size()) / 2;
			_title_y = _position.y + 2; 

			// condition on map should not empty
			// have at least two values map[0] and map[_length];
			// using assert() for this:
			if (map.empty()) {
				_map[0] = T{};
				_map[_length] = T{};
			}

			// initialization of value at begining
			value = _map[0];
		}

		virtual void set_title(const std::wstring_view title) override {

		}

		virtual void set_glyph(wchar_t line = DScale::bline , 
			                   wchar_t lbeg = DScale::corner_bline_dn,
			                   wchar_t lend = DScale::corner_eline_dn,
			                   wchar_t ltee = DScale::tline_dn) override {
			    _line = line;
			_line_end = lend;
			_line_beg = lbeg;
			_line_tee = ltee;
		}

		void set_value(T _value) {
			value = std::clamp(_value, _map[0], _map[_length]);
			// calculate l
			float _l = float(_length) * float(value - _map[0]) / float(_map[_length] - _map[0]);
			l = std::clamp(int(std::round(_l)), 0, _length);
			// calculate l_100
			l_100 = std::clamp(100.f * _l / float(_length), 0.f, 100.f);
			//wprint_ << "l100 " << l_100 << wend_;
		}

		void display_value(bool display = false, int colour = color::Red) {
			if (l == _length) l = l - 1;

			std::wstring str_value;
			if (display) str_value = L"\x1f" + std::to_wstring(value);
			else str_value = L"\x1f";

			wprint_ << WMOVETO(_position.x + l , _position.y - 1) 
				    << _wCOLOR_FG256(colour)
    				<< str_value
		            << RESETMODE;
		}

		virtual void draw() override {
			// set glyph
			set_glyph();

			// helpfull lambda function return a half of size of stringable object in integer int.
			auto Size = [](const T& value)->int { return int(Fn::_size<wchar_t>(value)) / 2; };

			wprint_ << WMOVETO(_position.x - Size(_map[0]), _position.y + 1)
				    << wCOLOR(_color, _map[0]);

			for (int i = 0; i < _length - 1 ; ++i) {
				wchar_t t = _line;

				if (_map.contains(i)) {
					t = _line_tee;
					wprint_ << WMOVETO(_position.x + i - Size(_map[i]), _position.y + 1)   // showing
						    << wCOLOR(_value_color, _map[i]);
				}

				wprint_ << WMOVETO(_position.x + i, _position.y)
					    << wCOLOR(_color, t);
			}

			wprint_ << WMOVETO(_position.x + _length - 1 - Size(_map[_length]), _position.y + 1)
				    << wCOLOR(_value_color, _map[_length]);

			wprint_ << WMOVETO(_position.x, _position.y) << wCOLOR(_color, _line_beg)
				<< WMOVETO(_position.x + _length - 1, _position.y) << wCOLOR(_color, _line_end)
				<< WMOVETO(_title_x, _title_y) << wCOLOR(_title_fg_color, _scale_title);
		}


	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    ScaleY vertical class
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class ScaleY : private DScale, public IScale {

		std::map<int, T> _map; 
		int              _value_color;
		T                value;

	public:
		ScaleY(int x, int y, const std::wstring& title, int length,
			int colour, int text_color, const std::map<int, T>& map)
			:DScale(x, y, title, length, colour, text_color)
			, _map{ map }
			, _value_color{ color::White }
		{
			_title_y = _position.y - _length / 2 - int(_scale_title.size()) / 2;
			_title_x = _position.x - 3;
			// condition on map should not empty
			// have at least two values map[0] and map[_length];
			// using assert() for this:
			if (map.empty()) {
				_map[0] = T{};
				_map[_length] = T{};
			}

			// initialization of value at begining
			value = _map[0];

			// set glyph
			set_glyph();
		}

		virtual void set_title(const std::wstring_view title) override {

		}

		virtual void set_glyph(wchar_t line = DScale::hline,
			wchar_t lbeg = DScale::hline_dn,
			wchar_t lend = DScale::hline_up,
			wchar_t ltee = DScale::hline_t) override {
			_line = line;
			_line_end = lend;
			_line_beg = lbeg;
			_line_tee = ltee;
		}

		void set_value(T _value) {
			value = std::clamp(_value, _map[0], _map[_length]);
			// calculate l
			float _l = float(_length) * float(value - _map[0]) / float(_map[_length] - _map[0]);
			l = std::clamp(int(std::round(_l)), 0, _length);
			// calculate l_100
			l_100 = std::clamp(100.f * _l / float(_length), 0.f, 100.f);
			//wprint_ << "l100 " << l_100 << wend_;
		}

		void display_value(int colour = color::Red) {

			wprint_ << WMOVETO(_position.x - 1, _position.y - l)
				<< _wCOLOR_FG256(colour)
				<< L'\x10'
				<< RESETMODE;
		}

		virtual void draw() override {
			// lambda function helpfully.
			auto Size = [](const T& value)->int { return int(Fn::_size<wchar_t>(value)); };

			wprint_ << WMOVETO(_position.x - 1 - Size(_map[0]), _position.y) // values
				<< wCOLOR(_color, _map[0]);

			for (int i = 0; i < _length - 1; ++i) {
				wchar_t t = _line;

				if (_map.contains(i)) {
					t = _line_tee;
					wprint_ << WMOVETO(_position.x - 1 - Size(_map[i]), _position.y - i) // values
						<< wCOLOR(_value_color, _map[i]);
				}

				wprint_ << WMOVETO(_position.x, _position.y - i)
					<< wCOLOR(_color, t);
			}
			wprint_ << WMOVETO(_position.x - 1 - Size(_map[_length]), _position.y - _length + 1) // values
				<< wCOLOR(_value_color, _map[_length]);

			wprint_ << WMOVETO(_position.x, _position.y) << wCOLOR(_color, _line_beg)
				<< WMOVETO(_position.x, _position.y - _length + 1) << wCOLOR(_color, _line_end);

			
			esc::put_string_horizontal_up_at(_title_x , _title_y, _scale_title, _title_fg_color);
		}

		void adjust_title(int offset) {
			_title_x = _title_x - offset;
		}
	};
}