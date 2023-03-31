// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "principal.h"

void myinit()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Setup and enable light 0
    static GLfloat  ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);

    // Pour séparer le calculs des faces avant et arrière
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Valeurs pour le brouillard
 /*   glFogi(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, couleurBrouillard);
    glFogf(GL_FOG_DENSITY, 0.1);*/


    glEnable(GL_DEPTH_TEST);
    char Texte[80];
    sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
    glutSetWindowTitle(Texte);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Objets solides avec brouilard");

    myinit();
    glutKeyboardFunc(Key);
    glutSpecialFunc(ToucheSpecial);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc( Animate );
    glutMouseFunc(Souris);
    glutMotionFunc(DeplacerSouris);
    glutMainLoop();
    return 0;
}

