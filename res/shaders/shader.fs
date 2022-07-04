#version 330 core

in vec2 uvTex;

out vec4 outColor;

uniform sampler2D texture;

void main() {
    outColor = texture2D(texture, uvTex);
}