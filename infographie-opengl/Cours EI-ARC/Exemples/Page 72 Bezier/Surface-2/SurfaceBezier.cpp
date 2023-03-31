// Fichier SurfaceBezier.cpp

// Ce programme montre l'utilisation des surfaces de B�zier.

// Voir commentaire dans glut.h sur ATEXIT
//#define GLUT_DISABLE_ATEXIT_HACK

#include <gl\glut.h>                // Librairie GLUT

// Remarque concernant #include <iostream.h> et <iostream> :
//
// Utiliser l'option -Wno-deprecated
// pour �viter le warning suivant :
// #warning This file includes at least one deprecated or antiquated header.
// Please consider using one of the 32 headers found in section 17.4.1.2
// of the C++ standard. Examples include substituting the <X> header
// for the <X.h> header for C++ includes, or <iostream> instead of
// the deprecated header <iostream.h>.
// To disable this warning use -Wno-deprecated.

// Si on �crit : #include <iostream> (sans le .h), alors on doit �crire :

//    std::cout << "blabla" << std::endl;

#include <iostream.h>
#include "evenements.h"
#include "global.h"
#include "lumieres.h"
#include "dessin.h"
#include "SurfaceBezier.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.5f, 0.0f ); // Ce sont les valuers par d�faut.
   glEnable(GL_DEPTH_TEST);
//   glEnable(GL_POLYGON_SMOOTH);
   SetLight();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur, hauteur);
  glutCreateWindow("Surface de B�zier");

  cout << " Touches fl�ches      pour d�placer la cam�ra" << endl;
  cout << "   w    pour afficher en plein �cran" << endl;
  cout << "   l    pour lumi�re � l'infini ou non" << endl;
  cout << "   p    pour afficher les points ou non" << endl;
  SetupRC();
  Make_CallListes();
  glutReshapeFunc(Reshape);//fonction g�rant le redimensionnement de la fen�tre
  glutDisplayFunc(Display);
  glutSpecialFunc(ToucheSpecial);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();				//boucle principale
  return 0;
}

