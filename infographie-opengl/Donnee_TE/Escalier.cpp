// Loïc Correvon
// Fichier Escalier.cpp

#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include "escalier.h"

void DessinerLEscalier()
{
    static int nbMarche = 10;
    static float hauteurEscalier = 3.0;
    static float hauteurColone = 4.0;
    static float rayonColone = 0.2;
    int i;

    glPushMatrix();
        glPushMatrix(); // J'ai dessiné le cylindre couché, il faut donc le redresser
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            DessinerUnCylindre(hauteurColone, rayonColone);
        glPopMatrix();

        for(i = 0; i < nbMarche; i++) // Les marche en revanche sont dessinées juste dès le départ
        {
            glRotatef(360.0/(float)nbMarche, 0.0, 1.0, 0.0); // Tourne autour du pilier
            glTranslatef(0.0, hauteurEscalier / nbMarche,0.0); // Monte d'une marche
            DessinerUneMarche();
        }
    glPopMatrix();
}

void DessinerUneMarche()
{
    static float a = 0.2;
    static float b = 1.0;
    static float c = 2.0;
    static float d = 0.2; // = hauteur de la marche.

    /* Haut de la marche */
    glFrontFace(GL_CW);
    glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex3f(0.0f, d, -a/2.0);
        glVertex3f(c, d, -b/2.0);
        glVertex3f(c, d, b/2.0);
        glVertex3f(0.0f, d, a/2.0);
    glEnd();

    /* Coté collé à la colone */
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.7f, 0.7f, 0.0f);

        glVertex3f(0.0f, d, -a/2.0);
        glVertex3f(0.0f, d, a/2.0);

        glVertex3f(0.0f, 0, -a/2.0);
        glVertex3f(0.0f, 0, a/2.0);
    glEnd();

    /* Grand coté 1 (face que l'on voit de la 1ère marche lorsqu'on lance le programme) */
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.8f, 0.8f, 0.0f);

        glVertex3f(0.0f, d, -a/2.0);
        glVertex3f(0.0f, 0.0f, -a/2.0);

        glVertex3f(c, d, -b/2.0);
        glVertex3f(c, 0.0f, -b/2.0);
    glEnd();

    /* Coté opposé à la colone */
    glFrontFace(GL_CCW);
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.9f, 0.9f, 0.0f);

        glVertex3f(c, d, -b/2.0);
        glVertex3f(c, d, b/2.0);

        glVertex3f(c, 0, -b/2.0);
        glVertex3f(c, 0, b/2.0);
    glEnd();

    /* Grand coté 2 (opposée au coté 1)*/
    glBegin(GL_QUAD_STRIP);
        glColor3f(1.0f, 1.0f, 0.0f);

        glVertex3f(0.0f, d, a/2.0);
        glVertex3f(0.0f, 0.0f, a/2.0);

        glVertex3f(c, d, b/2.0);
        glVertex3f(c, 0.0f, b/2.0);
    glEnd();

    /* Bas de la marche */
    glFrontFace(GL_CCW);
    glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.6f, 0.0f);
        glVertex3f(0.0f, 0.0f, -a/2.0);
        glVertex3f(c, 0.0f, -b/2.0);
        glVertex3f(c, 0.0f, b/2.0);
        glVertex3f(0.0f, 0.0f, a/2.0);
    glEnd();
}

void DessinerUnCylindre(GLfloat hauteur, GLfloat rayon)
{
    static float    nbFace = 15, // Nombre de face du cylindre. Correspond avec les cercle de base et du haut. Augmenter pour affiner le tracé
                    i,
                    pas = 2*M_PI / nbFace; // pas veut dire deltaAngle

    /* Cercle de base */
    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.9f);
        glVertex3f(0.0, 0.0, 0.0);
        for(i = 0.0; i <= 2*M_PI+pas; i += pas)
            glVertex3f(cos(i)*rayon,sin(i)*rayon,0.0f);
    glEnd();


    /* Corps */
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.0f, 0.0f, 0.4f);
        for(i = 0.0; i < 2*M_PI+pas; i += pas)
        {
            glVertex3f(cos(i)*rayon, sin(i)*rayon, 0.0f);
            glVertex3f(cos(i+pas)*rayon, sin(i+pas)*rayon, 0.0f);

            glVertex3f(cos(i)*rayon, sin(i)*rayon, hauteur);
            glVertex3f(cos(i+pas)*rayon, sin(i+pas)*rayon, hauteur);
        }
    glEnd();

    /* Cercle du haut */
    glFrontFace(GL_CCW);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.9f);
        glVertex3f(0.0, 0.0, hauteur);
        for(i = 0.0; i < 2*M_PI+pas; i += pas)
            glVertex3f(cos(i)*rayon, sin(i)*rayon, hauteur);
    glEnd();
}
