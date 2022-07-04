#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "libs/math/my_math.h"
#include "render/loader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


using namespace std;

int main() {

    sf::ContextSettings settings;
    settings.depthBits = 24; // количество битов буффера глубины
    settings.stencilBits = 8; //количество битов буфера трафарета
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    // settings.attributeFlags = sf::ContextSettings::Core;


    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "First Window", sf::Style::Titlebar | sf::Style::Close,
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

    std::vector<Vertex> vertices = {
            Vertex{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), 	Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), 	Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},

            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
            Vertex{Vector3(-0.5f, 0.5f, 0.5f), 	Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},

            Vertex{Vector3(-0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},

            Vertex{Vector3(0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), 	Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), 	Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},

            Vertex{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},

            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), 	Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), 	Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, 0.5f), 	Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
    };

    VertexArray VAO;
    VAO.bind();

    VertexBuffer VBO;
    VBO.bind(vertices);

    VBO.bindAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
    VBO.bindAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, uv));
    VBO.bindAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, norm));



    VAO.unbind();
    VBO.unbind();


    auto texture = TextureLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/img/kolkie.jpg");

    auto cameraPos = Vector3(3.0f, 3.0f, 3.0f);

    auto lightPos = Vector3(0.0f, 0.0f, 5.0f);
    auto lightAmb = Vector3(0.2f, 0.2f, 0.2f);
    auto lightDiff = Vector3(0.5f, 0.5f, 0.5f);
    auto lightSpec = Vector3(1.0f, 1.0f, 1.0f);

    auto materialSpec = Vector3(0.5f, 0.5f, 0.5f);
    auto materialShine = 32.0f;

    bool isGo = true;
    float deg = 0.0f;
    Vector3 scale_vec(1.0f);
    Vector3 translate_vec(0.0f);
    float scaleV[3] = {1.0f, 1.0f, 1.0f};
    float spinSpeed = 0.0f;

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

        texture->bind();

        shaderProgram->bind();

        VAO.bind();

        Matrix<4, 4> translation = Transform(translate_vec);

        Matrix<4, 4> rotation = Rotation(Vector3(0, 1, 0), GetRadians(deg));

        deg += spinSpeed;

        Matrix<4, 4> scale = Scale(scale_vec);

        Matrix<4, 4> model;
        model = CraeteModelMatrix(translation, rotation, scale);// * identity(model);

        Matrix<4, 4> view = CreateViewMatrix(cameraPos, Vector3(0.0f, 0.0f, 0.0f),
                                             Vector3(0.0f, 1.0f, 0.0f));
        Matrix<4, 4> proj = Perspective(GetRadians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

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

        VAO.unbind();

        VBO.unbindAttribure();
        texture->unbind();
        shaderProgram->unbind();

        if (abs(deg) > 360)
            deg = 0.0f;

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window title");
        {
            static int tabb = 0;
            ImGui::SameLine();
            if (ImGui::Button("Scale", ImVec2(150, 25)))
            {
                tabb = 0;
            }
            ImGui::SameLine();
            if (ImGui::Button("Rotate", ImVec2(150, 25)))
            {
                tabb = 1;
            }
            ImGui::SameLine();
            if (ImGui::Button("Translate", ImVec2(150, 25)))
            {
                tabb = 2;
            }
            ImGui::SameLine();
            if (ImGui::Button("Light", ImVec2(150, 25)))
            {
                tabb = 3;
            }
            if (tabb == 0)
            {
                static float scaleV[3] = {1.0f, 1.0f, 1.0f};
                if (ImGui::SliderFloat("Scale prop", &scaleV[0], -10.0f, 10.0f))
                {
                    scaleV[1] = scaleV[0];
                    scaleV[2] = scaleV[0];
                    scale_vec.x = scaleV[0];
                    scale_vec.y = scaleV[1];
                    scale_vec.z = scaleV[2];
                }

                if (ImGui::SliderFloat3("Scale", scaleV, -10.0f, 10.0f))
                {
                    scale_vec.x = scaleV[0];
                    scale_vec.y = scaleV[1];
                    scale_vec.z = scaleV[2];
                }
            }
            if (tabb == 1)
            {
                ImGui::SliderFloat("Degree", &deg, -360.0f, 360.0f);
                ImGui::SliderFloat("Spin speed", &spinSpeed, -360.0f, 360.0f);
            }
            if (tabb == 2)
            {
                static float transV[3] = {0.0f, 0.0f, 0.0f};
                if(ImGui::SliderFloat3("Translate vector", transV, -10.0f, 10.0f))
                {
                    translate_vec[0] = transV[0];
                    translate_vec[1] = transV[1];
                    translate_vec[2] = transV[2];
                }
            }
            if(tabb == 3)
            {
                static float lightPosV[3] = {0.0f, 0.0f, 0.0f};
                ImGui::SliderFloat("Shininess", &materialShine, 0.0f, 32.0f);
                if(ImGui::SliderFloat3("LightPos", lightPosV, -10.0f, 10.0f))
                {
                    lightPos[0] = lightPosV[0];
                    lightPos[1] = lightPosV[1];
                    lightPos[2] = lightPosV[2];
                }
            }
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::SFML::Render(window);

        window.display();
    }


    window.close();

    ImGui::SFML::Shutdown();
    return 0;
}