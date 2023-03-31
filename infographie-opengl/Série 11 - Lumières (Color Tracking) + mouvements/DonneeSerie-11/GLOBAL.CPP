// Fichier Global.cpp

#include <GL\glut.h>

int Mode = 0xB;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_TRUE;

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zPos = 25.0f;
GLfloat xPos = 0.0f;
GLfloat Theta = 90.0f;

GLfloat rotationSphere = 0.0f;     // Rotation de la sphère
GLfloat xSphere1 = -10.0f; // Position de la sphère
GLfloat zSphere2 = -5.0f; // Position de la sphère
int sphere1 = 1;
int sphere2 = 1;
GLdouble fRadius = 4.0;   // Rayon de la sphère
int nbSommetSphere = 7;

bool ButtonLeftDown = false;
bool ButtonRightDown = false;
bool FullScreen = false;

GLdouble AngleOuverture = 90.0;   // en degrés
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 500.0;

extern const int bCull = 0x1;        // 00000001
extern const int bDepth = 0x2;       // 00000010
extern const int bOutline = 0x4;     // 00000100
extern const int bShadeModel = 0x8;  // 00001000

