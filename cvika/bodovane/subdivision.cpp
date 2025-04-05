#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define POCET_RIDICICH_BODU 4
#define STEPS 100

int aktBod = 100;

// Ridici body cele krivky
float ridiciBody[POCET_RIDICICH_BODU][3] = {
    {60, 400, 0}, {300, 300, 0}, {150, 200, 0}, {60, 60, 0}};

// Ridici body rozdelene krivky – 1. cast (inicializovano na nuly)
float ridiciBodySub1[POCET_RIDICICH_BODU][3] = {
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

// Ridici body rozdelene krivky – 2. cast (inicializovano na nuly)
float ridiciBodySub2[POCET_RIDICICH_BODU][3] = {
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void vykresliridiciBody(float ridiciBody[POCET_RIDICICH_BODU][3]) {
  // Vykresleni ridicich bodu
  glPointSize(11);
  glBegin(GL_POINTS);
  for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
    glVertex2f(ridiciBody[i][0], ridiciBody[i][1]);
  }
  glEnd();

  // Vykresleni ridiciho polygonu
  glLineWidth(1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
    glVertex2fv(ridiciBody[i]);
  }
  glEnd();
}

void vykreslikrivku(float ridiciBody[POCET_RIDICICH_BODU][3], GLint PRIM) {
  glEnable(
      GL_MAP1_VERTEX_3); // povolí použití evaluátoru počítajícího souřadnice
  glMap1f(GL_MAP1_VERTEX_3, 0, STEPS - 1, 3, 4,
          ridiciBody[0]); // nastavení řídících bodů a rozsah t
  glEnable(GL_POINT_SMOOTH);
  glBegin(PRIM);
  for (int i = 0; i < STEPS; i++) {
    glEvalCoord1f(i); // výpočet 100 souřadnic vertexů
  }
  glEnd();
  glDisable(GL_MAP1_VERTEX_3);
  glDisable(GL_POINT_SMOOTH);
}

void onReshape(int w, int h) // event handler pro zmenu velikosti okna
{
  glViewport(0, 0, w, h);      // OpenGL: nastaveni rozmenu viewportu
  glMatrixMode(GL_PROJECTION); // OpenGL: matice bude typu projekce
  glLoadIdentity(); // OpenGL: matice bude identicka (jen jednicky v hlavni
                    // diagonale)
  glOrtho(0, w, 0, h, -1,
          1); // OpenGL: mapovani abstraktnich souradnic do souradnic okna
}

void subdivision(float ridiciBody[POCET_RIDICICH_BODU][3]) {
  // Tato funkce prijima jako vstup ridici body cele krivky (ridiciBody)
  // V ramci funkce spocitejte souradnice ridicich bodu rozdelenych segmentu
  // a ulozte je do promennych ridiciBodySub1 a ridiciBodySub2
  float t = 0.5;
  float P01[2], P12[2], P23[2], P0112[2], P1223[2], PC[2];
  for (int i = 0; i < 2; i++) {
    P01[i] = (1 - t) * ridiciBody[0][i] + t * ridiciBody[1][i];
    P12[i] = (1 - t) * ridiciBody[1][i] + t * ridiciBody[2][i];
    P23[i] = (1 - t) * ridiciBody[2][i] + t * ridiciBody[3][i];

    P0112[i] = (1 - t) * P01[i] + t * P12[i];
    P1223[i] = (1 - t) * P12[i] + t * P23[i];

    PC[i] = (1 - t) * P0112[i] + t * P1223[i];

    ridiciBodySub1[0][i] = P01[i];
    ridiciBodySub1[1][i] = P12[i];
    ridiciBodySub1[2][i] = P23[i];
    ridiciBodySub1[3][i] = P23[i];

    ridiciBodySub2[0][i] = P0112[i];
    ridiciBodySub2[1][i] = P1223[i];
    ridiciBodySub2[2][i] = PC[i];
    ridiciBodySub2[3][i] = PC[i];
  }
}

void onDisplay(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Vykresleni cele krivky
  glColor3f(1, 0, 0);
  glPointSize(2);
  vykreslikrivku(ridiciBody, GL_POINTS);
  glColor3f(1, 1, 0);
  vykresliridiciBody(ridiciBody);

  // Vypocet subdivision
  subdivision(ridiciBody);
  // Vykresleni rozdelene krivky – 1. cast
  glPointSize(8);
  glColor3f(1, 1, 1);
  glBegin(GL_POINTS);
  for (int i = 0; i < sizeof(ridiciBodySub1) / sizeof(ridiciBodySub1[0]); i++) {
    glVertex2f(ridiciBodySub1[i][0], ridiciBodySub1[i][1]);
  }
  glEnd();
  glLineWidth(1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < sizeof(ridiciBodySub1) / sizeof(ridiciBodySub1[0]); i++) {
    glVertex2fv(ridiciBodySub1[i]);
  }
  glEnd();
  // Vykresleni rozdelene krivky – 2. cast
  glPointSize(8);
  glColor3f(0.5, 0.5, 1);
  glBegin(GL_POINTS);
  for (int i = 0; i < sizeof(ridiciBodySub2) / sizeof(ridiciBodySub2[0]); i++) {
    glVertex2f(ridiciBodySub2[i][0], ridiciBodySub2[i][1]);
  }
  glEnd();
  glLineWidth(1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < sizeof(ridiciBodySub2) / sizeof(ridiciBodySub2[0]); i++) {
    glVertex2fv(ridiciBodySub2[i]);
  }
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_LINE_SMOOTH);

  glFlush();

  glutSwapBuffers();
}

// Obsluha tlacitek mysi
void onMouse(int button, int state, int mx, int my) {
  // Posun y souradnice aby byl pocatek vlevo dole
  my = glutGet(GLUT_WINDOW_HEIGHT) - my;

  // Detekce povoleneho pohybu (left button only)
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_UP) {
      aktBod = 100;
    } else {
      for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
        if (abs(ridiciBody[i][0] - mx) < 10 &&
            abs(ridiciBody[i][1] - my) <
                10) // drag and drop funguje v okoli 10 px - osetreno abs
                    // hodnotou pro + i -
          aktBod = i;
      }
    }
  } else {
    aktBod = 100;
  }
}

// Obsluha pohybu mysi (aktivniho)
void onMotion(int mx, int my) {
  // Posun y souradnice aby byl pocatek vlevo dole
  my = glutGet(GLUT_WINDOW_HEIGHT) - my;

  if (aktBod < POCET_RIDICICH_BODU) {
    ridiciBody[aktBod][0] = mx;
    ridiciBody[aktBod][1] = my;
  }

  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv); // inicializace knihovny GLUT

  glutInitDisplayMode(GLUT_DOUBLE);

  glutInitWindowSize(
      400, 500); // nastaveni pocatecni velikosti dale oteviranych oken
  glutInitWindowPosition(
      200, 200); // nastaveni pocatecniho umisteni dale oteviranych oken

  glutCreateWindow("Subdivision de Casteljau"); // vytvoreni okna
  glutDisplayFunc(
      onDisplay); // registrace funkce volane pri prekreslovani aktualniho okna
  glutReshapeFunc(onReshape); // registrace funkce volane pri zmene velikosti
                              // aktualniho okna
  glutMouseFunc(onMouse);
  glutMotionFunc(onMotion);

  glutMainLoop(); // nekonecna smycka, interakce uz jen pomoci event handleru
  return 0;       // ukonceni programu
}
