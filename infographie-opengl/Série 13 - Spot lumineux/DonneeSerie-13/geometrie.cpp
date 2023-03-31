// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

const int bCull = 0x1;        // 00000001
const int bDepth = 0x2;       // 00000010
const int bOutline = 0x4;     // 00000100
const int bShadeModel = 0x8;  // 00001000

void DessinerLaScene()
{
    ModeDeDessin(Mode);

    glPushMatrix();
        glRotatef(xRot, 1.0, 0.0, 0.0);
        glRotatef(yRot, 0.0, 1.0, 0.0);
        PlacerLeSpot(55.0, 55.0, 55.0);
    glPopMatrix();
    DessinerLaSphere();
 }

void DessinerLaSphere()
{
    static GLfloat ambiant[]={0.0, 0.0, 0.3, 1.0};	// Bleu. Pour qu'on voit qqch meme si on est derrière la face éclairée
    static GLfloat diffuse[]={0.0, 0.0, 1.0, 1.0};	// Bleu
    static GLfloat speculaire[]={1.0, 1.0, 1.0, 1.0};	// Blanc

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
    glMaterialf(GL_FRONT, GL_SHININESS, 120.0);

    glutSolidSphere(40, 200, 200);
}

void PlacerLeSpot(GLfloat x, GLfloat y, GLfloat z)
{
    static GLfloat position[]= {x, y, z, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glPushMatrix();
        glTranslatef(x, y, z);
        DessinerSpot(x, y, z);
    glPopMatrix();
}

void DessinerSpot(GLfloat x, GLfloat y, GLfloat z)
{
    glPushAttrib(GL_LIGHTING);
        glDisable(GL_LIGHTING);

        glColor3f(1.0, 1.0, 0.0);
        glutSolidSphere(10.0, 50, 50);

        glBegin(GL_LINES);
            glVertex3f(x, y, z);
            glVertex3f(0.0, 0.0, 0.0);
        glEnd();

        glColor3f(1.0, 0.0, 0.0);
        glutSolidCone(15.0, 20.0, 120, 120);
    glPopAttrib();
}

void DessinerLesAxes()
{
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.8f, -0.05f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.8f, 0.05f, 0.0f);

        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.05f, 0.8f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.05f, 0.8f, 0.0f);

        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.05f, 0.0f, 0.8f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.05f, 0.0f, 0.8f);
    glEnd();
    glPopAttrib();
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
