//Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
  ModeDeDessin(Mode);
  DessinerLesAxes();
  DessinerLeSol();

/*
  // Dessiner la 1ère maison
  glPushMatrix();
    glTranslatef(-15.0f, 0.0f, 2.5f);
    DessinerLaMaison();
  glPopMatrix();

  // Dessiner la 2ème maison
  glPushMatrix();
    glTranslatef(15.0f, 0.0f, 2.5f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    DessinerLaMaison();
  glPopMatrix();

  // Dessiner le 1er cône
  glPushMatrix();
    glTranslatef(10.0f, 0.0f, 10.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(3.0f, 4.0f, 3.0f);
    glColor3f(1.0f, 0.0f, 0.0f);   // Rouge
    DessinerLeCone();
  glPopMatrix();

  // Dessiner le 2ème cône
  glPushMatrix();
    glTranslatef(10.0f, 0.0f, -20.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(3.0f, 5.0f, 3.0f);
    glColor3f(0.0f, 0.7f, 0.0f);   // Vert
    DessinerLeCone();
  glPopMatrix();

  // Dessiner le 3ème cône avec la librairie GLUT
  glPushMatrix();
  //  glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);   // Jaune
    glutSolidCone(1.0f, 3.0f, 20.0f, 20.0f);
  glPopMatrix();
*/
//  DessinerLeSol();
}

void DessinerLesAxes()
{
  glCallList(axes);
}

void DessinerLaMaison()
{
  glCallList(maison);
}

void DessinerLesMurs()
{
  glCallList(murs);
}

void DessinerLeToit()
{
  glCallList(toit);
}

void DessinerLeSol()
{
  glCallList(sol);
}

void DessinerLeCone()
{
  glCallList(cone);
}

void ModeDeDessin(int mask)
{
	// Turn culling on if flag is set
	if(mask & bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Enable depth testing if flag is set
	if(mask & bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Draw back side as a polygon only, if flag is set
	if(mask & bOutline)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   if(mask & bShadeModel)
      glShadeModel(GL_SMOOTH);  // Interpolation de la couleur
                                // entre les différents sommets
   else
      glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur
                                // du dernier sommet (qui est aussi le premier)
}

