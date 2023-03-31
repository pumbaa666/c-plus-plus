// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "principal.h"

void myinit()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Fond noir

    char Texte[80];
    sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
    glutSetWindowTitle(Texte);

    GLfloat position[]= {0.0, 0.0, 1.0, 0.0}; // A l'infini, sur l'axe Z
    GLfloat ambiante[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat diffuse[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat speculaire[]= {1.0, 1.0, 1.0, 1.0}; // blanc

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiante);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, speculaire);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, -45.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, position);

    glEnable(GL_LIGHT0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spot lumineux");

    myinit();
    glutKeyboardFunc(Key);
    glutSpecialFunc(ToucheSpecial);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    //  glutIdleFunc( Animate );
    glutMouseFunc(Souris);
    glutMotionFunc(DeplacerSouris);
    glutMainLoop();
    return 0;
}

