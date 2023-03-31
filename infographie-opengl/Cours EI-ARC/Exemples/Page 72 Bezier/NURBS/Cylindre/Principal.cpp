// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>

// Remarque concernant #include <iostream.h> et <iostream> :
//
// Utiliser l'option -Wno-deprecated
// pour éviter le warning suivant :
// #warning This file includes at least one deprecated or antiquated header.
// Please consider using one of the 32 headers found in section 17.4.1.2
// of the C++ standard. Examples include substituting the <X> header
// for the <X.h> header for C++ includes, or <iostream> instead of
// the deprecated header <iostream.h>.
// To disable this warning use -Wno-deprecated.

// Si on écrit : #include <iostream> (sans le .h), alors on doit écrire :

//    std::cout << "blabla" << std::endl;

#include <iostream.h>
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
    float Z;
    int u;
    int v;
    for(u = 0, Z=0.0; u< NbPoints; u++, Z -= 0.2 /*180.0/(NbPoints-1)*/)
    {
     for(v=0; v < NbPoints; v++)
     {
      PointsSurface[u][v][0] = ctrlPoints[v][0]; // x
/*
      if((ctrlPoints[v][0]*ctrlPoints[v][0]-Z*Z) > 0.0)
      {
        PointsSurface[u][v][0] = sqrt((ctrlPoints[v][0]*ctrlPoints[v][0])-
                                Z*Z); // x
      }
      else
      {
        PointsSurface[u][v][0] = 0.0;
      }
*/
      PointsSurface[u][v][1] = ctrlPoints[v][1]; // y
      PointsSurface[u][v][2] = ctrlPoints[v][2] + Z*ctrlPoints[v][3]; // z
      PointsSurface[u][v][3] = ctrlPoints[v][3]; // w
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
  cout << "  x, y, z     : position du point n" << endl;
  cout << "  1, 2, ... 0 : Point No n" << endl;
  cout << "  k           : Modifier le noeud No n" << endl;
  cout << "  +           : Changer de signe" << endl;
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
