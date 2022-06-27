#include "loader.h"
#include "../libs/utils/shaderLoader.h"

void Shader::bind() {
    glUseProgram(id.id);
}

void Shader::unbind() {
    glUseProgram(0);
}

Shader::Shader(Id id_) {
    this->id = id_;
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

Shader ShaderLoader::load(std::string path) {
    auto _id = LoadShaders(path + ".vs", path + ".fs");
    auto asd = Shader(Id{_id});
    return asd;
}