cmake_minimum_required(VERSION 3.10)
project(projmpg)

set(CMAKE_CROSSCOMPILING true)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/deps)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS deps/*.h)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE
  #${GLUT_INCLUDE_DIR}
  #)
#target_link_libraries(${PROJECT_NAME} PRIVATE
  #${GLUT_LIBRARY}         # freeglut or glut32
  #OpenGL::GL              # -lopengl32
  #OpenGL::GLU             # -lglu32
  #)
