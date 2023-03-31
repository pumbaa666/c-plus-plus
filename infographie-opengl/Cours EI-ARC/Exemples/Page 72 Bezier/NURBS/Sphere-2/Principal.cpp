// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "geometrie.h"
#include "principal.h"

#include <math.h>
// Permet de calculer cos et sin avec des angles en degrés.
#define COS(X) cos( (X) * M_PI/180.0)
#define SIN(X) sin( (X) * M_PI/180.0)

void MyInit()
{
  // Fond blanc
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
  // glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

  // Pour séparer le calculs des faces avant et arrière
//  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// Enable this light in particular
	glEnable(GL_LIGHT0);

// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
	// Setup the Nurbs object
    pNurb = gluNewNurbsRenderer();
    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 50.0f);
	gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
//	  gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_OUTLINE_POLYGON);
    gluNurbsCallback(pNurb, GLU_ERROR, 
               reinterpret_cast<GLvoid (CALLBACK *)()>(&NurbsErrorHandler));
    float angle;
    int i;
    int j;
    for(i = 0, angle=0.0; i< NbPoints; i++, angle += 180.0/(NbPoints-1))
    {
     for(j=0; j < NbPoints; j++)
     {
      PointsSurface[i][j][0] = ctrlPoints[j][0]*COS(angle); // x
      PointsSurface[i][j][2] = ctrlPoints[j][0]*SIN(angle); // z
      PointsSurface[i][j][1] = ctrlPoints[j][1]; // y
      PointsSurface[i][j][3] = ctrlPoints[j][3]; // w
     }
    }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Courbes NURBS");

  MyInit();
  glutKeyboardFunc(Key);
  glutSpecialFunc(ToucheSpecial);
  glutReshapeFunc(MyReshape);
  glutDisplayFunc(Display);
  glutIdleFunc( Animate );
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();
  return 0;
}
