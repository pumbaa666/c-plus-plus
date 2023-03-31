// Fichier Ombre.cpp

// Ce programme montre l'utilisation du Stencil Buffer et de la
// transparence pour r�aliser une ombre.
// Si on n'utilise pas le Stencil Buffer, l'ombre ne se limitera
// pas � la surface du sol, mais va d�border.
// La transparence est utilis�e pour que l'ombre ne soit
// pas totalement noir sur le sol.
// En effet, dans la r�alit�, et si il y a de la lumi�re ambiente,
// une ombre est simplement une partie du sol moins �clair�e que le reste.
// Il suffit donc de dessiner l'ombre en noir avec un facteur
// de transparence convenable (alpha = 0.5 par exemple).
//
// Attention, l'utilisation du Stencil Buffer ralentit passablement
// l'animation.
//
// Attention, Si on regarde le sol par en-dessous, on voit toujours
// l'ombre !!! (� cause du glDisable(DEPTH_TEST) avant de dessiner l'ombre)
// Si le Depth est actif, alors l'ombre se confond avec le sol, car
// la valeur de z est la m�me pour les deux (sol et ombre)
// Pour �viter cela (Z-fighting), il faut placer l'ombre � peine
// au-dessus du sol (0.01f) par exemple.

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

//     std::cout << "blabla" << std::endl;

#include <iostream.h>
#include "evenements.h"
#include "global.h"
#include "lumieres.h"
#include "dessin.h"
#include "ombres.h"

void SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.5f, 0.0f ); // Ce sont les valeurs par d�faut.
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
  glutCreateWindow("Ombre, appuyer sur S pour le Stencil Buffer");

  cout << "   s    pour activer ou non le Stencil Buffer" << endl;
  cout << "   l    pour lumipre � l'infini ou non" << endl;
  cout << " Touches fl�ches      pour d�placer la cam�ra" << endl;
  cout << "   w    pour afficher en plein �cran" << endl;
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

