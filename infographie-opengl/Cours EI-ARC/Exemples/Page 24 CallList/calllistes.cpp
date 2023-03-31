// Fichier CallListes.cpp

#include <gl\glut.h>                // Librairie GLUT
#include "define.h"
#include "global.h"
#include "evenements.h"

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); // Ce sont les valeurs par défaut

  // Anti-aliasing
	glShadeModel(GL_SMOOTH);
//	glShadeModel(GL_FLAT);
  glEnable(GL_POINT_SMOOTH);
//  glDisable(GL_POINT_SMOOTH);

  // Culling
	glFrontFace(GL_CCW);
//	glFrontFace(GL_CW);
  glCullFace(GL_BACK);  // GL_BACK, GL_FRONT ou GL_FRONT_AND_BACK
  glEnable(GL_CULL_FACE);
//  glDisable(GL_CULL_FACE);

	// Depth-buffer
	glEnable(GL_DEPTH_TEST);
}

void Make_CallListes()
{
		//Facile, non ?
		//il suffit de faire cela une fois, au debut du programme
		//et cela reste en mémoire disponible à tout instant
  point = glGenLists(3);
  triangle = point + 1;
  droite = triangle + 1;
	glNewList(point,GL_COMPILE);
  	glColor3f(1.0f,1.0f,1.0f);
    glPointSize(5.0);
		glBegin(GL_POINTS);
			glVertex2f(-10.0f,-10.0f);
		glEnd();
	glEndList();

	glNewList(triangle,GL_COMPILE);
		glBegin(GL_TRIANGLES);
				//remarquez que l'on peut mettre beaucoup de choses 
				//dans une CallListe tel que de la couleur.
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f,130.0f,0.0f);

			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,0.0f);

			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(130.0f,0.0f,0.0f);
		glEnd();
	glEndList();

	glNewList(droite,GL_COMPILE);
		glColor3f(1.0f,0.0f,1.0f);
		glBegin(GL_LINES);
			glVertex3f(-10.0f,-10.0f,-50.0f);
			glVertex3f(100.0f,100.0f,50.0f);
		glEnd();
	glEndList();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  // Ne pas oublier d'initialiser le Depth-Buffer
  // Pas de Double-buffering
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur,hauteur);
  glutCreateWindow("Test");

  SetupRC();
  Make_CallListes();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}
