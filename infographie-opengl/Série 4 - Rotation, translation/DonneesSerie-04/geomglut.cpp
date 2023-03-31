// Fichier GeomGlut.CPP

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"

void myinit()
{
    glClearColor(BLEU, 0.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Objets g�om�triques avec GLUT");

    myinit();
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}

