// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <sys\timeb.h>
#include <math.h>
#include "global.h"
#include "matriceombre.h"
#include "lumieres.h"
#include "dessin.h"
#include "evenements.h"

void Display (void)
{
	static timeb tt ,t;
	static int total;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ftime(&t);
	total += (t.time - tt.time)*1000 + (t.millitm - tt.millitm);
	total %= 360*300;
	tt = t;

  glPushMatrix();  // Sauvegarder la matrice de visualisation actuelle
  glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  PositionLumiere();

  // Limitation de l'ombre à la surface
  if(Stencil)
  {
//    glDisable(GL_DEPTH_TEST);
//    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
    drawFloor();               // Dessin de la surface dans le Stencil Buffer
//    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
  }
  else
  {
    // Dessiner la surface
//    glDisable(GL_LIGHTING);
    drawFloor();
//    glEnable(GL_LIGHTING);
  }
  // Dessin de l'objet
/*
  if(Stencil)
  {
    // Le Stencil Buffer contiendra la valeur 2 à l'emplacement
    // des points de l'objet (le cube).
    // Si ce code est absent, et que le Depth est Off pour dessiner l'ombre,
    // L'ombre est visible à travers le cube.
    // Mais si le Depth est On pour dessiner l'ombre, ce code n'est plus
    // nécessaire.
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 2, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  }
*/
	glPushMatrix();
		glTranslatef(0.0f, 5.0f, 0.0f);
		glTranslatef(sin(total/30.0f/180.0f*3.1415f)*5.0f, 0.0f, 0.0f);
		glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
		glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
		glCallList(cube);                        // Dessin de l'objet
	glPopMatrix();

    // Calcul de la matrice de projection
    // (avec vfloor des points de la surface)
    static GLfloat floorPlane[4];
    static GLfloat floorShadow[4][4];
    findPlane(floorPlane, vfloor2[1], vfloor2[2], vfloor2[3]);
    shadowMatrix(floorShadow, floorPlane, positionProperties);

    //Changement des paramètres pour dessiner une surface noire transparente
  if(Stencil)
  {
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xffffffff); // draw if ==1
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
  }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_LIGHTING);
//    glDisable(GL_DEPTH_TEST);  // Garder le Depth actif, sinon, on voit
                                 // l'ombre sous le sol et à travers du cube
                                 // Voir remarque sour Dessin de l'objet.
//    glColor4f(0.0, 0.0, 0.0, 0.5);

    // Dessin de l'ombre
    glPushMatrix();
      glMultMatrixf((GLfloat *) floorShadow);
      glTranslatef(0.0f, 5.0f, 0.0f);
      glTranslatef(sin(total/30.0f/180.0f*3.1415f)*5.0f, 0.0f, 0.0f);
      glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
      glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
      glCallList(cubeOmbre);                        // Dessin de l'objet
    glPopMatrix();
  glPopMatrix();

    // Pour terminer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);

  glutSwapBuffers();
  glutPostRedisplay();
}

void Reshape (int w, int h)
{
   GLdouble RapportAspect;
   GLdouble AngleOuverture = 45.0;
   GLdouble PlanAvant = 1.0;
   GLdouble PlanArriere = 100.0;

   if (h == 0) h = 1;
   if (w == 0) w = 1;
   glViewport (0, 0, w, h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   RapportAspect = (GLdouble)w / (GLdouble)h;
   gluPerspective (AngleOuverture, RapportAspect,PlanAvant,PlanArriere);

   DeplacerLaCamera(0, Theta);
}

void Keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  static bool FullScreen = false;
  switch(key)
  {
    case 's' :
    case 'S' : Stencil = !Stencil;
               if(Stencil)
                 glutSetWindowTitle("Avec Stencil Buffer");
               else
                 glutSetWindowTitle("Sans Stencil Buffer");
               break;
    case 'w' :
    case 'W' : if(FullScreen)
               {
                 glutPositionWindow(100, 100);
                 glutReshapeWindow(largeur, hauteur);
               }
               else
                 glutFullScreen();
               FullScreen = !FullScreen;
               break;
    case 'l' :
    case 'L' : if(positionProperties[3] == 0.0)
                 positionProperties[3] = 1.0;
               else
                 positionProperties[3] = 0.0;
               break;
    case 27 :  exit(0);
               break;
  }
}

void Souris(int button, int state, int /*x*/, int /*y*/)
{
  if(button == GLUT_LEFT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      ButtonLeftDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonLeftDown = false;
    }

  if(button == GLUT_RIGHT_BUTTON)
    if(state == GLUT_DOWN)      // Le bouton gauche a été pressé
    {
      ButtonRightDown = true;
    }
    else                        // Le bouton gauche a été relâché
    {
      ButtonRightDown = false;
    }
}

void DeplacerSouris(int x, int y) // La souris s'est déplacée
{
  static int yOld = 0;
  static int xOld = 0;
  if(ButtonLeftDown) // Le bouton gauche est en bas
  {
    int DeltaAngleX;
    DeltaAngleX = yOld - y;
    if(DeltaAngleX < 0)
    {
      xRot++;
      if(xRot >= 360.0) xRot = 0.0;
    }
    else
    {
      xRot--;
      if(xRot <= -360.0) xRot = 0.0;
    }
  }

  if(ButtonRightDown) // Le bouton gauche est en bas
  {
    int DeltaAngleY;
    DeltaAngleY = xOld - x;
    if(DeltaAngleY < 0)
    {
      yRot++;
      if(yRot >= 360.0) yRot = 0.0;
    }
    else
    {
      yRot--;
      if(yRot <= -360.0) yRot = 0.0;
    }
  }
  xOld = x;
  yOld = y;
  glutPostRedisplay();
}

void ToucheSpecial(int key, int /*x*/, int /*y*/)
{
  GLfloat d = 0.0f;
  // Si on appuie sur la touche <flèche en haut>
  if(key == GLUT_KEY_UP)
    d = 1.0f;
  // Si on appuie sur la touche <flèche en bas>
  else if (key == GLUT_KEY_DOWN)
    d = -1.0f;
  else if (key == GLUT_KEY_LEFT)
    Theta += 1.0f;
  else if (key == GLUT_KEY_RIGHT)
    Theta -= 1.0f;

  DeplacerLaCamera(d, Theta);
  glutPostRedisplay();
}

void DeplacerLaCamera(GLfloat d, GLfloat Theta)
{
  // d = + 1 --> La caméra avance
  // d = - 1 --> La caméra recule
  // Sinon, d = 0 --> la caméra tourne et fait un angle Theta
  //                  avec l'axe des X
   
  static GLfloat fRadius = 50.0f;
  GLfloat xDelta, zDelta;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // Charger la matrice de visualisation identité

  xDelta = d*cos(Theta*M_PI/180.0);
  zDelta = -d*sin(Theta*M_PI/180.0);
  xPos += xDelta;
  zPos += zDelta;

  gluLookAt(xPos,
            2.0f,
            zPos,   // Position de la caméra
            xPos + fRadius*cos(Theta*M_PI/180.0),
            2.0f,
            zPos - fRadius*sin(Theta*M_PI/180.0),
            0.0f, 1.0f, 0.0f);  // Axe dirigé vers le haut
}

