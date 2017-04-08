#pragma once
struct Matrix
{
protected:
	float data[4][4];

public:
	Matrix(float _initial = 0);

	// Matrix mathematical operations
	void operator+=(const Matrix& rhs);
	void operator-=(const Matrix& rhs);
	void operator*=(const Matrix& rhs);
	Matrix  operator+ (const Matrix& rhs);
	Matrix  operator- (const Matrix& rhs);
	Matrix  operator* (const Matrix& rhs);
	Matrix  transpose ();

	// Matrix/scalar operations
	Matrix operator+(const float rhs);
	Matrix operator-(const float rhs);
	Matrix operator*(const float rhs);
	Matrix operator/(const float rhs);

	friend Float3 operator*(const Matrix lhs, const Float3 rhs);

	float* operator[](int x) { return data[x]; }
};

