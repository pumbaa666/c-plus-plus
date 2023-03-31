// Fichier Dessin.cpp

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "global.h"

void DessinerUnRectangle()
{
  glDisable(GL_LIGHTING);
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex3f(-5.0f, 0.0f, 0.0f);
    glTexCoord2i(1, 0); glVertex3f(5.0f, 0.0f, 0.0f);
    glTexCoord2i(1, 1); glVertex3f(5.0f, 4.0f, 0.0f);
    glTexCoord2i(0, 1); glVertex3f(-5.0f, 4.0f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
