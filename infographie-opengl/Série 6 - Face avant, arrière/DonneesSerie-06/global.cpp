// Fihcier Global.cpp

#include <GL\glut.h>

GLfloat yCamera = 30.0f;
GLfloat yRot = 45.0f;
bool ButtonLeftDown = false;
int Coef = 3;
bool RotationOn = false;

GLdouble AngleOuverture = 60.0;   // en degrés
bool ButtonRightDown = false;
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 200.0;

GLvoid * font_style = GLUT_BITMAP_TIMES_ROMAN_24;
