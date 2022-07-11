cmake_minimum_required(VERSION 3.22)
project(GameEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameEngine main.cpp libs/math/vector.h libs/math/matrix.h libs/math/my_math.h libs/math/tests.h render/loader.cpp render/loader.h libs/utils/shaderLoader.cpp libs/utils/shaderLoader.h libs/scene/scene.cpp libs/scene/scene.h libs/scene/object/primitive.h libs/utils/assimpParser.cpp libs/utils/assimpParser.h)
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})
find_package(GLEW)
include_directories(${GLEW_INCLUDE_DIRS})
find_package(assimp REQUIRED)
find_package(ImGui-SFML REQUIRED)
target_link_libraries(GameEngine PRIVATE ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} ImGui-SFML::ImGui-SFML sfml-graphics)

