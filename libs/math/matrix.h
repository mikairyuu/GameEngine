#pragma once

#include <array>
#include <iostream>

using namespace std;

template<int M, int N>
class Matrix {
    array<array<float, N>, M> data;
public:
    Matrix() {
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                data[i][j] = 0;
    }

    explicit Matrix(float f) {
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                data[i][j] = f;
    }

    Matrix(initializer_list<initializer_list<float>> list) {
        if (list.size() != M) {
            cout << "Dimensions are different";
            throw;
            //return Matrix();
        }
        for (int i = 0; i < M; i++) {
            if ((list.begin() + i)->size() != N) {
                cout << "Dimensions are different";
                //return Matrix();
                throw;
            }

            for (int j = 0; j < N; j++)
                data[i][j] = *((list.begin() + i)->begin() + j);
        }
    }

    inline array<float, N> &operator[](const int index) {
        return data[index];
    }

    inline const array<float, N> &operator[](const int index) const {
        return data[index];
    }

    inline Matrix<M, N> operator+(Matrix<M, N> &m) {
        Matrix<M, N> res;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                res[i][j] = m[i][j] + this->data[i][j];
        return res;
    }

    inline Matrix<M, N> operator-(Matrix<M, N> &m) {
        Matrix<M, N> res;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                res[i][j] = this->data[i][j]- m[i][j];
        return res;
    }

    inline Matrix<M, N> operator*(float f) {
        Matrix<M, N> res;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                res[i][j] = this->data[i][j] * f;
        return res;
    }

    inline Matrix<M, M> operator*(Matrix<M, M> m) {
        Matrix<M, M> res;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    res[j][i] += this->data[k][i] * m[j][k];
        return res;
    }

};

