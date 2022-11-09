#include <Engine/Matrix3.hpp>
#include <Engine/Transform.hpp>
#include <Engine/Vector2.hpp>
#include <fmt/core.h>

Matrix3::Matrix3()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m_datas[i][j] = 0;
        }
    }
}

// I hate using double ptr
//Matrix3::Matrix3(float** datas) :
//    m_datas(datas)
//{
//}

Matrix3::Matrix3(const float datas[3][3])
{
	std::copy(&datas[0][0], &datas[3][3], &m_datas[0][0]);
}

Matrix3::~Matrix3()
{
}

void Matrix3::Print() const
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            fmt::print("{}\t", m_datas[row][col]);
        }
        fmt::print("\n");
    }
}

float& Matrix3::operator()(int row, int col)
{
    return m_datas[row][col];
}

const float& Matrix3::operator()(int row, int col) const
{
    return m_datas[row][col];
}

Matrix3 Matrix3::operator/(float f) const
{
    Matrix3 ret(m_datas);

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            ret(row, col) = operator()(row, col) / f;
        }
    }

    return ret;
}

Matrix3 Matrix3::operator*(float f) const
{
    Matrix3 ret(m_datas);

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            ret(row, col) = operator()(row, col) * f;
        }     
    }

    return ret;
}

Matrix3 Matrix3::operator/(const Matrix3& m) const
{
    Matrix3 ret(m_datas);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float tmp = 0.f;
            for (int k = 0; k < 3; k++)
            {
                tmp += operator()(i, k) / m(k, j);
            }
            ret(i, j) = tmp;
        }
    }

    return ret;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
    Matrix3 ret(m_datas);

    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            float tmp = 0.f;
            for (int k = 0; k < 3; k++)
            {
                tmp += operator()(i, k) * other(k, j);
            }   
            ret(i, j) = tmp;
        }
    }

    return ret;
}

Matrix3 Matrix3::operator*(const Vector2f& v) const
{
    Matrix3 ret = Matrix3();
    float temp[3] = { v.x, v.y, 1 };
    //float ret[3]{};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ret.m_datas[i][j] += m_datas[i][j] * temp[j];
        }
    }
    return ret;
}

Matrix3& Matrix3::operator+=(const Matrix3& m)
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            m_datas[i][j] += m.m_datas[i][j];
        }
    }
    return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& m)
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            m_datas[i][j] -= m.m_datas[i][j];
        }
    }
    return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& m)
{
    // Matrix3 temp(); why not working for god sakeeeee ???
    Matrix3 temp = Matrix3();
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            for (int k = 0; k < 3; ++k) 
            {
                temp.m_datas[i][j] += (m_datas[i][k] * m.m_datas[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix3& Matrix3::operator*=(float f)
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            m_datas[i][j] *= f;
        }
    }
    return *this;
}

Matrix3& Matrix3::operator/=(float f)
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            m_datas[i][j] /= f;
        }
    }
    return *this;
}

Matrix3 Matrix3::Identity()
{
    Matrix3 result;

    for (int i = 0; i < 3; i++)
    {
        result(i, i) = 1;
    }
        
    return result;
}

Matrix3 Matrix3::Translate(Vector2f position)
{
    Matrix3 ret = Matrix3::Identity();

    ret.m_datas[0][2] = position.x;
    ret.m_datas[1][2] = position.y;

    return ret;
}

Matrix3 Matrix3::Rotate(float angle)
{
    Matrix3 ret = Matrix3::Identity();

    float a = angle * Deg2Rad;
    float cos = std::cos(a);
    float sin = std::sin(a);

    ret.m_datas[0][0] = cos;
    ret.m_datas[0][1] = -sin;
    ret.m_datas[1][0] = sin;
    ret.m_datas[1][1] = cos;

    return ret;
}

Matrix3 Matrix3::Scale(Vector2f scale)
{
    Matrix3 ret = Matrix3::Identity();

    ret.m_datas[0][0] = scale.x;
    ret.m_datas[1][1] = scale.y;

    return ret;
}

Matrix3 Matrix3::MatrixTransform(Vector2f scale, float angle, Vector2f position)
{
    return Matrix3::Scale(scale) * Matrix3::Rotate(angle) * Matrix3::Translate(position);
}

Matrix3 Matrix3::TRS(Vector2f position, float angle, Vector2f scale)
{
    return Matrix3::Translate(position) * Matrix3::Rotate(angle) * Matrix3::Scale(scale);
}

std::vector<std::vector<float>> Matrix3::GetDataAsVector() const
{
    std::vector<std::vector<float>> ret(3, std::vector<float>(3, 0));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ret[i][j] = m_datas[i][j];
        }   
    }
    return ret;
}

// urgh i don't like using double ptr how can I bypass it ?
//float** Matrix3::SubMatrix(float m[3][3], int p, int q)
//{
//    float** ret = 0;
//    ret = new float* [2];
//
//    int subi = 0;
//    for (int i = 0; i < 3; i++)
//    {
//        if (i == p)
//        {
//            continue;
//        }
//
//        ret[subi] = new float[2];
//        int subj = 0;
//        for (int j = 0; j < 3; j++)
//        {
//            if (j == q)
//            {
//                continue;
//            }
//
//            ret[subi][subj] = m[i][j];
//            subj++;
//        }
//        subi++;
//    }
//
//    return ret;
//}


std::vector<std::vector<float>> Matrix3::Submatrix(const std::vector<std::vector<float>>& m, int p, int q)
{
    std::vector<std::vector<float>> ret(2, std::vector<float>(2, 0));

    int subi = 0;
    for (int i = 0; i < 3; i++) 
    {
        if (i == p)
        {
            continue;
        }
        
        int subj = 0;
        for (int j = 0; j < 3; j++) 
        {
            if (j == q)
            {
                continue;
            }
                
            ret[subi][subj] = m[i][j];
            subj++;
        }
        subi++;
    }

    return ret;
}

float Matrix3::Determinant(std::vector<std::vector<float>> matrix)
{
    int rows = matrix.size();
    float d = 0.f;

    if (rows == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }
    else
    {
        for (int col = 0; col < rows; col++)
        {
            d += (float)std::pow(-1, col) * matrix[0][col] * Determinant(Submatrix(matrix, 0, col));
        }
    }
    return d;
}

Matrix3 Matrix3::Transpose() const
{
    Matrix3 ret = Matrix3();
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            ret(j, i) = m_datas[i][j];
        }
    }
    return ret;
}

Matrix3 Matrix3::Inverse() const
{
    float d = Determinant(GetDataAsVector());
    if (d == 0)
    {
        throw std::runtime_error("Matrix is singular.");
    }
    return Adjugate() / d;
}

Matrix3 Matrix3::Adjugate() const
{
    return CofactorMatrix().Transpose();
}

Matrix3 Matrix3::CofactorMatrix() const
{
    Matrix3 ret = Matrix3();
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            ret(row, col) = Cofactor(row, col);
        }
    }
    return ret;
}

float Matrix3::Cofactor(int row, int col) const
{
    float minor = 0.f;
    minor = GetMinor(row, col);
    return (row + col) % 2 == 0 ? minor : -minor;
}

float Matrix3::GetMinor(int row, int col) const
{
    return Determinant(Submatrix(GetDataAsVector(), row, col));
}

