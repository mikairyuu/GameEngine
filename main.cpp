#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <imgui.h>
//#include "imgui-sfml.h"

#include "libs/math/my_math.h"
#include "render/loader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb/stb_image.h"

using namespace std;

int main() {

    sf::ContextSettings settings;
    settings.depthBits = 24; // количество битов буффера глубины
    settings.stencilBits = 8; //количество битов буфера трафарета
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;

    sf::Window window(sf::VideoMode(800, 600, 32), "First Window",
                      sf::Style::Titlebar | sf::Style::Close, settings);

    glewExperimental = GL_TRUE; // включить все современные функции ogl

    if (GLEW_OK != glewInit()) { // включить glew
        cout << "Error:: glew not init =(" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    auto shaderProgram = ShaderLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/shaders/shader");



    float vertices [] = {
            // координаты        // текстурные координаты
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); //сгенерили id для массивов вершин (1 шт)
    glBindVertexArray(VAO); // связали массив с opengl

    glGenBuffers(1, &VBO); //буфер данных размером 1
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //связали буфер с opengl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //прокинули массив в opengl


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0); // прописали параметры для объекта
    glEnableVertexAttribArray(0); //layout y позиции 0

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float))); // прописали параметры для объекта
    glEnableVertexAttribArray(1); //цвет

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //снять бинд с массивов

    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("/home/bender/CLionProjects/GameEngine/res/img/me.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        cout << "Cant load img" << endl;
    }

    stbi_image_free(data);

    bool isGo = true;

    while (isGo) {
        sf::Event windowEvent;

        while (window.pollEvent(windowEvent)) { // обработка ивентов
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    isGo = false;
                    break;
                default:
                    break;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //отчистка экрана
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана

        shaderProgram.bind(); //прокидываем шейдерную прогу
       // glUseProgram(s);

        glBindVertexArray(VAO);

        glBindTexture(GL_TEXTURE_2D, texture);

        Matrix<4,4> model({
                           {1.0f,0,0,0},
                           {0,1.0f,0,0},
                           {0,0,1.0f,0},
                           {0,0,0,1.0f}
                   });

        Matrix<4,4>  view = CreateViewMatrix(Vector3(5.0f, 5.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        Matrix<4,4>  proj = Perspective(GetRadians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

        shaderProgram.setUniformMat4("model", model);
        shaderProgram.setUniformMat4("view", view);
        shaderProgram.setUniformMat4("projection", proj);




       glDrawArrays(GL_TRIANGLES, 0, 36);


        window.display();
    }


    window.close();
    return 0;
}