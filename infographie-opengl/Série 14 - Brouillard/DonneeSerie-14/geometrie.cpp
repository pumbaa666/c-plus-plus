// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "normal.h"
#include "geometrie.h"

float normal[3];
float v[3][3];

void DessinerLaScene()
{
  ModeDeDessin(Mode);

  // Positionner la lumière :
  glPushMatrix();
    glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f); // Rotation de la lampe
    PositionLumiere(lightPos[0], lightPos[1], lightPos[2]);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 2.5f);
    DessinerLesMurs();
    DessinerLeToit();
  glPopMatrix();

  DessinerLeSol();
}

void PositionLumiere(float x, float y, float z)
{
  GLfloat LightPos[4] = {x,y,z,1.0};  // ww = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  // Afficher la lampe
  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
  // Sauvegarde de la matrice de transformation
  glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
        glTranslatef(x, y, z);
        glutSolidSphere(.5, 50, 50);
  glPopMatrix();
  glPopAttrib();
}

void DessinerLesAxes()
{
  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
  glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.05f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.05f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.05f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.8f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.0f, 0.8f);
  glEnd();
  glPopAttrib();
}

void DessinerLesMurs()
{
   GLfloat  ambientMaterial[] =  { 0.4f, 0.4f, 0.4f, 1.0f };
   GLfloat  diffuseMaterial[] =  { 0.5f, 0.5f, 0.5f, 1.0f };
   GLfloat  specularMaterial[] =  { 0.0f, 0.0f, 0.0f, 1.0f };
//   GLint shininess = 0;
   GLfloat  ambientMaterialB[] =  { 0.0f, 0.5f, 0.0f, 1.0f };
   GLfloat  diffuseMaterialB[] =  { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
//	glMateriali(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_BACK, GL_AMBIENT, ambientMaterialB);
	glMaterialfv(GL_BACK, GL_DIFFUSE, diffuseMaterialB);

   glFrontFace(GL_CW);
	glBegin(GL_QUAD_STRIP);

     // 1
     v[0][0] = 0.0;
     v[0][1] = 4.0;
     v[0][2] = 0.0;
     // 2
     v[1][0] = 10.0;
     v[1][1] = 0.0;
     v[1][2] = 0.0;
     // 3
     v[2][0] = 10.0;
     v[2][1] = 4.0;
     v[2][2] = 0.0;
     calcNormal(v, normal);
     glNormal3fv(normal);
     glVertex3f(0.0f, 0.0f, 0.0f);  // 0
     glVertex3fv(v[0]);   // 1
     glVertex3fv(v[1]);   // 2
     glVertex3fv(v[2]);  // 3

     // 3
     v[0][0] = 10.0;
     v[0][1] = 4.0;
     v[0][2] = 0.0;
     // 4
     v[1][0] = 10.0;
     v[1][1] = 0.0;
     v[1][2] = -5.0;
     // 5
     v[2][0] = 10.0;
     v[2][1] = 4.0;
     v[2][2] = -5.0;
     calcNormal(v, normal);
     glNormal3fv(normal);
     glVertex3fv(v[1]);   // 4
     glVertex3fv(v[2]);  // 5

     // 5
     v[0][0] = 10.0;
     v[0][1] = 4.0;
     v[0][2] = -5.0;
     // 6
     v[1][0] = 0.0;
     v[1][1] = 0.0;
     v[1][2] = -5.0;
     // 7
     v[2][0] = 0.0;
     v[2][1] = 4.0;
     v[2][2] = -5.0;
     calcNormal(v, normal);
     glNormal3fv(normal);
     glVertex3fv(v[1]);   // 6
     glVertex3fv(v[2]);  // 7

     // 7
     v[0][0] = 0.0;
     v[0][1] = 4.0;
     v[0][2] = -5.0;
     // 8
     v[1][0] = 0.0;
     v[1][1] = 0.0;
     v[1][2] = 0.0;
     // 9
     v[2][0] = 0.0;
     v[2][1] = 4.0;
     v[2][2] = 0.0;
     calcNormal(v, normal);
     glNormal3fv(normal);
     glVertex3fv(v[1]);   // 8
     glVertex3fv(v[2]);  // 9

	glEnd();
}

void DessinerLeToit()
{
   GLfloat  ambientMaterial[] =  { 0.5f, 0.0f, 0.0f, 1.0f };
   GLfloat  diffuseMaterial[] =  { 1.0f, 0.0f, 0.0f, 1.0f };
   GLfloat  specularMaterial[] =  { 1.0f, 0.0f, 0.0f, 1.0f };
   GLint shininess = 100;
   GLfloat  ambientMaterialB[] =  { 0.5f, 0.0f, 0.0f, 1.0f };
   GLfloat  diffuseMaterialB[] =  { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);

	glMaterialfv(GL_BACK, GL_AMBIENT, ambientMaterialB);
	glMaterialfv(GL_BACK, GL_DIFFUSE, diffuseMaterialB);

   glFrontFace(GL_CW);
	 glBegin(GL_QUAD_STRIP);

     // 1
     v[0][0] = -0.5;
     v[0][1] = 4.0;
     v[0][2] = 0.5;
     // 2
     v[1][0] = 10.5;
     v[1][1] = 6.0;
     v[1][2] = -2.5;
     // 3
     v[2][0] = -0.5;
     v[2][1] = 6.0;
     v[2][2] = -2.5;
     calcNormal(v, normal);
     glNormal3fv(normal);
     glVertex3f(10.5f, 4.0f, 0.5f);   // 0
     glVertex3fv(v[0]);   // 1
     glVertex3fv(v[1]);   // 2
     glVertex3fv(v[2]);  // 3

     // 3
     v[0][0] = -0.5;
     v[0][1] = 6.0;
     v[0][2] = -2.5;
     // 4
     v[1][0] = 10.5;
     v[1][1] = 4.0;
     v[1][2] = -5.5;
     // 5
     v[2][0] = -0.5;
     v[2][1] = 4.0;
     v[2][2] = -5.5;
     calcNormal(v, normal);
     glNormal3fv(normal);
     glVertex3fv(v[1]);   // 4
     glVertex3fv(v[2]);  // 5
	 glEnd();
}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

  glPushAttrib(GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
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
      glShadeModel(GL_SMOOTH);
   else
      glShadeModel(GL_FLAT);
}

