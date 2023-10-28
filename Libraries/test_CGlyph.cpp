#include <iostream>
#include <MyLib/strings/CWord.h>




int main() {

	text::CWord    words{ "hello this mine", ESC::Colors::_RED_BG };

	std::cout << "this word : [" << words <<"]\n";

	words.set_color(ESC::Colors::_GREEN_FG);


	std::cout << " ad this is ";

	std::cout << words << end_;

	std::cin.get();
	return 0;
}






//int main()
//{
//	text::CGlyph g = 'a';
//	g.g_color = ESC::Colors::_CYAN_FG;
//	text::CGlyph g2 = 'd';
//	g2.g_color = ESC::Colors::_YELLOW_FG;
//
//	std::vector<text::CGlyph> word{ g,g2, g, g2 };
//
//	print_ << "char of glyph " << g << end_;
//
//	print_ << "char " << g2 << " here" << end_;
//
//	print_ << "word is [";
//	for (auto& e : word) print_ << e; print_ << "]\n";
//
//
//	std::cin.get();
//	return 0;
//}