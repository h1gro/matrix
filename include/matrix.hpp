#pragma once

#include <algorithm>
#include <limits>
#include <cmath>
#include <cassert>

//const float EPSILON = 1e-10;

namespace matrix
{

template<typename type>
constexpr type EPS()
{
    return static_cast<type>(100) * std::numeric_limits<type>::epsilon();
}

template <typename type = double >
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

    void mull_row_by_num (type* row, type number);
    void rows_addition   (type* row1, type* row2, type multiply_coefficient);
    void rows_swap       (type** row1, type** row2);

    type diagonal_determinant ();
    type determinant          ();

    bool is_matrix_square ();

    size_t get_columns () {return columns;}
    size_t get_rows    () {return rows;   }
};

template <typename type>
type Matrix<type>::determinant()
{
    Matrix copy_matrix(*this);

    copy_matrix.GaussAlgorithm();

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

template <typename type>
void Matrix<type>::StraightGaussAlgorithm()
{
    //Алгоритм приведения матрицы к ступенчатому виду

    //default состояния флагов
    bool unit_flag = false; //показывает есть ли единица в столбце
    bool zero_flag = true;  //показывает все ли элементы столбцы - нули

    size_t non_zero_elem = 0;

    for (size_t j = 0; j < columns - 1; j++)
    {
        //перехожу к подматрице jxj
        for (size_t i = j; i < rows; i++)
        {
            //проверяем есть ли в текущем столбце ненулевой элемент, если нет, то флаг zero_flag останется выставленным
            //в true [zero_flag = true - столбец весь из нулей, = false - есть хотя бы один ненулевой элемент]
            if (fabs(data[i][j]) > EPS<type>())
            {
                non_zero_elem = i; //запоминаем ненулевой элемент (вдруг он будет единственным)
                zero_flag = false;
            }

            //нашли строку в подматрице с первым элементом - единичкой
            if (data[i][j] == 1)
            {
                //std::cout << "------------------------" << std::endl;
                //std::cout << "нашёл строку с единичкой - первым элементом" << std::endl;

                //перемещаем строку с первым элементом - единичкой наверх подматрицы
                if (data[j][j] != 1) {rows_swap(&data[i], &data[j]);}
                //print_matrix();

                //флаг - найдена строка с единицей
                unit_flag = true;
                break;
            }

            //аналогично со строкой с отрицательной единицей
            else if (data[i][j] == -1)
            {
                //std::cout << "------------------------" << std::endl;
                //std::cout << "нашёл строку с минус единичкой - первым элементом" << std::endl;

                //домножаем всю строку на минус единицу
                mull_row_by_num(data[i], (-1));
                //print_matrix();

                //std::cout << "------------------------" << std::endl;
                //std::cout << "свапаю строчки" << std::endl;

                //перемещаем строку с первым элементом - единичкой наверх подматрицы
                if (data[j][j] != 1) {rows_swap(&data[i], &data[j]);}
                //print_matrix();

                //флаг - найдена строка с единицей
                unit_flag = true;
                break;
            }
        }

        //если есть хотя бы один ненулевой элемент, то выполнится тело if
        if (!zero_flag)
        {
            if (fabs(data[j][j]) < EPS<type>())
            {
                //std::cout << "------------------------" << std::endl;
                //std::cout << "первую лок строку если нулевая кидаю вниз" << std::endl;

                //перемещаем строку с нулевым элементом в самый низ подматрицы
                rows_swap(&data[j], &data[non_zero_elem]);
                //print_matrix();
            }

            //если в столбце нет единицы то выполнится тело if
            if (!unit_flag)
            {
                //std::cout << "------------------------" << std::endl;
                //std::cout << "первый элемент строки делаю единицей" << std::endl;

                //домножаем всю строку на коэф, чтоб первый элемент был единицей
                mull_row_by_num(data[j], 1.0 / data[j][j]);
                //print_matrix();
            }

            //зануляем все элементы столбца (кроме первого) путем сложения каждой строки с первой строкой подматрицы,
            //умноженной на некоторый коэф, таким образом получаем столбец (1 0 0 0 ... 0)^T
            if (fabs(data[j][j]) > EPS<type>())
            {
                //std::cout << " j = " << j << std::endl;
                for (size_t i = j + 1; i < rows; i++)
                {
                    //std::cout << "------------------------" << std::endl;
                    //std::cout << "вычитаю из " << i << "-ой строки локальную первую умноженную на коэф " << data[i][j] << std::endl;
                    rows_addition(data[i], data[j], (-1) * data[i][j]);
                    //print_matrix();
                }
            }
        }

        // возвращаем флаги в default состояние
        zero_flag = true;
        unit_flag = false;
    }

    //последний элемент главной диагонали привожу к единице, если он не нулевой
    if (fabs(data[columns - 1][columns - 1]) > EPS<type>())
    {
        //std::cout << "------------------------" << std::endl;
        //std::cout << "первый элемент строки делаю единицей" << std::endl;
        mull_row_by_num(data[columns - 1], 1.0 / data[columns - 1][columns - 1]);
        //print_matrix();
    }
}

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

    if (fabs(number) > EPS<type>())
    {
        for (size_t i = 0; i < columns; i++)
        {
            if (fabs(row[i]) > EPS<type>())
                row[i] *= number;
        }
        //std::cout << "old det coef = " << det_coef << std::endl;

        //домножение строки матрицы на число, увеличивает детерминант матрицы в это число раз
        det_coef /= number;

        //std::cout << "det coef = " << det_coef << std::endl;
    }

    else
    {
        std::cerr << "We must not multiply by zero!" << std::endl;
    }
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
}

