#include <iostream>
#include <MyLib/strings/CWord.h>




int main() {

	// constructor will remove other words
	text::CWord    words{ "hello this mine", ESC::Colors::_RED_BG };
	text::CWord    word2{ "    this my name " };

	std::cout << "this word1 : [" << words <<"]\n";
	std::cout << "this word2 : [" << word2 <<"]\n";

	// change the colors of word1 
	words.set_color(ESC::Colors::_GREEN_FG);

	// We want to set first char with red:
	word2.set_color(ESC::Colors::_YELLOW_BG,0,1);
	std::cout << "this word2 : [" << word2 <<"]\n";

	std::cout << "words with other color: ";

	std::cout << words << end_;

	// now with call these two words in sentenses:
	newline_;
	std::cout << "hello in color " << words << " and other this " << word2 << " end" << end_;

	// convert string from the 

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