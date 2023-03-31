#include <GL\glut.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"


void InitialiserHauteurs(GLfloat ** &hauteur)
{
  int i, j;
  GLfloat max, min;
  if(hauteur == NULL)
  {
    hauteur= new GLfloat*[LARGEUR_TERRAIN];
    for(i = 0; i < LARGEUR_TERRAIN; i++)
    {
      hauteur[i] = new GLfloat[LARGEUR_TERRAIN];
    }
    for(i = 0; i < LARGEUR_TERRAIN; i++)
    {
      for (j= 0; j < LARGEUR_TERRAIN; j++)
      {
        hauteur[i][j] = 0.0f;
//        hauteur[i][j] = sin((float)i/5.);// * cos(j);
      }
    }

    // Calcul de la colline
    int r;
    int x1, z1;
    GLfloat h;
    GLfloat f_i, f_j, f_r, f_x1, f_z1;

//    randomize(); // Initialiser le générateur de nombre aléatoires.
    for(int k = 0; k < nbDeCollines; k++)
    {
//      srand(k);
//      r = random (rayonDesCollines);  // Valeur aléatoire entre 0 et n-1
//      x1 = random(LARGEUR_TERRAIN);
//      z1 = random(LARGEUR_TERRAIN);
      r = rand() % (rayonDesCollines);  // Valeur aléatoire entre 0 et n-1
      x1 = rand() % (LARGEUR_TERRAIN);
      z1 = rand() % (LARGEUR_TERRAIN);
      f_r = r;
      f_x1 = x1;
      f_z1 = z1;
      for(i = 0; i < LARGEUR_TERRAIN; i++)
      {
        f_i = i;
        for (j= 0; j < LARGEUR_TERRAIN; j++)
        {
          f_j = j;
          h = hauteur[i][j] + f_r*f_r -
             ((f_i-f_x1)*(f_i-f_x1) + (f_j-f_z1)*(f_j-f_z1));
          if(h >= hauteur[i][j]) hauteur[i][j] = h;
          if(hauteur[i][j] < 0.0f) hauteur[i][j] = 0.0f;
        }
      }
    }

    // Calculer le max et le min
    max = min = hauteur[0][0];
    for(i = 0; i < LARGEUR_TERRAIN; i++)
    {
      for (j= 0; j < LARGEUR_TERRAIN; j++)
      {
        if(hauteur[i][j] < min) min = hauteur[i][j];
        else
        if(hauteur[i][j] > max) max = hauteur[i][j];
      }
    }

    GLfloat altitudeDeLaMer;
    altitudeDeLaMer = altitudeMer * (max-min);
    // Normaliser le terrain entre 0 et 1
    for(i = 0; i < LARGEUR_TERRAIN; i++)
    {
      for (j= 0; j < LARGEUR_TERRAIN; j++)
      {
        hauteur[i][j] = ((hauteur[i][j] - (min+altitudeDeLaMer)) /
                         (max - (min+altitudeDeLaMer)));
        if(hauteur[i][j] < 0.0f)
          hauteur[i][j] = 0.0f;
      }
    }

  }
}

void DetruireLesHauteurs(GLfloat ** & hauteur)
{
  int i, j;
  if(hauteur != NULL)
  {
    for(i = 0; i < LARGEUR_TERRAIN; i++)
    {
      delete hauteur[i];
    }
    delete hauteur;
    hauteur = NULL;
  }
}

