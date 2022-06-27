 #version 330 core

// Интерполированные значения из вершинного шейдера
in vec2 UV;

// Выходные данные
out vec3 color;

// Значения, которые остаются неизменными для объекта.
uniform sampler2D myTextureSampler;

void main(){

    // Выходной цвет = цвету текстуры в указанных UV-координатах
    color = texture( myTextureSampler, UV ).rgb;
}