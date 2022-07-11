
#include "loader.h"
#include "../libs/utils/shaderLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/utils/assimpParser.h"
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

void Shader::setUniformVec3(std::string name, Vector3 vec) {
    glUniform3fv(glGetUniformLocation(id.id, name.c_str()), 1, &vec[0]);
}

void Shader::setUniformFloat(std::string name, float number) {
    glUniform1f(glGetUniformLocation(id.id, name.c_str()), number);
}

void Shader::setUniformInt(std::string name, int number) {
    glUniform1i(glGetUniformLocation(id.id, name.c_str()), number);
}

std::unique_ptr<ShaderLoader> ShaderLoader::instance = nullptr;

ShaderLoader &ShaderLoader::getInstance() {
    if (instance) {
        return *instance;
    }
    instance = std::unique_ptr<ShaderLoader>(new ShaderLoader());
    return *instance;
}


std::shared_ptr<Shader> ShaderLoader::load(std::string path) {
    auto _id = LoadShaders(path + ".vs", path + ".fs");
    auto shader = new Shader();
    shader->id.id = _id;
    return std::shared_ptr<Shader>(shader);
}

Texture::Texture() {
    unsigned int texture;
    glGenTextures(1, &texture);
    id = Id<Texture>{texture};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id.id);
}

void Texture::bind(int texSlot)
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, id.id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::unbind(int texSlot)
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::unique_ptr<TextureLoader> TextureLoader::instance = nullptr;

TextureLoader &TextureLoader::getInstance() {
    if (instance) {
        return *instance;
    }
    instance = std::unique_ptr<TextureLoader>(new TextureLoader());
    return *instance;
}

std::shared_ptr<Texture> TextureLoader::load(std::string path) {
    stbi_set_flip_vertically_on_load(true);

    const auto texture = new Texture();
    texture->bind(0);
    int width, height, nrChannels;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Cant load img" << std::endl;
    }

    stbi_image_free(data);
    texture->unbind(0);
    return std::shared_ptr<Texture>(texture);
}


std::shared_ptr<Texture> TextureLoader::genTexture() {
    srand(time(nullptr));
    struct {
        unsigned char r, g, b;
    } data[1];
    data[0].r = rand() % 256;
    data[0].g = rand() % 256;
    data[0].b = rand() % 256;

    const auto texture = new Texture();
    texture->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


    texture->unbind();
    return std::shared_ptr<Texture>(texture);
}

std::unique_ptr<TextureHolder> TextureHolder::instance = nullptr;

TextureHolder &TextureHolder::getInstance() {
    if (instance) {
        return *instance;
    }
    instance = std::unique_ptr<TextureHolder>(new TextureHolder());
    return *instance;
}


void Mesh::createBuffers(std::vector<Vertex>& p_vertices, std::vector<unsigned>& p_indices)
{
    vertexArray.bind();

    vertexBuffer = std::make_unique<VertexBuffer>();
    indexBuffer = std::make_unique<IndexBuffer>();

    uint32_t vertexSize = sizeof(Vertex);

    vertexBuffer->bind(p_vertices);
    indexBuffer->bind(p_indices);

    vertexBuffer->bindAttribute(0, 3, vertexSize, offsetof(Vertex, pos));
    vertexBuffer->bindAttribute(1, 2, vertexSize, offsetof(Vertex, uv));
    vertexBuffer->bindAttribute(2, 3, vertexSize, offsetof(Vertex, norm));
    vertexBuffer->bindAttribute(3, 3, vertexSize, offsetof(Vertex, tangent));
    vertexBuffer->bindAttribute(4, 3, vertexSize, offsetof(Vertex, bitangent));

    vertexArray.unbind();
    vertexBuffer->unbind();
    vertexBuffer->unbindAttribure();
}


void Object::set_model(const std::string path)
{
    EModelParserFlags flags = EModelParserFlags::TRIANGULATE;
    flags |= EModelParserFlags::GEN_SMOOTH_NORMALS;
    flags |= EModelParserFlags::CALC_TANGENT_SPACE;
    AssimpParser().LoadModel(path, this->model, flags);
}