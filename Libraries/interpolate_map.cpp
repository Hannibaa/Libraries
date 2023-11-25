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
#include <MyLib/container_utility.h>


int main() {

    std::set<int> _set{ 10,3,6,7,0, -5,-9 };
    std::vector<int> _v{ 4,6,7,8,8,9 };

    cu::print_container(_set, "set value :");
    cu::print_container(_v, "vector value :");

    auto p = cu::get_Interval(_set, 10);

    std::map<int, int> _m{ {2000,0},{4000,1}, {100,3}, {-100,6 } };
    cu::print_container(_m, "map value : ");

    // -100, 100 , 2000, 4000 
    auto ptr = _m.upper_bound(1000);
   // auto vp = get_Interval(_v, 6);
    auto mp = cu::get_Interval(_m, 0);

    
    print_ << *p.first << "|" << *p.second << end_;
    print_ << ptr->first << "|" << (++ptr)->first << end_;
    print_ << "lower " << _m.begin()->first << "| upper " << (--_m.end())->first << end_;
    print_ << "lower get : " << mp.first->first << "| upper get : " << mp.second->first << end_;

    wait_;
    return 0;
}