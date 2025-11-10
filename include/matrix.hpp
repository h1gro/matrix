#ifndef MATRIX
#define MATRIX

#include <algorithm>

template <typename type>
class Matrix
{
private:

    size_t columns, rows;
    type** data;

public:

    //constructor
    Matrix(size_t columns, size_t rows) : columns(columns), rows(rows)
    {
        data = new type*[rows];

        for (size_t i = 0; i < rows; i++)
        {
            data[i] = new type[columns]{};
        }
    }

    //copy constructor
    Matrix(const Matrix<type>& original_matrix) : columns(original_matrix.columns), rows(original_matrix.rows)
    {
        data = new type*[rows];

        for (size_t i = 0; i < rows; i++)
        {
            data[i] = new type[columns]{};

            std::copy(original_matrix.data[i], original_matrix.data[i] + columns, data[i]);
        }
    }

    //move constructor
    Matrix(Matrix<type>&& original_matrix) : columns(original_matrix.columns), rows(original_matrix.rows), data(original_matrix.data)
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

    void print_matrix();
    void filling_matrix();
};

template <typename type>
void Matrix<type>::print_matrix()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cout << data[i][j]  << " ";
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
