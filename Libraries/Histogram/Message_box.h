#pragma once
#include <MyLib/Console_Library/escape_code.h>



namespace cui {

	class Message_Box {

		std::string _message_head;
		std::string _message_body;


		int _x;
		int _y;
		int _length;
		int _width;

		// Glyph drawing box
		const char line = '\xc4';
		const char bar = '\xb3';
		const char shap_L = '\xc0';
		const char shap_7 = '\xbf';
		const char shap_J = '\xd9';
		const char shap_F = '\xda';

	public:

		void operator()(int x, int y ,
			const std::string& message_head, const std::string& message_body,
			int offset_width = 0, int offset_length = 0 )
		{
			_x = x; _y = y;
			_message_head = message_head;
			_message_body = message_body;

			// calculate width and length
			_width = 4 + _message_body.size() + offset_width;
			_length = 3 + offset_length;

			make_box();
		}

		void make_box() {

			print_ << MOVETO(_x, _y) << shap_F << REPEAT(_width, line) << shap_7;
			for (int k = 1; k != _length + 1; ++k) {
				print_ << MOVETO(_x, _y + k) << bar
					<< MOVETO(_x + _width + 1, _y + k) << bar;
			}

			print_ << MOVETO(_x, _y + _length + 1) << shap_L << REPEAT(_width, line) << shap_J;

			print_ << MOVETO(_x + 2, _y + 2) << _message_body 
				<< MOVETO(_x + 1, _y) << '[' << _message_head << ']'
				<< MOVETO(_x + 2 + _message_body.size() , _y + 2);
				 

		}

		void draw() {
			
		}
	};

	class Area_Text {

	};

}