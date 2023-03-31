// Fichier Global.cpp

#include <GL\glut.h>

int Mode = 0x3;  // GL_SMOOTH = 0, GL_LINE = 0, DEPTH = 1, CULL = 1
GLboolean spinMode = GL_FALSE;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
bool ButtonLeftDown = false;
bool ButtonRightDown = false;
bool FullScreen = false;

GLdouble AngleOuverture = 60.0;   // en degrés
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 10.0;

GLuint cone, axes;

extern const int bCull = 0x1;        // 00000001
extern const int bDepth = 0x2;       // 00000010
extern const int bOutline = 0x4;     // 00000100
extern const int bShadeModel = 0x8;  // 00001000
