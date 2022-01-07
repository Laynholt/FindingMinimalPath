#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <iomanip>
#include <cstdint>


#define INF UINT16_MAX
#define MATRIX_METHOD 0
#define FLOYD_METHOD 1

class Matrix
{
public:
	Matrix(int16_t rows, int16_t cols);
	Matrix(const Matrix& mat);
	~Matrix();

	int16_t get_size() const;
	int16_t get_number_of_vertex() const;

	uint16_t& at(int16_t rows, int16_t cols) const;
	void copy(const Matrix& mat);

	void multiply(const Matrix& mat, bool method);
	void print_points();

	friend std::istream& operator>>(std::istream& in, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);

private:
	uint16_t* _arr_ptr;
	int16_t _rows;
	int16_t _cols;
	int16_t _size;
};

#endif // !_MATRIX_H_
