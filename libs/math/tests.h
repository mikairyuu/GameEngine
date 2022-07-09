#pragma once

#include <random>
#include <iomanip>

#include "my_math.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

template<typename T, typename Ti>
bool CheckVector(T my_vec, Ti glm_vec, int size) {
    for (int i = 0; i < size; i++) {
        auto first = (int)(my_vec[i] * 10000) / 10000.;
        auto second = (int)(glm_vec[i] * 10000) / 10000.;
        if (first != second)
            return false;
    }
    return true;
}

template<typename T, typename Ti>
bool CheckMatrix(T my_mat, Ti glm_mat, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            auto first = (int)(my_mat[i][j] * 1000) / 1000.;
            auto second = (int)(glm_mat[i][j] * 1000) / 1000.;
            if (first != second)
                return false;
        }
    return true;
}

void VectorTest() {
    srand(time(nullptr));
    { // vec2 test
        glm::vec2 glm_vec1;
        glm::vec2 glm_vec2;
        Vector2 my_vec1;
        Vector2 my_vec2;
        for (int i = 0; i < 2; i++) {
            float temp = rand() % 1000;
            glm_vec1[i] = temp;
            my_vec1[i] = temp;
            temp = rand() % 1000;
            glm_vec2[i] = temp;
            my_vec2[i] = temp;
        }
        // init
        assert(CheckVector(my_vec1, glm_vec1, 2));
        assert(CheckVector(my_vec2, glm_vec2, 2));
        // +
        assert(CheckVector(my_vec1 + my_vec2, glm_vec1 + glm_vec2, 2));
        // -
        assert(CheckVector(my_vec1 - my_vec2, glm_vec1 - glm_vec2, 2));
        // *
        {
            int temp = rand() % 1000;
            auto temp_glm_vec = glm_vec1;
            assert(CheckVector(my_vec1 * temp, temp_glm_vec.operator*=(temp), 2));
            temp = rand() % 1000;
            temp_glm_vec = glm_vec2;
            assert(CheckVector(my_vec2 * temp, temp_glm_vec.operator*=(temp), 2));
            assert(CheckVector(my_vec1 * my_vec2, glm_vec1 * glm_vec2, 2));
        }
        // DotProduct
        assert(DotProduct(my_vec1, my_vec2) == glm::dot(glm_vec1, glm_vec2));
        // Normalize
        assert(CheckVector(Normalize(my_vec1), glm::normalize(glm_vec1), 2));
        assert(CheckVector(Normalize(my_vec2), glm::normalize(glm_vec2), 2));
        // Length
        assert((my_vec1.getLength()) == glm::length(glm_vec1));
        assert(my_vec2.getLength() == glm::length(glm_vec2));
        // Invert
        assert(CheckVector(my_vec1.getInvertVector(), -glm_vec1, 2));
        assert(CheckVector(~my_vec2, -glm_vec2, 2));

    }

    { // vec3 test
        glm::vec3 glm_vec1;
        glm::vec3 glm_vec2;
        Vector3 my_vec1;
        Vector3 my_vec2;

        for (int i = 0; i < 3; i++) {
            float temp = rand() % 1000;
            glm_vec1[i] = temp;
            my_vec1[i] = temp;
            temp = rand() % 1000;
            glm_vec2[i] = temp;
            my_vec2[i] = temp;
        }
        // init
        assert(CheckVector(my_vec1, glm_vec1, 3));
        assert(CheckVector(my_vec2, glm_vec2, 3));
        // +
        assert(CheckVector(my_vec1 + my_vec2, glm_vec1 + glm_vec2, 3));
        // -
        assert(CheckVector(my_vec1 - my_vec2, glm_vec1 - glm_vec2, 3));
        // *
        {
            int temp = rand() % 1000;
            auto temp_glm_vec = glm_vec1;
            assert(CheckVector(my_vec1 * temp, temp_glm_vec.operator*=(temp), 3));
            temp = rand() % 1000;
            temp_glm_vec = glm_vec2;
            assert(CheckVector(my_vec2 * temp, temp_glm_vec.operator*=(temp), 3));
            assert(CheckVector(my_vec1 * my_vec2, glm_vec1 * glm_vec2, 3));
        }
        // DotProduct
        assert(DotProduct(my_vec1, my_vec2) == glm::dot(glm_vec1, glm_vec2));
        // Normalize
        assert(CheckVector(Normalize(my_vec1), glm::normalize(glm_vec1), 3));
        assert(CheckVector(Normalize(my_vec2), glm::normalize(glm_vec2), 3));
        // Length
        assert(my_vec1.getLength() == glm::length(glm_vec1));
        assert(my_vec2.getLength() == glm::length(glm_vec2));
        // CrossProduct
        assert(CheckVector(CrossProduct(my_vec1, my_vec2), glm::cross(glm_vec1, glm_vec2), 3));
        // DotProduct
        assert(DotProduct(my_vec1, my_vec2) == glm::dot(glm_vec1, glm_vec2));
        // Invert
        assert(CheckVector(my_vec1.getInvertVector(), -glm_vec1, 3));
        assert(CheckVector(~my_vec2, -glm_vec2, 3));


    }

    { // vec4 test
        glm::vec4 glm_vec1;
        glm::vec4 glm_vec2;
        Vector4 my_vec1;
        Vector4 my_vec2;

        for (int i = 0; i < 4; i++) {
            float temp = rand() % 1000;
            glm_vec1[i] = temp;
            my_vec1[i] = temp;
            temp = rand() % 1000;
            glm_vec2[i] = temp;
            my_vec2[i] = temp;
        }
        // init
        assert(CheckVector(my_vec1, glm_vec1, 4));
        assert(CheckVector(my_vec2, glm_vec2, 3));
        // +
        assert(CheckVector(my_vec1 + my_vec2, glm_vec1 + glm_vec2, 4));
        // -
        assert(CheckVector(my_vec1 - my_vec2, glm_vec1 - glm_vec2, 4));
        // *
        {
            int temp = rand() % 1000;
            auto temp_glm_vec = glm_vec1;
            assert(CheckVector(my_vec1 * temp, temp_glm_vec.operator*=(temp), 4));
            temp = rand() % 1000;
            temp_glm_vec = glm_vec2;
            assert(CheckVector(my_vec2 * temp, temp_glm_vec.operator*=(temp), 4));
            assert(CheckVector(my_vec1 * my_vec2, glm_vec1 * glm_vec2, 4));
        }
        // DotProduct
        assert(DotProduct(my_vec1, my_vec2) == glm::dot(glm_vec1, glm_vec2));
        // Normalize
        assert(CheckVector(Normalize(my_vec1), glm::normalize(glm_vec1), 4));
        assert(CheckVector(Normalize(my_vec2), glm::normalize(glm_vec2), 4));
        // Length
        assert(my_vec1.getLength() == glm::length(glm_vec1));
        assert(my_vec2.getLength() == glm::length(glm_vec2));

        // Invert
        assert(CheckVector(my_vec1.getInvertVector(), -glm_vec1, 4));
        assert(CheckVector(~my_vec2, -glm_vec2, 4));

    }

    std::cout << "Vector success" << std::endl;
}

