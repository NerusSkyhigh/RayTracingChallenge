//
// Created by Gugli on 30/12/2025.
//

#pragma once

#include <cassert>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "Matrix.h"
#include "Tuple.h"

#define EPSILON 0.00001
#define APPROX_EQUAL(a, b) (std::fabs((a) - (b)) < EPSILON)

class Matrix {

private:
    std::vector<double> data;

public:
    const int size;

    Matrix(const int size) : size(size) {
        data = std::vector<double>(size*size, 0.0);
    }

    // Construct a matrix from size and data
    Matrix(const int size, const std::vector<double>& values) : size(size) {
        assert(values.size() == size * size);
        data = values;
    }

    double& at(const int row, const int col) {
        return data[row * size + col];
    }

    const double& at(const int row, const int col) const {
        return data[row * size + col];
    }

    bool operator==(const Matrix& m) const {
        if (this->size != m.size) {
            return false;
        }

        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (!APPROX_EQUAL(this->at(row, col), m.at(row, col))) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix operator*(const Matrix& m) const {
        assert(this->size == m.size);
        Matrix result(this->size);

        for (int row = 0; row < this->size; row++) {
            for (int col = 0; col < this->size; col++) {
                double sum = 0.0;
                for (int k = 0; k < this->size; k++) {
                    sum += this->at(row, k) * m.at(k, col);
                }
                result.at(row, col) = sum;
            }
        }

        return result;
    }

    Matrix operator*(const Tuple& t) {
        assert(APPROX_EQUAL(this->size, 4.0));

        Matrix result(this->size);
        for (int row = 0; row < this->size; row++) {
            double sum = 0.0;
            sum += this->at(row, 0) * t.x;
            sum += this->at(row, 1) * t.y;
            sum += this->at(row, 2) * t.z;
            sum += this->at(row, 3) * t.w;
            result.at(row, 0) = sum;
        }

        return result;
    }

    Matrix transpose() {
        Matrix result(this->size);
        for (int row = 0; row < this->size; row++) {
            for (int col = 0; col < this->size; col++) {
                result.at(col, row) = this->at(row, col);
            }
        }
        return result;
    }

    Matrix submatrix(const int removeRow, const int removeCol) const {
        Matrix result(size - 1);
        int destRow = 0;
        for (int row = 0; row < size; row++) {
            if (row == removeRow) continue;
            int destCol = 0;
            for (int col = 0; col < size; col++) {
                if (col == removeCol) continue;
                result.at(destRow, destCol) = this->at(row, col);
                destCol++;
            }
            destRow++;
        }
        return result;
    }

    double minor(const int row, const int col) const {
        Matrix sub = this->submatrix(row, col);
        return sub.determinant();
    }

    Matrix cofactorMatrix() const {
        Matrix result(size);
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                double minorValue = this->minor(row, col);
                double sign = ((row + col) % 2 == 0) ? 1.0 : -1.0;
                result.at(row, col) = sign * minorValue;
            }
        }
        return result;
    }

    double determinant() const {
        switch (size) {
            case 2: {
                return at(0,0) * at(1,1) - at(0,1) * at(1,0);
            }

            case 3: {
                // There is an explicit formula for 3x3 determinants
                // Which computes the signed sum of the products of the diagonals
                double diag1 = at(0,0) * at(1,1) * at(2,2);
                double diag2 = at(0,1) * at(1,2) * at(2,0);
                double diag3 = at(0,2) * at(1,0) * at(2,1);
                double diag4 = at(0,2) * at(1,1) * at(2,0);
                double diag5 = at(0,0) * at(1,2) * at(2,1);
                double diag6 = at(0,1) * at(1,0) * at(2,2);
                return diag1 + diag2 + diag3 - diag4 - diag5 - diag6;
            }

            case 4: {
                // For 4x4 matrices, we can expand along the forth row and use the 3x3 determinant
                double det = 0.0;
                for (int row = 0; row < 4; row++) {
                    int row1 = (row + 1) % 4;
                    int row2 = (row + 2) % 4;
                    int row3 = (row + 3) % 4;

                    // sub diagonal
                    double sdiag1 = at(row1,1) * at(row2,2) * at(row3,3);
                    double sdiag2 = at(row1,2) * at(row2,3) * at(row3,1);
                    double sdiag3 = at(row1,3) * at(row2,1) * at(row3,2);
                    double sdiag4 = at(row1,3) * at(row2,2) * at(row3,1);
                    double sdiag5 = at(row1,1) * at(row2,3) * at(row3,2);
                    double sdiag6 = at(row1,2) * at(row2,1) * at(row3,3);

                    double sign = (row % 2 == 0) ? 1.0 : -1.0;
                    det += sign * at(row, 0) * (sdiag1 + sdiag2 + sdiag3 - sdiag4 - sdiag5 - sdiag6);
                }
                return det;
            }
            default: {
                // [TODO] I should just switch to Eigen...
                throw std::runtime_error("Determinant not implemented for matrices larger than 4x4");
            }
        }
    }

    Matrix inverse() const {
        double det = this->determinant();
        if (APPROX_EQUAL(det, 0.0)) {
            throw std::runtime_error("Matrix is not invertible");
        }

        Matrix cofactorMat = this->cofactorMatrix();
        Matrix adjugate = cofactorMat.transpose();

        Matrix result(size);
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                result.at(row, col) = adjugate.at(row, col) / det;
            }
        }

        return result;
    }

    static Matrix identity(const int size) {
        Matrix id(size);
        for (int i = 0; i < size; i++) {
            id.at(i, i) = 1.0;
        }
        return id;
    }

};
