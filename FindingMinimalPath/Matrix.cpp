#include "Matrix.h"

Matrix::Matrix(int16_t rows, int16_t cols) : _rows(rows), _cols(cols)
{
	_size = _rows * _cols;

	if (_size <= 0)
		throw "Incorrected size value";

	_arr_ptr = new uint16_t[_size];
}

Matrix::Matrix(const Matrix& mat)
{
	copy(mat);
}

Matrix::~Matrix()
{
	delete[] _arr_ptr;
}

int16_t Matrix::get_size()
{
	return _size;
}

uint16_t& Matrix::at(int16_t rows, int16_t cols) const
{
	return *(_arr_ptr + rows * _cols + cols);
}

void Matrix::copy(const Matrix& mat)
{
	if (_arr_ptr != nullptr)
		delete[] _arr_ptr;

	_size = mat._size;
	_cols = mat._cols;
	_rows = mat._rows;

	_arr_ptr = new uint16_t[_size];

	for (int16_t i = 0; i < _rows; ++i)
	{
		for (int16_t j = 0; j < _cols; ++j)
		{
			*(_arr_ptr + i * _cols + j) = mat.at(i, j);
		}
	}
}

void Matrix::multiply(const Matrix& mat, bool method)
{
	if (_cols != mat._cols || _rows != mat._rows)
		throw "Matrix must be same size!\n";

	uint16_t min_value = INF;
	uint16_t temp_value = 0;

	int16_t index = -1;
	int16_t count = 0;

	bool is_same_index = false;

	Matrix temp_mat(*this);

	for (int16_t i1 = 0; i1 < _rows; ++i1)
	{
		for (int16_t j = 0, j2 = 0; j < _cols; ++j, ++j2)
		{
			for (int16_t j1 = 0, i2 = 0; j1 < _cols; ++j1, ++i2)
			{
				if (i1 == j)
				{
					if (method == MATRIX_METHOD)	temp_value = 0;
					else							temp_value = INF;

					is_same_index = true;
				}

				else if (i1 == i2 && j1 == j2)							temp_value = 0;
				else if (at(i1, j1) == INF || mat.at(i2, j2) == INF)	temp_value = INF;
				else													temp_value = at(i1, j1) + mat.at(i2, j2);

				if (min_value > temp_value)
				{
					min_value = temp_value;
					index = count;
				}
				++count;

				if (is_same_index)										break;
			}

			if (method == MATRIX_METHOD)								temp_mat.at(i1, j) = min_value;
			else if (index != -1)										temp_mat.at(i1, j) = 'A' + static_cast<uint16_t>(index);
			else if (index == -1)										temp_mat.at(i1, j) = INF;

			min_value = INF;
			index = -1;
			count = 0;
			is_same_index = false;
		}
	}

	copy(temp_mat);
}

void Matrix::print_points()
{
	char c = 'A';

	std::cout << " ";
	for (int16_t j = 0; j < _cols; ++j)
	{
		std::cout << std::setw(5) << c++;
	}
	std::cout << "\n" << std::endl;

	c = 'A';

	for (int16_t i = 0; i < _rows; ++i)
	{
		std::cout << c++ << " ";

		for (int16_t j = 0; j < _cols; ++j)
		{
			if (at(i, j) == INF)		std::cout << std::setw(4) << "inf" << " ";
			else						std::cout << std::setw(4) << static_cast<char>(at(i, j)) << " ";
		}
		std::cout << std::endl;
	}
}

std::istream& operator>>(std::istream& in, Matrix& mat)
{
	for (int16_t i = 0; i < mat._rows; ++i)
	{
		for (int16_t j = 0; j < mat._cols; ++j)
		{
			in >> mat.at(i, j);
		}
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	char c = 'A';

	out << " ";
	for (int16_t j = 0; j < mat._cols; ++j)
	{
		out << std::setw(5) << c++;
	}
	out << std::endl;

	c = 'A';

	for (int16_t i = 0; i < mat._rows; ++i)
	{
		out << c++ << " ";

		for (int16_t j = 0; j < mat._cols; ++j)
		{
			if (mat.at(i, j) == INF)	out << std::setw(4) << "inf" << " ";
			else						out << std::setw(4) << mat.at(i, j) << " ";
		}
		out << std::endl;
	}

	return out;
}
