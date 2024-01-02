#include <iostream>
#include "MyLib/bitmap/bitmap_image.hpp"
#include "MyLib/opendialogfile.h"
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/stringfunctionhelper.h"


int main()
{
	DEFINE_rgb2ansi

	COMDLG_FILTERSPEC bmp_ext{ L"bitmap .bmp", L"*.bmp" };
	auto image_file = Str::to_char<char>(opendialog::OpenFile(L"GET FILE BITMAP .BMP", bmp_ext));

	if (image_file.empty()) {
		Print_(color::Red, "Error...") << end_;
		return -1;
	}


	bitmap_image image(image_file);

	int w = image.width();
	int h = image.height();

	Print_(color::Green, "dimension of image :") << image.width() << " "
		<< image.height() << end_;

	

	for (int i = 0; i != w; ++i)
	{
		for (int j = 0; j != h; ++j)
		{
			auto rgb = image.get_pixel(i, j);
			int _color = RGB2INT(rgb.red, rgb.blue, rgb.blue);
			printm_(i,j) <<_COLOR_BG256(rgb2ansi[_color]) << " " << RESETMODE;
		}
	}

	print_ << "End....." << end_;
	std::cin.get();
	return 0;
}