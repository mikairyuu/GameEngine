//
// Created by bender on 10.07.22.
//

#include "scene.h"

void scene::render() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана

    glEnable(GL_DEPTH_TEST);

    shaderProgram->bind();
    for (int i = 0; i < primitives.size(); ++i) {
         TextureHolder::getInstance().get(primitives[i].texture_id)->bind();



        primitives[i].VAO.bind();

        Matrix<4, 4> translation = Transform(primitives[i].translate);


        Matrix<4, 4> rotation = Rotation(Vector3(1, 0, 0), GetRadians(primitives[i].angle[0])) *
                                Rotation(Vector3(0, 1, 0), GetRadians(primitives[i].angle[1])) *
                                Rotation(Vector3(0, 0, 1), GetRadians(primitives[i].angle[2]));

        Matrix<4, 4> scale = Scale(primitives[i].scale);

        Matrix<4, 4> model;
        model = CraeteModelMatrix(translation, rotation, scale);

        Matrix<4, 4> view = CreateViewMatrix(cameraPos, Vector3(0.0f, 0.0f, 0.0f),
                                             Vector3(0.0f, 1.0f, 0.0f));
        Matrix<4, 4> proj = Perspective(GetRadians(45.0f), 1024.0f / 720.0f, 0.1f, 100.0f);

        shaderProgram->setUniformVec3("light.ambient", lightAmb);
        shaderProgram->setUniformVec3("light.diffuse", lightDiff);
        shaderProgram->setUniformVec3("light.specular", lightSpec);
        shaderProgram->setUniformVec3("light.position", lightPos);

        shaderProgram->setUniformVec3("material.specular", materialSpec);
        shaderProgram->setUniformFloat("material.shininess", materialShine);

        shaderProgram->setUniformVec3("viewPos", cameraPos);

        shaderProgram->setUniformMat4("model", model);
        shaderProgram->setUniformMat4("view", view);
        shaderProgram->setUniformMat4("projection", proj);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        primitives[i].VAO.unbind();

        primitives[i].VBO.unbindAttribure();
         TextureHolder::getInstance().get(primitives[i].texture_id)->unbind();
    }
    for (int i = 0; i < objects.size(); ++i) {
        auto obj_ = objects[i];
        Matrix<4, 4> view = CreateViewMatrix(cameraPos, Vector3(0.0f, 0.0f, 0.0f),
                                             Vector3(0.0f, 1.0f, 0.0f));
        Matrix<4, 4> proj = Perspective(GetRadians(45.0f), 1024.0f / 720.0f, 0.1f, 100.0f);

        shaderProgram->setUniformVec3("light.ambient", lightAmb);
        shaderProgram->setUniformVec3("light.diffuse", lightDiff);
        shaderProgram->setUniformVec3("light.specular", lightSpec);
        shaderProgram->setUniformVec3("light.position", lightPos);

        shaderProgram->setUniformInt("material.diffuse", 0);
        shaderProgram->setUniformInt("material.normalMap", 1);
        shaderProgram->setUniformVec3("material.specular", materialSpec);
        shaderProgram->setUniformFloat("material.shininess", materialShine);

        shaderProgram->setUniformVec3("viewPos", cameraPos);

        shaderProgram->setUniformMat4("view", view);
        shaderProgram->setUniformMat4("projection", proj);
        obj_.bind();
        Matrix<4, 4> translation = Transform(obj_.get_position());
        Matrix<4, 4> rotation = Rotation(obj_.get_rotation().spin_vec, GetRadians(obj_.get_rotation().spin_deg));
        Matrix<4, 4> scale = Scale(obj_.get_scale());
        Matrix<4, 4> model = CraeteModelMatrix(translation, rotation, scale);
        shaderProgram->setUniformMat4("model", model);
        obj_.draw();
        obj_.unbind();
    }
    shaderProgram->unbind();

}

void scene::change_obj(int i) {
    selected_obj = i;
}

