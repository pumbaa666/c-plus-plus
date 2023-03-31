// Fichier Evenements.cpp

#include <gl\glut.h>  // Librairie GLUT
#include <sys\timeb.h>
#include <math.h>
#include "define.h"
#include "global.h"
#include "dessin.h"
#include "lumiere.h"
#include "evenements.h"

GLfloat vfloor[4][3] = {{-4, 0, 4}, {4, 0, 4}, {4,0, -4},{-4,0, -4}};
GLfloat positionProperties[] = {0.0f, 15.0f, -5.0f, 0.0f}; // Lumière à l'infini
// Plan de projection de l'ombre à 0.01 de hauteur à cause du Depth Buffer
GLfloat vfloor2[4][3] = { {-4, 0.05,  4},
                          { 4, 0.05,  4},
                          { 4, 0.05, -4},
                          {-4, 0.05, -4} };


void drawFloor()
{
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3fv(vfloor[0]);
        glVertex3fv(vfloor[1]);
        glVertex3fv(vfloor[2]);
        glVertex3fv(vfloor[3]);
    glEnd();
}

void Display(void)
{
	static timeb tt ,t;
	static int total;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Pour l'animation
	ftime(&t);
	total += (t.time - tt.time)*1000 + (t.millitm - tt.millitm);
	total %= 360*300;
	tt = t;

	// Limitation de l'ombre à la surface
	glDisable(GL_DEPTH_TEST);	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);	
	glEnable(GL_STENCIL_TEST);	
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
   //****** Le stencil a la même forme que le sol
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
   // Dessiner la surface dans le stencil buffer
	drawFloor();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	// Dessiner la surface dans le framebuffer
	glDisable(GL_LIGHTING);
	drawFloor();
	glEnable(GL_LIGHTING);

	// Dessin de l'objet
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 2, 0xffffffff);
   //****** Pour éviter de voir l'ombre au travers du cube
   // Si le Deptjh est actif plus bas, ce n'est pas nécessaire.
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glPushMatrix();
		glTranslatef(sin(total/30.0f/180.0f*3.1415f)*5.0f, 5.0f, 0.0f);
		glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
		glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
      cube(0);
//		glCallList(cube);
	glPopMatrix();

	// Calcul de la matrice de projection
	// (avec vfloor trois points de la surface)
	static GLfloat floorPlane[4];
	static GLfloat floorShadow[4][4];

   // Le sol pour l'ombre est légèrement au-dessus
	findPlane(floorPlane, vfloor[1], vfloor[2], vfloor[3]);
	shadowMatrix(floorShadow, floorPlane, positionProperties);

	glEnable(GL_STENCIL_TEST);
	//Changement des paramètres pour dessiner une surface noire transparente
	glStencilFunc(GL_EQUAL, 1, 0xffffffff); /* draw if ==1 */
//	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
   //****** Pour éviter de tenir compte N fois de l'obstacle pour l'ombre
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);

   //****** Si le Depth est inactif, on voit l'ombre sous le sol.
	glDisable(GL_DEPTH_TEST);
//   glDepthFunc(GL_LESS);

	// Dessin de l'ombre
	glPushMatrix();
		glMultMatrixf((GLfloat *) floorShadow);
		glTranslatef(sin(total/30.0f/180.0f*3.1415f)*5.0f, 5.0f, 0.0f);
		glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
		glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
      cube(1);
//		glCallList(cube);
	glPopMatrix();

	// Pour terminer
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);

	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape (int w, int h)
{
   GLdouble RapportAspect;
   GLdouble AngleOuverture = 45.0;
   GLdouble PlanAvant = 1.0;
   GLdouble PlanArriere = 100.0;

   if (h == 0) h = 1;
   if (w == 0) w = 1;
   glViewport (0, 0, w, h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   RapportAspect = (GLdouble)w / (GLdouble)h;
   gluPerspective (AngleOuverture, RapportAspect,PlanAvant,PlanArriere);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0,15.0,1.0, 0.0, 0.0, 0.0,0.0,1.0, 0.0);
}

