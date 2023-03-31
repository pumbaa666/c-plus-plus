// Fichier Textures.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <stdio.h>
#include "define.h"
#include "global.h"
#include "lumiere.h"
#include "evenements.h"

GLuint Texture2, Texture1;

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f ); // Ce sont les valeurs par défaut.
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_POLYGON_SMOOTH);
}

void Make_CallListes()
{
  GLfloat Blanc[]  = {1.0f, 1.0f, 1.0f, 1.0f};
	cube = glGenLists(1);
	glNewList(cube, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, Texture2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Blanc);
	glBegin(GL_QUADS);		
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0, 1.0); glVertex3d(-1, 1, 1);
		glTexCoord2f(1.0, 1.0); glVertex3d(-1, -1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3d( 1, -1, 1);
		glTexCoord2f(0.0, 0.0); glVertex3d( 1, 1, 1);
		glNormal3d(0.0,0.0,-1.0);
		glTexCoord2f(1.0, 0.0); glVertex3d( 1, 1, -1);
		glTexCoord2f(1.0, 1.0); glVertex3d( 1, -1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3d( -1, -1, -1);
		glTexCoord2f(0.0, 0.0); glVertex3d( -1, 1, -1);
		glNormal3d(1.0,0.0,0.0);
		glTexCoord2f(1.0, 1.0); glVertex3d( 1, 1, 1);
		glTexCoord2f(0.0, 1.0); glVertex3d( 1, -1, 1);
		glTexCoord2f(0.0, 0.0); glVertex3d( 1, -1, -1);
		glTexCoord2f(1.0, 0.0); glVertex3d( 1, 1, -1);
		glNormal3d(-1.0,0.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -1, 1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3d( -1, 1, -1);
		glTexCoord2f(1.0, 1.0); glVertex3d( -1, -1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3d( -1, -1, 1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Texture1);
	glBegin(GL_QUADS);		
		glNormal3d(0.0,-1.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -1, -1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3d( -1, -1, -1);
		glTexCoord2f(1.0, 1.0); glVertex3d( 1, -1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3d( 1, -1, 1);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -1, 1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3d( 1, 1, 1);
		glTexCoord2f(1.0, 1.0); glVertex3d( 1, 1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3d( -1, 1, -1);
	glEnd();
	glEndList();
}

void ChargerTextures()
{
	char buffer[32*32*3];
	FILE *f = fopen("Marbre.raw", "rb");
	if (f)
	{
		fread(buffer, 3072, 1, f);
		fclose(f);
		glGenTextures(1, &Texture1);
		glBindTexture(GL_TEXTURE_2D, Texture1);
		glTexImage2D(	GL_TEXTURE_2D,0,3, 32, 32, 0,
								GL_RGB, GL_UNSIGNED_BYTE, buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glEnable(GL_TEXTURE_2D);
	}
  else
    printf("Problème au chargement de la texture\n");
	f = fopen("Marbre2.raw", "rb");
	if (f)
	{
		fread(buffer, 3072, 1, f);
		fclose(f);
		glGenTextures(1, &Texture2);
		glBindTexture(GL_TEXTURE_2D, Texture2);
		glTexImage2D(	GL_TEXTURE_2D,0,3, 32, 32, 0,
								GL_RGB, GL_UNSIGNED_BYTE, buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }
  else
    printf("Problème au chargement de la texture\n");
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

