// Fichier Mur.cpp

#include <GL\glut.h>
#include <stdio.h>
#include "texture.h"
#include "global.h"
#include "normal.h"
#include "mur.h"

GLint mur; // Variable globale pour la Call List

void DessinerLeMur()
{
  glCallList(mur);
}

void MakeMurCallList(GLfloat longueur, GLfloat hauteur, GLfloat epaisseur)
{
   // Construction d'un mur dont le centre de gravit� se trouve
   // � l'origine des axes.
   // Le mur a les dimensions : longueur x hauteur x epaisseur.

   // Le fichier "mur.bmp" contient la texture � appliquer.

   // ---> Cr�er la Call List pour le mur
}

