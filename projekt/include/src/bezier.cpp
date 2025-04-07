// MPC-MPG cviceni 5
// Subdivision bezierove bikubiky, rozdil mezi subdivision a openGL evaluatorem

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#include <iostream>

bool castlejaued = false;
float field_pts[7][7][3];
float lead_pts[4][4][3] = {{{-0.5f, 0.5f, 0.3333f},
                            {-0.1667f, 0.5f, 0.6667f},
                            {0.1667f, 0.5f, 0.6667f},
                            {0.5f, 0.5f, 0.3333f}},
                           {{-0.5f, 0.8333f, 0.1667f},
                            {-0.1667f, 0.8333f, 0.5f},
                            {0.1667f, 0.8333f, 0.5f},
                            {0.5f, 0.8333f, 0.1667f}},
                           {{-0.5f, 1.1667f, 0.0f},
                            {-0.1667f, 1.1667f, 0.3333f},
                            {0.1667f, 1.1667f, 0.3333f},
                            {0.5f, 1.1667f, 0.0f}},
                           {{-0.5f, 1.5f, -0.3333f},
                            {-0.1667f, 1.5f, 0.0f},
                            {0.1667f, 1.5f, 0.0f},
                            {0.5f, 1.5f, -0.3333f}}};

GLfloat color_points[2][2][4] = {{{1.0, 1.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}},
                                 {{1.0, 0.0, 0.0, 0.0}, {1.0, 1.0, 1.0, 0.0}}};

void subCasteljau() {
  std::cout << "Subdivision of Bezier curve using Casteljau's algorithm"
            << std::endl;
  double t = 0.5;

  for (int u = 0; u < 4; u++) {
    for (int k = 0; k < 3; k++) {
      float temp = (1.0 - t) * lead_pts[u][1][k] + t * lead_pts[u][2][k];

      float nulty = lead_pts[u][0][k];
      float prvni = (1.0 - t) * nulty + t * lead_pts[u][1][k];
      float druhy = (1.0 - t) * prvni + t * temp;

      float sesty = lead_pts[u][3][k];
      float paty = (1.0 - t) * lead_pts[u][2][k] + t * sesty;
      float ctvrty = (1.0 - t) * temp + t * paty;

      float treti = (1.0 - t) * druhy + t * ctvrty;

      field_pts[u * 2][0][k] = nulty;
      field_pts[u * 2][1][k] = prvni;
      field_pts[u * 2][2][k] = druhy;
      field_pts[u * 2][3][k] = treti;
      field_pts[u * 2][4][k] = ctvrty;
      field_pts[u * 2][5][k] = paty;
      field_pts[u * 2][6][k] = sesty;
    }
  }

  for (int s = 0; s < 7; s++) {
    for (int k = 0; k < 3; k++) {
      float temp = (1.0 - t) * field_pts[2][s][k] + t * field_pts[4][s][k];

      float nulty = field_pts[0][s][k];
      float prvni = (1.0 - t) * nulty + t * field_pts[2][s][k];
      float druhy = (1.0 - t) * prvni + t * temp;

      float sesty = field_pts[6][s][k];
      float paty = (1.0 - t) * field_pts[4][s][k] + t * field_pts[6][s][k];
      float ctvrty = (1.0 - t) * temp + t * paty;

      float treti = (1.0 - t) * druhy + t * ctvrty;

      field_pts[0][s][k] = nulty;
      field_pts[1][s][k] = prvni;
      field_pts[2][s][k] = druhy;
      field_pts[3][s][k] = treti;
      field_pts[4][s][k] = ctvrty;
      field_pts[5][s][k] = paty;
      field_pts[6][s][k] = sesty;
    }
  }
}

void drawLeadPoints() {
  glPointSize(4.0);
  glColor3f(0.5, 0.5, 0.4);
  glBegin(GL_POINTS);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      glVertex3fv(lead_pts[i][j]);
    }
  }
  glEnd();
}

void drawBezierPlate(int density = 20) {
  if (castlejaued == false) {
    subCasteljau();
    castlejaued = true;
  }
  int dimensions = 4;

  glEnable(GL_MAP2_VERTEX_3);
  // glEnable(GL_MAP2_COLOR_4);

  glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, dimensions, 0.0, 1.0, 3 * dimensions,
          dimensions, &lead_pts[0][0][0]);
  // glMap2f(GL_MAP2_COLOR_4, 0.0, 1.0, 3, dimensions, 0.0, 1.0, 3 * dimensions,
  //         dimensions, &color_points[0][0][0]);

  glMapGrid2f(density, 0.0, 1.0, density, 0.0, 1.0);
  glEvalMesh2(GL_LINE, 0, density, 0, density);

  // glDisable(GL_MAP2_COLOR_4);
  glDisable(GL_MAP2_VERTEX_3);
}

void showMesh(void) {
  glPointSize(4.0);
  glColor4f(1.0, 1.0, 0.0, 1.0);
  int rows = 7;
  glBegin(GL_POINTS);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 7; j++) {
      glVertex3fv(field_pts[i][j]);
    }
  }
  glEnd();

  glColor4f(1.0, 1.0, 0.0, 0.1);
  glBegin(GL_QUADS);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      glVertex3fv(field_pts[i][j]);          // Bottom-left
      glVertex3fv(field_pts[i + 1][j]);      // Bottom-right
      glVertex3fv(field_pts[i + 1][j + 1]);  // Top-right
      glVertex3fv(field_pts[i][j + 1]);      // Top-left
    }
  }
  glEnd();
}
