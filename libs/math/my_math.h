#pragma once

#include "vector.h"
#include "matrix.h"

inline float GetRadians(float degree) {
    return M_PI * degree / 180.0f;
}

inline float ScalarProduct(Vector2 v1, Vector2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

inline float DotProduct(Vector2 v1, Vector2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

inline Vector2 Normalize(Vector2 v) {
    return v / v.getLength();
}

inline float GetDistance(Vector2 v1, Vector2 v2) {
    return (v2 - v1).getLength();
}

inline Vector2 operator*(Matrix<2, 2> m, Vector2 v) {
    Vector2 res;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            res[i] += m[i][j] * v[j];
    return res;
}

inline float ScalarProduct(Vector3 v1, Vector3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3 CrossProduct(Vector3 v1, Vector3 v2) {
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

inline Vector3 Normalize(Vector3 v) {
    return v / v.getLength();
}

inline float DotProduct(Vector3 v1, Vector3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float GetDistance(Vector3 v1, Vector3 v2) {
    return (v2 - v1).getLength();
}

inline Vector3 operator*(Matrix<3, 3> m, Vector3 v) {
    Vector3 res;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res[i] += m[i][j] * v[j];
    return res;
}

inline float DotProduct(Vector4 v1, Vector4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.q * v2.q;
}


inline Vector4 Normalize(Vector4 v) {
    return v / v.getLength();
}

inline float distance(Vector4 v1, Vector4 v2) {
    return (v2 - v1).getLength();
}

inline Vector4 operator*(Matrix<4, 4> m, Vector4 v) {
    Vector4 res;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res[i] += m[i][j] * v[j];
    return res;
}

template<int M>
inline Matrix<M, M> Identity(Matrix<M, M> m, float f = 1.0f){
    Matrix<M, M> out;
    for (int i = 0; i < M; i++){
        out[i][i] = f;
    }
    return out;
}


template<int M, int N>
inline Matrix<M, N> Transpose(Matrix<M, N> m) {
    Matrix<N, M> res;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            res[i][j] = m[j][i];
    return res;
}

inline float GetDeterminant(Matrix<2, 2> m) {
    return (m[0][0] * m[1][1]
            - m[0][1] * m[1][0]);
}

inline float GetDeterminant(Matrix<3, 3> m) {
    return (m[0][0] * m[1][1] * m[2][2]
            + m[0][1] * m[1][2] * m[2][0]
            + m[0][2] * m[1][0] * m[2][1]
            - m[0][2] * m[1][1] * m[2][0]
            - m[0][0] * m[1][2] * m[2][1]
            - m[0][1] * m[1][0] * m[2][2]);
}

inline float GetDeterminant(Matrix<4, 4> m) {
    float res = 0;
    Matrix<3, 3> buff;
    for (int i = 0; i < 4; i++) {
        if (m[0][i] == 0)
            continue;

        for (int j = 1; j < 4; ++j) {
            int q = 0;
            for (int k = 0; k < 4; ++k) {
                if (k != i) {
                    buff[j - 1][q] = m[j][k];
                    q++;
                }
            }
        }
        res += m[0][i] * pow(-1, i) * GetDeterminant(buff);
    }
    return res;
}


inline Matrix<2, 2> GetMinorMatrix(Matrix<2, 2> m) {
    Matrix<2, 2> out;
    out[0][0] = m[1][1];
    out[0][1] = -m[1][0];
    out[1][0] = -m[0][1];
    out[1][1] = m[0][0];
    return out;
}

inline Matrix<3, 3> GetMinorMatrix(Matrix<3, 3> m) {
    Matrix<3, 3> out;
    out[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    out[0][1] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
    out[0][2] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
    out[1][0] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
    out[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
    out[1][2] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);
    out[2][0] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    out[2][1] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);
    out[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    return out;
}

inline Matrix<4, 4> GetMinorMatrix(Matrix<4, 4> m) {
    Matrix<4, 4> res;
    Matrix<3, 3> buff;
    for (int t = 0; t < 4; ++t)
        for (int i = 0; i < 4; i++) {
            int j1 = 0;
            for (int j = 0; j < 4; ++j) {
                int k1 = 0;
                for (int k = 0; k < 4; ++k) {
                    if (k != i && j != t) {
                        buff[j1][k1] = m[j][k];
                        k1++;
                    }
                }
                if (k1 == 3)
                    j1++;
            }
            res[t][i] = pow(-1, i + t) * GetDeterminant(buff);
        }
    return res;
}

template<int M, int N>
inline Matrix<M, N> Inverse(Matrix<M, N> m) {
    float determinant = GetDeterminant(m);
    Matrix<M, N> res = GetMinorMatrix(m);
    res = Transpose(res);
    return res * (1 / determinant);
}

inline Matrix<3, 3> Transform(Vector2 v) {
    Matrix<3, 3> res;
    res[0][0] = 1;
    res[1][1] = 1;
    res[2][2] = 1;
    res[0][2] = v.x;
    res[1][2] = v.y;
    return res;
}

inline Matrix<4, 4> Transform(Vector3 v) {
    Matrix<4, 4> res;
    res[0][0] = 1;
    res[1][1] = 1;
    res[2][2] = 1;
    res[3][3] = 1;
    res[0][3] = v.x;
    res[1][3] = v.y;
    res[2][3] = v.z;
    return Transpose(res);
}

inline Matrix<3, 3> Scale(Vector2 v) {
    Matrix<3, 3> res;
    res[0][0] = v.x;
    res[1][1] = v.y;
    res[2][2] = 1;
    return res;
}

inline Matrix<4, 4> Scale(Vector3 v) {
    Matrix<4, 4> res;
    res[0][0] = v.x;
    res[1][1] = v.y;
    res[2][2] = v.z;
    res[3][3] = 1;
    return res;
}

inline Matrix<4, 4> Rotation(Vector3 v) {
    float sX = sinf(v.x);
    float cX = cosf(v.x);
    float sY = sinf(v.y);
    float cY = cosf(v.y);
    float sZ = sinf(v.z);
    float cZ = cosf(v.z);
    return {
            {cX * cZ - sX * cY * sZ, -cX * sZ - sX * cY + cZ, sX * sY,  0.0f},
            {sX * cZ + cX * cY * sZ, -sX * sZ + cX * cY * cZ, -cX * sY, 0.0f},
            {sY * sZ,                sY * cZ,                 cY,       0.0f},
            {0.0f,                   0.0f,                    0.0f,     1.0f}
    };
}

inline Matrix<4, 4> Rotation(Vector3 v, float a) {
    Vector3 R = Normalize(v);
    float c = cosf(a);
    float s = sinf(a);
    return Transpose(Matrix<4, 4>{
            {c + R.x * R.x * (1 - c),       R.x * R.y * (1 - c) - R.z * s, R.x * R.z * (1 - c) + R.y * s, 0},
            {R.y * R.x * (1 - c) + R.z * s, c + R.y * R.y * (1 - c),       R.y * R.z * (1 - c) - R.x * s, 0},
            {R.z * R.x * (1 - c) - R.y * s, R.z * R.y * (1 - c) + R.x * s, c + R.z * R.z * (1 - c),       0},
            {0,                             0,                             0,                             1}
    });
}

inline Matrix<4, 4>
CraeteModelMatrix(Matrix<4, 4> Translation_Matrix, Matrix<4, 4> Rotation_Matrix, Matrix<4, 4> Scale_Matrix) {
    return Translation_Matrix * Rotation_Matrix * Scale_Matrix;
}

inline Matrix<4, 4> CreateViewMatrix(Vector3 from, Vector3 to, Vector3 worldUp) {
    Vector3 forward = Normalize(to - from);
    Vector3 right = Normalize(CrossProduct(forward, worldUp));
    Vector3 up = Normalize(CrossProduct(right, forward));
    Matrix<4, 4> view = {
            {right.x,                     up.x,                     -forward.x,                   0},
            {right.y,                     up.y,                     -forward.y,                   0},
            {right.z,                     up.z,                     -forward.z,                   0},
            {-ScalarProduct(right, from), -ScalarProduct(up, from), ScalarProduct(forward, from), 1}
    };
    return view;
}

inline Matrix<4, 4> Orthographic(float left, float right, float bottom, float top, float near, float far) {
    Matrix<4, 4> orthographic;
    orthographic[0][0] = 2 / (right - left);
    orthographic[1][1] = 2 / (top - bottom);
    orthographic[2][2] = -2 / (far - near);
    orthographic[3][0] = -(right + left) / (right - left);
    orthographic[3][1] = -(top + bottom) / (top - bottom);
    orthographic[3][2] = -(far + near) / (far - near);
    orthographic[3][3] = 1;
    return orthographic;
}

inline Matrix<4, 4> Perspective(float fow, float ratio, float near, float far) {
    Matrix<4, 4> perspect;
    float tfov = tanf(fow / 2);
    perspect[0][0] =1/ ratio/tfov;
    perspect[1][1] = 1 / tfov;
    perspect[2][2] = (far + near) / (near - far);
    perspect[2][3] = -1;
    perspect[3][2] = 2 * far * near / (near - far);
    return perspect;
}