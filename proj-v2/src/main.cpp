#include "state.h"
#include "obj_loader.h"
#include "colors.h"
#include <iostream>
#include <GL/glut.h>

static State *gstate;
objl::Loader loader;
GLuint texture[1];

void draw_tree(void) {
  glPushMatrix();
  glTranslatef(100.0f, -5.0f, 50.0f);
  glScalef(10.0f, 10.0f, 10.0f);

  for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
    objl::Mesh mesh = loader.LoadedMeshes[i];
    int meshSize = mesh.Vertices.size();
    glBegin(GL_TRIANGLES);
    for (int j = 0; j < meshSize ; j++) {
      glTexCoord2f(mesh.Vertices[j].TextureCoordinate.X, mesh.Vertices[j].TextureCoordinate.Y);
      glNormal3f(mesh.Vertices[j].Normal.X, mesh.Vertices[j].Normal.Y, mesh.Vertices[j].Normal.Z);
      glVertex3f(mesh.Vertices[j].Position.X, mesh.Vertices[j].Position.Y, mesh.Vertices[j].Position.Z);
    }
    glEnd();
  }
  glPopMatrix();
}

void menu() {
  glutCreateMenu([](int value) { gstate->on_menu(value); });
  glutAddMenuEntry("Resetovat pozici", GameMenu_t::RESET_POS);
  glutAddMenuEntry("Vypnout/zapnout svetlo", GameMenu_t::FLASHLIGHT);
  glutAddMenuEntry("Vypnout/zapnout textury", GameMenu_t::TOGGLE_TEXTURE);
  glutAddMenuEntry("Vypnout/zapnout pohyb slunce", GameMenu_t::TOGGLE_SUN);
  glutAddMenuEntry("Ukončit", GameMenu_t::EXIT);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

static void gameInit(void) {
  glutWarpPointer(gstate->game.win_w / 2, gstate->game.win_h / 2);

  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
  glClearColor(sky.r, sky.g, sky.b, 1.0f);

  glutKeyboardFunc(
      [](unsigned char k, int x, int y) { gstate->input->dkey(k, x, y); });
  glutKeyboardUpFunc(
      [](unsigned char k, int x, int y) { 
      gstate->input->ukey(k, x, y); 
      if (k == ' ') {              
        gstate->shoot();
      }
  });
  glutPassiveMotionFunc([](int x, int y) { gstate->input->pmouse(x, y); });
  glutDisplayFunc([](void) { gstate->display(); });
  glutReshapeFunc([](int w, int h) { gstate->resize(w, h); });
  glutIdleFunc([](void) { gstate->idle(); });

  gstate->loaded = loader.LoadFile("assets/Untitled.obj");

  //if (gstate->game.fullscreen) {
  //  glutFullScreen();
  //}
}

int main(int argc, char **argv) {
  std::cout << "MPG" << std::endl;
  glutInit(&argc, argv);
  gstate = new State(draw_tree);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(gstate->game.win_w, gstate->game.win_h);
  glutCreateWindow("MPG");
  std::cout << "GL context created" << std::endl;

  menu();
  gameInit();
  glutMainLoop();

  return 0;
}
