#include <memory>
#include "../libs/math/my_math.h"
#include <GL/glew.h>
#include <vector>

#pragma once

template<typename T>
struct Id {
    unsigned id = 0;
};

class Shader {

    friend class ShaderLoader;

    Id<Shader> id;

    Shader() {}

public:

    void bind();

    void unbind();

    void setUniformMat4(std::string name, Matrix<4, 4> mat);

    void setUniformVec3(std::string name, Vector3 vec);

    void setUniformFloat(std::string name, float number);

    void setUniformInt(std::string name, int number);
};

class ShaderLoader {
public:
    ShaderLoader(ShaderLoader &) = delete;

    ShaderLoader(ShaderLoader &&) = delete;

    static ShaderLoader &getInstance();

    std::shared_ptr<Shader> load(std::string path);

    ShaderLoader() = default;

private:

    static std::unique_ptr<ShaderLoader> instance;

};

class Texture {
    friend class TextureLoader;

    Id<Texture> id;

    Texture();

public:
    void bind();

    void bind(int texSlot);

    void unbind();

    void unbind(int texSlot);
};

class TextureLoader {
public:
    TextureLoader(TextureLoader &) = delete;

    TextureLoader(TextureLoader &&) = delete;

    static TextureLoader &getInstance();

    std::shared_ptr<Texture> load(std::string path);

    shared_ptr<Texture> genTexture();

private:
    TextureLoader() = default;

    static std::unique_ptr<TextureLoader> instance;


};


class TextureHolder {
public:

    TextureHolder(TextureHolder &) = delete;

    TextureHolder(TextureHolder &&) = delete;

    static TextureHolder &getInstance();

    void add(std::shared_ptr<Texture> texture) {
        texture_vec.push_back(texture);
    }

    std::shared_ptr<Texture> get(int i) {
        return texture_vec[i];
    }

    int size() {
        return texture_vec.size();
    }

private:
    std::vector<std::shared_ptr<Texture>> texture_vec;

    TextureHolder() = default;

    static std::unique_ptr<TextureHolder> instance;


};

struct Vertex {
    Vector3 pos;
    Vector2 uv;
    Vector3 norm;
    Vector3 tangent;
    Vector3 bitangent;
};

class VertexArray {
    Id<VertexArray> id;
public:
    VertexArray() {
        glGenVertexArrays(1, &id.id);
    }

    void bind() {
        glBindVertexArray(id.id);
    }

    void unbind() {
        glBindVertexArray(0);
    }
};

class VertexBuffer {
    Id<VertexBuffer> id;
public:
    VertexBuffer() {
        glGenBuffers(1, &id.id);
    }

    void bind(std::vector<Vertex> &data) {
        glBindBuffer(GL_ARRAY_BUFFER, id.id);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
    }

    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void bindAttribute(int index, int size, int vertSize, intptr_t offset) {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, vertSize, (void *) (intptr_t) offset);
        glEnableVertexAttribArray(index);
    }

    void unbindAttribure() {
        glDisableVertexAttribArray(0);
    }
};

class IndexBuffer {
    Id<IndexBuffer> id;

public:
    enum class UsageType : uint8_t {
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY,
        DYNAMIC_DRAW,
        DYNAMIC_READ,
        DYNAMIC_COPY,
    };
    std::vector<GLenum> UsageTypeToEnum = {
            GL_STREAM_DRAW,
            GL_STREAM_READ,
            GL_STREAM_COPY,
            GL_STATIC_DRAW,
            GL_STATIC_READ,
            GL_STATIC_COPY,
            GL_DYNAMIC_DRAW,
            GL_DYNAMIC_READ,
            GL_DYNAMIC_COPY,
    };

    IndexBuffer() {
        glGenBuffers(1, &id.id);
    }

    void bind(std::vector<unsigned> &data) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned), data.data(), GL_STATIC_DRAW);
    }

    void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

};

class Mesh {
public:
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned> &indices, unsigned materialIndex) :
            vertexCount(static_cast<unsigned>(vertices.size())),
            indicesCount(static_cast<unsigned>(vertices.size())),
            materialIndex(materialIndex),
            indices(indices),
            vertices(vertices) {
        createBuffers(vertices, indices);
    }

    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    ~Mesh() = default;

    virtual void bind() {
        vertexArray.bind();
    }

    virtual void unbind() {
        vertexArray.unbind();
    }

    virtual unsigned getVertexCount() {
        return vertexCount;
    }

    virtual unsigned getIndexCount() {
        return indicesCount;
    }

    uint32_t getMaterialIndex() const {
        return materialIndex;
    }

private:
    void createBuffers(std::vector<Vertex> &p_vertices, std::vector<unsigned> &p_indices);

    void createBuffers(std::vector<Vertex> &p_vertices);

public:
    const unsigned int vertexCount;
    const unsigned int indicesCount;
    const unsigned int materialIndex;

    VertexArray vertexArray;
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<IndexBuffer> indexBuffer;

};

class Model {
public:
    std::vector<Mesh *> meshes;
    std::vector<std::string> materialNames;
};


class Object {
    struct Spin {
        Vector3 spin_vec;
        float spin_deg;
    };
public:

    Object() {
        this->position = Vector3(0.0f);
        this->scale = Vector3(1.0f);
        this->spin = {Vector3(0.0f), 0.0f};
        this->model = std::make_shared<Model>();
    }

    void draw() {
        for (auto &m: this->model->meshes)
            glDrawElements(GL_TRIANGLES, m->getIndexCount(), GL_UNSIGNED_INT, 0);
    }

    void bind() {
        this->texture->bind(0);
        this->textureNorm->bind(1);
        for (auto &m: this->model->meshes)
            m->bind();
    }

    void unbind() {
        this->texture->unbind(0);
        this->textureNorm->unbind(1);
        for (auto &m: this->model->meshes)
            m->unbind();
    }

    void set_name(std::string name) {
        this->name = name;
    }

    std::string get_name() {
        return this->name;
    }

    void set_model(const std::string path);

    void set_texture(std::string path) {
        this->texture = TextureLoader::getInstance().load(path);
    }

    void set_texture_norm(std::string path) {
        this->textureNorm = TextureLoader::getInstance().load(path);
    }

    void set_position(Vector3 pos) {
        this->position = pos;
    }

    Vector3 get_position() {
        return this->position;
    }

    void set_scale(Vector3 scale) {
        this->scale = scale;
    }

    Vector3 get_scale() {
        return this->scale;
    }

    void set_rotation(Vector3 spin_vec, float spin_deg) {
        if (spin_deg > 360)
            spin_deg = 360;
        else if (spin_deg < -360)
            spin_deg = -360;
        this->spin = {spin_vec, spin_deg};
    }

    Spin get_rotation() {
        return this->spin;
    }

private:
    Id<Object> id;
    std::string name;
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> textureNorm;
    Vector3 position;
    Vector3 scale;
    Spin spin;
    int rotationX;
    int rotationY;
    int rotationZ;
};