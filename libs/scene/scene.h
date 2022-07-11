//
#pragma once
// Created by bender on 10.07.22.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H


#include <vector>
#include "object/primitive.h"
#include "../math/vector.h"
#include "../../render/loader.h"

enum geo_obj {
    Cube, Sphere, Tetrahedron, Surface,ModelObject
};

class scene {


    int select_obj;

    Vector3 lightAmb;
    Vector3 lightDiff;
    Vector3 lightSpec;
    Vector3 cameraPos;
    Vector3 materialSpec;


public:
    std::shared_ptr<Shader> shaderProgram = ShaderLoader::getInstance().load(
            "/home/bender/CLionProjects/GameEngine/res/shaders/shader");

    float materialShine;
    Vector3 lightPos;
    std::vector<primitive> primitives;
    std::vector<Object> objects;
    int selected_obj;

    scene();

    void add_object(geo_obj obj) {
        CreateObject(obj);
    }

    void scale_obj(Vector3 scale) {
        primitives[selected_obj].scale = scale;
    }

    void rotate_obj(Vector3 angle) {
        primitives[selected_obj].angle = angle;
    }

    void translate_obj(Vector3 translate) {
        primitives[selected_obj].translate = translate;
    }

    void change_obj(int i);

    void change_texture();

    void render();

    vector<string> getNames() {
        vector<string> res;
        for (int i = 0; i < primitives.size(); ++i) {
            res.push_back(primitives[i].name);
        }
        return res;
    }

private:
    std::vector<Vertex> getVertexes(geo_obj obj);

    void CreateObject(geo_obj obj);

};


#endif //GAMEENGINE_SCENE_H
