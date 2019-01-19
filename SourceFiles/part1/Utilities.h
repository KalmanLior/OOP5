#ifndef OOP5_PART1_UTILITIES_H
#define OOP5_PART1_UTILITIES_H


//============================================ Int ============================================//
template<int N>
struct Int {
    constexpr static int value = N;
};

//=========================================== List ===========================================//
template<typename>
struct List {
};

template<typename H, typename... Elements>
struct List<H, Elements...> {
public:
    typedef H head;
    typedef List<Elements...> next;
    constexpr static int size = sizeof...(Elements) + 1;
};

template<>
struct List<> {
    constexpr static int size = 0;
};

//======================================== PrependList ========================================//
template<typename T, typename... N>
struct PrependList {
};

template<typename T, typename... N>
struct PrependList<T, List<N...>> {
    typedef List<T, N...> list;
};

//========================================== ListGet ==========================================//
template<int, typename>
struct ListGet {
};

template<int N, typename T, typename... L>
struct ListGet<N, List<T, L...>> {
    typedef typename ListGet<N - 1, List<L...>>::value value;
};

template<typename T, typename... L>
struct ListGet<0, List<T, L...>> {
    typedef T value;
};

//========================================== ListSet ==========================================//
template<int N, typename T, typename... L>
struct ListSet {
};

template<int N, typename T, typename... L>
struct ListSet<N, T, List<L...>> {
    typedef typename PrependList<List<L...>::head, ListSet<N - 1, T, List<L...>::next>::list>
    ::list list;
};

template<typename T, typename... L>
struct ListSet<0, T, List<L...>> {
    typedef typename PrependList<T, List<L...>::next>::list list;
};

#endif //OOP5_PART1_UTILITIES_H
