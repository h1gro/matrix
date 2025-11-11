#ifndef MATRIX
#define MATRIX

#include <algorithm>
#include <cmath>
#include <cassert>

const float EPSILON = 1e-8;

template <typename type = float >
class Matrix
{
private:

    type** data;
    size_t columns, rows;
    float  det_coef;

public:

    //constructor
    Matrix(size_t columns, size_t rows) : columns(columns), rows(rows), det_coef(1)
    {
        data = new type*[rows];

        for (size_t i = 0; i < rows; i++)
        {
            data[i] = new type[columns]{};
        }
    }

    //copy constructor
    Matrix(const Matrix<type>& original_matrix) : columns(original_matrix.columns), rows(original_matrix.rows), det_coef(1)
    {
        data = new type*[rows];

        for (size_t i = 0; i < rows; i++)
        {
            data[i] = new type[columns]{};

            std::copy(original_matrix.data[i], original_matrix.data[i] + columns, data[i]);
        }
    }

    //move constructor
    Matrix(Matrix<type>&& original_matrix) : columns(original_matrix.columns), rows(original_matrix.rows), data(original_matrix.data), det_coef(1)
    {
        original_matrix.data    = nullptr;
        original_matrix.columns = 0;
        original_matrix.rows    = 0;
    }

    //copy assignment
    Matrix& operator=(const Matrix<type>& original_matrix)
    {
        if ((original_matrix.columns == columns) &&
            (original_matrix.rows    == rows)    &&
            (this                    != &original_matrix))

            for (size_t i = 0; i < rows; i++)
            {
                std::copy(original_matrix.data[i], original_matrix.data[i] + columns, data[i]);
            }

        else
        {
            std::cerr << "Error in copy assignment!" << std::endl;
        }

        return *this;
    }

    //move assignment
    Matrix& operator=(Matrix<type>&& original_matrix)
    {
        if ((original_matrix.columns == this->columns) &&
            (original_matrix.rows    == this->rows)    &&
            (this                    != &original_matrix))
        {
            data = original_matrix.data;

            original_matrix.data    = nullptr;
            original_matrix.columns = 0;
            original_matrix.rows    = 0;
        }

        else
        {
            std::cerr << "Error in move assignment!" << std::endl;
        }

        return *this;
    }

    //destructor
    ~Matrix()
    {
        for (size_t i = 0; i < rows; i++)
        {
            delete [] data[i];
        }

        delete [] data;
    }

    void print_matrix            ();
    void filling_matrix          ();
    void StraightGaussAlgorithm  ();
    void ReverseGaussAlgorithm   ();
    void GaussAlgorithm          ();

    void mull_row_by_num (type* row, float number);
    void rows_addition   (type* row1, type* row2, auto multiply_coefficient);
    void rows_swap       (type** row1, type** row2);

    type diagonal_determinant();
    type determinant         ();

    bool is_matrix_square();

    size_t get_columns() {return columns;}
    size_t get_rows   () {return rows;   }
};

template <typename type>
type Matrix<type>::determinant()
{
    Matrix copy_matrix(*this);

    copy_matrix.GaussAlgorithm();

    return copy_matrix.diagonal_determinant();
}

template <typename type>
void Matrix<type>::GaussAlgorithm()
{
    StraightGaussAlgorithm();
    ReverseGaussAlgorithm ();
}

