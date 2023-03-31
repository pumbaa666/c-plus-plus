// Fichier Global.cpp

#include <windows.h>
#include <GL\glut.h>
#include <math.h>
#include "global.h"

// NURBS object pointer
GLUnurbsObj *pNurb = NULL;

extern const int NbPoints = 5;
extern const int Ordre = 3;
extern const int NbKnots = NbPoints + Ordre;

const float Racine = sqrt(2.0) / 2.0;
// Dessin d'un cercle avec 3 arcs :
GLfloat ctrlPoints[NbPoints][4] = {
               {0.0, 1.0, 0., 1.0},
               {-Racine, Racine, 0., Racine},
               {-1.0, 0.0, 0., 1.0},
               {-Racine, -Racine, 0., Racine},
               {0.0, -1.0, 0., 1.0},
                                  };

// Knot sequence for the NURB
GLfloat Knots[NbKnots] = {0, 0, 0, 1./2., 1./2., 1, 1, 1};
//GLfloat Knots[NbKnots] = {0, 0, 0, 1, 2, 3, 4, 5, 5, 5};

int Mode = 0x2;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_FALSE;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zPos = 5.0f;
GLfloat xPos = 0.0f;
GLfloat Theta = 90.0f;
bool ButtonLeftDown = false;
bool ButtonRightDown = false;
bool FullScreen = false;

GLdouble AngleOuverture = 90.0;   // en degr�s
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 500.0;

extern const int bCull = 0x1;        // 00000001
extern const int bDepth = 0x2;       // 00000010
extern const int bOutline = 0x4;     // 00000100
extern const int bShadeModel = 0x8;   // 00001000


// Light values and coordinates
GLfloat	 lightPos[] = { 10.0f, 5.0f, 5.0f, 1.0f };
GLfloat  ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat RotationLumiere = 0.0;

