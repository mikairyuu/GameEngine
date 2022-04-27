#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "libs/math/vector.h"

using namespace std;

int main() {
    Vector2 v(5.4);
    Vector2 v1(3.4);
    Vector2 v2 = v * v1;
    //v->operator-=(*v1);
    bool b = v1 != v1;
    cout << b << endl;
    cout << v2.y;

    return 0;
}
