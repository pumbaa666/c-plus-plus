// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"
#include "normal.h"
#include <math.h>

float tabPts[3][3];
float normal[3];

void DessinerLaScene()
{
    ModeDeDessin(Mode);
    glPushMatrix();
        glRotatef(rotLumiere, 0.0f, 1.0f, 0.0f);
        PossitionnerLumiere(0.0f, 7.0f, 9.0f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.0f, 0.0f, 2.5f);
        DessinerLesMurs();
        DessinerLeToit();
    glPopMatrix();

    DessinerLeSol();
}

void PossitionnerLumiere(GLfloat x, GLfloat y, GLfloat z)
{
    static GLfloat position[]= {x, y, z, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glPushMatrix();
        glTranslatef(x, y, z); // Mieux : faire une 2ème lumière
        DessinerSoleil();
    glPopMatrix();
}

void DessinerSoleil()
{
    static GLfloat ambiant[]={1.0, 1.0, 0.0, 1.0};	// Jaune. Pour qu'on voit qqch meme si on est derrière la face éclairée
    static GLfloat diffuse[]={1.0, 1.0, 0.0, 1.0};	// Jaune
    static GLfloat speculaire[]={1.0, 1.0, 0.0, 1.0};	// Jaune

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glutSolidSphere(1.0, 50, 50);
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

void DessinerLesMurs()
{
    static GLfloat ambiant[]={0.2, 0.2, 0.2, 1.0};	// un peu gris. Pour qu'on voit qqch meme si on est derrière la face éclairée
    static GLfloat diffuse[]={1.0, 1.0, 1.0, 1.0};	// Blanc
    static GLfloat speculaire[]={0.0, 0.0, 0.0, 1.0};	// Blanc // static, pour ne pas recréer la variable à chaque fois

    static GLfloat ambiantInterieur[]={0.0, 0.7, 0.0, 1.0};	// Vert
    static GLfloat diffuseInterieur[]={0.0, 0.0, 0.0, 1.0};	// Noir : pas de lumière difuse => pas affecté par la lumière ambiante

    glFrontFace(GL_CW);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
        glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

        glMaterialfv(GL_BACK, GL_AMBIENT, ambiantInterieur);
        glMaterialfv(GL_BACK, GL_DIFFUSE, diffuseInterieur);
    glBegin(GL_TRIANGLE_STRIP);

        tabPts[0][0] = 0.0;
        tabPts[0][1] = 0.0;
        tabPts[0][2] = 0.0;

        tabPts[1][0] = 0.0;
        tabPts[1][1] = 4.0;
        tabPts[1][2] = 0.0;

        tabPts[2][0] = 10.0;
        tabPts[2][1] = 0.0;
        tabPts[2][2] = 0.0;

        calcNormal(tabPts, normal);
        InverserNormal(normal);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(tabPts[0][0], tabPts[0][1], tabPts[0][2]);   // 0
        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);   // 1
        glVertex3f(tabPts[2][0], tabPts[2][1], tabPts[2][2]);  // 2

        tabPts[0][0] = 10.0;
        tabPts[0][1] = 0.0;
        tabPts[0][2] = 0.0;

        tabPts[1][0] = 10.0;
        tabPts[1][1] = 4.0;
        tabPts[1][2] = 0.0;

        tabPts[2][0] = 10.0;
        tabPts[2][1] = 0.0;
        tabPts[2][2] = -5.0;
        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 3

        calcNormal(tabPts, normal);
        InverserNormal(normal);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(tabPts[2][0], tabPts[2][1], tabPts[2][2]); // 4

        tabPts[0][0] = 10.0;
        tabPts[0][1] = 0.0;
        tabPts[0][2] = -5.0;

        tabPts[1][0] = 10.0;
        tabPts[1][1] = 4.0;
        tabPts[1][2] = -5.0;

        tabPts[2][0] = 0.0;
        tabPts[2][1] = 0.0;
        tabPts[2][2] = -5.0;
        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 5

        calcNormal(tabPts, normal);
        InverserNormal(normal);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(tabPts[2][0], tabPts[2][1], tabPts[2][2]); // 6

        tabPts[0][0] = 0.0;
        tabPts[0][1] = 0.0;
        tabPts[0][2] = -5.0;

        tabPts[1][0] = 0.0;
        tabPts[1][1] = 4.0;
        tabPts[1][2] = -5.0;

        tabPts[2][0] = 0.0;
        tabPts[2][1] = 0.0;
        tabPts[2][2] = 0.0;
        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 7

        calcNormal(tabPts, normal);
        InverserNormal(normal);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(tabPts[2][0], tabPts[2][1], tabPts[2][2]); // 0, 8

        tabPts[0][0] = 0.0;
        tabPts[0][1] = 0.0;
        tabPts[0][2] = 0.0;

        tabPts[1][0] = 0.0;
        tabPts[1][1] = 4.0;
        tabPts[1][2] = 0.0;

        tabPts[2][0] = 10.0;
        tabPts[2][1] = 0.0;
        tabPts[2][2] = 0.0;

        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 1, 9
    glEnd();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}

void DessinerLeToit()
{
    static GLfloat ambiant[]={0.3, 0.0, 0.0, 1.0};	// un peu rouge. Pour qu'on voit qqch meme si on est derrière la face éclairée
    static GLfloat diffuse[]={1.0, 0.0, 0.0, 1.0};	// Rouge
    static GLfloat speculaire[]={1.0, 1.0, 1.0, 1.0};	// Blanc // static, pour ne pas recréer la variable à chaque fois

    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
        glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

        tabPts[0][0] = -0.5;
        tabPts[0][1] = 4.0;
        tabPts[0][2] = 0.0;

        tabPts[1][0] = -0.5;
        tabPts[1][1] = 7.0;
        tabPts[1][2] = -2.5;

        tabPts[2][0] = 10.5;
        tabPts[2][1] = 4.0;
        tabPts[2][2] = 0.0;

        calcNormal(tabPts, normal);
        InverserNormal(normal);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(tabPts[0][0], tabPts[0][1], tabPts[0][2]);  // 1
        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 2
        glVertex3f(tabPts[2][0], tabPts[2][1], tabPts[2][2]);  // 3

        tabPts[1][0] = 10.5;
        tabPts[1][1] = 7.0;
        tabPts[1][2] = -2.5;

        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 4
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
        glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

        tabPts[0][0] = 10.5;
        tabPts[0][1] = 4.0;
        tabPts[0][2] = -5.5;

        tabPts[1][0] = 10.5;
        tabPts[1][1] = 7.0;
        tabPts[1][2] = -2.5;

        tabPts[2][0] = -0.5;
        tabPts[2][1] = 4.0;
        tabPts[2][2] = -5.5;

        calcNormal(tabPts, normal);
        InverserNormal(normal);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(tabPts[0][0], tabPts[0][1], tabPts[0][2]);  // 1
        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 2
        glVertex3f(tabPts[2][0], tabPts[2][1], tabPts[2][2]);  // 3

        tabPts[1][0] = -0.5;
        tabPts[1][1] = 7.0;
        tabPts[1][2] = -2.5;

        glVertex3f(tabPts[1][0], tabPts[1][1], tabPts[1][2]);  // 4
    glEnd();}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

    glPushAttrib(GL_LIGHTING);
        glDisable(GL_LIGHTING); // Désactiver la lumière permet d'utiliser glColor
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);

        for(r = -100; r  <= 100; r += nStep)
            {
            glVertex3f((float)r, 0.0f, -100.0f);
            glVertex3f((float)r, 0.0f, 100.0f);
            }

        for(c = -100; c <= 100; c += nStep)
            {
            glVertex3f(100.0f, 0.0f, (float)c);
            glVertex3f(-100.0f, 0.0f, (float)c);
            }

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
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);

    if(mask & bShadeModel)
        glShadeModel(GL_SMOOTH);  // Interpolation de la couleur entre les différents sommets
    else
        glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur du dernier sommet (qui est aussi le premier)
}

