// Fichier Global.cpp

#include <gl\glut.h>                // Librairie GLUT

GLfloat sol[3][3] = {{0.0f,0.0f,0.05f},
                     {4.0f,0.0f,0.05f},
                     {0.0f,4.0f,0.05f}};
GLfloat ombre[4][4];
GLfloat light_pos[] = {0.0f, 0.0f, 15.0f, 1.0f};

// Ombre décalée
//GLfloat light_pos[] = {10.0f, 0.0f, 15.0f, 1.0f};

