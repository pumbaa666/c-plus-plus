// Fichier Transparence.cpp

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
   SetLight();
}

void Make_CallListes()
{
  //C'est la partie la plus importante
  //Les couleurs sont définies avec un alpha de 0.25
  //qui va servir dans le calcul de la transparence
  //Rappel : 0 = transparent, 1 = opaque
  GLfloat alpha = 0.25f;
//  GLfloat alpha = 1.0f; // Avec 1, il n'y a plus de transparence
  GLfloat Rouge[] = {0.8f, 0.0f, 0.0f, alpha};
	GLfloat Vert[]  = {0.0f, 0.8f, 0.0f, alpha};
	GLfloat Bleu[]  = {0.0f, 0.0f, 0.8f, alpha};
	GLfloat Jaune[]  = {0.8f, 0.8f, 0.0f, alpha};
	GLfloat Rose[]  = {0.8f, 0.0f, 0.8f, alpha};
	GLfloat	Cyan[]  = {0.0f, 0.8f, 0.8f, alpha};

   //on se contente de dessiner le cube,
   //en utilisant cependant la fonction
   //glColor4f() au lieu de glColor3f()
   //car la composante alpha compte cette fois-ci
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
}

int  main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur,hauteur);
  glutCreateWindow("Transparence");

  SetupRC();
  Make_CallListes();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}

