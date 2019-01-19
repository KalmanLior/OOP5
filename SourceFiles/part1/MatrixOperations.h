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

template<int size, typename L>
struct NewRow {
    typedef typename NewRow<size - 1, PrependList<Int<0>, L>::list>::row row;
};

template<typename L>
struct NewRow<1, L> {
    typedef L row;
};

template<int Rows, int Cols, typename M>
struct NewMatrix {
private:
    typedef typename NewRow<Cols, List<Int<0>>>::row newRow;
public:
    typedef typename NewMatrix<Rows - 1, Cols, PrependList<newRow, M>::list>::matrix matrix;
};

template<int Cols, typename M>
struct NewMatrix<1, Cols, M> {
    typedef M matrix;
};

template<int Rows, int Cols>
struct CreateMatrix {
private:
    typedef typename NewRow<Cols, List<Int<0>>>::row newRow;
public:
    typedef typename NewMatrix<Rows, Cols, List<newRow>>::matrix matrix;
};

template<int N, typename L1, typename L2>
struct MultiplyListsHelper {
private:
    constexpr static int addedValue = ListGet<N, L1>::value * ListGet<N, L2>::value;
public:
    constexpr static int value = addedValue + MultiplyListsHelper<N - 1, L1, L2>::value;
};

template<typename L1, typename L2>
struct MultiplyListsHelper<0, L1, L2> {
    constexpr static int value = ListGet<0, L1>::value * ListGet<0, L2>::value;
};

template<typename L1, typename L2>
struct MultiplyLists {
    constexpr static int value = MultiplyListsHelper<L1::size - 1, L1, L2>::value;
};

//============================================ Add ============================================//
template<int i, int j, typename M1, typename M2>
struct AddHelper {
private:
    constexpr static int newInt = MatrixGet<i, j, M1>::value + MatrixGet<i, j, M2>::value;
    typedef typename MatrixSet<i, j, Int<newInt>, M1>::matrix newMatrix;
public:
    typedef typename AddHelper<i, j - 1, newMatrix, M2>::result result;
};

template<int i, typename M1, typename M2>
struct AddHelper<i, 0, M1, M2> {
private:
    constexpr static int newInt = MatrixGet<i, 0, M1>::value + MatrixGet<i, 0, M2>::value;
    typedef typename MatrixSet<i, 0, Int<newInt>, M1>::matrix newMatrix;
public:
    typedef typename AddHelper<i - 1, MatrixSizes<M1>::columns - 1, newMatrix, M2>::result result;
};

template<typename M1, typename M2>
struct AddHelper<0, 0, M1, M2> {
private:
    constexpr static int newInt = MatrixGet<0, 0, M1>::value + MatrixGet<0, 0, M2>::value;
public:
    typedef typename MatrixSet<0, 0, Int<newInt>, M1>::matrix result;
};

template<typename M1, typename M2>
struct Add {
    static_assert(SizesCheck<M1, M2>::addCond, "can't Add, sizes don't match\n");
    typedef typename AddHelper<MatrixSizes<M1>::rows - 1, MatrixSizes<M1>::columns - 1, M1, M2>::result result;
};

//============================================ Multiply ============================================//
template<int i, int j, typename M1, typename M2T, typename NewM>
struct MultiplyHelper {
private:
    constexpr static int newInt = MultiplyLists<ListGet<i, M1>, ListGet<j, M2T>>::value;
    typedef typename MatrixSet<i, j, Int<newInt>, NewM>::matrix newMatrix;
public:
    typedef typename MultiplyHelper<i, j - 1, M1, M2T, newMatrix>::result result;
};

template<int i, typename M1, typename M2T, typename NewM>
struct MultiplyHelper<i, 0, M1, M2T, NewM> {
private:
    constexpr static int newInt = MultiplyLists<ListGet<i, M1>, ListGet<0, M2T>>::value;
    typedef typename MatrixSet<i, 0, Int<newInt>, NewM>::matrix newMatrix;
    typedef typename MatrixSizes<M2T>::rows j;
public:
    typedef typename MultiplyHelper<i - 1, j - 1, M1, M2T, newMatrix>::result result;
};

template<typename M1, typename M2T, typename NewM>
struct MultiplyHelper<0, 0, M1, M2T, NewM> {
private:
    constexpr static int newInt = MultiplyLists<ListGet<0, M1>, ListGet<0, M2T>>::value;
public:
    typedef typename MatrixSet<0, 0, Int<newInt>, NewM>::matrix result;
};

template<typename M1, typename M2>
struct Multiply {
    static_assert(SizesCheck<M1, M2>::mulCond, "can't Multiply, sizes don't match\n");
private:
    typedef typename MatrixSizes<M1>::rows rows;
    typedef typename MatrixSizes<M2>::columns columns;
    typedef typename CreateMatrix<rows, columns>::matrix newMatrix;
public:
    typedef typename MultiplyHelper<rows - 1, columns - 1, M1, Transpose<M2>::matrix, newMatrix>::result result;
};

#endif //OOP5_MATRIXOPERATIONS_H
