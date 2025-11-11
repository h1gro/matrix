#include <iostream>
#include <gtest/gtest.h>
#include "../include/matrix.hpp"

enum test_values
{
    TEST_COLUMNS = 5,
    TEST_ROWS    = 3,
};

TEST (MatrixTest, Constructor)
{
    Matrix<int> matrix(TEST_COLUMNS, TEST_ROWS);

    EXPECT_EQ(matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix.get_rows(), TEST_ROWS);
}

TEST (MatrixTest, CopyConstructor)
{
    Matrix<int> matrix(TEST_COLUMNS, TEST_ROWS);

    Matrix<int> copy_matrix(matrix);

    //TODO filling

    EXPECT_EQ(copy_matrix.get_columns(), matrix.get_columns());
    EXPECT_EQ(copy_matrix.get_rows(),    matrix.get_rows());
}

TEST (MatrixTest, MoveConstructor)
{
    Matrix<int> matrix(TEST_COLUMNS, TEST_ROWS);
    Matrix<int> move_matrix(std::move(matrix));

    //TODO filling

    EXPECT_EQ(move_matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(move_matrix.get_rows(),    TEST_ROWS);
}

TEST (MatrixTest, CopyAssignment)
{
    Matrix<int> matrix1(TEST_COLUMNS, TEST_ROWS);
    Matrix<int> matrix2(TEST_COLUMNS, TEST_ROWS);

    //TODO filling

    matrix2 = matrix1;

    EXPECT_EQ(matrix1.get_columns(), matrix2.get_columns());
    EXPECT_EQ(matrix1.get_rows(),    matrix2.get_rows());
}

TEST (MatrixTest, MoveAssignment)
{
    Matrix<int> matrix1(TEST_COLUMNS, TEST_ROWS);
    Matrix<int> matrix2(TEST_COLUMNS, TEST_ROWS);

    //TODO filling

    matrix2 = std::move(matrix1);

    EXPECT_EQ(matrix2.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix2.get_rows(),    TEST_ROWS);
}