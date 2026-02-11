#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include "../include/matrix.hpp"
#include "../include/utilits.hpp"

namespace e2e_tests
{

const char* TEST_FILE_1 = "tests_proc/tests/001.dat";
const char* TEST_FILE_2 = "tests_proc/tests/002.dat";
const char* TEST_FILE_3 = "tests_proc/tests/003.dat";
const char* TEST_FILE_4 = "tests_proc/tests/004.dat";
const char* TEST_FILE_5 = "tests_proc/tests/005.dat";
const char* TEST_FILE_6 = "tests_proc/tests/006.dat";
const char* TEST_FILE_7 = "tests_proc/tests/007.dat";
const char* TEST_FILE_8 = "tests_proc/tests/008.dat";
const char* TEST_FILE_9 = "tests_proc/tests/009.dat";

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
TEST(MatrixAlgebraTest, Determinant_1x1_Zero)
{
    matrix::Matrix<long double> matrix({{0}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_2x2_Negative)
{
    matrix::Matrix<long double> matrix({{-1, 2},
                                  {3, -4}});

    //EXPECT_EQ(matrix.determinant(), -2);
    EXPECT_NEAR(matrix.determinant(), -2, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_2x2_Zero)
{
    matrix::Matrix<long double> matrix({{1, 2},
                                  {2, 4}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_Positive)
{
    matrix::Matrix<long double> matrix({{2, 1, 3},
                                  {1, 0, 2},
                                  {3, 2, 1}});

    //EXPECT_EQ(matrix.determinant(), 3);
    EXPECT_NEAR(matrix.determinant(), 3, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_Identity)
{
    matrix::Matrix<long double> matrix({{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}});

    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_UpperTriangular)
{
    matrix::Matrix<long double> matrix({{2, 1, 4},
                                  {0, 3, 1},
                                  {0, 0, 5}});

    //EXPECT_EQ(matrix.determinant(), 30);
    EXPECT_NEAR(matrix.determinant(), 30, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_3x3_LowerTriangular)
{
    matrix::Matrix<long double> matrix({{2, 0, 0},
                                  {1, 3, 0},
                                  {4, 2, 5}});

    //EXPECT_EQ(matrix.determinant(), 30);
    EXPECT_NEAR(matrix.determinant(), 30, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Identity)
{
    matrix::Matrix<long double> matrix({{1, 0, 0, 0},
                                  {0, 1, 0, 0},
                                  {0, 0, 1, 0},
                                  {0, 0, 0, 1}});

    //EXPECT_EQ(matrix.determinant(), 1);
    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Zero)
{
    matrix::Matrix<long double> matrix({{1, 2, 3, 4},
                                  {2, 4, 6, 8},
                                  {3, 6, 9, 12},
                                  {4, 8, 12, 16}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Negative)
{
    matrix::Matrix<long double> matrix({{-1, 2, -3, 4},
                                  {1, -2, 3, -4},
                                  {2, -1, 4, -3},
                                  {3, -4, 1, -2}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Triangular)
{
    matrix::Matrix<long double> matrix({{2, 0, 0, 0},
                                  {1, 3, 0, 0},
                                  {4, 2, 1, 0},
                                  {3, 1, 2, 5}});

    //EXPECT_EQ(matrix.determinant(), 30);
    EXPECT_NEAR(matrix.determinant(), 30, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_4x4_Block)
{
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

TEST(MatrixAlgebraTest, Determinant_5x5_Zero)
{
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

TEST(MatrixAlgebraTest, Determinant_6x6_ZeroRow)
{
    matrix::Matrix<long double> matrix({{1, 2, 3, 4, 5, 6},
                                  {2, 3, 4, 5, 6, 7},
                                  {3, 4, 5, 6, 7, 8},
                                  {4, 5, 6, 7, 8, 9},
                                  {5, 6, 7, 8, 9, 10},
                                  {0, 0, 0, 0, 0, 0}});

    //EXPECT_EQ(matrix.determinant(), 0);
    EXPECT_NEAR(matrix.determinant(), 0, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_6x6_Toeplitz)
{
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

TEST(MatrixAlgebraTest, Determinant_2x2_001dat)
{
    std::ifstream test(TEST_FILE_1);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    matrix.print_matrix();

    EXPECT_NEAR(matrix.determinant(), -1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_100x100_002dat)
{
    std::ifstream test(TEST_FILE_2);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 42, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_100x100_003dat)
{
    std::ifstream test(TEST_FILE_3);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 1, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_100x100_004dat)
{
    std::ifstream test(TEST_FILE_4);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 137, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_200x200_005dat)
{
    std::ifstream test(TEST_FILE_5);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 199, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_200x200_006dat)
{
    std::ifstream test(TEST_FILE_6);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 157, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_200x200_007dat)
{
    std::ifstream test(TEST_FILE_7);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 199, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_500x500_008dat)
{
    std::ifstream test(TEST_FILE_8);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 157, 1e-6);
}

TEST(MatrixAlgebraTest, Determinant_500x500_009dat)
{
    std::ifstream test(TEST_FILE_9);

    size_t size = 0;
    test >> size;

    matrix::Matrix<long double> matrix(size, size);

    filling_matrix_from_file(matrix, test);

    test.close();

    EXPECT_NEAR(matrix.determinant(), 173, 1e-6);
}

}
