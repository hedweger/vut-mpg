#include "state.h"
#include <GLUT/glut.h>

static State *gstate;

static void gameInit(void) {
  glutWarpPointer(gstate->game.win_w / 2, gstate->game.win_h / 2);

  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);
  glutSetCursor(GLUT_CURSOR_NONE);

  GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat position[] = {0.0f, 50.0f, 50.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glClearColor(0.2, 0.6, 1.0, 1.0);

  glutKeyboardFunc(
      [](unsigned char k, int x, int y) { gstate->input->dkey(k, x, y); });
  glutKeyboardUpFunc(
      [](unsigned char k, int x, int y) { gstate->input->ukey(k, x, y); });
  glutPassiveMotionFunc([](int x, int y) { gstate->input->pmouse(x, y); });
  glutDisplayFunc([](void) { gstate->display(); });
  glutReshapeFunc([](int w, int h) { gstate->resize(w, h); });
  // glutIdleFunc([](void) { gstate->idle(); });

  if (gstate->game.fullscreen) {
    glutFullScreen();
  }
}

int main(int argc, char **argv) {
  gstate = new State();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(gstate->game.win_w, gstate->game.win_h);
  glutCreateWindow("MPG");

  gameInit();
  glutMainLoop();

  return 0;
}
