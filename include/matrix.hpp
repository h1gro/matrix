#pragma once

#include <algorithm>
#include <limits>
#include <cmath>
#include <cassert>

namespace matrix
{
template<typename type>
constexpr type EPS()
{
    return static_cast<type>(100) * std::numeric_limits<type>::epsilon();
}

template <typename type = long double >
class Matrix
{
private:

    size_t columns, rows;
    type** data;
    type   det_coef;

public:

    //constructor with initializer list
    Matrix(std::initializer_list<std::initializer_list<type>> init_list): columns(init_list.begin()->size()), rows(init_list.size()), det_coef(1)
    {
        if (init_list.size() == 0) {return;}

        for (const auto& row : init_list)
            if (row.size() != columns) {throw std::invalid_argument("All rows must have the same length");}

        data = new type*[rows];

        size_t i = 0;
        for (const auto& row_list : init_list)
        {
            data[i] = new type[columns];
            size_t j = 0;
            for (const auto& value : row_list)
            {
                data[i][j] = value;
                j++;
            }
            i++;
        }
    }

    //constructor
    Matrix(size_t columns, size_t rows, type** init_data = {}) : columns(columns), rows(rows), det_coef(1)
    {
        data = new type*[rows];

        if (init_data != nullptr)
        {
            for (size_t i = 0; i < rows; i++)
            {
                data[i] = new type[columns];
                for (size_t j = 0; j < columns; j++)
                {
                    data[i][j] = init_data[i][j];
                }
            }
        }

        else
        {
            for (size_t i = 0; i < rows; i++)
            {
                data[i] = new type[columns]{};
            }
        }
    }

    //copy constructor
    Matrix(const Matrix& original_matrix) : columns(original_matrix.columns), rows(original_matrix.rows), det_coef(1)
    {
        data = new type*[rows];

        for (size_t i = 0; i < rows; i++)
        {
            data[i] = new type[columns]{};

            std::copy(original_matrix.data[i], original_matrix.data[i] + columns, data[i]);
        }
    }

    //move constructor
    Matrix(Matrix&& original_matrix) noexcept : columns(original_matrix.columns), rows(original_matrix.rows), data(original_matrix.data), det_coef(1)
    {
        original_matrix.data    = nullptr;
        original_matrix.columns = 0;
        original_matrix.rows    = 0;
    }

    //copy assignment
    Matrix& operator=(const Matrix& original_matrix)
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
    Matrix& operator=(Matrix&& original_matrix) noexcept
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

    type determinant ();

    //метод класса - для дебага!
    void print_matrix   () const;
    void GaussAlgorithm (); //хотим уметь применять алгоритм гаусса для приведения матрицы к даигональному виду без вычисления детерминанта

    size_t get_columns () const {return columns;}
    size_t get_rows    () const {return rows;   }
    type** get_data    () const {return data;   }

    bool is_matrix_square () const;

private:
    // методы - этапы алгоритма Гаусса не обязательно добавлять в public, пусть реализация алгоритма Гаусса будет скрыта
    void StraightGaussAlgorithm  ();
    void ReverseGaussAlgorithm   ();

    void mull_row_by_num (type* row, type number);
    void rows_addition   (type* row1, type* row2, type multiply_coefficient);
    void rows_swap       (type** row1, type** row2);

    type diagonal_determinant ();
};

template <typename type>
type Matrix<type>::determinant()
{
    Matrix copy_matrix(*this);

    copy_matrix.StraightGaussAlgorithm();

    type determinant = copy_matrix.diagonal_determinant();

    if (fabs(determinant) < EPS<type>()){return 0;}
    else {return determinant;}
}

template <typename type>
void Matrix<type>::GaussAlgorithm()
{
    //Алгоритм приведения матрицы к E, путем последовательного применения
    //прямого хода Гаууса и обратного

    StraightGaussAlgorithm();
    ReverseGaussAlgorithm ();
}

//Прямой ход Гаусса
template <typename type>
void Matrix<type>::StraightGaussAlgorithm()
{
    // Прямой ход Гаусса -> верхнетреугольная матрица
    const size_t n = std::min(rows, columns);

    for (size_t j = 0; j < n; ++j)
    {
        size_t piv = j;
        type max_abs = std::fabs(data[j][j]);

        for (size_t i = j + 1; i < rows; ++i)
        {
            const type v = std::fabs(data[i][j]);
            if (v > max_abs) { max_abs = v; piv = i; }
        }

        // столбец почти нулевой — пропускаем
        if (max_abs <= EPS<type>()){continue;}

        if (piv != j)
        {
            rows_swap(&data[piv], &data[j]); // det_coef *= -1
        }

        const type pivot = data[j][j];

        for (size_t i = j + 1; i < rows; ++i)
        {
            if (std::fabs(data[i][j]) <= EPS<type>())
                continue;

            const type factor = -data[i][j] / pivot;
            rows_addition(data[i], data[j], factor);
            data[i][j] = static_cast<type>(0);
        }
    }
}

//Обратный ход Гаусса, для вычисления детерминанта в нём нет необходимости
template <typename type>
void Matrix<type>::ReverseGaussAlgorithm()
{
    //Алгоритм приведения ступенчатой матрицы к диагональной

    for (int j = columns - 1; j >= 0; j--)
    {
        for (int i = j - 1; i >= 0 ; i--)
        {
            //std::cout << "------------------------" << std::endl;
            //std::cout << "удаляю последний элемент строки вычитая из строки самую нижнюю" << std::endl << "j: " << j << "; i: " << i << std::endl;
            rows_addition(data[i], data[j], (-1) * data[i][j]);
            //print_matrix();
        }
    }
}

template <typename type>
void Matrix<type>::mull_row_by_num(type* row, type number)
{
    assert(row);

    //std::cout << "number : " << number << std::endl;

    if (std::fabs(number) <= EPS<type>())
    {
        std::cerr << "We must not multiply by zero!\n";
        return;
    }

    for (size_t i = 0; i < columns; ++i)
    {
        row[i] *= number;
    }

    det_coef /= number;

    //std::cout << "det coef = " << det_coef << std::endl;
}

template <typename type>
void Matrix<type>::rows_addition(type* row1, type* row2, type multiply_coefficient)
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

    //swap строк изменяет знак детерминанта матрицы
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

    //std::cout << determinant << std::endl;
    return determinant * det_coef;
}

template <typename type>
bool Matrix<type>::is_matrix_square() const
{
    if (columns == rows)
        return true;
    else
        return false;
}

template <typename type>
void Matrix<type>::print_matrix() const
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cout << data[i][j]  << "\t";
        }
        std::cout << std::endl;
    }
}
}

