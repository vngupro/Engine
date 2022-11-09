#pragma once

#include "Engine/Export.hpp"
#include "Engine/Vector2.hpp"
#include <vector>
//#include <array>

class ENGINE_API Matrix3
{
public:
	// how should I represent the matrix ?
	Matrix3();
	//Matrix3(std::vector<float> datas);
	//Matrix3(std::array<float, 6> datas);
	//Matrix3(std::array<std::array<float, 3>, 3> datas);
	Matrix3(const float datas[3][3]);
	//Matrix3(float** datas);
	~Matrix3();

	void Print() const;
	float** GetDatas();
	float& operator()(int row, int col);
	const float& operator()(int row, int col) const;

	Matrix3 operator/(float f) const;
	Matrix3 operator*(float f) const;
	Matrix3 operator/(const Matrix3& m) const;
	Matrix3 operator*(const Matrix3& m) const;
	Matrix3 operator*(const Vector2f& v) const;
	Matrix3& operator+=(const Matrix3&);
	Matrix3& operator-=(const Matrix3&);
	Matrix3& operator*=(const Matrix3&);
	Matrix3& operator*=(float f);
	Matrix3& operator/=(float f);

 	static Matrix3 Identity();
	static Matrix3 Translate(Vector2f position);
	static Matrix3 Rotate(float angle);
	static Matrix3 Scale(Vector2f scale);

	static Matrix3 MatrixTransform(Vector2f scale, float angle, Vector2f position);
	static Matrix3 TRS(Vector2f position, float angle, Vector2f scale);

	std::vector<std::vector<float>> GetDataAsVector() const;

	Matrix3 Transpose() const;
	Matrix3 Inverse() const;
	Matrix3 Adjugate() const;
	Matrix3 CofactorMatrix() const;
	float Cofactor(int row, int col) const;
	float GetMinor(int row, int col) const;
	
	static float Determinant(std::vector<std::vector<float>> matrix);
	static std::vector<std::vector<float>> Submatrix(const std::vector<std::vector<float>>& m, int p, int q);
	//static float** SubMatrix(float m[3][3], int p, int q);
private:
	float m_datas[3][3];
};