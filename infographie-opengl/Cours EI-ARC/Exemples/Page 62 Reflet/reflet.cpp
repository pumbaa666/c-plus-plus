// Fichier Reflet.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "lumiere.h"
#include "evenements.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); // Ce sont les valuers par défaut.
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_POLYGON_SMOOTH);
   glEnable(GL_CULL_FACE);
   SetLight();
}

void Make_CallListes()
{
		GLfloat Rouge[] = {0.8f, 0.0f, 0.0f, 1.0f};
		GLfloat Vert[]  = {0.0f, 0.8f, 0.0f, 1.0f};
		GLfloat Bleu[]  = {0.0f, 0.0f, 0.8f, 1.0f};
		GLfloat Jaune[]  = {0.8f, 0.8f, 0.0f, 1.0f};
		GLfloat Rose[]  = {0.8f, 0.0f, 0.8f, 1.0f};
		GLfloat	Cyan[]  = {0.0f, 0.8f, 0.8f, 1.0f};

		cube = glGenLists(1);
		glNewList(cube, GL_COMPILE);
			   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Rouge);
			   glNormal3d(0.0,0.0,1.0);
			glBegin(GL_QUADS);
			   glVertex3d(-1,  1, 1);
			   glVertex3d(-1, -1, 1);
			   glVertex3d( 1, -1, 1);
			   glVertex3d( 1,  1, 1);
			glEnd();
			   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Jaune);
			   glNormal3d(-1.0,0.0,0.0);
			glBegin(GL_QUADS);
			   glVertex3d( -1,  1,  1);
			   glVertex3d( -1,  1, -1);
			   glVertex3d( -1, -1, -1);
			   glVertex3d( -1, -1,  1);
			glEnd();
			   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Vert);
			   glNormal3d(1.0,0.0,0.0);
			glBegin(GL_QUADS);
			   glVertex3d( 1,  1,  1);
			   glVertex3d( 1, -1,  1);
			   glVertex3d( 1, -1, -1);
			   glVertex3d( 1,  1, -1);
			glEnd();
			   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Rose);
			   glNormal3d(0.0,1.0,0.0);
			glBegin(GL_QUADS);
			   glVertex3d( -1, 1,  1);
			   glVertex3d(  1, 1,  1);
			   glVertex3d(  1, 1, -1);
			   glVertex3d( -1, 1, -1);
			glEnd();
			   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Bleu);
			   glNormal3d(0.0,-1.0,0.0);
			glBegin(GL_QUADS);
			   glVertex3d( -1, -1,  1);
			   glVertex3d( -1, -1, -1);
			   glVertex3d(  1, -1, -1);
			   glVertex3d(  1, -1,  1);
			glEnd();
			   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Cyan);
			   glNormal3d(0.0,0.0,-1.0);
			glBegin(GL_QUADS);
			   glVertex3d(  1,  1, -1);
			   glVertex3d(  1, -1, -1);
			   glVertex3d( -1, -1, -1);
			   glVertex3d( -1,  1, -1);		   
			glEnd();
		glEndList();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur,hauteur);
  glutCreateWindow("Reflet");

  SetupRC();
  Make_CallListes();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}

