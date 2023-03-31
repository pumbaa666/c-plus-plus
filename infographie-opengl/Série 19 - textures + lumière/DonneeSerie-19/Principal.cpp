// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "principal.h"
#include "Texture2.h"

void MyInit()
{
    // Fond blanc
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    GLfloat position[]= {0.0, 0.0, 1.0, 0.0}; // A l'infini, sur l'axe Z
    GLfloat ambiante[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat diffuse[]= {1.0, 1.0, 1.0, 1.0}; // blanc
    GLfloat speculaire[]= {1.0, 1.0, 1.0, 1.0}; // blanc

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiante);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, speculaire);

    // Penser à tester si les fichiers existe (  if(textures[i] == true)  )
    textures[0] = TextureLoad("a.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    textures[1] = TextureLoad("b.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    textures[2] = TextureLoad("c.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    textures[3] = TextureLoad("d.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    textures[4] = TextureLoad("e.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    textures[5] = TextureLoad("f.bmp", false, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_CLAMP);

    glEnable(GL_LIGHT0);
    char Texte[80];
    sprintf(Texte, "Mode (GL_SMOOTH, GL_LINE, DEPTH, CULL) : %X", Mode);
    glutSetWindowTitle(Texte);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(20, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Canevas de programme OpenGL");

  MyInit();
  glutKeyboardFunc(Key);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(MyReshape);
  glutDisplayFunc(Display);
//  glutIdleFunc( Animate );
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();
  return 0;
}

