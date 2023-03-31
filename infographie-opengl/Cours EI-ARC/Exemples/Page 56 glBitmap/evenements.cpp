// Fichier Evenements.cpp

#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "evenements.h"

/*
// Si on utilise : glPixelStorei (GL_UNPACK_ALIGNMENT, 4)
GLubyte rasters[] = {
   0xc0, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xff, 0x00, 0x00, 0x00,
   0xff, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xc0, 0x00, 0x00, 0x00,
   0xff, 0xc0, 0x00, 0x00,
   0xff, 0xc0, 0x00, 0x00};
*/

// Si on utilise : glPixelStorei (GL_UNPACK_ALIGNMENT, 1)
GLubyte rasters[] = {
   0xc0, 0x00,
   0xc0, 0x00,
   0xc0, 0x00,
   0xc0, 0x00,
   0xc0, 0x00,
   0xff, 0x00,
   0xff, 0x00,
   0xc0, 0x00,
   0xc0, 0x00,
   0xc0, 0x00,
   0xff, 0xc0,
   0xff, 0xc0};

void Display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   // Position de départ (x, y)
   glRasterPos2i (0, 0);
   // Pour dessiner une ligne du bitmap, on utilise 10 pixels
   // c'est-à-dire :
   // les 8 bits du premier octet et les deux premiers bits
   // du second. Les 6 bits restants sont ignorés, puisque
   // l'alignement se fait sur un octet. appel de :
   // glPixelStorei (GL_UNPACK_ALIGNMENT, 1)

   //         w   h  Xbo  Ybo  Xbi   Ybi  bitmap
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glRasterPos2i (0, 480);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glRasterPos2i (480, 480);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glRasterPos2i (480, 0);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glFlush();
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

