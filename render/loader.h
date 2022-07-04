#include <memory>
#include "../libs/math/my_math.h"
#include <GL/glew.h>
#include <vector>

template<typename T>
struct Id {
    unsigned  id;
};

class Shader{

    friend class ShaderLoader;

    Id<Shader> id;
    Shader(){}
public:

    void bind();
    void unbind();
    void setUniformMat4(std::string name, Matrix<4, 4>  mat);
};

class ShaderLoader{
public:
    ShaderLoader(ShaderLoader&) = delete;
    ShaderLoader(ShaderLoader&&) = delete;

    static ShaderLoader& getInstance();
    std::shared_ptr<Shader> load(std::string path);

private:
    ShaderLoader() = default;
    static std::unique_ptr<ShaderLoader> instance;

};

class Texture{
    friend class TextureLoader;

    Id<Texture> id;
    Texture();
public:
    void bind();
    void unbind();
};

class TextureLoader{
public:
    TextureLoader(TextureLoader&) = delete;
    TextureLoader(TextureLoader&&) = delete;

    static TextureLoader& getInstance();
    std:: shared_ptr<Texture> load(std::string path);

private:
    TextureLoader() = default;
    static std::unique_ptr<TextureLoader> instance;
};

struct Vertex {
    Vector3 pos;
    Vector2 uv;
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
    void bind(std::vector<Vertex>& data) {
        glBindBuffer(GL_ARRAY_BUFFER, id.id);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
    }
    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void bindAttribute(int index, int size, int vertSize, intptr_t offset) {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, vertSize * sizeof(Vertex), (void*)(intptr_t)offset);
        glEnableVertexAttribArray(index);
    }

    void unbindAttribure() {
        glDisableVertexAttribArray(0);
    }
};