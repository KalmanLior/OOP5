#ifndef OOP5_PART1_UTILITIES_H
#define OOP5_PART1_UTILITIES_H

template<int N>
struct Int{
    constexpr static int value = N;
};

// a template for unpacking a list
template<typename H, typename... Elements>
struct UnpackedList{
    typedef H head;
    // this does the "unpacking"
    typedef UnpackedList<Elements...> next;
    constexpr static int size = sizeof...(Elements) + 1;
};

template<typename H>
struct UnpackedList<H>{
    typedef H head;
    constexpr static int size = 1;
};


//======================================= List and specializations =======================================//
template<typename... Elements>
struct List{
private:
    typedef UnpackedList<Elements...> unpacked_list;
public:
    typedef typename unpacked_list::head head;
    // this does the "unpacking"
    typedef typename unpacked_list::next next;
    constexpr static int size = sizeof...(Elements);
};

//specialization - a list with 1 element, this is our terminating condition
template<typename T>
struct List<T>{
    typedef T head;
    typedef List next;
    constexpr static int size = 1;
};

//specialization - a list with no elements, this is our terminating condition
template<>
struct List<>{
    constexpr static int size = 0;
};


//======================================= PrependList and specializations =======================================//
template<typename T, typename... N>
struct PrependList{
    typedef List<T, N...> list;
};

//======================================= ListGet and specializations =======================================//
template<int N, typename T>
struct ListGet{};

template<int N, typename T, typename... L>
struct ListGet<N, List<T, L...>>{
    typedef typename ListGet<N-1, List<L...>>::value value;

};

template<typename T, typename... L>
struct ListGet<0, List<T, L...>>{
        typedef T value;
};



//======================================= ListSet and specializations =======================================//
template<int N, typename T, typename... L>
struct ListSet{};

template<int N, typename T, typename... L>
struct ListSet<N, T, List<L...>>{
    typedef typename PrependList<typename List<L...>::head,
                                 typename ListSet<N-1, T, typename List<L...>::next>::list>
                                 ::list list;
};

template<typename T, typename... L>
struct ListSet<0, T, List<L...>>{
    typedef typename PrependList<T, typename List<L...>::next>::list list;
};

#endif //OOP5_PART1_UTILITIES_H
