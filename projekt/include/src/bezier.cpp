// MPC-MPG cviceni 5
// Subdivision bezierove bikubiky, rozdil mezi subdivision a openGL evaluatorem

#include <GLUT/glut.h>
#include <cmath>

#define PI 3.14159265

double xnew = 0, ynew = 0, znew = 0; // aktualni poloha mysi
double xold = 0, yold = 0, zold = 0; // predchozi poloha mysi
double tranznew = -100;              // aktualni posunuti ve smeru osy z
double tranzold = -50;               // predchozi posunuti ve smeru osy z
bool tocime = false;                 // ovladac rotace
bool posouvame = false;              // ovladac translace
double newnorm, oldnorm;             // normy polohovych vektoru mysi
double xaxis = 0, yaxis = 0,
       zaxis = 0;              // osa rotace // PR: dava smysl nulovy vektor?
double xaxis2, yaxis2, zaxis2; // pomocna osa rotace
double angle = 0;              // uhel rotace
double zz;        // pomocna promenna pro vypocet posunuti ve smeru osy z
int hustota = 10; // hustota bodu generovanych ridicimi body
GLfloat rotationmatrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
float fov = 90.0;
float nearPlane = 0.1;
float farPlane = 500.0;
double xw, yw, zw;
GLdouble zWindow;

float pole_boduN[7][7][3];

float ridiciBody[4][4][3] = {
    {{-15, -15, 20}, {-5, -15, 40}, {5, -15, 40}, {15, -15, 20}},
    {{-15, -5, 10}, {-5, -5, 30}, {5, -5, 30}, {15, -5, 10}},
    {{-15, 5, 0}, {-5, 5, 20}, {5, 5, 20}, {15, 5, 0}},
    {{-15, 15, -20}, {-5, 15, 0}, {5, 15, 0}, {15, 15, -20}}};

GLfloat colorPoints[2][2][4] = {{{1.0, 1.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}},
                                {{1.0, 0.0, 0.0, 0.0}, {1.0, 1.0, 1.0, 0.0}}};

void drawLeadPoints() {
  glPointSize(4.0);
  glColor3f(0.5, 0.5, 0.4);
  glBegin(GL_POINTS);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      glVertex3fv(ridiciBody[i][j]);
    }
  }
  glEnd();
}

void drawBezierPlate(int density = 20) {
  int dimensions = 4;

  glEnable(GL_MAP2_VERTEX_3);
  glEnable(GL_MAP2_COLOR_4);

  glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, dimensions, 0.0, 1.0, 3 * dimensions,
          dimensions, &ridiciBody[0][0][0]);
  glMap2f(GL_MAP2_COLOR_4, 0.0, 1.0, 3, dimensions, 0.0, 1.0, 3 * dimensions,
          dimensions, &colorPoints[0][0][0]);

  glMapGrid2f(density, 0.0, 1.0, density, 0.0, 1.0);
  glEvalMesh2(GL_LINE, 0, density, 0, density);

  glDisable(GL_MAP2_VERTEX_3); // vypnuti aplikace obou typu evaluatoru
  glDisable(GL_MAP2_COLOR_4);
}

void subCasteljau() {
  double t = 0.5;

  for (int u = 0; u < 4; u++) {
    for (int k = 0; k < 3; k++) {

      float temp = (1.0 - t) * ridiciBody[u][1][k] + t * ridiciBody[u][2][k];

      float nulty = ridiciBody[u][0][k];
      float prvni = (1.0 - t) * nulty + t * ridiciBody[u][1][k];
      float druhy = (1.0 - t) * prvni + t * temp;

      float sesty = ridiciBody[u][3][k];
      float paty = (1.0 - t) * ridiciBody[u][2][k] + t * sesty;
      float ctvrty = (1.0 - t) * temp + t * paty;

      float treti = (1.0 - t) * druhy + t * ctvrty;

      pole_boduN[u * 2][0][k] = nulty;
      pole_boduN[u * 2][1][k] = prvni;
      pole_boduN[u * 2][2][k] = druhy;
      pole_boduN[u * 2][3][k] = treti;
      pole_boduN[u * 2][4][k] = ctvrty;
      pole_boduN[u * 2][5][k] = paty;
      pole_boduN[u * 2][6][k] = sesty;
    }
  }

  for (int s = 0; s < 7; s++) {
    for (int k = 0; k < 3; k++) {
      float temp = (1.0 - t) * pole_boduN[2][s][k] + t * pole_boduN[4][s][k];

      float nulty = pole_boduN[0][s][k];
      float prvni = (1.0 - t) * nulty + t * pole_boduN[2][s][k];
      float druhy = (1.0 - t) * prvni + t * temp;

      float sesty = pole_boduN[6][s][k];
      float paty = (1.0 - t) * pole_boduN[4][s][k] + t * pole_boduN[6][s][k];
      float ctvrty = (1.0 - t) * temp + t * paty;

      float treti = (1.0 - t) * druhy + t * ctvrty;

      pole_boduN[0][s][k] = nulty;
      pole_boduN[1][s][k] = prvni;
      pole_boduN[2][s][k] = druhy;
      pole_boduN[3][s][k] = treti;
      pole_boduN[4][s][k] = ctvrty;
      pole_boduN[5][s][k] = paty;
      pole_boduN[6][s][k] = sesty;
    }
  }
}

void showMesh(void) {
  glPointSize(4.0);
  glColor4f(1.0, 1.0, 0.0, 1.0);
  int rows = 7;
  glBegin(GL_POINTS);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 7; j++) {
      glVertex3fv(pole_boduN[i][j]);
    }
  }
  glEnd();

  glColor4f(1.0, 1.0, 0.0, 0.1);
  glBegin(GL_QUADS);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      glVertex3fv(pole_boduN[i][j]);         // Bottom-left
      glVertex3fv(pole_boduN[i + 1][j]);     // Bottom-right
      glVertex3fv(pole_boduN[i + 1][j + 1]); // Top-right
      glVertex3fv(pole_boduN[i][j + 1]);     // Top-left
    }
  }
  glEnd();
}
