/*

     Interpolation of associative container for given value have to
     chose between :
     1. interpolate between value
     2. add value
     3. chose closed or, who satisfy criteria P().

*/

#include <iostream>
#include <MyLib/containers.h>
#include <MyLib/Console_Library/escape_code.h>
#include "Interpolation_container_adaptor.h"


int main() {

    std::set _set{ 10,3,6,7,0, -5,-9 };
    std::vector _v{ 4,6,7,8,8,9 };
    std::map<int,int>  _m{ {2000,0},{4000,1}, {100,3}, {-100,6 } };

    std::map<std::string, int> _mstr{ {"hello", 2},{"world", 9} ,{"morning", 5} };

    cu::print_container(_set, "value of set : ");
    cu::print_container(_v, "value of vector : ");
    cu::print_container(_m, "value of map : ");
    cu::print_container(_mstr, "value of string");

    cu::InterContainer  _map(&_m);
    cu::InterContainer  _mm(&_mstr);


    print_ << _mm["that"] << end_;
    print_ << _map[0] << ", " << _map[1000] << ", " << _map[5000] << " , " << _map[-1000]<< end_;
  //  cu::InterContainer  _imap(&_m);



    wait_;
    return 0;
}