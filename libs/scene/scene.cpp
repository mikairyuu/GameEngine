//
// Created by bender on 10.07.22.
//

#include "scene.h"

void scene::render() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана

    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < objects.size(); ++i) {
        TextureHolder::getInstance().get(objects[i].texture_id)->bind();

        shaderProgram->bind();

        objects[i].VAO.bind();

        Matrix<4, 4> translation = Transform(objects[i].translate);


        Matrix<4, 4> rotation = Rotation(Vector3(1, 0, 0), GetRadians(objects[selected_obj].angle[0])) *
                                Rotation(Vector3(0, 1, 0), GetRadians(objects[selected_obj].angle[1])) *
                                Rotation(Vector3(0, 0, 1), GetRadians(objects[selected_obj].angle[2]));

        Matrix<4, 4> scale = Scale(objects[i].scale);

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

        objects[i].VAO.unbind();

        objects[i].VBO.unbindAttribure();
        TextureHolder::getInstance().get(objects[i].texture_id)->unbind();
        shaderProgram->unbind();
    }

}

void scene::change_obj() {
    selected_obj = (select_obj + 1) % objects.size();
}

std::vector<Vertex> scene::getVertexes(primitive primitive) {
    switch (primitive) {
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

void scene::CreateObject(primitive primitive) {
    std::vector<Vertex> vertices = getVertexes(primitive);

    VertexArray VAO;
    VAO.bind();

    VertexBuffer VBO;
    VBO.bind(vertices);

    VBO.bindAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
    VBO.bindAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, uv));
    VBO.bindAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, norm));

    VAO.unbind();
    VBO.unbind();

    objects.push_back(object(VAO, VBO));
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
    objects[selected_obj].texture_id = (objects[selected_obj].texture_id + 1) % TextureHolder::getInstance().size();
}



