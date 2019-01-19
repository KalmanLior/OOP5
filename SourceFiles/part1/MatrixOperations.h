#ifndef OOP5_MATRIXOPERATIONS_H
#define OOP5_MATRIXOPERATIONS_H

#include "Transpose.h"


//============================================ Auxiliary ============================================//
template<int i, int j, typename M>
struct MatrixGet {
    typedef typename ListGet<j, ListGet<i, M>::value>::value value;
};

template<int i, int j, typename T, typename M>
struct MatrixSet {
private:
    typedef typename ListSet<j, T, ListGet<i, M>::value>::list newRow;
public:
    typedef typename ListSet<i, newRow, M>::list matrix;
};

template<typename M>
struct MatrixSizes {
    constexpr static int rows = M::size;
    constexpr static int columns = ListGet<0, M>::value::size;
};

template<typename M1, typename M2>
struct SizesCheck {
    constexpr static bool addCond = (MatrixSizes<M1>::rows == MatrixSizes<M2>::rows) &&
                                    ((MatrixSizes<M1>::columns == MatrixSizes<M2>::columns));
    constexpr static bool mulCond = MatrixSizes<M1>::columns == MatrixSizes<M2>::rows;
};

//============================================ Add ============================================//
template<int i, int j, typename M1, typename M2>
struct AddHelper {
private:
    constexpr static int newInt = MatrixGet<i, j, M1>::value + MatrixGet<i, j, M2>::value;
    typedef typename MatrixSet<i, j, Int < newInt>, M1>::matrix newMatrix;
public:
    typedef typename AddHelper<i, j - 1, newMatrix, M2>::result result;
};

template<int i, typename M1, typename M2>
struct AddHelper<i, 0, M1, M2> {
private:
    constexpr static int newInt = MatrixGet<i, 0, M1>::value + MatrixGet<i, 0, M2>::value;
    typedef typename MatrixSet<i, 0, Int < newInt>,M1>::matrix newMatrix;
public:
    typedef typename AddHelper<i - 1, MatrixSizes<M1>::columns - 1, newMatrix, M2>::result result;
};

template<typename M1, typename M2>
struct AddHelper<0, 0, M1, M2> {
private:
    constexpr static int newInt = MatrixGet<0, 0, M1>::value + MatrixGet<0, 0, M2>::value;
public:
    typedef typename MatrixSet<0, 0, Int < newInt>,M1>::matrix result;
};

template<typename M1, typename M2>
struct Add {
    static_assert(SizesCheck<M1, M2>::addCond, "can't Add, sizes don't match\n");
    typedef typename AddHelper<MatrixSizes<M1>::rows - 1, MatrixSizes<M1>::columns - 1, M1, M2>::result result;
};

//============================================ Multuply ============================================//

#endif //OOP5_MATRIXOPERATIONS_H
