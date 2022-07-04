#version 330 core

// Входные данные вершин, различные для всех запусков этого шейдера
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 norm;

// Выходные данные, которые будут интерполированы для каждого фрагмента
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 UvTex;
out vec3 Norm;
out vec3 FragPos;

void main() {


    // UV-координаты вершины.
    UvTex = vertexUV;
    Norm = mat3(transpose(inverse(model))) * norm;
    FragPos = vec3(model * vec4(vertexPosition_modelspace, 1.0));
    gl_Position = projection * view * model * vec4(vertexPosition_modelspace, 1.0f);
}