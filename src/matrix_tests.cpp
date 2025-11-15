#include <iostream>
#include <gtest/gtest.h>
#include "../include/matrix.hpp"
#include "../include/utilits.hpp"

enum test_values
{
    TEST_COLUMNS = 5,
    TEST_ROWS    = 3,
};

TEST (MatrixInterfaceTest, Constructor)
{
    matrix::Matrix<int> matrix(TEST_COLUMNS, TEST_ROWS);

    EXPECT_EQ(matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix.get_rows(), TEST_ROWS);
}

TEST (MatrixInterfaceTest, CopyConstructor)
{
    matrix::Matrix<int> matrix(TEST_COLUMNS, TEST_ROWS);

    matrix::Matrix<int> copy_matrix(matrix);

    EXPECT_EQ(matrix::is_matrices_equal(matrix, copy_matrix), true);

    EXPECT_EQ(copy_matrix.get_columns(), matrix.get_columns());
    EXPECT_EQ(copy_matrix.get_rows(),    matrix.get_rows());
}

TEST (MatrixInterfaceTest, MoveConstructor)
{
    matrix::Matrix<int> matrix(TEST_COLUMNS, TEST_ROWS);
    matrix::Matrix<int> copy_matrix(matrix);

    matrix::Matrix<int> move_matrix(std::move(matrix));

    EXPECT_EQ(matrix::is_matrices_equal(copy_matrix, move_matrix), true);

    EXPECT_EQ(move_matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(move_matrix.get_rows(),    TEST_ROWS);
}

TEST (MatrixInterfaceTest, CopyAssignment)
{
    matrix::Matrix<int> matrix1(TEST_COLUMNS, TEST_ROWS);
    matrix::Matrix<int> matrix2(TEST_COLUMNS, TEST_ROWS);

    EXPECT_EQ(matrix::is_matrices_equal(matrix1, matrix2), true);

    matrix2 = matrix1;

    EXPECT_EQ(matrix1.get_columns(), matrix2.get_columns());
    EXPECT_EQ(matrix1.get_rows(),    matrix2.get_rows());
}

TEST (MatrixInterfaceTest, MoveAssignment)
{
    matrix::Matrix<int> matrix1(TEST_COLUMNS, TEST_ROWS);
    matrix::Matrix<int> copy_matrix(matrix1);

    matrix::Matrix<int> matrix2(TEST_COLUMNS, TEST_ROWS);

    matrix2 = std::move(matrix1);

    EXPECT_EQ(matrix::is_matrices_equal(copy_matrix, matrix2), true);

    EXPECT_EQ(matrix2.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix2.get_rows(),    TEST_ROWS);
}

TEST (MatrixAlgebraTest, Determinant_1x1)
{
    matrix::Matrix<float> matrix({{153}});

    EXPECT_EQ(matrix.determinant(), 153);
}

TEST (MatrixAlgebraTest, det_E_2x2)
{
    matrix::Matrix<float> matrix({{1, 0},
                                  {0, 1}});

    EXPECT_EQ(matrix.determinant(), 1);
}

TEST (MatrixAlgebraTest, Determinant_2x2)
{
    matrix::Matrix<float> matrix({{1, 1},
                                  {1, 1}});

    EXPECT_EQ(matrix.determinant(), 0);
}

TEST (MatrixAlgebraTest, Determinant_3x3)
{
    matrix::Matrix<float> matrix({{2, 3, 2},
                                  {5, 1, 3},
                                  {2, 2, 3}});

    EXPECT_EQ(matrix.determinant(), -17);
}

TEST (MatrixAlgebraTest, Determinant_4x4)
{
    matrix::Matrix<float> matrix({{1, 2, 2, 1},
                                  {0, 8, 9, 7},
                                  {5, 5, 5, 5},
                                  {8, 2, 1, 1}});

    EXPECT_EQ(matrix.determinant(), 0);
}

TEST (MatrixAlgebraTest, Determinant_5x5)
{
    matrix::Matrix<float> matrix({{1, 2, 3, 4, 5},
                                  {2, 3, 4, 5, 1},
                                  {3, 4, 5, 1, 2},
                                  {4, 5, 1, 2, 3},
                                  {5, 1, 2, 3, 4}});

    EXPECT_EQ(matrix.determinant(), 1875);
}
