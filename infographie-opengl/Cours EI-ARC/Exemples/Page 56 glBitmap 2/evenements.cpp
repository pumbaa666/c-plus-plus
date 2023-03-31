// Fichier Evenements.cpp

#include <GL\glut.h>
#include "rasterfont.h"
#include "evenements.h"

void Display()
{
   GLfloat white[3] = { 1.0, 1.0, 1.0 };

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3fv(white);

   glRasterPos2i(20, 60);
   printString("VOICI UNE PREMIERE LIGNE DE TEXTE");
   glRasterPos2i(20, 40);
   printString("EN VOICI UNE DEUXIEME");
   glFlush ();
}

void MyReshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void Key(unsigned char key, int /*x*/, int /*y*/ )
{
   switch (key) {
      case 27:
         exit(0);
   }
}

