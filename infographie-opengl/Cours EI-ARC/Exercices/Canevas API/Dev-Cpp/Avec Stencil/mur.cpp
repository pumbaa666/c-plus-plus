// Fichier Mur.cpp

#include <GL\glut.h>
#include <stdio.h>
#include "texture2.h"
#include "global.h"
#include "normal.h"
#include "mur.h"

GLint mur; // Variable globale pour la Call List

void DessinerLeMur()
{
  glCallList(mur);
}

int MakeMurCallList(GLfloat longueur, GLfloat hauteur, GLfloat epaisseur)
{
   int code = 0;
   // Construction d'un mur dont le centre de gravité se trouve
   // à l'origine des axes.
   // Le mur a les dimensions : longueur x hauteur x epaisseur.

   // Le fichier "mur.bmp" contient la texture à appliquer.

   GLdouble DemiLongueur = longueur/2.0;
   GLdouble DemiHauteur = hauteur/2.0;
   GLdouble DemiEpaisseur = epaisseur/2.0;

   GLfloat  ambientMaterial[] =  { 0.3f, 0.3f, 0.3f, 1.0f };
   GLfloat  diffuseMaterial[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat  specularMaterial[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
   GLint shininess = 10;

   // Charger la texture
   GLint texture;
   texture = TextureLoad("mur.bmp", GL_FALSE,
                                    GL_LINEAR_MIPMAP_LINEAR,
                                    GL_LINEAR,
                                    GL_REPEAT);
   if(texture == 0)
     code = 1;
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   // Créer la Call List
   mur = glGenLists(1);
   glNewList(mur, GL_COMPILE);
      glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
      glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
      glMateriali(GL_FRONT, GL_SHININESS, shininess);

      glBindTexture(GL_TEXTURE_2D, texture);
      glBegin(GL_QUADS);
         glNormal3d(0.0,0.0,1.0);
         // On spécifie la position des épingles
         // (on tourne : une seule coordonnée change à la fois)
         glTexCoord2d(0,1);
         glVertex3d(-DemiLongueur,  DemiHauteur, DemiEpaisseur);
         glTexCoord2d(0,0);
         glVertex3d(-DemiLongueur, -DemiHauteur, DemiEpaisseur);
         glTexCoord2d(10,0);
         glVertex3d( DemiLongueur, -DemiHauteur, DemiEpaisseur);
         glTexCoord2d(10,1);
         glVertex3d( DemiLongueur,  DemiHauteur, DemiEpaisseur);
      glEnd();

      glBegin(GL_QUADS);
         glNormal3d(-1.0,0.0,0.0);
            //idem
         glTexCoord2d(1,.1);
         glVertex3d( -DemiLongueur,  DemiHauteur,  DemiEpaisseur);
         glTexCoord2d(1,0);
         glVertex3d( -DemiLongueur,  DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(0,0);
         glVertex3d( -DemiLongueur, -DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(0,.1);
         glVertex3d( -DemiLongueur, -DemiHauteur,  DemiEpaisseur);
            //idem
      glEnd();

      glBegin(GL_QUADS);
        glNormal3d(1.0,0.0,0.0);
         glTexCoord2d(1,.1);
         glVertex3d( DemiLongueur,  DemiHauteur,  DemiEpaisseur);
         glTexCoord2d(0,.1);
         glVertex3d( DemiLongueur, -DemiHauteur,  DemiEpaisseur);
         glTexCoord2d(0,0);
         glVertex3d( DemiLongueur, -DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(1,0);
         glVertex3d( DemiLongueur,  DemiHauteur, -DemiEpaisseur);
      glEnd();

      glBegin(GL_QUADS);
         glNormal3d(0.0,1.0,0.0);
            //idem
         glTexCoord2d(0,.1);
         glVertex3d( -DemiLongueur, DemiHauteur,  DemiEpaisseur);
         glTexCoord2d(10,.1);
         glVertex3d(  DemiLongueur, DemiHauteur,  DemiEpaisseur);
         glTexCoord2d(10,0);
         glVertex3d(  DemiLongueur, DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(0,0);
         glVertex3d( -DemiLongueur, DemiHauteur, -DemiEpaisseur);
      glEnd();

      glBegin(GL_QUADS);
         glNormal3d(0.0,-1.0,0.0);
            //idem
         glTexCoord2d(0,.1);
         glVertex3d( -DemiLongueur, -DemiHauteur,  DemiEpaisseur);
         glTexCoord2d(0,0);
         glVertex3d( -DemiLongueur, -DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(10,0);
         glVertex3d(  DemiLongueur, -DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(10,.1);
         glVertex3d(  DemiLongueur, -DemiHauteur,  DemiEpaisseur);
      glEnd();

      glBegin(GL_QUADS);
         glNormal3d(0.0,0.0,-1.0);
            //idem
         glTexCoord2d(10,1);
         glVertex3d(  DemiLongueur,  DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(10,0);
         glVertex3d(  DemiLongueur, -DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(0,0);
         glVertex3d( -DemiLongueur, -DemiHauteur, -DemiEpaisseur);
         glTexCoord2d(0,1);
         glVertex3d( -DemiLongueur,  DemiHauteur, -DemiEpaisseur);
      glEnd();
   glEndList();
   return code;
}

