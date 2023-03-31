// Fichier Textures.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <stdio.h>
#include "define.h"
#include "global.h"
#include "lumiere.h"
#include "evenements.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); // Ce sont les valeurs par défaut.
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_POLYGON_SMOOTH);
   SetLight();
}

void Make_CallListes()
{
   GLfloat	Blanc[]  = {1.0f, 1.0f, 1.0f, 1.0f};

   cube = glGenLists(1);
   glNewList(cube, GL_COMPILE);
      glBegin(GL_QUADS);
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Blanc);
         glNormal3d(0.0,0.0,1.0);
            //on spécifie la position des épingles (on tourne : une seule coordonnée change à la fois)
         glTexCoord2d(0,1);glVertex3d(-1,  1, 1);
         glTexCoord2d(0,0);glVertex3d(-1, -1, 1);
         glTexCoord2d(1,0);glVertex3d( 1, -1, 1);
         glTexCoord2d(1,1);glVertex3d( 1,  1, 1);
         glNormal3d(-1.0,0.0,0.0);
            //idem
         glTexCoord2d(1,1);glVertex3d( -1,  1,  1);
         glTexCoord2d(1,0);glVertex3d( -1,  1, -1);
         glTexCoord2d(0,0);glVertex3d( -1, -1, -1);
         glTexCoord2d(0,1);glVertex3d( -1, -1,  1);
            //idem
         glNormal3d(1.0,0.0,0.0);
         glTexCoord2d(1,1);glVertex3d( 1,  1,  1);
         glTexCoord2d(0,1);glVertex3d( 1, -1,  1);
         glTexCoord2d(0,0);glVertex3d( 1, -1, -1);
         glTexCoord2d(1,0);glVertex3d( 1,  1, -1);
         glNormal3d(0.0,1.0,0.0);
            //idem
         glTexCoord2d(0,1);glVertex3d( -1, 1,  1);
         glTexCoord2d(1,1);glVertex3d(  1, 1,  1);
         glTexCoord2d(1,0);glVertex3d(  1, 1, -1);
         glTexCoord2d(0,0);glVertex3d( -1, 1, -1);
         glNormal3d(0.0,-1.0,0.0);
            //idem
         glTexCoord2d(0,1);glVertex3d( -1, -1,  1);
         glTexCoord2d(0,0);glVertex3d( -1, -1, -1);
         glTexCoord2d(1,0);glVertex3d(  1, -1, -1);
         glTexCoord2d(1,1);glVertex3d(  1, -1,  1);
         glNormal3d(0.0,0.0,-1.0);
            //idem
         glTexCoord2d(1,1);glVertex3d(  1,  1, -1);
         glTexCoord2d(1,0);glVertex3d(  1, -1, -1);
         glTexCoord2d(0,0);glVertex3d( -1, -1, -1);
         glTexCoord2d(0,1);glVertex3d( -1,  1, -1);
      glEnd();
   glEndList();
}

void ChargerTextures()
{
   //Taille = 128 * 128. RGB 3 octets
   char buffer[128*128*3];
   FILE *f = fopen("herbe.raw", "rb");
   if (f)
   {
      fread(buffer, 128*128*3, 1, f);
      fclose(f);
      printf("texture chargée");
      //On spécifie qu'elle texture, sa taille, son type ...
      glTexImage2D(GL_TEXTURE_2D,0,3, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
      //cela définit la façon dont la texture est appliquée. LINEAR est le meilleur, mais le + lent.
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //On répète la texture si s et t sortent des bornes [0,1]
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //ouf, ca y est !!!
      glEnable(GL_TEXTURE_2D);
   }
   else
      printf("Il y a un problème de fichier!!!!\n");
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur,hauteur);
  glutCreateWindow("Textures");

  SetupRC();
  ChargerTextures();
  Make_CallListes();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}

