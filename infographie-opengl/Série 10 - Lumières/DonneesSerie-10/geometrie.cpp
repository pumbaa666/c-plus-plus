// Fichier Geometrie.cpp
#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

void DessinerLesAxes()
{
    glPushAttrib(GL_LIGHTING_BIT); // sauvegarde les état des lumières (source, pos, etc...)
    glDisable(GL_LIGHTING); // Désactiver la lumière permet d'utiliser glColor
    glColor3f(1.0, 1.0, 0.0);

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

void DessinerTore()
{
    static GLfloat ambiant[]={0.0, 0.0, 0.2, 1.0};	// un peu bleu. Pour qu'on voit qqch meme si on est derrière la face éclairée
    static GLfloat diffuse[]={0.0, 0.0, 1.0, 1.0};	// Bleu
    static GLfloat speculaire[]={1.0, 1.0, 0.0, 1.0};	// Blanc // static, pour ne pas recréer la variable à chaque fois

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);  // A utiliser si on utilise de la lumière spéculaire.
                                                //Plus le nombre (ici 50.0) est grand, plus la tache de lumière est étallée
    glutSolidTorus(0.33, 0.75, 50, 100);
}

void DessinerLaScene()
{
    static GLfloat position[]= {0.0, 0.0, 1.0, 0.0}; // A l'infini, sur l'axe Z
    glPushMatrix();
        glRotatef(a, 0.0, 1.0, 0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glScalef(1.5, 1.5, 1.5);
        DessinerLesAxes();
    glPopMatrix();

    DessinerTore();
}