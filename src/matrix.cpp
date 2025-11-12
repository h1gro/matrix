#include <iostream>
#include "../include/matrix.hpp"

int main()
{
    size_t matrix_size = 0;
    std::cin >> matrix_size;

    Matrix<float> matrix(matrix_size, matrix_size);

    matrix.filling_matrix();
    matrix.print_matrix();

    std::cout << matrix.determinant() << std::endl;

    return 0;
}
