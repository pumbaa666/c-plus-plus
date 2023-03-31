// fichier Global.cpp

#include <GL\glut.h>

int Mode = 0xa;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
GLenum spinMode = GL_FALSE;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zPos = 100.0f;
GLfloat xPos = 0.0f;
GLfloat Theta = 90.0f;
bool ButtonLeftDown = false;
bool ButtonRightDown = false;
bool FullScreen = false;

GLdouble AngleOuverture = 90.0;   // en degrés
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 500.0;

// Light values and coordinates
//GLfloat	 lightPos[] = { 0.0f, 0.0f, 75.0f, 0.0f }; // Lumière à l'infini
GLfloat	 lightPos[] = { 0.0f, 0.0f, 75.0f, 1.0f };
GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };

// cutOff entre 0 et 90 (angle d'ouverture)
// 180 --> lumière uniforme
GLfloat spotCutOff = 60.0f; //60.0f;

// spotExponent entre 0 et 128, 0 --> lumière uniforme
GLfloat spotExponent = 0.0f; //100.0f;

GLfloat  ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};

