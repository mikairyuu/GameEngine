#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "libs/math/vector.h"
#include "libs/math/matrix.h"
#include "libs/math/my_math.h"
using namespace std;

int main() {
    Vector2 v(5.4);
    Vector2 v1(3.4);
    Vector2 v2 = v * v1;
    //v->operator-=(*v1);
    bool b = v1 != v1;
    cout << b << endl;
    cout << v2.y << endl;
    v = ~v2;
    float a = v ^ v2;
    cout << v[1] << endl;




    Matrix<4, 4> m(5);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j]+=i+j;
        }
    }
    m[1][1]=8;m[2][1]=9;m[3][2]=5;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    GetDeterminant(m);

/*    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout<<m1[i][j]<<" ";
        }
        cout<<endl;
    }*/


    Matrix<4, 4> m1 = Inverse(m);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout<<m1[i][j]<<" ";
        }
        cout<<endl;
    }

/*
    Matrix<2, 2> m1;
    m1 = m;
    float t = m[3][2];
    cout << m1[1][1];*/

    return 0;
}
