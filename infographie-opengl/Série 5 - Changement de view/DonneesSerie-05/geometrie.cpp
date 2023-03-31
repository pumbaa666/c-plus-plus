// Fichier Geometrie.cpp

#include <GL\glut.h>
#include <string.h>
#include "geometrie.h"
#include "global.h"

// Afficher la chaîne string dans le viewport
void drawstr(GLdouble x, GLdouble y, GLdouble z, char * string)
{
    int len, i;
    glRasterPos3d(x, y, z);  // Positionner le curseur
    len = (int)strlen(string);
    for(i = 0; i < len; i++)
        glutBitmapCharacter(font_style, string[i]);
}

void AfficherLeTexte()
{
    // Afficher le texte :
    glColor3f(1.0f, 1.0f, 1.0f);  // Couleur blanche pour le texte
    glMatrixMode(GL_PROJECTION);  // On garde la même projection pour le texte
    glPushMatrix();           // Sauvegarder la matrice de projection actuelle
        glLoadIdentity();         // Charger la matrice identité
        gluPerspective(60.0, RapportAspect, PlanAvant, PlanArriere);

        glMatrixMode(GL_MODELVIEW);   // On ne fait pas de rotation pour le texte
        glPushMatrix();       // Sauvegarder la matrice de visualisation actuelle
            glLoadIdentity();     // Charger la matrice identité
            gluLookAt(0, 0, 3,
                      0, 0, 0,
                      0, 1, 0);
            drawstr(-1.7, 1.5, 0.0, "Bouton gauche pour les rotations");
            drawstr(-1.7, 1.3, 0.0, "Bouton droit pour l'angle d'ouverture");
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();               // Restaurer la matrice de projection
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();               // Restaurer la matrice de visualisation
}

void DessinerLaScene()
{
    glPushMatrix();
        glScalef(3.0, 3.0, 3.0);
        DessinerLesAxes();
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(1.0);

    glPushMatrix();
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glTranslatef(2.0, 0.0, 0.0);
        glPushMatrix();
            glScalef(2.0, 2.0, 2.0);
            DessinerLesAxes();
        glPopMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidSphere(0.8, 50, 50);
    glPopMatrix();

    AfficherLeTexte();
}

void DessinerLesAxes()
{
    glColor3f(1.0f, 1.0f, 1.0f);
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
}
