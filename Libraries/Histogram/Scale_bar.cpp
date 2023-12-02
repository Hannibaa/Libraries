#include <iostream>
#include "MyProject\Libraries\Libraries\Histogram\Histogram.h"
#include "MyLib/random_vector.h"


template<typename T>
void scale(
	int x,                        // x coordinate
	int y, 						  // y coordinate
	const std::wstring& title, 	  // title to be shown in bar scale
	int length,					  // length of scale
	int step,					  // step between every graduation 
	wchar_t line,				  // glyph for line
	wchar_t T_line,				  // glyph for teeth midle 
	wchar_t begin_line,			  // glyph for begin of bar
	wchar_t end_line,			  // glyph for end of bar
	int scale_color,			  // color of bar line
	int text_color,			      // color of title
	const std::vector<T>& sv)
{
	int title_size = int(title.size());

	int title_x = x + length / 2 - title_size / 2;
	int title_y = y + 2;

	// helpfull lambda function 
	auto Size = [](const T& value)->int { return int(Fn::_size<wchar_t>(value)) / 2; };

	wprint_ << WMOVETO(x - Size(sv[0]), y + 1)
		    << wCOLOR(scale_color, sv[0]);

	for (int i = 0; i < length - 1; ++i) {
		wchar_t t = line;
		if ((i + 1) % step == 0) {
			t = T_line;
			int subscript = int(float(i) * (float(sv.size() - 1ull) / float(length-2)));
			wprint_ << WMOVETO(x + i - Size(sv[subscript]), y + 1)
				    << wCOLOR(scale_color, sv[subscript]);
		}

		wprint_ << WMOVETO(x + i, y)
			<< wCOLOR(scale_color, t);
	}
	wprint_ << WMOVETO(x + length - 1 - Size(*(sv.end()-1)), y + 1)
		    << wCOLOR(scale_color, sv[sv.size() - 1]);

	wprint_ << WMOVETO(x, y) << wCOLOR(scale_color, begin_line)
		<< WMOVETO(x + length - 1, y) << wCOLOR(scale_color, end_line)
		<< WMOVETO(title_x, title_y) << wCOLOR(text_color, title);

}

template<typename T>
void scale_horizontal(
	int x,                        // x coordinate
	int y, 						  // y coordinate
	const std::wstring& title, 	  // title to be shown in bar scale
	int length,					  // length of scale
	int step,					  // step between every graduation 
	wchar_t line,				  // glyph for line
	wchar_t T_line,				  // glyph for teeth midle 
	wchar_t begin_line,			  // glyph for begin of bar
	wchar_t end_line,			  // glyph for end of bar
	int scale_color,			  // color of bar line
	int text_color ,			  // color of title
	const std::vector<T>&   sv)
{
	int title_size = int(title.size());

	int title_y = y - length / 2 - title_size / 2;
	int title_x = x - 4;

	// lambda function helpfully.
	auto Size = [](const T& value)->int { return int(Fn::_size<wchar_t>(value)); };

	wprint_ << WMOVETO(x - 1 - Size(sv[0]), y) // values
		    << wCOLOR(scale_color, sv[0]);

	for (int i = 0; i < length - 1; ++i) {
		wchar_t t = line;

		if ((i + 1) % step == 0) {
			t = T_line;
			int subscript = int(float(i) * (float(sv.size() - 1ull) / float(length - 2)));
			wprint_ << WMOVETO(x - 1 - Size(sv[subscript]), y - i) // values
				    << wCOLOR(scale_color, sv[subscript]);
		}

		wprint_ << WMOVETO(x , y - i)
			    << wCOLOR(scale_color, t);
	}
	wprint_ << WMOVETO(x - 1 - Size(*(sv.end()-1)), y - length + 1) // values
		    << wCOLOR(scale_color, sv[sv.size() - 1]);

	wprint_ << WMOVETO(x, y) << wCOLOR(scale_color, begin_line)
		    << WMOVETO(x, y - length + 1) << wCOLOR(scale_color, end_line);

	put_string_horizontal_up_at(title_x, title_y, title, text_color);
}

int main()
{
	INIT_WCHAR_TEXT;
	
	// glyph for vertical line; upside
	const wchar_t corner_bline  = 0x2517;
	const wchar_t corner_eline  = 0x251b;
	const wchar_t corner_bline1 = 0x2515;
	const wchar_t corner_eline1 = 0x2519;
	const wchar_t tline1        = 0x2537;
	const wchar_t tline         = 0x253b;
	const wchar_t bline         = 0x2501;
	//glyph for downside;
	const wchar_t corner_bline_dn = 0x250d;
	const wchar_t corner_eline_dn = 0x2511;
	const wchar_t tline_dn = 0x252f;



	// glyph for horizontal line; left 
	const wchar_t hline         = 0x2503;
	const wchar_t hline_up         = 0x2512;
	const wchar_t hline_dn         = 0x251a;
	const wchar_t hline_t         = 0x2528;


	// what we used for 
	wchar_t line{}, begin_line{}, end_line{}, T_line{};

	const std::wstring title = L"scale 100";
	int title_size = int(title.size());

	const int scale_color = color::Red;
	const int text_color = color::Fuchsia;

	const int length = 25;
	const int lengthV = 50;
	const int step = 7;
	const int stepV = 10;
	int x = 10, y = 30;

	auto Values = vu::makeRandomContainer<std::vector>(10.f, 1000.f, 30);

	std::vector vint{ 90000,1,2,3,4,5,6,7,8,9,10,11, 123456 };
	std::vector vstr{ L"this",L"hello" ,L"that", L"there", L"in" };

	scale(x+2, y+1, title, lengthV , stepV, bline, 
		      tline_dn, corner_bline_dn, corner_eline_dn, scale_color,text_color, vstr);

	scale_horizontal(x, y, title, length , step, hline, 
		      hline_t, hline_dn, hline_up, scale_color,text_color, vint);
	

	std::cin.get();
	return 0;
}