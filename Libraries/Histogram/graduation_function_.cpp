#include <iostream>
#include "MyLib/Console_Library/escape_code.h"

// we need to learn how to print another closer and for more than 
/*
*        (l=10)[0,30](3)   (l=9)[-15,15](2)   (l=12)[0,30](1)
            --30			 --15			   --30
			-				 -				   -
			-				 -				   -
			--20			 -			       -
			-				 - 0			   -
			-				 -				   -
			--10			 -			       -
			-				 -				   -
			-				 ---15			   -
			--0				 			       -
			                                   -
			                                   --0
*/


template<typename T>
requires std::is_arithmetic_v<T>
void draw_graduation(int length, int n, Pint _pos, T min, T max) {
	int width = 3;                // _bar.get_width();
	T   l = (max - min) / T(n);

	int il = length / n;
	int k{1};

	for (int i = 1; i != length - 1; ++i) {
		wprintm_(_pos.x + width + 1, _pos.y - i) << L"\x2500";

		if (i == k*il ) {
			wprintm_(_pos.x + width + 1, _pos.y - i) << L"\x2501\x2501";
			wprint_ << min + T(k) * l;
			++k;
		}
	}
	wprintm_(_pos.x + width + 1, _pos.y )     << L"\x2501\x2501";
	wprintm_(_pos.x + width + 1, _pos.y - length + 1 ) << L"\x2501\x2501";

	wprintm_(_pos.x + width + 3, _pos.y ) << min;            
	wprintm_(_pos.x + width + 3, _pos.y - length +1) << max;
}

int main()
{
	INIT_UNICODE_TEXT;
	WHIDE_CURSOR;
	Pint p(10, 26);

	draw_graduation<int>(11, 4, p, -10, 10);



	wwait_;
	return 0;
}