cmake_minimum_required(VERSION 3.10)
project(projmpg)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

include_directories(${CMAKE_SOURCE_DIR}/deps)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS deps/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
