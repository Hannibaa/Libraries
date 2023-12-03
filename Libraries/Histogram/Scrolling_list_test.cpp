#include <iostream>
#include "MyLib/Console_Library/Event_Windows.h"
#include "Scrolling_list.h"
#include "Message_box.h"


int main()
{
	WHIDE_CURSOR;

	cui::Message_Box msg;

	std::string file;
	msg(10,15, "File", "enter your file name : ", 16);
	std::cin >> file;

	msg(10, 20, "Folder", "Enter your folder file name : ", 16);
	std::string folder;
	std::cin >> folder;

	msg(50, 10, "Folder/File", "Path : /" + folder + "/" + file, 16);
	wait_;

	// return for testing 
	return 0;

	cui::Scrolling_list  sl(80, 5, 14, 8);
	cui::Scrolling_list  list(10, 10, 50, 4);

	list.add("tool crt 1");
	list.add("benchmark c++");
	list.add("sin function");
	list.add("algebra");
	list.add("mathematics");
	list.add(file);


	sl.make_box();
	list.make_box();

	sl.define_controle('W', 'S', 'D', 'A');

	for (int j = 0; j < 3; ++j) {
		sl.add("hello" + std::to_string(j+1));
		wait_;
	}


	list.draw();
	//while (true) {

	//	if (KeyReleased(VK_UP))   sl.scrolling();
	//	if (KeyReleased(VK_DOWN)) sl.scrolling(false);
	//	if (KeyReleased(VK_ESCAPE)) break;


	//	if (KeyReleased(_u('L'))) sl.move(1, 0);
	//	if (KeyReleased(_u('R'))) sl.move(-1, 0);
	//	if (KeyReleased(_u('U'))) sl.move(0, -1);
	//	if (KeyReleased(_u('D'))) sl.move(0, +1);



	//	if (KeyReleased(VK_SPACE)) {
	//		print_ << MOVETO(1, 1) << "add names : ";
	//		std::string  name;
	//		std::cout.flush();
	//		std::cin >> name;

	//		sl.add(name);
	//		esc::clear_line(1, 1);
	//	}

	//}

	std::cin.get();
	return 0;
}