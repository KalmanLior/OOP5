#ifndef OOP5_PART1_UTILITIES_H
#define OOP5_PART1_UTILITIES_H

template<int N>
struct Int{
    constexpr static int value = N;
};

//======================================= List and specializations =======================================//
template<typename... Elements>
struct List{};

template<typename H,typename... Elements>
struct List<H, Elements...>{
public:
    typedef H head;
    // this does the "unpacking"
    typedef List<Elements...> next;
    constexpr static int size = sizeof...(Elements) + 1;
};

//specialization - a list with no elements, this is our terminating condition
template<>
struct List<>{
    constexpr static int size = 0;
};

//======================================= PrependList and specializations =======================================//
template<typename T, typename... N>
struct PrependList{};

template<typename T, typename... N>
struct PrependList<T, List<N...>>{
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
