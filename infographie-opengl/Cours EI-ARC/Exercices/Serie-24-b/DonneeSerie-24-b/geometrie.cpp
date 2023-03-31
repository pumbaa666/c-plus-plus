// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "matriceombre.h"
#include "normal.h"
#include "geometrie.h"
#include <math.h>
// Permet de calculer cos et sin avec des angles en degrés.
#define COS(X) cos( (X) * M_PI/180.0)
#define SIN(X) sin( (X) * M_PI/180.0)

float normal[3];
float v[3][3];

void drawFloor()
{
  glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
  glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
//      glTranslatef(0.0f, -0.02f, 0.0f);
      glBegin(GL_QUADS);
//      glNormal3f(0.0,1.0,0.0);
        glVertex3fv(vfloor[0]);
        glVertex3fv(vfloor[1]);
        glVertex3fv(vfloor[2]);
        glVertex3fv(vfloor[3]);
      glEnd();
    glPopMatrix();
  glPopAttrib();
}

void DessinerLaScene()
{
//  glPushMatrix();
//    glRotatef(RotationLumiere, 0.0f, 1.0f, 0.0f); // Rotation de la lampe
//    PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
//  glPopMatrix();

  // Le vecteur lightPos doit être remis à jour pour le calcul
  // de la matrice de projection dans shadowMatrix.
  lightPos[0] = DistanceLumiere * COS(RotationLumiere);
  lightPos[2] = -DistanceLumiere * SIN(RotationLumiere);
  // La sphère jaune doit être dessiner en même temps que l'objet,
  // avec le Stencil On (écrire 2), sinon on voit l'ombre à travers la sphère.
//  PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3], true);

  ModeDeDessin(Mode);

  // Limitation de l'ombre à la surface
  if(Stencil)
  {
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
    drawFloor();               // Dessin de la surface dans le Stencil Buffer
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
  }

  glPushMatrix();
//    glTranslatef(0.0f, -0.2f, 0.0f);
    drawFloor();       // Dessiner la surface

    glDisable(GL_DEPTH_TEST); // En dessinant le sol ici, on a le meilleur
      DessinerLeSol();        // résultat concernant le Depth !!!
      DessinerLesAxes();
    glEnable(GL_DEPTH_TEST);
	glPopMatrix();

  // Dessin de l'objet
  if(Stencil)
  {
    // Le Stencil Buffer contiendra la valeur 2 à l'emplacement
    // des points de l'objet (le cube).
    // Si ce code est absent, et que le Depth est Off pour dessiner l'ombre,
    // L'ombre est visible à travers le cube.
    // Mais si le Depth est On pour dessiner l'ombre, ce code n'est plus
    // nécessaire, mais, alors, on a des problème avec le sol.
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 2, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  }

  // Ici on dessine la lampe si le Depth est Off pour dessiner l'ombre.
  PositionLumiere(lightPos[0], lightPos[1], lightPos[2], lightPos[3], true);

	glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 2.5f);
    DessinerLesMurs();        // Dessin de l'objet
    DessinerLeToit();
	glPopMatrix();

    // Calcul de la matrice de projection
    // (avec vfloor2 des points de la surface)
    static GLfloat floorPlane[4];
    static GLfloat floorShadow[4][4];
//    findPlane(floorPlane, vfloor2[1], vfloor2[2], vfloor2[3]);
    findPlane(floorPlane, vfloor[1], vfloor[2], vfloor[3]);
//  Pourrait être remplacé par :
/*
    floorPlane[0] = 0;
    floorPlane[1] = 1;
    floorPlane[2] = 0;
    floorPlane[3] = 0;
*/
    shadowMatrix(floorShadow, floorPlane, lightPos);

    //Changement des paramètres pour dessiner une surface noire transparente
  if(Stencil)
  {
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xffffffff); // draw if ==1
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR); // Incrémentation du Stencil
                                            // pour éviter d'assombrir 2 fois !
  }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    
    // Attention :
    // Si le Depth est actif pour dessiner l'ombre, il y a un problème
    // du fait que l'ombre est exactement sur le sol. donc le Depth test
    // ne fonctionne pas très bien.
    // Dans ce cas, il faut dessiner le sol légèrement plus bas, ou bien
    // projeter l'ombre légèrement plus haut.
    //
    // Par contre, si on désactive le Depth pour dessiner l'ombre, on voit
    // l'ombre sous le sol, et on voit l'ombre à travers la lampe.
    // Pour éviter cela, on peut dessiner la lampe juste avant de dessiner
    // l'objet (c'est-à-dire avec le Stencil On, et on écrit la valeur 2)
    // Voir remarque sous Dessin de l'objet.
    glDisable(GL_DEPTH_TEST);

    glColor4f(0.0, 0.0, 0.0, 0.5);   // Valeur Alpha pour la transparence.

    // Dessin de l'ombre
    glPushMatrix();
		  glDisable(GL_CULL_FACE); // On désactive le culling pour l'ombre.
      glMultMatrixf((GLfloat *) floorShadow);

      glTranslatef(-5.0f, 0.0f, 2.5f);
      DessinerLesMurs();        // Dessin de l'objet
      DessinerLeToit();

      if(Mode & bCull) // Réactiver le culling si nécessaire.
        glEnable(GL_CULL_FACE);
    glPopMatrix();

    // Pour terminer
    glEnable(GL_DEPTH_TEST);
    glPopAttrib();  // Pour la lumière
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);

/*
  glPushMatrix();
//    glDepthFunc(GL_LEQUAL);
    glTranslatef(0.0f, 0.02f, 0.0f); // Monter légèrement le sol à cause
    DessinerLeSol();                // du Depth
//    glDepthFunc(GL_LESS);
  glPopMatrix();
*/
//  DessinerLesAxes();

  // On dessine encore la surface en-dessous de la scène pour lui donner
  // une petit épaisseur. De cette manière, on ne voit plus l'ombre
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

  if(visible)
  {
    // Afficher la lampe
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    // Sauvegarde de la matrice de transformation
    glPushMatrix();
          glColor3f(1.0f, 1.0f, 0.0f); // Couleur jaune pour la lampe
          glTranslatef(x, y, z);
          glutSolidSphere(.5, 50, 50);
    glPopMatrix();
    glPopAttrib();
  }
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

