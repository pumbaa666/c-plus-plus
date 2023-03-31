// Fichier Global.cpp

#include <windows.h>
#include <GL\glut.h>

// NURBS object pointer
GLUnurbsObj *pNurb = NULL;
// The number of control points for this curve
GLint nNumPoints = 4; // 4 X 4

// Mesh extends four units -6 to +6 along x and y axis
// Lies in Z plane
//                 u  v  (x,y,z)
GLfloat ctrlPoints[4][3]  = {{  -6.0f, -6.0f, 0.0f},
							 {   2.0f, -2.0f, 8.0f},
							 {   2.0f,  6.0f, 0.0f},
							 {   6.0f, 6.0f,  0.0f}};


// Knot sequence for the NURB
GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
//GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0f, 1.0f};


int Mode = 0x2;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_TRUE;
GLfloat xRot = 30.0f;
GLfloat yRot = 45.0f;
GLfloat zPos = 15.0f;
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


// Light values and coordinates
GLfloat	 lightPos[] = { 10.0f, 5.0f, 5.0f, 1.0f };
GLfloat  ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat RotationLumiere = 0.0;

