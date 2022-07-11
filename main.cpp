#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "libs/utils/assimpParser.h"
#include "libs/scene/scene.h"

using namespace std;

int main() {

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
        cout << "Error:: glew not init" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    auto scene = new class scene();

    TextureHolder::getInstance().add(
            TextureLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/img/kolkie.jpg"));
    TextureHolder::getInstance().add(
            TextureLoader::getInstance().load("/home/bender/CLionProjects/GameEngine/res/img/me.jpg"));

    bool isGo = true;
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
        auto selected_obj = scene->primitives[scene->selected_obj];


        scene->render();

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window");
        {
            float scaleV[3] = {selected_obj.scale.x,
                               selected_obj.scale.y,
                               selected_obj.scale.z};
            if (ImGui::SliderFloat("Scale", &scaleV[0], -10.0f, 10.0f)) {
                scaleV[1] = scaleV[0];
                scaleV[2] = scaleV[0];
                scene->scale_obj(Vector3(scaleV[0], scaleV[1], scaleV[2]));
            }

            if (ImGui::SliderFloat3("", scaleV, -10.0f, 10.0f)) {
                scene->scale_obj(Vector3(scaleV[0], scaleV[1], scaleV[2]));
            }

            float angleV[3] = {selected_obj.angle.x, selected_obj.angle.y, selected_obj.angle.z};
            if (ImGui::SliderFloat3("Rotate", angleV, -360.0f, 360.0f)) {
                scene->rotate_obj(Vector3(angleV[0], angleV[1], angleV[2]));
            }

            float transV[3] = {selected_obj.translate.x, selected_obj.translate.y,
                               selected_obj.translate.z};
            if (ImGui::SliderFloat3("Translate", transV, -10.0f, 10.0f)) {
                scene->translate_obj(Vector3(transV[0], transV[1], transV[2]));

            }
            float lightPosV[3] = {scene->lightPos.x, scene->lightPos.y, scene->lightPos.z};
            ImGui::SliderFloat("Shininess", &scene->materialShine, 0.0f, 32.0f);
            if (ImGui::SliderFloat3("LightPos", lightPosV, -10.0f, 10.0f)) {
                scene->lightPos.x = lightPosV[0];
                scene->lightPos.y = lightPosV[1];
                scene->lightPos.z = lightPosV[2];
            }

        }

        if (ImGui::BeginCombo("ObjectList", selected_obj.name.c_str())) {
            if (scene->primitives.size() > 1)
                for (int i = 0; i < scene->primitives.size(); i++) {
                    if (ImGui::Selectable(scene->primitives[i].name.c_str())) {
                        scene->change_obj(i);
                    }
                }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Change  texture", ImVec2(150, 25))) {
            scene->change_texture();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add  texture", ImVec2(150, 25))) {
            TextureHolder::getInstance().add(TextureLoader::getInstance().genTexture());
        }
        ImGui::SameLine();
        if (ImGui::Button("Create ModelObject", ImVec2(150, 25))) {
            scene->add_object(ModelObject);
        }
        if (ImGui::Button("Create Cube", ImVec2(150, 25))) {
            scene->add_object(Cube);
        }
        ImGui::SameLine();
        if (ImGui::Button("Create Sphere", ImVec2(150, 25))) {
            scene->add_object(Sphere);
        }
        ImGui::SameLine();
        if (ImGui::Button("Create trian", ImVec2(150, 25))) {
            scene->add_object(Tetrahedron);;
        }
        ImGui::SameLine();
        if (ImGui::Button("Create surface", ImVec2(150, 25))) {
            scene->add_object(Surface);
        }
        ImGui::End();

        ImGui::SFML::Render(window);

        window.display();
    }


    window.close();

    ImGui::SFML::Shutdown();
    return 0;
}