#include <iostream>
#include <thread>
#include <mutex>
#include <MyLib/Console_Library/escape_code.h>

using namespace std::chrono_literals;

std::mutex mx;

void progress_bar(char c, int size, float position, std::chrono::milliseconds _duration)
{

}

void move_char(char c,color color, int distance, std::chrono::milliseconds seconds) {
	
	for (int i = 0; i < distance; ++i) {
		print_ << ERASELINE;
		mx.lock();
		print_ << _COLOR_FG256(color) << c;
		mx.unlock();
		std::this_thread::sleep_for(seconds);
	}
}

void movexy_char(char c, color _color, float(*fx)(float), float(*fy)(float), 
	std::chrono::milliseconds seconds, float step, std::chrono::milliseconds _duration)
{
		 float f =  0.f ; 
	for (std::chrono::system_clock::time_point d = std::chrono::system_clock::now();
		 (std::chrono::system_clock::now() - d) < _duration ; f += step) {
		mx.lock();
		print_ << ERASESCREEN;
		print_ << MOVETO(int(fx(f)),int(fy(f))) << _COLOR_FG256(_color) << c;
		mx.unlock();
		std::this_thread::sleep_for(seconds);
	}
}


int main()
{

	print_ << CURSOR_INVISIBLE;
	std::thread t_xy(movexy_char, 'B', ESC::Green, [](float x) {return 40.f + 35.f * std::sinf(x); },
		[](float x) {return 15.f; }, 10ms, 0.05f, 10s);
	std::thread t_xy2(movexy_char, 'G', ESC::Yellow, [](float x) {return 40.f + 35.f * std::sinf(x); },
		[](float x) {return 15.f + 20.f*std::cosf(4.6f*x); }, 10ms, 0.1f, 10s);
	movexy_char('A', ESC::Red, [](float x) {return 20.f + 10.f*std::sinf(5.f*x); },
		                       [](float x) {return 10.f + 10.f*std::cosf(x);}, 10ms , 0.05f,10s);

	//movexy_char('B', ESC::Green, [](float x) {return 40.f + 35.f * std::sinf(x); },
	//	[](float x) {return 15.f ; }, 50ms, 0.05f, 10s);
	//std::thread t(move_char, 'D', ESC::Red, 30, 190ms);
	//move_char('A', ESC::Aqua, 100, 100ms);
	//newline_;
	//move_char('K', color::Yellow, 50, 130ms);
	//t.join();
	t_xy.join();
	t_xy2.join();
	print_ << RESETMODE;
	std::cin.get();
	return 0;
}