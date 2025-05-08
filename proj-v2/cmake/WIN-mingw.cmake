set(CMAKE_SYSTEM_NAME Windows)

set(MINGW_PREFIX /opt/homebrew/opt/mingw-w64)

set(CMAKE_C_COMPILER   ${MINGW_PREFIX}/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER ${MINGW_PREFIX}/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER  ${MINGW_PREFIX}/bin/x86_64-w64-mingw32-windres)

set(CMAKE_AR        ${MINGW_PREFIX}/bin/x86_64-w64-mingw32-ar      CACHE FILEPATH "")
set(CMAKE_RANLIB    ${MINGW_PREFIX}/bin/x86_64-w64-mingw32-ranlib  CACHE FILEPATH "")
set(CMAKE_LINKER    ${MINGW_PREFIX}/bin/x86_64-w64-mingw32-ld      CACHE FILEPATH "")

set(CMAKE_FIND_ROOT_PATH          ${MINGW_PREFIX}/toolchain-x86_64/x86_64-w64-mingw32/)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY  ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE  ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE  ONLY)

find_package(OpenGL REQUIRED)
find_path(GLUT_INCLUDE_DIR GLUT/glut.h
    HINTS "${CMAKE_FIND_ROOT_PATH}/include"
)
find_library(GLUT_LIBRARY
    NAMES freeglut glut32
    HINTS "${CMAKE_FIND_ROOT_PATH}/lib"
)
target_include_directories(projmpg PRIVATE
  ${GLUT_INCLUDE_DIR}     # so <GL/glut.h> is found
)
target_link_libraries(projmpg PRIVATE
  OpenGL::GL              # links -lopengl32
  ${GLUT_LIBRARY}         # links -lfreeglut or -lglut32
  glu32                   # GLU on Windows
  winmm                   # WinMM is often needed by GLUT
  gdi32                   # GDI is needed for windowing
)
