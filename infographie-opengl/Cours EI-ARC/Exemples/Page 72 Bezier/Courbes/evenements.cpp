// Fichier Evenements.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <sys\timeb.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include "global.h"
#include "lumieres.h"
#include "dessin.h"
#include "evenements.h"

int Nb = 30; // Nombre de subdivisions, 0.0 -> u1, 1.0 -> u2
GLenum mode = GL_POINT;
int NumPoint = 1;

void Display (void)
{
  static char Texte[80];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING); // Désactive l'éclairage
    glPushMatrix();
        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Effectuer les rotations
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
/*
        static GLfloat ctrlpoints[4][3] = {
            {-4.0, -4.0, 0.0}, {-2.0, 4.0, 0.0},
            { 2.0, -4.0, 0.0}, { 4.0, 4.0, 0.0}};
*/
//        glColor3f(1.0f,1.0f,1.0f);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
        glEnable(GL_MAP1_VERTEX_3);

        glPointSize(5.0);

        // On dessine tous les points
        glColor3f(0.0f,1.0f,0.0f);
        glBegin(GL_POINTS);
        for (GLfloat i = 0.0; i <= 1.001; i+=0.05f)
            glEvalCoord1f(i);
        glEnd();

        // On ne dessine que les subdivisions demandées
        glColor3f(0.0, 0.0, 1.0);
        //Nb -> Nombre de subdivisions, 0.0 -> u1, 1.0 -> u2
        glMapGrid1f(Nb, 0.0, 1.0);
        // 0 -> 1ère subd., Nb -> dernière subd.
        glEvalMesh1(mode, 0, Nb);

        glDisable(GL_MAP1_VERTEX_3);

        // On dessine les points de contrôle
        glColor3f(1.0, 0.0, 0.0);
/*
        glBegin(GL_POINTS);
        for (int j = 0; j < 4; j++)
            glVertex3fv(&ctrlpoints[j][0]);
        glEnd();
*/
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < 4; j++)
            glVertex3fv(&ctrlpoints[j][0]);
        glEnd();
    glPopMatrix();

    sprintf(Texte, "Nb de subdivisions : %d", Nb);
    glutSetWindowTitle(Texte);
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
  static int delta = 1;
  switch(tolower(key))
  {

    case 's' :
               Nb += delta;
               break;
    case '1' :
               NumPoint = 1;
               break;
    case '2' :
               NumPoint = 2;
               break;
    case 'x' :
               ctrlpoints[NumPoint][0] += delta;
               break;
    case 'y' :
               ctrlpoints[NumPoint][1] += delta;
               break;
    case '+' :
               delta = -delta;
               break;
    case 'm' :
               if(mode == GL_POINT) mode = GL_LINE;
               else mode = GL_POINT;
               break;
    case 'w' :
               if(FullScreen)
               {
                 glutPositionWindow(100, 100);
                 glutReshapeWindow(largeur, hauteur);
               }
               else
                 glutFullScreen();
               FullScreen = !FullScreen;
               break;
    case 'l' : if(positionProperties[3] == 0.0)
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

