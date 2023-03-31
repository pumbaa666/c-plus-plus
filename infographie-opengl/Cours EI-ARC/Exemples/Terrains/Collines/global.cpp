// Fichier Global.cpp

#include <GL\glut.h>

int Mode = 0xA;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_FALSE;
GLfloat xRot = 20.0f;
GLfloat yRot = 0.0f;
GLfloat zPos = 120.0f;
GLfloat xPos = 0.0f;
GLfloat Theta = 90.0f;
bool ButtonLeftDown = false;
bool ButtonRightDown = false;
bool FullScreen = false;

GLdouble AngleOuverture = 90.0;   // en degrés
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 500.0;

extern const int bCull = 0x1;        // 00000001
extern const int bDepth = 0x2;       // 00000010
extern const int bOutline = 0x4;     // 00000100
extern const int bShadeModel = 0x8;   // 00001000

GLuint axes, murs, toit, maison, sol, cone;

GLfloat altitudeNeige = 0.6f; // Entre 0 et 1
GLfloat altitudeMer = 0.1f; // Entre 0 et 1
int nbDeCollines = 400;
int rayonDesCollines = 25;

