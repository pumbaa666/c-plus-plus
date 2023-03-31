// Fichier CallListes.cpp

#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "texture.h"
#include "calllistes.h"

void Make_CallListes()
{
   GLfloat  ambientMaterial[] =  { 0.3f, 0.3f, 0.3f, 1.0f };
   GLfloat  diffuseMaterial[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat  specularMaterial[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
   GLint shininess = 10;

   cube = glGenLists(1);
   glNewList(cube, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
      glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
      glMateriali(GL_FRONT, GL_SHININESS, shininess);

      glBindTexture(GL_TEXTURE_2D, texture1);
      glBegin(GL_QUADS);
         glNormal3d(0.0,0.0,1.0);
         // On spécifie la position des épingles
         // (on tourne : une seule coordonnée change à la fois)
         glTexCoord2d(0,1);glVertex3d(-1,  1, 1);
         glTexCoord2d(0,0);glVertex3d(-1, -1, 1);
         glTexCoord2d(1,0);glVertex3d( 1, -1, 1);
         glTexCoord2d(1,1);glVertex3d( 1,  1, 1);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, texture2);
      glBegin(GL_QUADS);
         glNormal3d(-1.0,0.0,0.0);
            //idem
         glTexCoord2d(1,1);glVertex3d( -1,  1,  1);
         glTexCoord2d(1,0);glVertex3d( -1,  1, -1);
         glTexCoord2d(0,0);glVertex3d( -1, -1, -1);
         glTexCoord2d(0,1);glVertex3d( -1, -1,  1);
            //idem
      glEnd();

      glBindTexture(GL_TEXTURE_2D, texture3);
      glBegin(GL_QUADS);
        glNormal3d(1.0,0.0,0.0);
         glTexCoord2d(1,1);glVertex3d( 1,  1,  1);
         glTexCoord2d(0,1);glVertex3d( 1, -1,  1);
         glTexCoord2d(0,0);glVertex3d( 1, -1, -1);
         glTexCoord2d(1,0);glVertex3d( 1,  1, -1);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, texture4);
      glBegin(GL_QUADS);
         glNormal3d(0.0,1.0,0.0);
            //idem
         glTexCoord2d(0,1);glVertex3d( -1, 1,  1);
         glTexCoord2d(1,1);glVertex3d(  1, 1,  1);
         glTexCoord2d(1,0);glVertex3d(  1, 1, -1);
         glTexCoord2d(0,0);glVertex3d( -1, 1, -1);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, texture5);
      glBegin(GL_QUADS);
         glNormal3d(0.0,-1.0,0.0);
            //idem
         glTexCoord2d(0,1);glVertex3d( -1, -1,  1);
         glTexCoord2d(0,0);glVertex3d( -1, -1, -1);
         glTexCoord2d(1,0);glVertex3d(  1, -1, -1);
         glTexCoord2d(1,1);glVertex3d(  1, -1,  1);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, texture6);
      glBegin(GL_QUADS);
         glNormal3d(0.0,0.0,-1.0);
            //idem
         glTexCoord2d(1,1);glVertex3d(  1,  1, -1);
         glTexCoord2d(1,0);glVertex3d(  1, -1, -1);
         glTexCoord2d(0,0);glVertex3d( -1, -1, -1);
         glTexCoord2d(0,1);glVertex3d( -1,  1, -1);
      glEnd();
   glEndList();
}
