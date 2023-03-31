// Fichier Lumiere2.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "lumiere2.h"

void myinit()
{
    GLfloat position[]= {0.0, 0.0, 1.0, 0.0}; // A l'infini, sur l'axe Z
    GLfloat ambiante[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat diffuse[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat speculaire[]= {1.0, 1.0, 1.0, 1.0}; // blanc

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiante);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, speculaire);

    glEnable(GL_LIGHT0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lumière");

    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(Animate);
    glutMainLoop();
    return 0;
}
