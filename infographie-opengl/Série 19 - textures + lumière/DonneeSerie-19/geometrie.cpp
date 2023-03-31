// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "normal.h"
#include "geometrie.h"
#include "Texture2.h"
#include "Bitmap2.h"

void DessinerLaScene()
{
    ModeDeDessin(Mode);

    // Positionner la lumière :
    glPushMatrix();
    glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f); // Rotation de la lampe
    PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
    glPopMatrix();

    /* si on veut agrandire le cube : */
    glScalef(2,2,2);
    /* mais ne pas oublier */
    glEnable(GL_NORMALIZE); // pour que les normales restes juste. Sinon la lumières sera fausse (dans ce cas : attenuée)

    DessinerCube();

    /* Ne pas oublier non plus de desactiver */
    glDisable(GL_NORMALIZE);

    DessinerLesAxes();
    DessinerLeSol();
}

void DessinerCube()
{
    static GLfloat ambiant[]={0.2, 0.2, 0.2, 1.0};	// un peu Blanc. Pour qu'on voit qqch meme si on est derrière la face éclairée
    static GLfloat diffuse[]={0.7, 0.7, 0.7, 1.0};	// Blanc
    static GLfloat speculaire[]={1.0, 1.0, 1.0, 1.0};	// Blanc // static, pour ne pas recréer la variable à chaque fois

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, speculaire);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textures[0]); // Ne peut pas se trouver entre glBegin et glEnd. --> Impossible de faire un quad_strip pour les 4 bords du tour, par exemple...
    glNormal3f(0, 0, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-3, 0, 3);
        glTexCoord2f(0, 1); glVertex3f(-3, 6, 3);
        glTexCoord2f(1, 1); glVertex3f(3, 6, 3);
        glTexCoord2f(1, 0); glVertex3f(3, 0, 3);
    glEnd();

    glNormal3f(1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(3, 0, 3);
        glTexCoord2f(0, 1); glVertex3f(3, 6, 3);
        glTexCoord2f(1, 1); glVertex3f(3, 6, -3);
        glTexCoord2f(1, 0); glVertex3f(3, 0, -3);
    glEnd();

    glNormal3f(0, 0, -1);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(3, 0, -3);
        glTexCoord2f(0, 1); glVertex3f(3, 6, -3);
        glTexCoord2f(1, 1); glVertex3f(-3, 6, -3);
        glTexCoord2f(1, 0); glVertex3f(-3, 0, -3);
    glEnd();

    glNormal3f(-1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-3, 0, -3);
        glTexCoord2f(0, 1); glVertex3f(-3, 6, -3);
        glTexCoord2f(1, 1); glVertex3f(-3, 6, 3);
        glTexCoord2f(1, 0); glVertex3f(-3, 0, 3);
    glEnd();

    glNormal3f(0, -1, 0);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-3, 0, 3);
        glTexCoord2f(0, 1); glVertex3f(3, 0, 3);
        glTexCoord2f(1, 1); glVertex3f(3, 0, -3);
        glTexCoord2f(1, 0); glVertex3f(-3, 0, -3);
    glEnd();

    glNormal3f(0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(3, 6, 3);
        glTexCoord2f(0, 1); glVertex3f(3, 6, -3);
        glTexCoord2f(1, 1); glVertex3f(-3, 6, -3);
        glTexCoord2f(1, 0); glVertex3f(-3, 6, 3);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void PositionLumiere(float x, float y, float z, float w)
{
  GLfloat LightPos[4] = {x,y,z,w};  // w = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  // Afficher la lampe
  // Sauvegarde de la matrice de transformation
  glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING); // Désactive l'éclairage
        glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
        glTranslatef(x, y, z);
        glutSolidSphere(.5, 50, 50);
    glPopAttrib();
  glPopMatrix();
}

void DessinerLesAxes()
{
  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
  glBegin(GL_LINES);
    // Axe X
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.05f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.05f, 0.0f);

    // Axe Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.05f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.8f, 0.0f);

    // Axe Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.0f, 0.8f);
  glEnd();
  glPopAttrib();
}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING);
//   glColor3f(1.0f, 1.0f, 1.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	for(r = -100; r  <= 100; r += nStep)
		{
		glVertex3f((float)r, 0.0f, -100.0f);
		glVertex3f((float)r, 0.0f, 100.0f);
		}

	for(c = -100; c <= 100; c += nStep)
		{
		glVertex3f(100.0f, 0.0f, (float)c);
		glVertex3f(-100.0f, 0.0f, (float)c);
		}

	glEnd();
  glPopAttrib();
}

void ModeDeDessin(int mask)
{
	// Turn culling on if flag is set
	if(mask & bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Enable depth testing if flag is set
	if(mask & bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// Draw back side as a polygon only, if flag is set
	if(mask & bOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);

   if(mask & bShadeModel)
      glShadeModel(GL_SMOOTH);  // Interpolation de la couleur
                                // entre les différents sommets
   else
      glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur
                                // du dernier sommet (qui est aussi le premier)
}

