// Fichier Global.cpp

#include <GL\glut.h>

int Mode = 0x2;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_TRUE;
GLfloat xRot = 15.0f;
GLfloat yRot = 70.0f;
GLfloat zPos = 30.0f;
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


// Light values and coordinates (w = 0 --> lumière à l'infini)
GLfloat  DistanceLumiere = 20.0f;
GLfloat	 lightPos[] = { DistanceLumiere, 11.0f, 0.0f, 0.0f };
GLfloat  ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat RotationLumiere = 0.0;

bool Stencil = true;
GLfloat vfloor[4][3] = {{-100, 0, 100}, {100, 0, 100}, {100,0, -100},{-100,0, -100}};

