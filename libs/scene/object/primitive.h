//


#ifndef GAMEENGINE_PRIMITIVE_H
#define GAMEENGINE_PRIMITIVE_H


#include <utility>
#include <string.h>
#include "../../../render/loader.h"

class primitive {

public:
    VertexArray VAO;
    VertexBuffer VBO;
    Vector3 scale;
    Vector3 translate;
    int texture_id{};
    Vector3 angle;
    string name;

    primitive(VertexArray VAO, VertexBuffer VBO, string name) : VAO(VAO), VBO(VBO) {
        scale = Vector3(0.5f);
       this->name = name;
        texture_id = 0;
        angle = Vector3(0.0f);
        translate = Vector3(0.0f);
    }

};


#endif //GAMEENGINE_PRIMITIVE_H
