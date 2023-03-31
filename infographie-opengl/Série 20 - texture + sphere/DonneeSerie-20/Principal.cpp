// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "calllistes.h"
#include "global.h"
#include "evenements.h"
#include "principal.h"
#include "texture2.h"

void MyInit()
{
    // Fond noir
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    GLfloat position[]= {0.0, 0.0, 1.0, 0.0}; // A l'infini, sur l'axe Z
    GLfloat ambiante[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat diffuse[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat speculaire[]= {1.0, 1.0, 1.0, 1.0}; // blanc

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiante);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, speculaire);

    texture_Terre = TextureLoad("petique.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);

    char Texte[80];
    sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %o", Mode);
    glutSetWindowTitle(Texte);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Canevas de programme OpenGL");

  MyInit();
  Make_CallListes();
  glutKeyboardFunc(Key);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(MyReshape);
  glutDisplayFunc(Display);
  glutIdleFunc( Animate );
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();
  return 0;
}

