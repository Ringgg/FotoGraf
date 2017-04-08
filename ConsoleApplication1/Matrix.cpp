#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix(float _initial) {
	
	for (unsigned i = 0; i<16; i++)
	{
		*data[i] = _initial;
	}
}

void Matrix::operator+=(const Matrix & rhs)
{

}
void Matrix::operator-=(const Matrix & rhs)
{

}
void Matrix::operator*=(const Matrix & rhs)
{

}

Matrix Matrix::operator+(const Matrix & rhs)
{
	Matrix result;
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			result[i][j] = data[i][j] + rhs.data[i][j];

	return result;
}
Matrix Matrix::operator-(const Matrix & rhs)
{
	return Matrix();
}
Matrix Matrix::operator*(const Matrix & rhs)
{
	return Matrix();
}

Matrix Matrix::transpose()
{
	return Matrix();
}

Matrix Matrix::operator+(const float rhs)
{
	return Matrix();
}

Matrix Matrix::operator-(const float rhs)
{
	return Matrix();
}

Matrix Matrix::operator*(const float rhs)
{
	return Matrix();
}

Matrix Matrix::operator/(const float rhs)
{
	return Matrix();
}

Float3 operator*(const Matrix lhs, const Float3 rhs)
{
	Float3 result;
	return Float3();
}
