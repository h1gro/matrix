#include <iostream>
#include "../include/matrix.hpp"

int main()
{
    size_t matrix_size = 0;
    std::cin >> matrix_size;

    matrix::Matrix<long double> matrix(matrix_size, matrix_size);

    matrix.filling_matrix();

    std::cout << matrix.determinant() << std::endl;

    return 0;
}

