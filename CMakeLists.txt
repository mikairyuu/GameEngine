cmake_minimum_required(VERSION 3.22)
project(GameEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameEngine main.cpp libs/math/vector.h libs/math/matrix.h libs/math/my_math.h libs/math/tests.h)
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(GameEngine ${OPENGL_LIBRARY})
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(GameEngine ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}) # Link SFML and dependencies

find_package(GLEW)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(GameEngine ${GLEW_LIBRARIES})

target_link_libraries(GameEngine sfml-graphics)