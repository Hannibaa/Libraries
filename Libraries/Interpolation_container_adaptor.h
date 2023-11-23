#pragma once
#include <concepts>
#include <utility>



namespace Container {


    template<typename Container>
    concept has_key_mapped_types = requires {
        typename Container::key_type;
        typename Container::mapped_type;
    };

    template<typename Container>
        requires requires { 
        typename Container::key_compare;
        typename Container::key_type;
        typename Container::mapped_type;
       // requires std::is_function_v<InterpolationFunction>; // only for function
    }
    class InterContainer {

        Container*             ptr_container;

        using mapped_type = typename Container::mapped_type;
        using key_type = typename Container::key_type;

        // mapped_type(*Function)(const key_type&);

        mapped_type inter_func(const key_type& key) {

            if (ptr_container->contains(key)) return ptr_container->at(key);

            auto it = ptr_container->upper_bound(key);

            if (it == ptr_container->end()) return (--ptr_container->end())->second;

            return it->second;
        }

        // Interpolation function mapped_type _func(key_type, Container *);
    public:
        InterContainer(Container* _ptr)
            : ptr_container{ _ptr }
        {}

        ~InterContainer() { ptr_container = nullptr; }

        mapped_type operator[](const key_type& key) {
            return inter_func(key);
        }
    };





    template<typename Set, typename It = typename Set::iterator>
        requires requires { typename Set::key_compare; }
    std::pair<It, It>  get_Interval(Set& set, const typename Set::key_type& key) {

        if (set.contains(key)) return std::pair(--set.upper_bound(key), --set.upper_bound(key));

        if (set.upper_bound(key) == set.begin()) return std::pair(set.begin(), set.begin());
        if (set.upper_bound(key) == set.end()) return std::pair(--set.end(), --set.end());

        It it1 = set.upper_bound(key);
        It it2 = --set.upper_bound(key);

        return std::pair(it2, it1);
    }


    template<typename Container>
    void print_container(const Container& container, std::string_view comment = "") {
        print_ << comment << end_;
        for (const auto& element : container)
            if constexpr (has_key_mapped_types<Container>)
                print_ << "{" << element.first << " , " << element.second << "} ,";
            else
                print_ << element << " , ";

        print_ << BACKSPACE << ' ' << end_;
    }

}

namespace cu = Container;