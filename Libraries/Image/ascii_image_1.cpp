#include <iostream>
#include "MyLib/bitmap/bitmap_image.hpp"
#include "MyLib/opendialogfile.h"
#include "MyLib/Console_Library/escape_code.h"
#include "MyLib/stringfunctionhelper.h"

// todo make library for convert to image ascii 

int Intensity(int x, int L) {
	const int Xmax = 0xffffff;
	const int l    = Xmax / L;
	
	for (int j = 0; j != L - 1; ++j) {
		if (x >= l * j && x < l * (j + 1)) return j;
	}

	if (x >= l * (L - 1) && x < Xmax + 1) return L - 1;

	return 0;
}

int main()
{
	COMDLG_FILTERSPEC bmp_ext{ L"bitmap .bmp", L"*.bmp" };
	auto image_file =Str::to_char<char>(opendialog::OpenFile(L"GET FILE BITMAP .BMP", bmp_ext));

	if (image_file.empty()) {
		Print_(color::Red, "Error...") << end_;
		return -1;
	}

	std::string pattern{ "#@$%&*_." };

	bitmap_image image(image_file);

	int w = image.width();
	int h = image.height();

	Print_(color::Green, "dimension of image :") << image.width() << " "
		<< image.height() << end_;

	std::ofstream ofs{ "image.txt" };

	if (!ofs.is_open()) {
		Print_(color::Red, "Error...") << end_;
		return -1;
	}

	for (int i = 0; i != w; ++i)
	{
		for (int j = 0; j != h; ++j)
		{
			auto rgb = image.get_pixel(i, j);
			int _color = RGB2INT(rgb.red, rgb.blue, rgb.blue);
			int _pos = Intensity(_color, 8);
			ofs << pattern[_pos];
		}
		ofs << end_;
	}

	ofs.close();
	print_ << "End....." << end_;
	std::cin.get();
	return 0;
}