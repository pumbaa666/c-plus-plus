// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
  glColor3f(1.0f, 0.0f, 0.0f);

  switch(Figure)
  {
    case 1 : glutWireSphere(1.0, 50, 50);
             glutSetWindowTitle("Sph�re en fil de fer");
             break;
    case 2 : glutSolidSphere(1.0, 50, 50);
             glutSetWindowTitle("Sph�re solide");
             break;

    case 3 : glutWireCube(1.0);
             glutSetWindowTitle("Cube en fil de fer");
             break;
    case 4 : glutSolidCube(1.0);
             glutSetWindowTitle("Cube solide");
             break;

    case 5 : glutWireCone(1.0, 1.5, 20, 20);
             glutSetWindowTitle("C�ne en fil de fer");
             break;
    case 6 : glutSolidCone(1.0, 1.5, 20, 20);
             glutSetWindowTitle("C�ne solide");
             break;

    case 7 : glutWireTorus(0.5, 1.0, 20, 20);
             glutSetWindowTitle("Tore en fil de fer");
             break;
    case 8 : glutSolidTorus(0.5, 1.0, 20, 20);
             glutSetWindowTitle("Tore solide");
             break;

    case 9 : glutWireDodecahedron();
             glutSetWindowTitle("Dod�cah�dre en fil de fer");
             break;
    case 10 : glutSolidDodecahedron();
              glutSetWindowTitle("Dod�cah�dre solide");
              break;

    case 11 : glutWireOctahedron();
              glutSetWindowTitle("Octah�dre en fil de fer");
              break;
    case 12 : glutSolidOctahedron();
              glutSetWindowTitle("Octah�dre solide");
              break;

    case 13 : glutWireTetrahedron();
              glutSetWindowTitle("T�trah�dre en fil de fer");
              break;
    case 14 : glutSolidTetrahedron();
              glutSetWindowTitle("T�trah�dre solide");
              break;

    case 15 : glutWireIcosahedron();
              glutSetWindowTitle("Icosah�dre en fil de fer");
              break;
    case 16 : glutSolidIcosahedron();
              glutSetWindowTitle("Icosah�dre solide");
              break;

    case 17 : glutWireTeapot(1.0);
              glutSetWindowTitle("Teapot en fil de fer");
              break;
    case 18 : glutSolidTeapot(1.0);
              glutSetWindowTitle("Teapot solide");
              break;
  }
}

void DessinerLesAxes()
{
}

