#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <MyLib/Console_Library/escape_code.h>

using vecwString = std::vector<std::wstring>;
using vecString = std::vector<std::string>;

namespace cui {

	class Scrolling_list {

		vecString                    _list;  // list of string no more than width character
		std::queue<std::string> q;

		int _x;
		int _y;
		unsigned short inc;

		int _length;
		int _width;

		std::chrono::milliseconds _elapsed_time;

		// Glyph drawing box
		const char line =    '\xc4';
		const char bar =     '\xb3';
		const char shap_L =  '\xc0';
		const char shap_7 =  '\xbf';
		const char shap_J=   '\xd9';
		const char shap_F=   '\xda';

		// controle key
		int _key_up ;
		int _key_down ;
		int _key_left ;
		int _key_right ;
		bool _is_defined{ false };

	public:


		Scrolling_list(int x, int y, int width, int length)
			: _x{ x }
			, _y{ y }
			, inc{}
			, _width{ width }
			, _length{ length }
			, _elapsed_time{100}
		{}

		void update() {
			int list_size = _list.size();
			int sz = std::min<int>(_length, list_size);

			esc::cls(_x+1, _y+1, _width, _length);

			print_ << MOVETO(_x + 1, _y) << '[' << _list.size() << ']';

			for (int h = 0; h < sz; ++h)
				print_ << MOVETO(_x + 1, _y + h + 1) << _list[(h + inc)%list_size];
		}

		void scrolling(bool increment = true) {
			if (increment) ++inc; else --inc;
			//update();
		}

		void add(const std::string& str) {
			_list.push_back(str.substr(0, _width));
			if (_list.size() > _length) scrolling();else
			update();
		}

		void make_box() {

			print_ << MOVETO(_x, _y) << shap_F << REPEAT(_width, line) << shap_7;
			for (int k = 1; k != _length + 1; ++k) {
				print_ << MOVETO(_x, _y + k) << bar
					<< MOVETO(_x + _width + 1, _y + k) << bar;
			}

			print_ << MOVETO(_x, _y + _length + 1) << shap_L << REPEAT(_width, line) << shap_J;

		}

		void move(int x, int y) {
			_x += x;
			_y += y;
			esc::cls();
		}

		void draw() {
			std::thread  tcontrol(&Scrolling_list::controle, this);

			while (true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(_elapsed_time));
				if (KeyPressed(VK_ESCAPE)) break;
				make_box();
				update();
			}

			std::cin.get();

			tcontrol.detach();
		}

		void define_controle(int key_up, int key_down, int key_right, int key_left) {
			_key_up = key_up;
			_key_down = key_down;
			_key_right = key_right;
			_key_left = key_left;
			_is_defined = true;
		}

		void controle() {
			while (true) {

				if (KeyReleased(VK_UP)) {
					++inc;
				}
				if (KeyReleased(VK_DOWN))   --inc;

				if (_is_defined) {
					if (KeyReleased(_u(_key_right))) move(1, 0);
					if (KeyReleased(_u(_key_left)))  move(-1, 0);
					if (KeyReleased(_u(_key_up)))    move(0, -1);
					if (KeyReleased(_u(_key_down)))  move(0, +1);
				}
			}
		}
	};



}



