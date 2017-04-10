#pragma once
struct Matrix
{
protected:
	double data[4][4];

public:
	Matrix(double _initial = 0);

	// Matrix mathematical operations
	void operator+=(const Matrix& rhs);
	void operator-=(const Matrix& rhs);
	void operator*=(const Matrix& rhs);
	Matrix  operator+ (const Matrix& rhs);
	Matrix  operator- (const Matrix& rhs);
	Matrix  operator* (const Matrix& rhs);
	Matrix  transpose ();

	// Matrix/scalar operations
	Matrix operator+(const double rhs);
	Matrix operator-(const double rhs);
	Matrix operator*(const double rhs);
	Matrix operator/(const double rhs);

	friend Float3 operator*(const Matrix lhs, const Float3 rhs);

	double* operator[](int x) { return data[x]; }
};

