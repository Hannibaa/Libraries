#include <iostream>
#include "scale.h"


int main()
{
	INIT_WCHAR_TEXT;
	WHIDE_CURSOR;

	int _length = 50;
	std::map<int, float> _m;
	_m[0] = 20.44f;
	_m[29] = 60.66f;
	_m[50] = 200.11f;
	
	std::map<int, int> _my;
	_my[0] = 20;
	_my[10] = 60;
	_my[20] = 200;

	cui::ScaleX scalex(10, 10, L"ROP[ft/h]", _length, color::Green, color::Maroon, _m);

	cui::ScaleY scaley(70, 27, L"WOB[klb]", 20, color::Green, color::Maroon, _my);
	scaley.adjust_title(3);


	scalex.set_value(40.f);
	scaley.set_value(40);
	
	scaley.draw();
	scaley.display_value();

	scalex.draw();
	scalex.display_value(true);


	std::wcin.get();
	return 0;
}