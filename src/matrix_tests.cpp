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
    matrix::Matrix<long double> matrix(TEST_COLUMNS, TEST_ROWS);

    EXPECT_EQ(matrix.get_columns(), TEST_COLUMNS);
    EXPECT_EQ(matrix.get_rows(), TEST_ROWS);
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

TEST (MatrixAlgebraTest, Determinant_1x1)
{
    matrix::Matrix<long double> matrix({{153}});

    //EXPECT_EQ(matrix.determinant(), 153);
    EXPECT_NEAR(matrix.determinant(), 153, 1e-6);
}

TEST (MatrixAlgebraTest, det_E_2x2)
{
    matrix::Matrix<long double> matrix({{1, 0},
                                   {0, 1}});

    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST (MatrixAlgebraTest, Determinant_2x2)
{
    matrix::Matrix<long double> matrix({{1, 1},
                                   {1, 1}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST (MatrixAlgebraTest, Determinant_3x3)
{
    matrix::Matrix<long double> matrix({{2, 3, 2},
                                  {5, 1, 3},
                                  {2, 2, 3}});

    //EXPECT_EQ(matrix.determinant(), -17);
    EXPECT_NEAR(matrix.determinant(), -17, 1e-6);
}

TEST (MatrixAlgebraTest, Determinant_4x4)
{
    matrix::Matrix<long double> matrix({{1, 2, 2, 1},
                                  {0, 8, 9, 7},
                                  {5, 5, 5, 5},
                                  {8, 2, 1, 1}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST (MatrixAlgebraTest, Determinant_5x5)
{
    matrix::Matrix<long double> matrix({{1, 2, 3, 4, 5},
                                  {2, 3, 4, 5, 1},
                                  {3, 4, 5, 1, 2},
                                  {4, 5, 1, 2, 3},
                                  {5, 1, 2, 3, 4}});

    //EXPECT_EQ(matrix.determinant(), 1875);
    EXPECT_NEAR(matrix.determinant(), 1875, 1e-6);
}

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

TEST(MatrixAlgebraTest, Determinant_1x1_Zero) {
    matrix::Matrix<long double> matrix({{0}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_2x2_Negative) {
    matrix::Matrix<long double> matrix({{-1, 2},
                                  {3, -4}});

    //EXPECT_EQ(matrix.determinant(), -2);
    EXPECT_NEAR(matrix.determinant(), -2, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_2x2_Zero) {
    matrix::Matrix<long double> matrix({{1, 2},
                                  {2, 4}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_Positive) {
    matrix::Matrix<long double> matrix({{2, 1, 3},
                                  {1, 0, 2},
                                  {3, 2, 1}});

    //EXPECT_EQ(matrix.determinant(), 3);
    EXPECT_NEAR(matrix.determinant(), 3, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_Identity) {
    matrix::Matrix<long double> matrix({{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}});

    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_UpperTriangular) {
    matrix::Matrix<long double> matrix({{2, 1, 4},
                                  {0, 3, 1},
                                  {0, 0, 5}});

    //EXPECT_EQ(matrix.determinant(), 30);
    EXPECT_NEAR(matrix.determinant(), 30, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_LowerTriangular) {
    matrix::Matrix<long double> matrix({{2, 0, 0},
                                  {1, 3, 0},
                                  {4, 2, 5}});

    //EXPECT_EQ(matrix.determinant(), 30);
    EXPECT_NEAR(matrix.determinant(), 30, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Identity) {
    matrix::Matrix<long double> matrix({{1, 0, 0, 0},
                                  {0, 1, 0, 0},
                                  {0, 0, 1, 0},
                                  {0, 0, 0, 1}});

    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Zero) {
    matrix::Matrix<long double> matrix({{1, 2, 3, 4},
                                  {2, 4, 6, 8},
                                  {3, 6, 9, 12},
                                  {4, 8, 12, 16}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Negative) {
    matrix::Matrix<long double> matrix({{-1, 2, -3, 4},
                                  {1, -2, 3, -4},
                                  {2, -1, 4, -3},
                                  {3, -4, 1, -2}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Triangular) {
    matrix::Matrix<long double> matrix({{2, 0, 0, 0},
                                  {1, 3, 0, 0},
                                  {4, 2, 1, 0},
                                  {3, 1, 2, 5}});

    //EXPECT_EQ(matrix.determinant(), 30);
    EXPECT_NEAR(matrix.determinant(), 30, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Block) {
    matrix::Matrix<long double> matrix({{1, 2, 0, 0},
                                  {3, 4, 0, 0},
                                  {0, 0, 2, 1},
                                  {0, 0, 3, 5}});

    //EXPECT_EQ(matrix.determinant(), -14);
    EXPECT_NEAR(matrix.determinant(), -14, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_5x5_Identity)
{
    matrix::Matrix<long double> matrix({{1, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 0},
                                  {0, 0, 1, 0, 0},
                                  {0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 1}});

    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_5x5_Zero) {
    matrix::Matrix<long double> matrix({{1, 2, 3, 4, 5},
                                  {2, 4, 6, 8, 10},
                                  {3, 6, 9, 12, 15},
                                  {4, 8, 12, 16, 20},
                                  {5, 10, 15, 20, 25}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_5x5_Triangular)
{
    matrix::Matrix<long double> matrix({{2, 0, 0, 0, 0},
                                  {1, 3, 0, 0, 0},
                                  {4, 2, 1, 0, 0},
                                  {3, 1, 2, 5, 0},
                                  {0, 2, 1, 3, 4}});

    //EXPECT_EQ(matrix.determinant(), 120);
    EXPECT_NEAR(matrix.determinant(), 120, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_6x6)
{
    matrix::Matrix<long double> matrix({{1, 0, 0, 0, 0, 0},
                                  {0, 2, 0, 0, 0, 0},
                                  {0, 0, 3, 0, 0, 0},
                                  {0, 0, 0, 4, 0, 0},
                                  {0, 0, 0, 0, 5, 0},
                                  {0, 0, 0, 0, 0, 6}});

    //EXPECT_EQ(matrix.determinant(), 720);
    EXPECT_NEAR(matrix.determinant(), 720, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_6x6_ZeroRow) {
    matrix::Matrix<long double> matrix({{1, 2, 3, 4, 5, 6},
                                  {2, 3, 4, 5, 6, 7},
                                  {3, 4, 5, 6, 7, 8},
                                  {4, 5, 6, 7, 8, 9},
                                  {5, 6, 7, 8, 9, 10},
                                  {0, 0, 0, 0, 0, 0}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_6x6_Toeplitz) {
    matrix::Matrix<long double> matrix({{2, 1, 0, 0, 0, 0},
                                  {3, 2, 1, 0, 0, 0},
                                  {0, 3, 2, 1, 0, 0},
                                  {0, 0, 3, 2, 1, 0},
                                  {0, 0, 0, 3, 2, 1},
                                  {0, 0, 0, 0, 3, 2}});

    //EXPECT_EQ(matrix.determinant(), 13);
    EXPECT_NEAR(matrix.determinant(), 13, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_6x6_Circulant)
{
    matrix::Matrix<long double> matrix({{1, 2, 3, 4, 5, 6},
                                   {6, 1, 2, 3, 4, 5},
                                   {5, 6, 1, 2, 3, 4},
                                   {4, 5, 6, 1, 2, 3},
                                   {3, 4, 5, 6, 1, 2},
                                   {2, 3, 4, 5, 6, 1}});

    //EXPECT_EQ(matrix.determinant(), -27216);
    EXPECT_NEAR(matrix.determinant(), -27216, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_7x7)
{
    matrix::Matrix<long double> matrix({{1, 0, 0, 0, 0, 0, 0},
                                   {0, 2, 0, 0, 0, 0, 0},
                                   {0, 0, 1, 0, 0, 0, 0},
                                   {0, 0, 0, 3, 0, 0, 0},
                                   {0, 0, 0, 0, 1, 0, 0},
                                   {0, 0, 0, 0, 0, 4, 0},
                                   {0, 0, 0, 0, 0, 0, 1}});

    //EXPECT_EQ(matrix.determinant(), 24);
    EXPECT_NEAR(matrix.determinant(), 24, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_7x7_Ones)
{
    matrix::Matrix<long double> matrix({{1, 1, 1, 1, 1, 1, 1},
                                  {1, 1, 1, 1, 1, 1, 1},
                                  {1, 1, 1, 1, 1, 1, 1},
                                  {1, 1, 1, 1, 1, 1, 1},
                                  {1, 1, 1, 1, 1, 1, 1},
                                  {1, 1, 1, 1, 1, 1, 1},
                                  {1, 1, 1, 1, 1, 1, 1}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_10x10_BlockDiagonal)
{
    matrix::Matrix<long double> matrix({
        {1, 2, 3, 4, 5, 6, 0, 0, 0, 0},
        {6, 1, 2, 3, 4, 5, 0, 0, 0, 0},
        {5, 6, 1, 2, 3, 4, 0, 0, 0, 0},
        {4, 5, 6, 1, 2, 3, 0, 0, 0, 0},
        {3, 4, 5, 6, 1, 2, 0, 0, 0, 0},
        {2, 3, 4, 5, 6, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 6}
    });

    //EXPECT_EQ(matrix.determinant(), -979776);
    EXPECT_NEAR(matrix.determinant(), -979776, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_100x100_Zero)
{
    matrix::Matrix<long double> matrix(100, 100);

    long double** data = matrix.get_data();

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            data[i][j] = 0.0;
        }
    }
    //EXPECT_EQ(matrix.determinant(), 0.0);
    EXPECT_NEAR(matrix.determinant(), 0.0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_100x100_E)
{
    matrix::Matrix<long double> matrix(100, 100);

    long double** data = matrix.get_data();

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (i == j)
                data[i][j] = 1;
        }
    }
    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_1000x1000_Zero)
{
    matrix::Matrix<long double> matrix(1000, 1000);

    long double** data = matrix.get_data();

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            data[i][j] = 0;
        }
    }
    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_1000x1000_E)
{
    matrix::Matrix<long double> matrix(1000, 1000);

    long double** data = matrix.get_data();

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (i == j)
                data[i][j] = 1;
        }
    }
    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}
