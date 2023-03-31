// Fichier Dessin.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "global.h"
#include "dessin.h"

void drawFloor()
{
    glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
    glBegin(GL_QUADS);
      glNormal3f(0.0,1.0,0.0);
      glVertex3fv(vfloor[0]);
      glVertex3fv(vfloor[1]);
      glVertex3fv(vfloor[2]);
      glVertex3fv(vfloor[3]);
    glEnd();
}

void Make_CallListes()
{
   //C'est la partie la plus importante
   //Les couleurs sont définies avec un alpha de 0.25
   //qui va servir dans le calcul de la transparence
   //Rappel : 0 = transparent, 1 = opaque
  GLfloat alpha = 1.0f; //0.25f;
	GLfloat Rouge[] = {0.8f, 0.0f, 0.0f, alpha};
	GLfloat Vert[]  = {0.0f, 0.8f, 0.0f, alpha};
	GLfloat Bleu[]  = {0.0f, 0.0f, 0.8f, alpha};
	GLfloat Jaune[]  = {0.8f, 0.8f, 0.0f, alpha};
	GLfloat Rose[]  = {0.8f, 0.0f, 0.8f, alpha};
	GLfloat	Cyan[]  = {0.0f, 0.8f, 0.8f, alpha};

   //on se contente de dessiner le cube,
   //en utilisant cependant la fonction
   //glColor4f() au lieu de glColor3f()
   //car la composante alpha compte cette fois_ci
	cube = glGenLists(1);
	glNewList(cube, GL_COMPILE);
		glBegin(GL_QUADS);
		   glColor4fv(Jaune);
		   glNormal3d(-1.0,0.0,0.0);
		   glVertex3d( -1,  1,  1);
		   glVertex3d( -1,  1, -1);
		   glVertex3d( -1, -1, -1);
		   glVertex3d( -1, -1,  1);
		   glColor4fv(Rose);
		   glNormal3d(0.0,1.0,0.0);
		   glVertex3d( -1, 1,  1);
		   glVertex3d(  1, 1,  1);
		   glVertex3d(  1, 1, -1);
		   glVertex3d( -1, 1, -1);
		   glColor4fv(Bleu);
		   glNormal3d(0.0,-1.0,0.0);
		   glVertex3d( -1, -1,  1);
		   glVertex3d( -1, -1, -1);
		   glVertex3d(  1, -1, -1);
		   glVertex3d(  1, -1,  1);
		   glColor4fv(Cyan);
		   glNormal3d(0.0,0.0,-1.0);
		   glVertex3d(  1,  1, -1);
		   glVertex3d(  1, -1, -1);
		   glVertex3d( -1, -1, -1);
		   glVertex3d( -1,  1, -1);
		   glColor4fv(Vert);
		   glNormal3d(1.0,0.0,0.0);
		   glVertex3d( 1,  1,  1);
		   glVertex3d( 1, -1,  1);
		   glVertex3d( 1, -1, -1);
		   glVertex3d( 1,  1, -1);
		   glColor4fv(Rouge);
		   glNormal3d(0.0,0.0,1.0);
		   glVertex3d(-1,  1, 1);
		   glVertex3d(-1, -1, 1);
		   glVertex3d( 1, -1, 1);
		   glVertex3d( 1,  1, 1);
		glEnd();
	glEndList();

  // Ombre du cube
	cubeOmbre = glGenLists(1);
	glNewList(cubeOmbre, GL_COMPILE);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		   glNormal3d(-1.0,0.0,0.0);
		   glVertex3d( -1,  1,  1);
		   glVertex3d( -1,  1, -1);
		   glVertex3d( -1, -1, -1);
		   glVertex3d( -1, -1,  1);
		   glNormal3d(0.0,1.0,0.0);
		   glVertex3d( -1, 1,  1);
		   glVertex3d(  1, 1,  1);
		   glVertex3d(  1, 1, -1);
		   glVertex3d( -1, 1, -1);
		   glNormal3d(0.0,-1.0,0.0);
		   glVertex3d( -1, -1,  1);
		   glVertex3d( -1, -1, -1);
		   glVertex3d(  1, -1, -1);
		   glVertex3d(  1, -1,  1);
		   glNormal3d(0.0,0.0,-1.0);
		   glVertex3d(  1,  1, -1);
		   glVertex3d(  1, -1, -1);
		   glVertex3d( -1, -1, -1);
		   glVertex3d( -1,  1, -1);
		   glNormal3d(1.0,0.0,0.0);
		   glVertex3d( 1,  1,  1);
		   glVertex3d( 1, -1,  1);
		   glVertex3d( 1, -1, -1);
		   glVertex3d( 1,  1, -1);
		   glNormal3d(0.0,0.0,1.0);
		   glVertex3d(-1,  1, 1);
		   glVertex3d(-1, -1, 1);
		   glVertex3d( 1, -1, 1);
		   glVertex3d( 1,  1, 1);
		glEnd();
	glEndList();
}