std::vector<Vertex> scene::getVertexes(geo_obj obj) {
    switch (obj) {
        case Cube:
            return {
                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},

                    Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
                    Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},

                    Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},

                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},

                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},

                    Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
            };
        case Sphere: {
            GLfloat radius = 1.0f;
            GLfloat PI = 3.14;
            int sectorCount = 10;
            int stackCount = 10;
            std::vector<Vertex> ans;
            float x, y, z, xy;                              // vertex position
            float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
            float s, t;                                     // vertex texCoord

            float sectorStep = 2 * PI / sectorCount;
            float stackStep = PI / stackCount;
            float sectorAngle, stackAngle;

            for (int i = 0; i <= stackCount; ++i) {
                stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
                xy = radius * cos(stackAngle);             // r * cos(u)
                z = radius * sin(stackAngle);              // r * sin(u)

                // add (sectorCount+1) vertices per stack
                // the first and last vertices have same position and normal, but different tex coords
                for (int j = 0; j <= sectorCount; ++j) {
                    sectorAngle = j * sectorStep;           // starting from 0 to 2pi

                    // vertex position (x, y, z)
                    x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
                    y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)
                    auto pos = Vector3(x, y, z);

                    // normalized vertex normal (nx, ny, nz)
                    nx = x * lengthInv;
                    ny = y * lengthInv;
                    nz = z * lengthInv;

                    // vertex tex coord (s, t) range between [0, 1]
                    s = (float) j / sectorCount;
                    t = (float) i / stackCount;
                    auto uv = Vector2(s, t);
                    ans.push_back(Vertex{pos, uv, Vector3(nx, ny, nz)});
                }
            }
            return ans;
        }
        case Tetrahedron: {
            GLfloat y_ = 0.366025;
            GLfloat med = 0.57735;
            GLfloat height = 0.366025;
            GLfloat z_ = 0.316497;

            auto res = {
                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.0f, -0.5, 0.5f), Vector2(0.5f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},

                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.0f, -0.5, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.0f, z_, 0.5f - med), Vector2(0.5f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},

                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.0f, -0.5, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.0f, z_, 0.5f - med), Vector2(0.5f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},

                    Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
                    Vertex{Vector3(0.0f, z_, 0.5f - med), Vector2(0.5f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},

            };
            return res;
        }
        case Surface: {
            return {
                    Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
                    Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
            };
        }
        default:
            return {};
    }
}

void scene::CreateObject(geo_obj obj) {
    if (obj != ModelObject) {
        std::vector<Vertex> vertices = getVertexes(obj);

        VertexArray VAO;
        VAO.bind();

        VertexBuffer VBO;
        VBO.bind(vertices);

        VBO.bindAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
        VBO.bindAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, uv));
        VBO.bindAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, norm));

        VAO.unbind();
        VBO.unbind();

        string name = "primitive " + to_string(primitives.size());
        primitives.push_back(primitive(VAO, VBO, name));
    } else {
        Object obj1;
        obj1.set_name("cottage");
        obj1.set_model("/home/bender/CLionProjects/GameEngine/res/models/cottage_fbx.fbx");
        obj1.set_texture("/home/bender/CLionProjects/GameEngine/res/models/cottage_diffuse.png");
        obj1.set_texture_norm("/home/bender/CLionProjects/GameEngine/res/models/cottage_normal.png");
        objects.push_back(obj1);
    }
}

scene::scene() {
    lightPos = Vector3(0.0f, 0.0f, 5.0f);
    lightAmb = Vector3(0.2f, 0.2f, 0.2f);
    lightDiff = Vector3(0.5f, 0.5f, 0.5f);
    lightSpec = Vector3(1.0f, 1.0f, 1.0f);
    materialSpec = Vector3(3.0f, 3.0f, 3.0f);
    cameraPos = Vector3(1.0f, 1.0f, 1.0f);
    materialShine = 32.0f;
    selected_obj = 0;
    add_object(Cube);
}

void scene::change_texture() {
    primitives[selected_obj].texture_id =
            (primitives[selected_obj].texture_id + 1) % TextureHolder::getInstance().size();
}



