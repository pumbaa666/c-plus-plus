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

#include <iostream>
#include "global.h"
#include "evenements.h"
#include "geometrie.h"
#include "principal.h"

using namespace std;

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
    gluNurbsCallback(pNurb, GLU_ERROR,
                  reinterpret_cast<GLvoid (CALLBACK *)()>(&NurbsErrorHandler));
    Key('v', 0, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Courbes NURBS");

  MyInit();
  cout << "  NbPoints    : 7" << endl;
  cout << "  Ordre       : 3 (degré = 2)" << endl;
  cout << "  NbKnots     : 7 + 3 (NbPoints + Ordre)" << endl;
  cout << "  Passe par le premier point si les 3 premiers noeuds sont égaux." << endl;
  cout << "  Passe par le dernier point si les 3 derniers noeuds sont égaux." << endl;
  cout << endl;
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

