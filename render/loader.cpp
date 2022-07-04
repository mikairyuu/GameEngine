#include "loader.h"
#include "../libs/utils/shaderLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>


void Shader::bind() {
    glUseProgram(id.id);
}

void Shader::unbind() {
    glUseProgram(0);
}



void Shader::setUniformMat4(std::string name, Matrix<4, 4> mat) {
    glUniformMatrix4fv(glGetUniformLocation(id.id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

std::unique_ptr<ShaderLoader> ShaderLoader::instance = nullptr;

ShaderLoader &ShaderLoader::getInstance() {
    if (instance) {
        return *instance;
    }
    instance = std::unique_ptr<ShaderLoader>(new ShaderLoader());
    return *instance;
}


std::shared_ptr<Shader> ShaderLoader::load(std::string path){
    auto _id = LoadShaders(path + ".vs", path + ".fs");
    auto shader = new Shader();
    shader->id.id = _id;
    return std::shared_ptr<Shader>(shader);
}

Texture::Texture(){
    unsigned int texture;
    glGenTextures(1, &texture);
    id = Id<Texture>{texture};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, id.id);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::unique_ptr<TextureLoader> TextureLoader::instance = nullptr;

TextureLoader& TextureLoader::getInstance(){
    if(instance){
        return *instance;
    }
    instance = std::unique_ptr<TextureLoader>(new TextureLoader());
    return *instance;
}

std::shared_ptr<Texture> TextureLoader::load(std::string path){
    stbi_set_flip_vertically_on_load(true);

    const auto texture = new Texture();
    texture->bind();
    int width, height, nrChannels;

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Cant load img" << std::endl;
    }

    stbi_image_free(data);
    texture->unbind();
    return std::shared_ptr<Texture>(texture);
}