// Fihcier Global.cpp

#include <GL\glut.h>

GLfloat yCamera = 5.0f;
GLfloat yRot = 45.0f;
bool ButtonLeftDown = false;
bool RotationOn = false;
GLfloat lastX = 0;
GLfloat lastY = 0;

GLdouble AngleOuverture = 60.0;   // en degrés
bool ButtonRightDown = false;
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 20.0;

GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
