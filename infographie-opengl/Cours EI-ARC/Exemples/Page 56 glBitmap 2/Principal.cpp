// Fichier Principal.CPP

/*
 *  Draws some text in a bitmapped font.  Uses glBitmap() 
 *  and other pixel routines.  Also demonstrates use of 
 *  display lists.
 */

#include <GL\glut.h>
#include "rasterfont.h"
#include "evenements.h"
#include "principal.h"

void MyInit(void)
{
   glShadeModel (GL_FLAT);
   makeRasterFont();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Du texte écrit avec des Bitmaps");

  MyInit();
  glutReshapeFunc(MyReshape);
  glutDisplayFunc(Display);
  glutMainLoop();
  return 0;
}

