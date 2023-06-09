// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "matriceombre.h"
#include "normal.h"
#include "geometrie.h"
#include "mur.h"
#include <math.h>
// Permet de calculer cos et sin avec des angles en degr�s.
#define COS(X) cos( (X) * M_PI/180.0)
#define SIN(X) sin( (X) * M_PI/180.0)

float normal[3];
float v[3][3];

void drawFloor()
{
  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING); // D�sactive l'�clairage
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPushMatrix();
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
//      glNormal3f(0.0,1.0,0.0);
      glVertex3fv(vfloor[0]);
      glVertex3fv(vfloor[1]);
      glVertex3fv(vfloor[2]);
      glVertex3fv(vfloor[3]);
    glEnd();
    glPopMatrix();
    glFrontFace(GL_CCW);
  glPopAttrib();
}

void DessinerLaScene()
{
    // Le vecteur lightPos doit �tre remis � jour pour le calcul
    // de la matrice de projection dans shadowMatrix.
    lightPos[0] = DistanceLumiere * COS(RotationLumiere);
    lightPos[2] = -DistanceLumiere * SIN(RotationLumiere);

// La sph�re jaune doit �tre dessiner en m�me temps que l'objet,
// avec le Stencil On (�crire 2), sinon on voit l'ombre � travers la sph�re.
  // ici on positionne la lumi�re sans la dessiner.
  PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3], false);

  ModeDeDessin(Mode);

  //***************************************************************
  // Limitation de l'ombre � la surface pour le sol
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

    // Le sol
    drawFloor();               // Dessin de la surface dans le Stencil Buffer

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

  //***************************************************************
  // Limitation de l'ombre � la surface pour le mur
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 10, 0xffffffff);

    // Le mur dans le stencil buffer
    glPushMatrix();
      glTranslatef(0.0f, 5.0f, -5.0f);
      DessinerLeMur();         // Dessin du mur dans le Stencil Buffer
    glPopMatrix();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

  // Le sol dans le frame buffer
  drawFloor();
  glDisable(GL_DEPTH_TEST); // En dessinant le sol ici, on a le meilleur
    DessinerLeSol();        // r�sultat concernant le Depth !!!
    DessinerLesAxes();
  glEnable(GL_DEPTH_TEST);

  //***************************************************************
  // Le mur dans le frame buffer
  glEnable(GL_TEXTURE_2D);
	glPushMatrix();
    glTranslatef(0.0f, 5.0f, -5.0f);
    DessinerLeMur();
	glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  // Dessin de l'objet
    // Le Stencil Buffer contiendra la valeur 2 � l'emplacement
    // des points de l'objet (la maison).
    // Si ce code est absent, et que le Depth est Off pour dessiner l'ombre,
    // L'ombre est visible � travers le cube.
    // Mais si le Depth est On pour dessiner l'ombre, ce code n'est plus
    // n�cessaire.
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 2, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  // Ici on dessine la lampe si le Depth est Off pour dessiner l'ombre.
  PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);

  // La maison
	glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 5.0f);
    DessinerLesMurs();
    DessinerLeToit();
	glPopMatrix();

    // Calcul de la matrice de projection pour le sol
    static GLfloat floorPlane[4];
    static GLfloat floorShadow[4][4];

    floorPlane[0] = 0;
    floorPlane[1] = 1;
    floorPlane[2] = 0;
    floorPlane[3] = 0;
    shadowMatrix(floorShadow, floorPlane, lightPos);

    // Changement des param�tres pour dessiner une surface noire transparente
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xffffffff); // draw if ==1
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR); // Incr�mentation du Stencil
                                            // pour �viter d'assombrir 2 fois !
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushAttrib(GL_LIGHTING_BIT);
      glDisable(GL_LIGHTING); // D�sactive l'�clairage

      // Attention :
      // Si le Depth est actif pour dessiner l'ombre, il y a un probl�me
      // du fait que l'ombre est exactement sur le sol. donc le Depth test
      // ne fonctionne pas tr�s bien.
      // Dans ce cas, il faut dessiner le sol l�g�rement plus bas, ou bien
      // projeter l'ombre l�g�rement plus haut.
      //
      // Par contre, si on d�sactive le Depth pour dessiner l'ombre, on voit
      // l'ombre sous le sol, et on voit l'ombre � travers la lampe.
      // Pour �viter cela, on peut dessiner la lampe juste avant de dessiner
      // l'objet (c'est-�-dire avec le Stencil On, et on �crit la valeur 2)
      // Voir remarque sous Dessin de l'objet.
      glDisable(GL_DEPTH_TEST);

      glColor4f(0.0, 0.0, 0.0, 0.5);   // Valeur Alpha pour la transparence.

      // Dessin de l'ombre sur le sol
      glPushMatrix();
        glDisable(GL_CULL_FACE); // On d�sactive le culling pour l'ombre.
        glMultMatrixf((GLfloat *) floorShadow);

        // L'ombre de la maison sur le sol
        glPushMatrix();
          glTranslatef(-5.0f, 0.0f, 5.0f);
          DessinerLesMurs();
          DessinerLeToit();
        glPopMatrix();

        if(Mode & bCull) // R�activer le culling si n�cessaire.
          glEnable(GL_CULL_FACE);
      glPopMatrix();

      // Calcul de la matrice de projection pour le mur
      // Rappel :
      // Le mur est parall�le au plan XY.
      // Il est translat� de -5 unit�s dans la direction Z et de 5 unit�s
      // dans la direction Y.
      // Comme son �paisseur est de 1 unit�, les coordonn�es du point
      // qui se trouve sur le mur, dans le plan XZ sont : (0, 0, -4.5)
      // On obtient donc les valeur A, B, C, D de l'�quation du plan :
      // Ax + By + Cz + D = 0
      //
      // A = 0
      // B = 0
      // C = 1
      // D = 4.5
      //
      // Rappel : (A, B, C) sont les composantes de la normale au mur.
      floorPlane[0] = 0;
      floorPlane[1] = 0;
      floorPlane[2] = 1;
      floorPlane[3] = 4.5;
      shadowMatrix(floorShadow, floorPlane, lightPos);

      //Changement des param�tres pour dessiner sur le mur
      glEnable(GL_STENCIL_TEST);
      glStencilFunc(GL_EQUAL, 10, 0xffffffff); // draw if ==10
      glStencilOp(GL_KEEP, GL_KEEP, GL_INCR); // Incr�mentation du Stencil
                                              // pour �viter d'assombrir 2 fois !
      // Dessin de l'ombre de la maison sur le mur
      glPushMatrix();
        glDisable(GL_CULL_FACE); // On d�sactive le culling pour l'ombre.
        glMultMatrixf((GLfloat *) floorShadow);

        // L'ombre de la maison sur le mur
        glPushMatrix();
          glTranslatef(-5.0f, 0.0f, 5.0f);
          DessinerLesMurs();
          DessinerLeToit();
        glPopMatrix();

        if(Mode & bCull) // R�activer le culling si n�cessaire.
          glEnable(GL_CULL_FACE);
      glPopMatrix();
    glPopAttrib();

    // Pour terminer
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);

