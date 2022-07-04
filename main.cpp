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
            // координаты        // текстурные координаты
            Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f)},

            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)},

            Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},

            Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},

            Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f)},

            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f)},
            Vertex{Vector3(0.5f, 0.5f, -0.5f), Vector2(1.0f, 1.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
            Vertex{Vector3(-0.5f, 0.5f, -0.5f), Vector2(0.0f, 1.0f)},
    };

    VertexArray VAO;
    VAO.bind();

    VertexBuffer VBO;
    VBO.bind(vertices);

    VBO.bindAttribute(0, 3, 1, offsetof(Vertex, pos));

    VBO.bindAttribute(1, 2, 1, offsetof(Vertex, uv));

    VAO.unbind();
    VBO.unbind();


    auto texture = TextureLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/img/kolkie.jpg");

    bool isGo = true;
    float deg = 0.0f;
    Vector3 scale_vec(1.0f);
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

        Matrix<4, 4> translation = Transform(Vector3(0.5, 0, 0.5));

        Matrix<4, 4> rotation = Rotation(Vector3(0, 1, 0), GetRadians(deg));

        deg += spinSpeed;

        Matrix<4, 4> scale = Scale(scale_vec);

        Matrix<4, 4> model;
        model = CraeteModelMatrix(translation, rotation, scale);// * identity(model);

        Matrix<4, 4> view = CreateViewMatrix(Vector3(3.0f, 3.0f, 3.0f), Vector3(0.0f, 0.0f, 0.0f),
                                             Vector3(0.0f, 1.0f, 0.0f));
        Matrix<4, 4> proj = Perspective(GetRadians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

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
        ImGui::Text("Hi!");
        ImGui::SliderFloat("Degree", &deg, -360.0f, 360.0f);
        ImGui::SliderFloat("Spin speed", &spinSpeed, -360.0f, 360.0f);


        if (ImGui::SliderFloat("Scale prop", &scaleV[0], -10.0f, 10.0f)) {
            scaleV[1] = scaleV[0];
            scaleV[2] = scaleV[0];
            scale_vec.x = scaleV[0];
            scale_vec.y = scaleV[1];
            scale_vec.z = scaleV[2];
        }

        if (ImGui::SliderFloat3("Scale", scaleV, -10.0f, 10.0f)) {
            scale_vec.x = scaleV[0];
            scale_vec.y = scaleV[1];
            scale_vec.z = scaleV[2];
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