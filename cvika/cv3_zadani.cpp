// MPC-MPG Lab 3: Uvod do vykreslovani, Bezierove krivky
#include "simpleMesh.h"
#include <string>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
bool trianglestrip = true;
int window1, window2, window3, winWidth;

float xOffset = 0;
float yOffset = 0;

// using namespace std;

#define POCET_RIDICICH_BODU 4
int aktBod = POCET_RIDICICH_BODU;

float ridiciBody[POCET_RIDICICH_BODU][3] = {
    {60, 400, 0.0}, {300, 300, 0.0}, {350, 150, 0.0}, {60, 60, 0.0}};

void zapniAA() {
  glEnable(GL_LINE_SMOOTH); // Aktivace antialiasingu - funguje pouze spolecne
                            // se zapnutim pruhlednosti!!!
  glHint(GL_LINE_SMOOTH, GL_NICEST); // Nastaveni Algoritmu
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void vypniAA() {
  glDisable(GL_BLEND);
  glDisable(GL_LINE_SMOOTH);
}

void vykresliKruh(int numVerticies, int sx, int sy, int r) {
  float t = 0;

  glBegin(GL_POLYGON);
  for (int i = 0; i < numVerticies; i++) {
    glVertex3f(sx + r * cos(2 * 3.14 * t), sy + r * sin(2 * 3.14 * t), 0.0);
    t += 1. / numVerticies;
  }
  glEnd();
}

void opakovaniUkol1() {

  bool antialiasing = true;

  if (antialiasing) {
    zapniAA();
  }

  glPointSize(25);
  glColor3f(1, 0, 0);
  glBegin(GL_POINTS);
  glVertex2f(200, 350);
  glVertex2f(300, 350);
  glEnd();

  // čára šířky 25 bodů barvy zelené, od (150, 300) do (350, 250)
  glLineWidth(25);
  glColor3f(0, 0, 1);
  glBegin(GL_LINE_STRIP);
  glVertex2f(150, 300);
  glVertex2f(350, 250);
  glEnd();
  // čára šířky 5 bodů barvy žluté, od (50, 250) do (350, 200), pattern 1:1 zapnuté
  // Apkkk / vypnuté bity (přerušovaná čára)
  glLineWidth(5);
  glColor3f(0.5, 0.5, 0);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0x5555);
  glBegin(GL_LINE_STRIP);
  glVertex2f(50, 250);
  glVertex2f(350, 200);
  glEnd();
  glDisable(GL_LINE_STIPPLE);

  // dvě čáry šířky 5 bodů, jedna červená (50, 150) – (350, 100), druhá zelená (50, 100) – 
  // 350, 150), čáry jsou plné
  glColor3f(1, 0, 0);
  glBegin(GL_LINE_STRIP);
  glVertex2f(50, 150);
  glVertex2f(350, 100);
  glEnd();

  glColor3f(0, 1, 0);
  glBegin(GL_LINE_STRIP);
  glVertex2f(50, 150);
  glVertex2f(350, 100);
  glEnd();

  if (antialiasing) {
    vypniAA();
  }
}

void vykreslovaniPole() {
  int tempPole[2 * numVer];

  // promenne poli ulozeny v souboru simpleMesh.h

  for (int i = 0; i < numVer; i++) {
    tempPole[2 * i] = coords[2 * i] + xOffset;         // x souradnice
    tempPole[2 * i + 1] = coords[2 * i + 1] + yOffset; // y souradnice
  }

  // TODO ukol 2
  // registrace vertex poli
  glVertexPointer(2, GL_INT, 0, tempPole);
  glColorPointer(4, GL_INT, 0, colors);

  // zapnuti vertex poli
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  // vykresleni vertex poli
  trianglestrip = false;
  if (trianglestrip) {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, numVer);
  } else {
    glDrawArrays(GL_TRIANGLES, 0, numVer);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void bitmapText() {
  // TODO Ukol 4
  // Vypis souradnic vsech ridicich bodu
  std::string str;
  for (int i = 0; i < POCET_RIDICICH_BODU; i++) {
    str = std::to_string((int)ridiciBody[i][0]) + ", " +
          std::to_string((int)ridiciBody[i][1]);
    glRasterPos2i(ridiciBody[i][0] + 5, ridiciBody[i][1] + 5);
    // Vypsani for cyklem kazdeho pismena
    for (int j = 0; j < str.length(); j++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[j]);
    }
  }
}

void vykresliBeziera() {

  glColor3f(1, 1, 0); // barva
  glLineWidth(1);

  float X_0, X_1, X_2, X_3, Y_0, Y_1, Y_2, Y_3;
  X_0 = ridiciBody[0][0];
  X_1 = ridiciBody[1][0];
  X_2 = ridiciBody[2][0];
  X_3 = ridiciBody[3][0];
  Y_0 = ridiciBody[0][1];
  Y_1 = ridiciBody[1][1];
  Y_2 = ridiciBody[2][1];
  Y_3 = ridiciBody[3][1];

  // TODO ukol 3
  glPointSize(10);
  glColor3f(1, 0, 0);
  bool antialiasing = true;
  if (antialiasing) {
    zapniAA();
  }
  int num_t = 50;
  float x, y, t2, t3;
  float t = 0;
  glBegin(GL_POINTS);
  for (int j = 0; j < 4; j++) {
    glVertex2f(ridiciBody[j][0], ridiciBody[j][1]);
  }
  glEnd();

  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0x5555);
  glBegin(GL_LINE_STRIP);
  for (int j = 0; j < 4; j++) {
    glVertex2f(ridiciBody[j][0], ridiciBody[j][1]);
  }
  glEnd();
  glDisable(GL_LINE_STIPPLE);

  glColor3f(0.5, 0.5, 0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= num_t; i++) {
    t = float((float)i / num_t);
    t2 = t * t;
    t3 = t * t * t;

    x = (-t3 + 3 * t2 - 3 * t + 1) * X_0 + (3 * t3 - 6 * t2 + 3 * t) * X_1 +
        (-3 * t3 + 3 * t2) * X_2 + t3 * X_3;
    y = (-t3 + 3 * t2 - 3 * t + 1) * Y_0 + (3 * t3 - 6 * t2 + 3 * t) * Y_1 +
        (-3 * t3 + 3 * t2) * Y_2 + t3 * Y_3;
    glVertex2f(x, y);
  }
  glEnd();
  if (antialiasing) {
    vypniAA();
  }
  vykresliKruh(100, 700, 700, 150); // ukazka na  zacatek

  // TODO ukol 4, dopln kod ve funkci
  bitmapText();
}

void onDisplay() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  int actwin = glutGetWindow();

  if (actwin == window1) {
    opakovaniUkol1();
    vykreslovaniPole();
  }

  else if (actwin == window2) {
    vykresliBeziera();
  }

  glFlush();
}

void onResize(int x, int y) {
  glViewport(0, 0, x, y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, x, 0, y, -1, 1);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  glutInitWindowSize(700, 700);
  glutInitWindowPosition(200, 200);
  glutInitDisplayMode(GLUT_RGBA);

  winWidth = 700;

  window1 = glutCreateWindow("Podokno 1");
  glutSetWindow(window1);
  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);

  window2 = glutCreateWindow("Podokno 2");
  glutSetWindow(window2);
  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onResize);

  glutMainLoop();

  return 0;
}