/*
  glPushMatrix();
    glTranslatef(0.0f, 0.02f, 0.0f); // Monter l�g�rement le sol � cause
    DessinerLeSol();                 // du Depth
  glPopMatrix();
  DessinerLesAxes();
*/

  // On dessine encore la surface en-dessous de la sc�ne pour lui donner
  // une petit �paisseur. De cette mani�re, on ne voit plus l'ombre
  // sous la surface.
  glFrontFace(GL_CW);
  glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.0f);
    drawFloor();       // Dessiner la surface
  glPopMatrix();
  glFrontFace(GL_CCW);
}

void PositionLumiere(float x, float y, float z, float w, bool visible)
{
  GLfloat LightPos[4] = {x,y,z,w};  // w = 1 --> Position = (x,y,z)
  glLightfv(GL_LIGHT0,GL_POSITION,LightPos);

  // Afficher la lampe
  if(visible)
  {
    // Sauvegarde de la matrice de transformation
    glPushAttrib(GL_LIGHTING_BIT);
      glDisable(GL_LIGHTING); // D�sactive l'�clairage
      glPushMatrix();
            glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
            glTranslatef(x, y, z);
            glutSolidSphere(.5, 50, 50);
      glPopMatrix();
      glEnable(GL_LIGHTING); // Active l'�clairage
    glPopAttrib();
  }
}

void DessinerLesAxes()
{
  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING); // D�sactive l'�clairage
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

void DessinerLesMurs()
{
   static GLfloat alpha = 0.5f;
   GLfloat  ambientMaterial[] =  { 0.4f, 0.4f, 0.4f, alpha };
   GLfloat  diffuseMaterial[] =  { 0.5f, 0.5f, 0.5f, alpha };
   GLfloat  specularMaterial[] =  { 0.0f, 0.0f, 0.0f, alpha };
   GLint shininess = 0;
   GLfloat  ambientMaterialB[] =  { 0.0f, 0.5f, 0.0f, alpha };
   GLfloat  diffuseMaterialB[] =  { 0.0f, 0.0f, 0.0f, alpha };
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
  glFrontFace(GL_CCW);
}

void DessinerLeToit()
{
   static GLfloat alpha = 0.5f;
   GLfloat  ambientMaterial[] =  { 0.5f, 0.0f, 0.0f, alpha };
   GLfloat  diffuseMaterial[] =  { 1.0f, 0.0f, 0.0f, alpha };
   GLfloat  specularMaterial[] =  { 1.0f, 0.0f, 0.0f, alpha };
   GLint shininess = 100;
   GLfloat  ambientMaterialB[] =  { 0.5f, 0.0f, 0.0f, alpha };
   GLfloat  diffuseMaterialB[] =  { 0.0f, 0.0f, 0.0f, alpha };

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
  glFrontFace(GL_CCW);
}

void DessinerLeSol()
{
	int r,c;
	int nStep = 3;

  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING); // D�sactive l'�clairage
//    glColor3f(1.0f, 1.0f, 1.0f);
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
                                // entre les diff�rents sommets
   else
      glShadeModel(GL_FLAT);    // La couleur du polygone est la couleur
                                // du dernier sommet (qui est aussi le premier)
}

