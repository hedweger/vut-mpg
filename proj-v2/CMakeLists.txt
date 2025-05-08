cmake_minimum_required(VERSION 3.10)
project(projmpg)

set(CMAKE_CROSSCOMPILING true)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define deps dir
set(DEPS_DIR "${CMAKE_SOURCE_DIR}/nupengl")

# Locate GLUT deps
set(GLUT_INCLUDE_DIR "${DEPS_DIR}/nupengl.core.0.1.0.1/build/native/include")
set(GLUT_LIB_DIR "${DEPS_DIR}/nupengl.core.0.1.0.1/build/native/lib/x64")
set(GLUT_DLL_DIR "${DEPS_DIR}/nupengl.core.redist.0.1.0.1/build/native/bin/x64")
set(GLUT_GLFW3_DLL "${GLUT_DLL_DIR}/glfw3.dll")
set(GLUT_GLEW32_DLL "${GLUT_DLL_DIR}/glew32.dll")
set(GLUT_FREEGLUT_DLL "${GLUT_DLL_DIR}/freeglut.dll")

message(${CMAKE_SOURCE_DIR}/nupengl)

include_directories(${CMAKE_SOURCE_DIR}/deps ${GLUT_INCLUDE_DIR})

link_directories(${GLUT_LIB_DIR})

# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS deps/*.h)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLUT_LIB_DIR})


# Copy freeglut.dll to the output directory
add_custom_command(TARGET projmpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${GLUT_FREEGLUT_DLL}"
    ${CMAKE_BINARY_DIR}
)

# Copy glew32.dll to the output directory
add_custom_command(TARGET projmpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${GLUT_GLEW32_DLL}"
    ${CMAKE_BINARY_DIR}
)

# Copy glfw3.dll to the output directory
add_custom_command(TARGET projmpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${GLUT_GLFW3_DLL}"
    ${CMAKE_BINARY_DIR}
)

# Copy assets dir to the output directory
add_custom_command(TARGET projmpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets/"
    "${CMAKE_BINARY_DIR}/assets/"
)