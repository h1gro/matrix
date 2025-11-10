#include <iostream>
#include "../include/matrix.hpp"

int main()
{
    size_t matrix_size = 0;
    std::cin >> matrix_size;

    Matrix<int> matrix(matrix_size, matrix_size);
    Matrix<int> matrix2(matrix_size, matrix_size);
    Matrix<int> matrix3(matrix_size, matrix_size);

    matrix.filling_matrix();

    //old----------------------------------
    std::cout << "old\n" << "matrix:" << std::endl;

    matrix.print_matrix();

    std::cout << "matrix2:" << std::endl;

    matrix2.print_matrix();

    std::cout << "matrix3:" << std::endl;

    matrix3.print_matrix();

    //----------------------------------------

    matrix2 = matrix;

    matrix3 = std::move(matrix);

    //new-----------------------------------
    std::cout << "new\n" <<"matrix:" << std::endl;

    matrix.print_matrix();

    std::cout << "matrix2:" << std::endl;

    matrix2.print_matrix();

    std::cout << "matrix3:" << std::endl;

    matrix3.print_matrix();

    //------------------------------------
    return 0;
}
