#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#include "include/hdr/bezier.h"
#include "include/hdr/draw.h"
#include "include/hdr/input.h"

void drawPlane(float size, int div) {
  float step = size / div;
  float half = size / 2.0f;

  for (int i = 0; i < div; i++) {
    for (int j = 0; j < div; j++) {
      float x = -half + i * step;
      float z = -half + j * step;

      glBegin(GL_QUADS);
      glColor3f(0.5f, 0.5f, 0.5f);
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(x, 0.0, z);
      glVertex3f(x + step, 0.0, z);
      glVertex3f(x + step, 0.0, z + step);
      glVertex3f(x, 0.0, z + step);
      glEnd();
    }
  }
}

void setupLight() {
  GLfloat light_pos[] = {2.0f, 5.0f, 5.0f, 1.0f};
  GLfloat light_amb[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat light_dif[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat light_spe[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_spe);
}

void onResize(int w, int h) {
  // std::cout << "resizing!" << std::endl;
  if (h == 0) h = 1;
  float aspect = (float)w / (float)h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, aspect, 0.1, 1000.0);

  glMatrixMode(GL_MODELVIEW);
}

void onDisplay(void) {
  // std::cout << "displaying!" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  // glTranslatef(0, 0, tranznew);
  // glMultMatrixf(rotationmatrix);

  updateCamera();
  setupLight();
  drawPlane(100.0f, 100);
  drawScaledCube(10.0f, 1.0f, 0.0f, 5.0f);

  glEnable(GL_MAP2_VERTEX_3);
  glEnable(GL_MAP2_TEXTURE_COORD_2);
  // subCasteljau();
  drawLeadPoints();
  showMesh();
  glDisable(GL_BLEND);

  drawBezierPlate(50);

  glFlush();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("MPC-MPG projekt -- Tomas Hadwiger | 230252");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);
  glutSetCursor(GLUT_CURSOR_NONE);
  glClearColor(0.2, 0.6, 1.0, 1.0);

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);
  glutKeyboardFunc(processKeys);
  glutPassiveMotionFunc(handleMouseMovement);
  glutMainLoop();
  return 0;
}
