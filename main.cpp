#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include "libs/math/my_math.h"
#include "libs/math/tests.h"
#include "render/loader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


using namespace std;
auto vectorVAO = std::vector<VertexArray>();
auto vectorVBO = std::vector<VertexBuffer>();
std::vector<Vector3> angle_vec;
std::vector<Vector3> scale_vec;
std::vector<Vector3> translate_vec;
std::vector<float> spin_speed_vec;
std::vector<int> texture_id_vec;
std::vector<Vector3> angle;

std::vector<Vertex> getVertexes(int i) {
    switch (i) {
        case 1:
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
        case 2: {
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
        case 3: {
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
        case 4: {
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

void CreateObject(int i) {
    std::vector<Vertex> vertices = getVertexes(i);

    VertexArray VAO;
    VAO.bind();

    VertexBuffer VBO;
    VBO.bind(vertices);

    VBO.bindAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
    VBO.bindAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, uv));
    VBO.bindAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, norm));


    VAO.unbind();
    VBO.unbind();

    vectorVAO.push_back(VAO);
    vectorVBO.push_back(VBO);

    angle_vec.push_back(Vector3(0.0f));
    translate_vec.push_back(Vector3(0.0f));
    scale_vec.push_back(Vector3(1.0f));
    spin_speed_vec.push_back(0.0f);
    texture_id_vec.push_back(0);
    angle.push_back(Vector3(0.0f));
}

int main() {

    VectorTest();
    MatrixTest();
    sf::ContextSettings settings;
    settings.depthBits = 24; // количество битов буффера глубины
    settings.stencilBits = 8; //количество битов буфера трафарета
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    sf::RenderWindow window(sf::VideoMode(1024, 720, 32), "First Window", sf::Style::Titlebar | sf::Style::Close,
                            settings);
    window.setActive();
    window.setFramerateLimit(60);

    glEnable(GL_DEPTH_TEST);


    ImGui::SFML::Init(window);


    glewExperimental = GL_TRUE; // включить все современные функции ogl

    if (GLEW_OK != glewInit()) { // включить glew
        cout << "Error:: glew not init =(" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    auto shaderProgram = ShaderLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/shaders/shader");

    CreateObject(1);

    std::vector<std::shared_ptr<Texture>> texture_vec;
    texture_vec.push_back(
            TextureLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/img/kolkie.jpg"));
    texture_vec.push_back(
            TextureLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/img/me.jpg"));

    auto cameraPos = Vector3(3.0f, 3.0f, 3.0f);

    auto lightPos = Vector3(0.0f, 0.0f, 5.0f);
    auto lightAmb = Vector3(0.2f, 0.2f, 0.2f);
    auto lightDiff = Vector3(0.5f, 0.5f, 0.5f);
    auto lightSpec = Vector3(1.0f, 1.0f, 1.0f);

    auto materialSpec = Vector3(0.5f, 0.5f, 0.5f);
    auto materialShine = 32.0f;


    bool isGo = true;
    int selected_obj = 0;

    sf::Clock deltaClock;
    while (isGo) {
        sf::Event windowEvent{};

        while (window.pollEvent(windowEvent)) { // обработка ивентов


            ImGui::SFML::ProcessEvent(windowEvent);

            switch (windowEvent.type) {
                case sf::Event::Closed:
                    isGo = false;
                    break;
                default:
                    break;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана

        glEnable(GL_DEPTH_TEST);

        for (int i = 0; i < vectorVAO.size(); ++i) {
            texture_vec[texture_id_vec[i]]->bind();

            shaderProgram->bind();

            vectorVAO[i].bind();

            Matrix<4, 4> translation = Transform(translate_vec[i]);


            Matrix<4, 4> rotation = Rotation(Vector3(1, 0, 0), GetRadians(angle[i][0])) *
                                    Rotation(Vector3(0, 1, 0), GetRadians(angle[i][1])) *
                                    Rotation(Vector3(0, 0, 1), GetRadians(angle[i][2]));

            Matrix<4, 4> scale = Scale(scale_vec[i]);

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

            vectorVAO[i].unbind();

            vectorVBO[i].unbindAttribure();
            texture_vec[texture_id_vec[i]]->unbind();
            shaderProgram->unbind();
        }


        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window");
        {

            float scaleV[3] = {scale_vec[selected_obj].x, scale_vec[selected_obj].y, scale_vec[selected_obj].z};
            if (ImGui::SliderFloat("Scale", &scaleV[0], -10.0f, 10.0f)) {
                scaleV[1] = scaleV[0];
                scaleV[2] = scaleV[0];
                scale_vec[selected_obj].x = scaleV[0];
                scale_vec[selected_obj].y = scaleV[1];
                scale_vec[selected_obj].z = scaleV[2];
            }

            if (ImGui::SliderFloat3("", scaleV, -10.0f, 10.0f)) {
                scale_vec[selected_obj].x = scaleV[0];
                scale_vec[selected_obj].y = scaleV[1];
                scale_vec[selected_obj].z = scaleV[2];
            }

            float angleV[3] = {angle_vec[selected_obj].x, angle_vec[selected_obj].y, angle_vec[selected_obj].z};
            if (ImGui::SliderFloat3("Rotate", angleV, -360.0f, 360.0f)) {
                for (int i = 0; i < 3; ++i)
                    if (angleV[i] != angle_vec[selected_obj][i]) {
                        angle_vec[selected_obj][i] = angleV[i];
                        angle[selected_obj][i] = angleV[i];
                    }
            }

            float transV[3] = {translate_vec[selected_obj].x, translate_vec[selected_obj].y,
                               translate_vec[selected_obj].z};
            if (ImGui::SliderFloat3("Translate", transV, -10.0f, 10.0f)) {
                translate_vec[selected_obj][0] = transV[0];
                translate_vec[selected_obj][1] = transV[1];
                translate_vec[selected_obj][2] = transV[2];

            }
            float lightPosV[3] = {lightPos[0], lightPos[1], lightPos[2]};
            ImGui::SliderFloat("Shininess", &materialShine, 0.0f, 32.0f);
            if (ImGui::SliderFloat3("LightPos", lightPosV, -10.0f, 10.0f)) {
                lightPos[0] = lightPosV[0];
                lightPos[1] = lightPosV[1];
                lightPos[2] = lightPosV[2];
            }

        }

        if (ImGui::Button("Change Object", ImVec2(150, 25))) {
            selected_obj = (selected_obj + 1) % vectorVAO.size();
        }
        ImGui::SameLine();
        if (ImGui::Button("Change  texture", ImVec2(150, 25))) {
            texture_id_vec[selected_obj] = (texture_id_vec[selected_obj] + 1) % texture_vec.size();
        }
        if (ImGui::Button("Create Cube", ImVec2(150, 25))) {
            CreateObject(1);
        }
        ImGui::SameLine();
        if (ImGui::Button("Create Sphere", ImVec2(150, 25))) {
            CreateObject(2);
        }
        ImGui::SameLine();
        if (ImGui::Button("Create trian", ImVec2(150, 25))) {
            CreateObject(3);
        }
        ImGui::SameLine();
        if (ImGui::Button("Create surface", ImVec2(150, 25))) {
            CreateObject(4);
        }
        ImGui::End();

        ImGui::SFML::Render(window);

        window.display();
    }


    window.close();

    ImGui::SFML::Shutdown();
    return 0;
}