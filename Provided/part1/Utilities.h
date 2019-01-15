#ifndef OOP5_PART1_UTILITIES_H
#define OOP5_PART1_UTILITIES_H

template<int N>
struct Int{
    int value = N;
};


template<typename Head, typename... Elements>
struct List{
    Head head;
    List<Elements...> next;
    int size;
};

template<int N>
struct List<Int<N>>{
    int head = N;
    int size = 1;
};

template<typename T, List<T> L>
struct PrependList{
    List<T> list = L;
};

template<int N, List<T> L>
struct ListGet{
    T head;
    List<T> next;
    int size;
};

template<typename T>
struct ListSet{
    T head;
    List<T> next;
    int size;
};


#endif //OOP5_PART1_UTILITIES_H
