#include <gl\glut.h>
#include "geometrie.h"
#include "global.h"

void Dessiner()
{
    switch(objet)
    {
        case 0 :
            glutWireSphere(1.0, 50, 50);
            glutSetWindowTitle("Sphère en fil de fer");
            break;

        case 1 :
            glutSolidSphere(1.0, 50, 50);
            glutSetWindowTitle("Sphère pleine");
            break;

        case 2 :
            glutWireCube(1.0);
            glutSetWindowTitle("Cube en fil de fer");
            break;

        case 3 :
            glutSolidCube(1.0);
            glutSetWindowTitle("Cube plein");
            break;

        case 4 :
            glutWireCone(1.0, 1.5, 20, 20);
            glutSetWindowTitle("Cone en fil de fer");
            break;

        case 5 :
            glutSolidCone(1.0, 1.5, 20, 20);
            glutSetWindowTitle("Cone plein");
            break;

        case 6 :
            glutWireTorus(0.5, 1.0, 20, 20);
            glutSetWindowTitle("Tore en fil de fer");
            break;

        case 7 :
            glutSolidTorus(0.5, 1.0, 20, 20);
            glutSetWindowTitle("Tore plein");
            break;

        case 8 :
            glutWireTeapot(1.0);
            glutSetWindowTitle("Théière en fil de fer");
            break;

        case 9 :
            glutSolidTeapot(1.0);
            glutSetWindowTitle("Théière pleine (comme vadi à la FDV)");
            break;
    }
}
