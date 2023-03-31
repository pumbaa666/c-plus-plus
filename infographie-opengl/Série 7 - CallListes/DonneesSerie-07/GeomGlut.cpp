// Fichier GeomGlut.cpp

#include <GL\glut.h>
#include "global.h"
#include "evenements.h"
#include "calllistes.h"
#include "geomglut.h"

void myinit()
{
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Objets solides");

    myinit();
    Make_CallListes();

    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Animate);  // Appel Animate si le processeur est libre.
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutMainLoop();
    return 0;
}
