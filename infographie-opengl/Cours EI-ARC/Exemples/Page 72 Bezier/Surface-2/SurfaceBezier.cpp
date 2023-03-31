// Fichier SurfaceBezier.cpp

// Ce programme montre l'utilisation des surfaces de Bézier.

// Voir commentaire dans glut.h sur ATEXIT
//#define GLUT_DISABLE_ATEXIT_HACK

#include <gl\glut.h>                // Librairie GLUT

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
#include "evenements.h"
#include "global.h"
#include "lumieres.h"
#include "dessin.h"
#include "SurfaceBezier.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.5f, 0.0f ); // Ce sont les valuers par défaut.
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
  glutCreateWindow("Surface de Bézier");

  cout << " Touches flèches      pour déplacer la caméra" << endl;
  cout << "   w    pour afficher en plein écran" << endl;
  cout << "   l    pour lumière à l'infini ou non" << endl;
  cout << "   p    pour afficher les points ou non" << endl;
  SetupRC();
  Make_CallListes();
  glutReshapeFunc(Reshape);//fonction gérant le redimensionnement de la fenètre
  glutDisplayFunc(Display);
  glutSpecialFunc(ToucheSpecial);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Souris);
  glutMotionFunc(DeplacerSouris);
  glutMainLoop();				//boucle principale
  return 0;
}

