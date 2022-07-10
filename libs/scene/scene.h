//
#pragma once
// Created by bender on 10.07.22.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H


#include <vector>
#include "object/object.h"
#include "../math/vector.h"
#include "../../render/loader.h"

enum primitive {
    Cube, Sphere, Tetrahedron, Surface
};
class scene {


    int select_obj;

    Vector3 lightAmb;
    Vector3 lightDiff;
    Vector3 lightSpec;
    Vector3 cameraPos;
    Vector3 materialSpec;


public:
    std::shared_ptr<Shader> shaderProgram = ShaderLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/shaders/shader");

    float materialShine;
    Vector3 lightPos;
    std::vector<object> objects;
    int selected_obj;

    scene();

    void add_object(primitive primitive) {
        CreateObject(primitive);
    }

    void scale_obj(Vector3 scale) {
        objects[selected_obj].scale = scale;
    }

    void rotate_obj(Vector3 angle) {
        objects[selected_obj].angle = angle;
    }

    void translate_obj(Vector3 translate) {
        objects[selected_obj].translate = translate;
    }

    void change_obj();

    void change_texture();

    void render();

private:
    std::vector<Vertex> getVertexes(primitive primitive);

    void CreateObject(primitive primitive);

};


#endif //GAMEENGINE_SCENE_H
