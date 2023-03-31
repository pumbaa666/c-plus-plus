// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <sys\timeb.h>
#include <math.h>
#include "global.h"
#include "lumieres.h"
#include "dessin.h"
#include "evenements.h"

void Display (void)
{
   GLfloat  ambientMaterial[] =  { 0.0f, 0.9f, 0.0f, 1.0f };
   GLfloat  diffuseMaterial[] =  { 0.0f, 0.6f, 0.0f, 1.0f };
   GLfloat  specularMaterial[] =  { 0.0f, 0.5f, 0.0f, 1.0f };
   GLint shininess = 10;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
//   SetLight();
    glPushMatrix();
        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
/*
  glColor3f(1.0f, 1.0f, 1.0f);
  DessinerLesAxes();
*/
		    glTranslatef(0.0f, 0.0f, 9.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

        static GLfloat ctrlpoints[4][4][3] = {
            {{-1.5, -1.5,  4.0}, {-0.5, -1.5,  2.0},
             { 0.5, -1.5, -1.0}, { 1.5, -1.5,  2.0}},
            {{-1.5, -0.5,  1.0}, {-0.5, -0.5,  3.0}, 
             { 0.5, -0.5,  0.0}, { 1.5, -0.5, -1.0}},
            {{-1.5,  0.5,  4.0}, {-0.5,  0.5,  0.0}, 
             { 0.5,  0.5,  3.0}, { 1.5,  0.5,  4.0}},
            {{-1.5,  1.5, -2.0}, {-0.5,  1.5, -2.0},
             { 0.5,  1.5,  0.0}, { 1.5,  1.5, -1.0}}
        };
        glEnable(GL_LINE_SMOOTH);
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,&ctrlpoints[0][0][0]);
        glEnable(GL_MAP2_VERTEX_3);
		static GLfloat tt= 0;
		if ((tt += 0.05f) > 360) tt -= 360.0f;
		glTranslatef(0.0f, 0.0f, -10.0f);
        glRotatef(tt, 0.7f, 0.0f, 1.0f);
        glColor3f(1.0, 1.0, 1.0);
		glMapGrid2f(9, 0.0, 1.0, 9, 0.0, 1.0);
        glEvalMesh2(/*GL_POINT*/ /*GL_FILL*/ GL_LINE, 0, 9, 0, 9);
        glDisable(GL_MAP2_VERTEX_3);
		glPopMatrix();
	glutSwapBuffers();
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
/*
    case 's' :
    case 'S' : Stencil = !Stencil;
               if(Stencil)
                 glutSetWindowTitle("Avec Stencil Buffer");
               else
                 glutSetWindowTitle("Sans Stencil Buffer");
               break;
*/
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
  glutPostRedisplay();
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
            0.0f,
            zPos,   // Position de la caméra
            xPos + fRadius*cos(Theta*M_PI/180.0),
            0.0f,
            zPos - fRadius*sin(Theta*M_PI/180.0),
            0.0f, 1.0f, 0.0f);  // Axe dirigé vers le haut
}

