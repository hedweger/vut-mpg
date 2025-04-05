// MPC-MPG cviceni 8 - prekryvani teles a efekt mlhy
#include <GLUT/glut.h>

// @ukol 2 - nastaveni barvy mlhy stejne jako je mazani frame bufferu
float fogColor[] = {0, 0, 0, 0};

void onResize(int w, int h) // event handler pro zmenu velikosti okna
{
  glViewport(0, 0, w, h);      // OpenGL: nastaveni rozmenu viewportu
  glMatrixMode(GL_PROJECTION); // OpenGL: matice bude typu projekce
  glLoadIdentity(); // OpenGL: matice bude identicka (jen jednicky v hlavni
                    // diagonale)
  glOrtho(-(double)w / 10, (double)w / 10, -(double)h / 10, (double)h / 10, 5,
          90);
}

void drawCube(float size, float x, float y, float z, float r, float g,
              float b) {
  float half = size / 2.0f; // Polovina velikosti pro snazsi umisteni

  glPushMatrix();
  glTranslatef(x, y, z); // Presunuti krychle na (x, y, z)

  glBegin(GL_QUADS);

  // Predni strana
  glColor3f(r, g, b);
  glVertex3f(-half, -half, half);
  glVertex3f(half, -half, half);
  glVertex3f(half, half, half);
  glVertex3f(-half, half, half);

  // Zadni strana
  glColor3f(r * 0.8, g * 0.8, b * 0.8);
  glVertex3f(-half, -half, -half);
  glVertex3f(-half, half, -half);
  glVertex3f(half, half, -half);
  glVertex3f(half, -half, -half);

  // Leva strana
  glColor3f(r * 0.6, g * 0.6, b * 0.6);
  glVertex3f(-half, -half, -half);
  glVertex3f(-half, -half, half);
  glVertex3f(-half, half, half);
  glVertex3f(-half, half, -half);

  // Prava strana
  glColor3f(r * 0.9, g * 0.9, b * 0.9);
  glVertex3f(half, -half, -half);
  glVertex3f(half, half, -half);
  glVertex3f(half, half, half);
  glVertex3f(half, -half, half);

  // Horni strana
  glColor3f(r * 1.1, g * 1.1, b * 1.1);
  glVertex3f(-half, half, -half);
  glVertex3f(-half, half, half);
  glVertex3f(half, half, half);
  glVertex3f(half, half, -half);

  // Dolni strana
  glColor3f(r * 0.7, g * 0.7, b * 0.7);
  glVertex3f(-half, -half, -half);
  glVertex3f(half, -half, -half);
  glVertex3f(half, -half, half);
  glVertex3f(-half, -half, half);

  glEnd();
  glPopMatrix();
}

void onDisplay(void) {
  glClearDepth(1.0);                // hloubka mazani z-bufferu
  glClearColor(0.5, 0.5, 0.5, 0.0); // barva mazani z-bufferu
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // mazani

  // @ukol 1 - zapnuti z-buffer testu
  glEnable(GL_DEPTH_TEST);
  // @ukol 1 - nastaveni srovnavaci funkce z-bufferu
  glDepthFunc(GL_LESS);
  // @ukol 1 - pohled pomoci gluLookAt
  gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // @ukol 2 - nastaveni a povoleni efektu mlhy
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, fogColor);
  glHint(GL_FOG_HINT, GL_NICEST);
  glFogf(GL_FOG_START, 0);
  glFogf(GL_FOG_END, 40);

  drawCube(30.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  // @ukol 1 - pridani dalsich kostek - vypnuti/zapnuti GL_DEPTH_TEST
  drawCube(35.0f, 10.0f, 10.0f, 10.0f, 0.0f, 0.0f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_FOG);

  // provedeni a vykresleni zmen
  glFlush();
  glutSwapBuffers(); // nezapomente zapnout double buffering!
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv); // inicializace knihovny GLUT
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
                      GLUT_DEPTH); // init double buffer, depth buffer

  glutInitWindowSize(
      400, 400); // nastaveni pocatecni velikosti dale oteviranych oken
  glutInitWindowPosition(
      200, 200); // nastaveni pocatecniho umisteni dale oteviranych oken

  glutCreateWindow("MPC-MPG cviceni 8 - ukol 1 a 2"); // vytvoreni okna
  glutDisplayFunc(
      onDisplay); // registrace funkce volane pri prekreslovani aktualniho okna
  glutReshapeFunc(
      onResize); // registrace funkce volane pri zmene velikosti aktualniho okna

  glutMainLoop(); // nekonecna smycka, interakce uz jen pomoci event handleru
  return 0;       // ukonceni programu
}
