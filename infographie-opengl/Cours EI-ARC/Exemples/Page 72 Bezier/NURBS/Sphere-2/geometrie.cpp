// Fichier Geometrie.cpp

#include <windows.h>
#include <GL\glut.h>
#include <conio.h>
#include "global.h"
#include "normal.h"
#include "geometrie.h"




// Called to draw the control points in Red over the NURB
void DrawPoints(void)
	{
	int i;

	// Large Red Points
	glPointSize(5.0f);
	glColor3ub(255,0,0);

	// Draw all the points in the array
	glBegin(GL_POINTS);
		for(i = 0; i < NbPoints; i++)
			glVertex4fv(ctrlPoints[i]);
	glEnd();
	}

// NURBS callback error handler
void CALLBACK NurbsErrorHandler(GLenum nErrorCode)
{
	char cMessage[64];

	// Extract a text message of the error
	strcpy(cMessage,"NURBS error occured: ");
	strcat(cMessage, (char *)gluErrorString(nErrorCode));

	// Display the message to the user
	MessageBox(NULL,cMessage,NULL,MB_OK | MB_ICONEXCLAMATION);
//  getch();
}

void DessinerLaScene()
{

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Positionner la lumière :
  glPushMatrix();
    glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f); // Rotation de la lampe
    PositionLumiere(lightPos[0], lightPos[1], lightPos[2]);
  glPopMatrix();

  ModeDeDessin(Mode);

  glPushMatrix();
//    glTranslatef(-2.0, 0.0, 0.0);
	  // Draw in Blue
	  glColor3ub(0,0,220);

   GLfloat  ambientMaterial[] =  { 0.4f, 0.4f, 0.4f, 1.0f };
   GLfloat  diffuseMaterial[] =  { 0.5f, 0.5f, 0.5f, 1.0f };
   GLfloat  specularMaterial[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
   GLint shininess = 100;
   GLfloat  ambientMaterialB[] =  { 0.0f, 0.5f, 0.0f, 1.0f };
   GLfloat  diffuseMaterialB[] =  { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
//	glMaterialfv(GL_BACK, GL_AMBIENT, ambientMaterialB);
//	glMaterialfv(GL_BACK, GL_DIFFUSE, diffuseMaterialB);

	  // Render the NURB
    glEnable(GL_AUTO_NORMAL);
	  // Begin the NURB definition
    gluBeginSurface(pNurb);
     // Evaluate the surface
     gluNurbsSurface(pNurb,
                  NbKnots, Knots, NbKnots, Knots,  // Nbr de noeuds = Nbr de pt de contrôle + Ordre
                  7*4, 4,         // Offset entre les pt de contrôle
                  &PointsSurface[0][0][0], // Pt de contrôle
                  Ordre, Ordre,         // Ordre = 1 + degré
                  GL_MAP2_VERTEX_4);

	   // Done with surface
	  gluEndSurface(pNurb);
    glDisable(GL_AUTO_NORMAL);

	  // Show the control points
  glDisable(GL_LIGHTING); // Désactive l'éclairage
	  DrawPoints();
  glEnable(GL_LIGHTING); // Active l'éclairage

	// Restore the modelview matrix
	glPopMatrix();

  glDisable(GL_LIGHTING); // Désactive l'éclairage
    DessinerLeSol();
    DessinerLesAxes();
  glEnable(GL_LIGHTING); // Active l'éclairage
}

void PositionLumiere(float x, float y, float z)
{
  GLfloat LightPos[4] = {x,y,z,1.0};  // ww = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  // Afficher la lampe
  // Sauvegarde de la matrice de transformation
  glDisable(GL_LIGHTING); // Désactive l'éclairage
  glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
        glTranslatef(x, y, z);
        glutSolidSphere(.5, 50, 50);
  glPopMatrix();
  glEnable(GL_LIGHTING); // Active l'éclairage
}

void DessinerLesAxes()
{
//  glDisable(GL_LIGHTING); // Désactive l'éclairage
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
//  glEnable(GL_LIGHTING); // Active l'éclairage
}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

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

