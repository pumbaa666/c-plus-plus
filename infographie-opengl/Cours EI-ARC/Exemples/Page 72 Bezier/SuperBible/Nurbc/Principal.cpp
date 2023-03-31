// Fichier Principal.CPP
#include <GL\glut.h>
#include <stdio.h>
#include "global.h"
#include "evenements.h"
#include "principal.h"

void MyInit()
{
  // Fond blanc
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
	// Setup the Nurbs object
    pNurb = gluNewNurbsRenderer();
    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.0f);
	gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
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