void MatrixTest() {
    srand(time(0));
    {// mat2 test
        Matrix<2, 2> my_mat1;
        Matrix<2, 2> my_mat2;
        glm::mat2 glm_mat1;
        glm::mat2 glm_mat2;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                float temp = rand() % 1000;
                my_mat1[i][j] = temp;
                glm_mat1[i][j] = temp;
                temp = rand() % 1000;
                my_mat2[i][j] = temp;
                glm_mat2[i][j] = temp;
            }
        }

        // init
        assert(CheckMatrix(my_mat1, glm_mat1, 2));
        assert(CheckMatrix(my_mat2, glm_mat2, 2));
        // +
        assert(CheckMatrix(my_mat1 + my_mat2, glm_mat1 + glm_mat2, 2));
        // -
        assert(CheckMatrix(my_mat1 - my_mat2, glm_mat1 - glm_mat2, 2));
        // *
        {
            int temp = rand() % 1000;
            auto temp_glm_mat = glm_mat1;
            assert(CheckMatrix(my_mat1 * temp, temp_glm_mat.operator*=(temp), 2));
            temp = rand() % 1000;
            temp_glm_mat = glm_mat2;
            assert(CheckMatrix(my_mat2 * temp, temp_glm_mat.operator*=(temp), 2));
            assert(CheckMatrix(my_mat1 * my_mat2, glm_mat1 * glm_mat2, 2));
            assert(CheckMatrix(my_mat2 * my_mat1, glm_mat2 * glm_mat1, 2));
        }

        // Transpose
        assert(CheckMatrix(Transpose(my_mat1), glm::transpose(glm_mat1), 2));
        assert(CheckMatrix(Transpose(my_mat2), glm::transpose(glm_mat2), 2));
        // Inverse
        assert(CheckMatrix(Inverse(my_mat1), glm::inverse(glm_mat1), 2));
        assert(CheckMatrix(Inverse(my_mat2), glm::inverse(glm_mat2), 2));
    }
    { // mat3 test
        Matrix<3, 3> my_mat1;
        Matrix<3, 3> my_mat2;
        glm::mat3 glm_mat1;
        glm::mat3 glm_mat2;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float temp = rand() % 1000;
                my_mat1[i][j] = temp;
                glm_mat1[i][j] = temp;
                temp = rand() % 1000;
                my_mat2[i][j] = temp;
                glm_mat2[i][j] = temp;
            }
        }

        // init
        assert(CheckMatrix(my_mat1, glm_mat1, 3));
        assert(CheckMatrix(my_mat2, glm_mat2, 3));
        // +
        assert(CheckMatrix(my_mat1 + my_mat2, glm_mat1 + glm_mat2, 3));
        // -
        assert(CheckMatrix(my_mat1 - my_mat2, glm_mat1 - glm_mat2, 3));
        // *
        {
            int temp = rand() % 1000;
            auto temp_glm_mat = glm_mat1;
            assert(CheckMatrix(my_mat1 * temp, temp_glm_mat.operator*=(temp), 3));
            temp = rand() % 1000;
            temp_glm_mat = glm_mat2;
            assert(CheckMatrix(my_mat2 * temp, temp_glm_mat.operator*=(temp), 3));
            assert(CheckMatrix(my_mat1 * my_mat2, glm_mat1 * glm_mat2, 3));
            assert(CheckMatrix(my_mat2 * my_mat1, glm_mat2 * glm_mat1, 3));
        }
        // Transpose
        assert(CheckMatrix(Transpose(my_mat1), glm::transpose(glm_mat1), 3));
        assert(CheckMatrix(Transpose(my_mat2), glm::transpose(glm_mat2), 3));
        // Inverse
        assert(CheckMatrix(Inverse(my_mat1), glm::inverse(glm_mat1), 3));
        assert(CheckMatrix(Inverse(my_mat2), glm::inverse(glm_mat2), 3));
    }
    { // mat4 test
        Matrix<4, 4> my_mat1;
        Matrix<4, 4> my_mat2;
        glm::mat4 glm_mat1;
        glm::mat4 glm_mat2;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float temp = rand() % 1000;
                my_mat1[i][j] = temp;
                glm_mat1[i][j] = temp;
                temp = rand() % 1000;
                my_mat2[i][j] = temp;
                glm_mat2[i][j] = temp;
            }
        }

        // init
        assert(CheckMatrix(my_mat1, glm_mat1, 4));
        assert(CheckMatrix(my_mat2, glm_mat2, 4));
        // +
        assert(CheckMatrix(my_mat1 + my_mat2, glm_mat1 + glm_mat2, 4));
        // -
        assert(CheckMatrix(my_mat1 - my_mat2, glm_mat1 - glm_mat2, 4));
        // *
        {
            int temp = rand() % 1000;
            auto temp_glm_mat = glm_mat1;
            assert(CheckMatrix(my_mat1 * temp, temp_glm_mat.operator*=(temp), 4));
            temp = rand() % 1000;
            temp_glm_mat = glm_mat2;
            assert(CheckMatrix(my_mat2 * temp, temp_glm_mat.operator*=(temp), 4));
            assert(CheckMatrix(my_mat1 * my_mat2, glm_mat1 * glm_mat2, 4));
            assert(CheckMatrix(my_mat2 * my_mat1, glm_mat2 * glm_mat1, 4));
        }
        // Transpose
        assert(CheckMatrix(Transpose(my_mat1), glm::transpose(glm_mat1), 4));
        assert(CheckMatrix(Transpose(my_mat2), glm::transpose(glm_mat2), 4));
        // inverse
        assert(CheckMatrix(Inverse(my_mat1), glm::inverse(glm_mat1), 4));
        assert(CheckMatrix(Inverse(my_mat2), glm::inverse(glm_mat2), 4));
        // Transform
        {
            Vector3 my_vec(rand() % 1000, rand() % 1000, rand() % 1000);
            glm::vec3 glm_temp_vec(my_vec[0], my_vec[1], my_vec[2]);
            assert(CheckMatrix(Transform(my_vec), glm::translate(glm::mat4(1.0f), glm_temp_vec), 4));
        }
        // Scale
        {
            Vector3 my_vec(rand() % 1000, rand() % 1000, rand() % 1000);
            glm::vec3 glm_temp_vec(my_vec[0], my_vec[1], my_vec[2]);
            assert(CheckMatrix(Scale(my_vec), glm::scale(glm::mat4(1.0f), glm_temp_vec), 4));
        }
        // Rotation
        {
            Vector3 my_vec(rand() % 1000, rand() % 1000, rand() % 1000);
            glm::vec3 glm_temp_vec(my_vec[0], my_vec[1], my_vec[2]);
            float angle = rand() % 1000;
            assert(CheckMatrix(Rotation(my_vec, GetRadians(angle)),
                                 glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm_temp_vec), 4));
        }
        // CreateViewMatrix
        {
            Vector3 my_from_vec(rand() % 1000, rand() % 1000, rand() % 1000);
            Vector3 my_to_vec(rand() % 1000, rand() % 1000, rand() % 1000);
            glm::vec3 glm_from_vec(my_from_vec[0], my_from_vec[1], my_from_vec[2]);
            glm::vec3 glm_to_vec(my_to_vec[0], my_to_vec[1], my_to_vec[2]);

            assert(CheckMatrix(CreateViewMatrix(my_from_vec, my_to_vec, Vector3(0.0f, 1.0f, 0.0f)),
                                 glm::lookAt(glm_from_vec, glm_to_vec, glm::vec3(0.0f, 1.0f, 0.0f)), 4));
        }
        //Orthographic
        {
            float left = rand() % 1000;
            float right = rand() % 1000;
            if (left > right)
                std::swap(left, right);
            float bottom = rand() % 1000;
            float top = rand() % 1000;
            if (bottom > top)
                std::swap(bottom, top);
            float near = rand() % 1000;
            float far = rand() % 1000;
            if (near > far)
                std::swap(near, far);
            assert(CheckMatrix(Orthographic(left, right, bottom, top, near, far),
                                 glm::ortho(left, right, bottom, top, near, far), 4));
        }
        //Perspective
        {
            float fow = rand() % 1000;
            float ratio = rand() % 1000;
            float near = rand() % 1000;
            float far = rand() % 1000;
            if (near > far)
                std::swap(near, far);
            cout << endl;
            Matrix<4, 4> m1 = Perspective(GetRadians(fow), ratio, near, far);
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    cout << m1[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            glm::mat4 m2 = glm::perspective(GetRadians(fow), ratio, near, far);
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    cout << m2[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            assert(CheckMatrix(Perspective(GetRadians(fow), ratio, near, far),
                                 glm::perspective(GetRadians(fow), ratio, near, far), 4));
        }

    }

    std::cout << "Matrix success" << std::endl;
}  