#include <iostream>
#include <thread>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>

using namespace std::literals;

void effect(int x, int y) {
	for (int i = 232; i != 266; ++i) {
		print_ << MOVETO(i - x, y);
		print_ << _COLOR_FG256(i) << "hello_" << i;
		std::this_thread::sleep_for(100ms);
	}

}

int main() {




	print_ << RESETMODE;

	std::cin.get();
	return 0;
}