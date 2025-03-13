#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define POCET_RIDICICH_BODU 4
#define STEPS 1000

float nalezeneBody[STEPS][2];
int aktBod = 100;
bool evaluator = false;

float ridiciBodyPracovni[POCET_RIDICICH_BODU][3] = {
    {60, 400, 0}, {300, 300, 0}, {150, 200, 0}, {60, 60, 0}};

float ridiciBodyZalozni[POCET_RIDICICH_BODU][3] = {
    {60, 400, 0}, {300, 300, 0}, {150, 200, 0}, {60, 60, 0}};

void bitmapText(int x, int y, void *font, string string) {
  glRasterPos2i(x, y);

  int delka = string.size();

  for (int i = 0; i < delka; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void vykresliridiciBody() {
  // Vypis souradnice ridicich bodu
  glColor3f(1, 1, 1);
  for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
    string text = " X: " + to_string((long int)ridiciBodyZalozni[i][0]) +
                  " Y: " + to_string((long int)ridiciBodyZalozni[i][1]);

    bitmapText(ridiciBodyZalozni[i][0] + 10, ridiciBodyZalozni[i][1],
               GLUT_BITMAP_HELVETICA_10, text);
  }

  // Vykresleni ridicich bodu
  glPointSize(11);
  glColor3f(0, 1, 0);

  glBegin(GL_POINTS);
  for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
    glVertex2f(ridiciBodyZalozni[i][0], ridiciBodyZalozni[i][1]);
  }
  glEnd();

  // Vykresleni ridiciho polygonu
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 255);

  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
    glVertex2fv(ridiciBodyZalozni[i]);
  }

  glEnd();
  glDisable(GL_LINE_STIPPLE);
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

void deCasteljau() {
  double t;

  for (int s = 0; s < STEPS; s++) {
    t = (double)s / (double)(STEPS - 1);

    float P01[2], P12[2], P23[2], P0112[2], P1223[2], PC[2];

    for (int i = 0; i < 2; i++) {
      P01[i] =
          (1 - t) * ridiciBodyPracovni[0][i] + t * ridiciBodyPracovni[1][i];
      P12[i] =
          (1 - t) * ridiciBodyPracovni[1][i] + t * ridiciBodyPracovni[2][i];
      P23[i] =
          (1 - t) * ridiciBodyPracovni[2][i] + t * ridiciBodyPracovni[3][i];
      P0112[i] = (1 - t) * P01[i] + t * P12[i];
      P1223[i] = (1 - t) * P12[i] + t * P23[i];
      PC[i] = (1 - t) * P0112[i] + t * P1223[i];
      nalezeneBody[s][i] = PC[i];
    }

    // nalezeneBody[s][0] = 0;
    // nalezeneBody[s][1] = 0;

    for (int j = 0; j < POCET_RIDICICH_BODU; j++) {
      ridiciBodyPracovni[j][0] = ridiciBodyZalozni[j][0];
      ridiciBodyPracovni[j][1] = ridiciBodyZalozni[j][1];
    }
  }
}

void onDisplay(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POINT_SMOOTH);

  if (evaluator) {
    glEnable(
        GL_MAP1_VERTEX_3); // povolí použití evaluátoru počítajícího souřadnice
    glMap1f(GL_MAP1_VERTEX_3, 0, STEPS - 1, 3, 4,
            ridiciBodyZalozni[0]); // nastavení řídicích bodů a rozsah t

    glColor3f(1, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < STEPS; i++) {
      glEvalCoord1f(i); // výpočet 100 souřadnic vertexů
    }
    glEnd();
    glDisable(GL_MAP1_VERTEX_3);
  } else {
    deCasteljau(); // tato funkce naplní pole nalezeneBody

    glColor3f(1, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int s = 0; s < STEPS; s++) {
      glVertex2f(nalezeneBody[s][0], nalezeneBody[s][1]);
    }
    glEnd();
  }
  glDisable(GL_POINT_SMOOTH);

  vykresliridiciBody();
  glFlush();
  glutSwapBuffers();

  glDisable(GL_BLEND);
  glDisable(GL_LINE_SMOOTH);
}

// Obsluha tlacitek mysi
void onMouse(int button, int state, int mx, int my) {
  // Posun y souradnice aby byl pocatek vlevo dole
  my = glutGet(GLUT_WINDOW_HEIGHT) - my;

  // Detekce povoleneho pohybu (pouze leveho tlacitka mysi)
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_UP) {
      aktBod = 100;
    } else {
      for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
        // drag and drop funguje v okoli 10 px - osetreno abs hodnotou pro + i -
        if (abs(ridiciBodyZalozni[i][0] - mx) < 10 &&
            abs(ridiciBodyZalozni[i][1] - my) < 10) {
          aktBod = i;
        }
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
    ridiciBodyZalozni[aktBod][0] = mx;
    ridiciBodyZalozni[aktBod][1] = my;
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

  glutCreateWindow("Bezier + de Casteljau"); // vytvoreni okna
  glutDisplayFunc(
      onDisplay); // registrace funkce volane pri prekreslovani aktualniho okna
  glutReshapeFunc(onReshape); // registrace funkce volane pri zmene velikosti
                              // aktualniho okna
  glutMouseFunc(onMouse);
  glutMotionFunc(onMotion);

  glutMainLoop(); // nekonecna smycka, interakce uz jen pomoci event handleru
  return 0;       // ukonceni programu
}
