//
// Created by bender on 10.07.22.
//

#ifndef GAMEENGINE_OBJECT_H
#define GAMEENGINE_OBJECT_H


#include "../../../render/loader.h"

class object {

public:
    VertexArray VAO;
    VertexBuffer VBO;
    Vector3 scale;
    Vector3 translate;
    int texture_id{};
    Vector3 angle;

    object(VertexArray VAO, VertexBuffer VBO) : VAO(VAO), VBO(VBO) {
        scale = Vector3(0.5f);
        texture_id = 0;
        angle = Vector3(0.0f);
        translate = Vector3(0.0f);
    }

};


#endif //GAMEENGINE_OBJECT_H
