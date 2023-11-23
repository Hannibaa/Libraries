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

template<typename Container, typename InterpolationFunction>
    requires requires { typename Container::key_compare;
                        typename Container::key_type;
                        typename Container::mapped_type;
                        requires std::is_function_v<InterpolationFunction>;
                        requires std::same_as<InterpolationFunction, 
                        typename Container::mapped_type(typename Container::key_type)>;
                      }
class InterContainer {

    Container*             ptr_container;
    InterpolationFunction  interpolate;

    using mapped_type = typename Container::mapped_type;
    using key_type    = typename Container::key_type;

   // mapped_type(*Function)(const key_type&);

    mapped_type inter_func(const key_type& key) {

        if (ptr_container->contains(key)) return ptr_container->at(key);

        auto it = ptr_container->upper_bound(key);
        return it->second;
    }

    // Interpolation function mapped_type _func(key_type, Container *);
public:
    InterContainer(Container *_ptr, InterpolationFunction _func) 
        : ptr_container{_ptr}
        , interpolate{_func}
    {}

    ~InterContainer() { ptr_container = nullptr; }

    mapped_type operator[](const key_type& key) {
        return inter_func(key);
    }

    mapped_type operator()(const key_type& key) {
        return interpolate(key);
    }
};

template<typename Set, typename It = typename Set::iterator>
    requires requires { typename Set::key_compare; }
std::pair<It, It>  get_Interval( Set& set,const typename Set::key_type& key) {

    if (set.contains(key)) return std::pair(--set.upper_bound(key), --set.upper_bound(key));

    if ( set.upper_bound(key) == set.begin() ) return std::pair(set.begin(), set.begin());
    if ( set.upper_bound(key) == set.end() ) return std::pair(--set.end(), --set.end());

    It it1 = set.upper_bound(key);
    It it2 = --set.upper_bound(key);

    return std::pair(it2, it1);
}



int main() {

    std::set<int> _set{ 10,3,6,7,0, -5,-9 };
    std::vector<int> _v{ 4,6,7,8,8,9 };

    print_ << "value : ";
    for (auto it = _set.begin(); it != _set.end(); ++it)
        print_ << *it << " ";
    print_ << end_;

    auto p = get_Interval(_set, 10);

    std::map<int, int> _m{ {2000,0},{4000,1}, {100,3}, {-100,6 } };

    // -100, 100 , 2000, 4000 
    auto ptr = _m.upper_bound(1000);
   // auto vp = get_Interval(_v, 6);
    auto mp = get_Interval(_m, 0);

    
    print_ << *p.first << "|" << *p.second << end_;
    print_ << ptr->first << "|" << (++ptr)->first << end_;
    print_ << "lower " << _m.begin()->first << "| upper " << (--_m.end())->first << end_;
    print_ << "lower get : " << mp.first->first << "| upper get : " << mp.second->first << end_;

    wait_;
    return 0;
}