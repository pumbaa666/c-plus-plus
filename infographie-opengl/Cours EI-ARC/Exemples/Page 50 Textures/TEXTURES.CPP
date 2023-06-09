// Fichier Textures.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <stdio.h>
#include "define.h"
#include "global.h"
#include "lumiere.h"
#include "evenements.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); // Ce sont les valeurs par d�faut.
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
            //on sp�cifie la position des �pingles (on tourne : une seule coordonn�e change � la fois)
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
      printf("texture charg�e");
      //On sp�cifie qu'elle texture, sa taille, son type ...
      glTexImage2D(GL_TEXTURE_2D,0,3, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
      //cela d�finit la fa�on dont la texture est appliqu�e. LINEAR est le meilleur, mais le + lent.
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //On r�p�te la texture si s et t sortent des bornes [0,1]
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //ouf, ca y est !!!
      glEnable(GL_TEXTURE_2D);
   }
   else
      printf("Il y a un probl�me de fichier!!!!\n");
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
  glutReshapeFunc(Reshape);//fonction g�rant le redimensionnement de la fen�tre
  glutDisplayFunc(Display);
  glutMainLoop();				//boucle principale
  return 0;
}

