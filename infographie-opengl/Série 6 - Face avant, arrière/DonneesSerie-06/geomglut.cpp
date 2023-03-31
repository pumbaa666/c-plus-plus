// Fichier GeomGlut.CPP

#include <GL\glut.h>
#include "evenements.h"
#include "GeomGlut.h"

void myinit()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //glShadeMode(GL_FLAT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Utilisation de gluPerspective");

    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(Souris);
    glutMotionFunc(Rotation);
    glutMainLoop();
    return 0;
}

