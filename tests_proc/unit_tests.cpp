#include <iostream>
#include <gtest/gtest.h>
#include "../include/matrix.hpp"
#include "../include/utilits.hpp"

enum test_values
{
    TEST_COLUMNS = 5,
    TEST_ROWS    = 3,
};

//================================================================
//                   Tests for BIG-5:

TEST (MatrixInterfaceTest, Constructor)
{
    matrix::Matrix<long double> matrix(TEST_COLUMNS, TEST_ROWS);

    EXPECT_EQ(matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix.get_rows(),    TEST_ROWS);
    EXPECT_NE(matrix.get_data(),    nullptr);
}

TEST(MatrixInterfaceTest, Destructor_ScopeExit_NoCrash)
{
    //own scope
    {
        matrix::Matrix<long double> matrix(200, 200);
        auto** data = matrix.get_data();

        data[153][77] = 1;
        data[77][153] = 2;
    } // leave current scope, so the matrix are being destroyed (~Matrix())

    //if we successfully leave the scope - all right
    SUCCEED();
}

TEST(MatrixInterfaceTest, Destructor_AfterMoveConstructor_NoCrash)
{
    {
        matrix::Matrix<long double> matrix(555, 678);
        matrix::Matrix<long double> move_matrix(std::move(matrix));

        EXPECT_EQ(move_matrix.get_columns(), 555);
        EXPECT_EQ(move_matrix.get_rows(),    678);
        EXPECT_NE(move_matrix.get_data(),    nullptr);
    } //similarly previous test
    SUCCEED();
}

TEST(MatrixInterfaceTest, Destructor_AfterMoveAssignment_NoCrash)
{
    {
        matrix::Matrix<long double> matrix(11, 11);
        matrix::Matrix<long double> move_matrix(10, 10);

        move_matrix = std::move(matrix);

        EXPECT_EQ(move_matrix.get_columns(), 11);
        EXPECT_EQ(move_matrix.get_rows(),    11);
        EXPECT_NE(move_matrix.get_data(),    nullptr);
    } //similarly previous test
    SUCCEED();
}

TEST (MatrixInterfaceTest, CopyConstructor)
{
    matrix::Matrix<long double> matrix(TEST_COLUMNS, TEST_ROWS);

    matrix::Matrix<long double> copy_matrix(matrix);

    EXPECT_EQ(matrix::is_matrices_equal(matrix, copy_matrix), true);

    EXPECT_EQ(copy_matrix.get_columns(), matrix.get_columns());
    EXPECT_EQ(copy_matrix.get_rows(),    matrix.get_rows());
}

TEST (MatrixInterfaceTest, MoveConstructor)
{
    matrix::Matrix<long double> matrix(TEST_COLUMNS, TEST_ROWS);
    matrix::Matrix<long double> copy_matrix(matrix);

    matrix::Matrix<long double> move_matrix(std::move(matrix));

    EXPECT_EQ(matrix::is_matrices_equal(copy_matrix, move_matrix), true);

    EXPECT_EQ(move_matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(move_matrix.get_rows(),    TEST_ROWS);
}

TEST (MatrixInterfaceTest, CopyAssignment)
{
    matrix::Matrix<long double> matrix1(TEST_COLUMNS, TEST_ROWS);
    matrix::Matrix<long double> matrix2(TEST_COLUMNS, TEST_ROWS);

    EXPECT_EQ(matrix::is_matrices_equal(matrix1, matrix2), true);

    matrix2 = matrix1;

    EXPECT_EQ(matrix1.get_columns(), matrix2.get_columns());
    EXPECT_EQ(matrix1.get_rows(),    matrix2.get_rows());
}

TEST (MatrixInterfaceTest, MoveAssignment)
{
    matrix::Matrix<long double> matrix1(TEST_COLUMNS, TEST_ROWS);
    matrix::Matrix<long double> copy_matrix(matrix1);

    matrix::Matrix<long double> matrix2(TEST_COLUMNS, TEST_ROWS);

    matrix2 = std::move(matrix1);

    EXPECT_EQ(matrix::is_matrices_equal(copy_matrix, matrix2), true);

    EXPECT_EQ(matrix2.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix2.get_rows(),    TEST_ROWS);
}

//====================================================================

TEST (MatrixAlgebraTest, MatricesSum)
{
   matrix::Matrix<long double> matrix1({{1, 2, 3, 4, 5, 7 },
                                  {2, 3, 4, 5, 1, 0 },
                                  {3, 4, 5, 1, 2, -5},
                                  {4, 5, 1, 2, 3, 9 },
                                  {5, 1, 2, 3, 4, 2 },
                                  {1, 1, 4, 0, -2, 2}});

    matrix::Matrix<long double> matrix2({{7, 2, 4, 1, 1, 8 },
                                   {7, 8, 4, 1, 2, 8 },
                                   {9, 7, 3, 1, 2, 8 },
                                   {7, 9, 5, 0, -4, 7},
                                   {1, 1, 2, 2, 3, 3 },
                                   {0, 9, 5, 5, 1, 2 }});
    //sum
    matrix::Matrix<long double> matrix3({{8, 4, 7, 5, 6, 15 },
                                   {9, 11, 8, 6, 3, 8 },
                                   {12, 11, 8, 2, 4, 3 },
                                   {11, 14, 6, 2, -1, 16},
                                   {6, 2, 4, 5, 7, 5 },
                                   {1, 10, 9, 5, -1, 4 }});

    matrix::Matrix<long double> matrix_sum = std::move(matrix::matrices_sum(matrix1, matrix2));

    EXPECT_EQ(is_matrices_equal(matrix_sum, matrix3), true);
}