template <typename type>
void Matrix<type>::StraightGaussAlgorithm()
{
    bool unit_flag = false;
    bool zero_flag = true;

    size_t non_zero_elem = 0;

    for (size_t j = 0; j < columns - 1; j++)
    {
        for (size_t i = j; i < rows; i++)
        {
            if (fabs(data[i][j]) > EPSILON)
                non_zero_elem = i;
                zero_flag = false;

            if (data[i][j] == 1)
            {
                std::cout << "------------------------" << std::endl;
                std::cout << "нашёл строку с единичкой - первым элементом" << std::endl;

                rows_swap(&data[i], &data[j]);
                print_matrix();
                unit_flag = true;
                break;
            }

            else if (data[i][j] == -1)
            {
                std::cout << "------------------------" << std::endl;
                std::cout << "нашёл строку с минус единичкой - первым элементом" << std::endl;

                mull_row_by_num(data[i], (-1));
                print_matrix();

                std::cout << "------------------------" << std::endl;
                std::cout << "свапаю строчки" << std::endl;

                rows_swap(&data[i], &data[j]);
                print_matrix();
                unit_flag = true;
                break;
            }
        }

        if (!zero_flag)
        {
            if (fabs(data[j][j]) < EPSILON)
            {
                std::cout << "------------------------" << std::endl;
                std::cout << "первую лок строку если нулевая кидаю вниз" << std::endl;
                rows_swap(&data[j], &data[non_zero_elem]);
                print_matrix();
            }

            if (!unit_flag)
            {
                std::cout << "------------------------" << std::endl;
                std::cout << "первый элемент строки делаю единицей" << std::endl;
                mull_row_by_num(data[j], 1.0 / data[j][j]);
                print_matrix();
            }

            std::cout << " j = " << j << std::endl;
            for (size_t i = j + 1; i < rows; i++)
            {
                std::cout << "------------------------" << std::endl;
                std::cout << "вычитаю из i-ой строки локальную первую умноженную на коэф" << std::endl;
                rows_addition(data[i], data[j], (-1) * data[i][j]);
                print_matrix();
            }
        }
        zero_flag = true;
        unit_flag = false;
    }

    std::cout << "------------------------" << std::endl;
    std::cout << "первый элемент строки делаю единицей" << std::endl;
    mull_row_by_num(data[columns - 1], 1.0 / data[columns - 1][columns - 1]);
    print_matrix();
}

template <typename type>
void Matrix<type>::ReverseGaussAlgorithm()
{
    for (int j = columns - 1; j >= 0; j--)
    {
        for (int i = j - 1; i >= 0 ; i--)
        {
            std::cout << "------------------------" << std::endl;
            std::cout << "удаляю последний элемент строки вычитая из строки самую нижнюю" << std::endl << "j: " << j << "; i: " << i << std::endl;
            rows_addition(data[i], data[j], (-1) * data[i][j]);
            print_matrix();
        }
    }
}

template <typename type>
void Matrix<type>::mull_row_by_num(type* row, float number)
{
    assert(row);

    std::cout << "number : " << number << std::endl;

    if (fabs(number) > EPSILON)
    {
        for (size_t i = 0; i < columns; i++)
        {
            if (fabs(row[i]) > EPSILON)
                row[i] *= number;
        }

        det_coef /= number;
        std::cout << "det coef = " << det_coef << std::endl;
    }

    else
    {
        std::cerr << "We must not multiply by zero!" << std::endl;
    }

}

template <typename type>
void Matrix<type>::rows_addition(type* row1, type* row2, auto multiply_coefficient)
{
    assert(row1);
    assert(row2);

    for (size_t i = 0; i < columns; i++)
    {
        row1[i] += (multiply_coefficient * row2[i]);
    }
}

template <typename type>
void Matrix<type>::rows_swap(type** row1, type** row2)
{
    assert(*row1);
    assert(*row2);

    type* fictitious_row = *row1;
                    *row1 = *row2;
                    *row2 = fictitious_row;

    det_coef *= (-1);
}

template <typename type>
type Matrix<type>::diagonal_determinant()
{
    assert(det_coef);

    if (!is_matrix_square())
    {
        std::cerr << "The matrix is not square!" << std::endl;
        return 0;
    }

    type determinant = 1;

    for (size_t i = 0; i < columns; i++)
    {
        determinant *= data[i][i];
    }

    std::cout << determinant << std::endl;
    return determinant * det_coef;
}

template <typename type>
bool Matrix<type>::is_matrix_square()
{
    if (columns == rows)
        return true;
    else
        return false;
}

template <typename type>
void Matrix<type>::print_matrix()
{
    //std::cout << "------------------------" << std::endl;
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
void Matrix<type>::filling_matrix()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cin >> data[i][j];
        }
    }
}

#endif
