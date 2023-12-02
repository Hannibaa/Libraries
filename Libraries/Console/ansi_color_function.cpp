#include <iostream>
#include <thread>
#include "MyLib/Console_Library/Event_Windows.h"
#include "MyLib/Console_Library/escape_code.h"

/* 
            testing function : ansi_color(r,g,b)
			                   ansi_color<r,g,b>
							   _rgb<r,g,b>
							   _rgb(r,g,b).
*/

int main()
{
	int r{};
	int g{};
	int b{};

	int colour = _rgb<2,4,6>();

    WHIDE_CURSOR;


	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		esc::clear_line(1,1);

		if (KeyPressed(VK_UP)) {
			if (KeyOn(_u('G'))) ++g;
			if (KeyOn(_u('R'))) ++r;
			if (KeyOn(_u('B'))) ++b;
		}


		if (KeyPressed(VK_DOWN)) {
			if (KeyPressed(_u('G'))) --g;
			if (KeyPressed(_u('R'))) --r;
			if (KeyPressed(_u('B'))) --b;
		}




		if (KeyPressed(VK_ESCAPE)) {
			break;
		}

		for (int k = 0; k != 5; ++k) {
			print_ << MOVETO(1, 1+k) << _COLOR_BG256(esc::ansi_color(r, g, b)) << "          "
				<< RESETMODE;
		}

		newline_;
		print_ << _COLOR_BG256(_rgb(r, g, b)) << " HELLO " << RESETMODE << end_;
	}






	std::cin.get();
	return 0;
}