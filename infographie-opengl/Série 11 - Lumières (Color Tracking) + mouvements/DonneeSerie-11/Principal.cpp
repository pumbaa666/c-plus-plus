// Fichier Principal.CPP

#include <GL\glut.h>
#include "evenements.h"
#include "principal.h"

void myinit()
{
    GLfloat position[]= {0.0, 0.0, 1.0, 0.0}; // A l'infini, sur l'axe Z
    GLfloat ambiante[]= {0.4, 0.4, 0.4, 1.0}; // glColorMaterial --> pas tout a fait blanc
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

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_DIFFUSE); // Tache blanche sur les sphère illuminées
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glClearColor(0.0, 0.0, 1.0, 1.0);

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Objets solides");

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
