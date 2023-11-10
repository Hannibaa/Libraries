#include <iostream>
#include <thread>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>

/* 
             Exemple how to using threading with escape code and we move to 
			 more in ASCII art.
*/

using namespace std::literals;

void effect(int x, int y, char c, std::chrono::milliseconds seconds) {
	for (int i = 232; i != 266; ++i) {
		print_ << MOVETO( x, y);
		print_ << _COLOR_FG256(i) << c << "hello_" << i;
		std::this_thread::sleep_for(seconds);
	}
}

int main() {

	std::thread t1(effect, 10, 10, 'A', 100ms);
	std::thread t2(effect, 20, 20, 'B', 250ms);
	//std::thread t3(effect, 0, 0);

	effect(100, 13, 'C', 250ms);

	print_ << RESETMODE;

	t1.detach();
	t2.detach();
	//t3.join();

	std::cin.get();
	return 0;
}