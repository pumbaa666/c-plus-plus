// Fichier Global.cpp

#include <gl\glut.h>                // Librairie GLUT

GLfloat ctrlpoints[4][3] = {
            {-4.0, -4.0, 0.0}, {-2.0, 4.0, 0.0},
            { 2.0, -4.0, 0.0}, { 4.0, 4.0, 0.0}};

int largeur = 500;
int hauteur = 500;

bool Stencil = true;
GLint cube;
GLint cubeOmbre;
GLfloat vfloor[4][3] = {{-4, 0, 4}, {4, 0, 4}, {4,0, -4},{-4,0, -4}};
//GLfloat vfloor2[4][3] = {{-4, 0, 4}, {4, 0, 4}, {4,0, -4},{-4,0, -4}};

// Plan de projection de l'ombre à 0.01 de hauteur à cause du Depth Buffer
GLfloat vfloor2[4][3] = { {-4, 0.05,  4},
                          { 4, 0.05,  4},
                          { 4, 0.05, -4},
                          {-4, 0.05, -4} };

GLfloat positionProperties[] = {0.0f, 6.0f, 0.0f, 0.0f};

bool ButtonLeftDown = false;
bool ButtonRightDown = false;
bool FullScreen = false;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zPos = 12.0f;
GLfloat xPos = 0.0f;
GLfloat Theta = 90.0f;

