// Fichier CourbeBezier.cpp

// Ce programme montre l'utilisation des courbes de Bézier.
// Utilisation de :
//
/*
        static GLfloat ctrlpoints[4][3] = {
            {-4.0, -4.0, -15.0}, {-2.0, 4.0, -15.0},
            { 2.0, -4.0, -15.0}, { 4.0, 4.0, -15.0}};
        glColor3f(1.0f,1.0f,1.0f);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
        glEnable(GL_MAP1_VERTEX_3);
        glBegin(GL_LINE_STRIP);
        for (GLfloat i = 0.0; i <= 1.0; i+=0.05f)
            glEvalCoord1f(i);
        glEnd();
        glDisable(GL_MAP1_VERTEX_3);

        glPointSize(5.0);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (int j = 0; j < 4; j++)
            glVertex3fv(&ctrlpoints[j][0]);
        glEnd();
*/

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
#include "CourbeBezier.h"

void SetupRC()
{
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f ); // Ce sont les valuers par défaut.
//   glEnable(GL_DEPTH_TEST);
//   glEnable(GL_POLYGON_SMOOTH);
   SetLight();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(largeur, hauteur);
  glutCreateWindow("Courbe de Bézier");

//  cout << "   l    pour lumière à l'infini ou non" << endl;
  cout << " Touches flèches      pour déplacer la caméra" << endl;
  cout << "   w    pour afficher en plein écran" << endl;
  cout << "   s    pour modifier le nombre de subdivisions" << endl;
  cout << "   +    pour changer le signe de delta" << endl;
  cout << "   m    pour changer le mode (GL_POINT ou GL_LINE)" << endl;
  cout << "   x    déplace le point numéro en x" << endl;
  cout << "   y    déplace le point numéro en y" << endl;
  cout << "   1    numéro du point" << endl;
  cout << "   2    numéro du point" << endl;
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

