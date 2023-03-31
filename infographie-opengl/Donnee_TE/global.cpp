// Loïc Correvon
// Fichier Global.cpp

#include <GL\glut.h>

GLfloat deltaAngle = 0.0f;
char AxeRotation = 'n';

int Mode = 0x3;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_FALSE;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat xPos = 0.0f;
GLfloat yPos = 2.0f;
GLfloat zPos = 7.0f;
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
