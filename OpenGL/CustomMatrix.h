#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include "StandardIncludes.h"

class CustomMatrix
{
public:
    int m_dimX;
    int m_dimY;
    vector<vector<float>> MatrixVals;

    CustomMatrix(int _dimX, int _dimY) 
    {
        m_dimX = _dimX;
        m_dimY = _dimY;
        MatrixVals.assign(m_dimY, std::vector<float>(m_dimX, 0.0f));
    }

    void SetVal(int i, int j, float val) 
    {
        if (i >= 0 && i < m_dimY && j >= 0 && j < m_dimX)
        {
            MatrixVals[i][j] = val;
        }
    }

    CustomMatrix operator+(const CustomMatrix& m)
    {
        if (m_dimX == m.m_dimX && m_dimY == m.m_dimY) {
            CustomMatrix c(m_dimX, m_dimY);
            for (int i = 0; i < m_dimY; ++i)
                for (int j = 0; j < m_dimX; ++j)
                    c.MatrixVals[i][j] = MatrixVals[i][j] + m.MatrixVals[i][j];
            return c;
        }
        return CustomMatrix(0, 0);
    }

    CustomMatrix operator-(const CustomMatrix& m) const {
        if (m_dimX == m.m_dimX && m_dimY == m.m_dimY) {
            CustomMatrix c(m_dimX, m_dimY);
            for (int i = 0; i < m_dimY; ++i)
                for (int j = 0; j < m_dimX; ++j)
                    c.MatrixVals[i][j] = MatrixVals[i][j] - m.MatrixVals[i][j];
            return c;
        }
        return CustomMatrix(0, 0);
    }

    CustomMatrix operator*(const CustomMatrix& m) const 
    {
        if (m_dimX == m.m_dimY) {
            CustomMatrix c(m.m_dimX, m_dimY);
            for (int i = 0; i < m_dimY; ++i) {
                for (int k = 0; k < m.m_dimX; ++k) {
                    float sum = 0.0f;
                    for (int j = 0; j < m_dimX; ++j) {
                        sum += MatrixVals[i][j] * m.MatrixVals[j][k];
                    }
                    c.MatrixVals[i][k] = sum;
                }
            }
            return c;
        }
        return CustomMatrix(0, 0);
    }

    std::string ToString() const {
        if (m_dimX == 0 || m_dimY == 0) return "";
        std::string result;
        for (int i = 0; i < m_dimY; ++i) {
            for (int j = 0; j < m_dimX; ++j) {
                result += std::to_string(MatrixVals[i][j]) + " ";
            }
            result += "\n";
        }
        return result;
	}
};

inline std::ostream& operator<<(std::ostream& os, CustomMatrix& m)
{
    for (int i = 0; i < m.m_dimY; ++i) {
        for (int j = 0; j < m.m_dimX; ++j) {
            os << m.MatrixVals[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

#endif // CUSTOMMATRIX_H