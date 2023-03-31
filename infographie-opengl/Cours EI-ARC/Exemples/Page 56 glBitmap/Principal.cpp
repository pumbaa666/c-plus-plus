// Fichier Principal.CPP

/*
 *  Draws the bitmapped letter F on the screen (several times).
 *  This demonstrates use of the glBitmap() call.
 */

#include <GL\glut.h>
#include <stdio.h>
#include "evenements.h"
#include "principal.h"

void MyInit()
{
   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("La lettre F dessinée avec un Bitmap");

  MyInit();
  glutReshapeFunc(MyReshape);
  glutDisplayFunc(Display);
  glutMainLoop();
  return 0;
}

