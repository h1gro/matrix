#pragma once

#include <iostream>
#include "matrix.hpp"

namespace matrix
{

// template <typename type>
// void print_matrix(const Matrix<type>& matrix);

template <typename type>
void print_matrix(const Matrix<type>& matrix)
{
    type** data = matrix.get_data();
    assert(data != nullptr);

    size_t columns = matrix.get_columns();
    size_t rows    = matrix.get_rows();

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cout << data[i][j]  << "\t";
        }
        std::cout << std::endl;
    }
}

template <typename type>
void filling_matrix(const Matrix<type>& matrix)
{
    type** data = matrix.get_data();
    assert(data != nullptr);

    size_t columns = matrix.get_columns();
    size_t rows    = matrix.get_rows();

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cin >> data[i][j];
        }
    }
}

template <typename type>
bool is_matrices_equal(const Matrix<type>& matrix1, const Matrix<type>& matrix2)
{
    type** data1 = matrix1.get_data();
    type** data2 = matrix2.get_data();

    size_t columns1 = matrix1.get_columns();
    size_t rows1    = matrix1.get_rows();

    // size_t columns2 = matrix2.get_columns();
    // size_t rows2    = matrix2.get_rows();

    assert((data1 != nullptr) && (data2 != nullptr));
    // assert(columns1 == columns2);
    // assert(rows1    == rows2);

    for (size_t i = 0; i < rows1; i++)
    {
        for (size_t j = 0; j < columns1; j++)
        {
            if (data1[i][j] != data2[i][j])
                return false;
        }
    }

    return true;
}
}
