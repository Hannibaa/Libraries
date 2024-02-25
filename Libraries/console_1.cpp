#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>

/* 
             Exemple how to using threading with escape code and we move to 
			 more in ASCII art.
*/

using namespace std::literals;

void effect(int x, int y, std::string_view _string, std::chrono::milliseconds seconds) {
	for (int i = 232; i != 266; ++i) {
		
		std::osyncstream(print_)  << MOVETO( x, y) << _COLOR_FG256(i) << _string 
			                      << "hello_" << i << RESETMODE;

		std::this_thread::sleep_for(seconds);
	}
}

int main() {

	std::thread t1(effect, 10, 10, "thread 111", 100ms);
	std::thread t2(effect, 20, 20, "thread 200", 250ms);
	//std::thread t3(effect, 0, 0);

	effect(100, 13, "Main Thread", 250ms);


	t1.detach();
	t2.detach();
	//t3.join();

	std::cin.get();
	return 0;
}