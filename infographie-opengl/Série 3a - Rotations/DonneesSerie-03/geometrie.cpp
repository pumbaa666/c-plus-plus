// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
  glColor3f(1.0f, 0.0f, 0.0f);

  switch(Figure)
  {
    case 1 : DessinerLesAxes();
             glutWireSphere(1.0, 50, 50);
             glutSetWindowTitle("Sphère en fil de fer");
             break;
    case 2 : DessinerLesAxes();
             glutSolidSphere(1.0, 50, 50);
             glutSetWindowTitle("Sphère solide");
             break;

    case 3 : DessinerLesAxes();
             glutWireCube(1.0);
             glutSetWindowTitle("Cube en fil de fer");
             break;
    case 4 : DessinerLesAxes();
             glutSolidCube(1.0);
             glutSetWindowTitle("Cube solide");
             break;

    case 5 : DessinerLesAxes();
             glutWireCone(1.0, 1.5, 20, 20);
             glutSetWindowTitle("Cône en fil de fer");
             break;
    case 6 : DessinerLesAxes();
             glutSolidCone(1.0, 1.5, 20, 20);
             glutSetWindowTitle("Cône solide");
             break;

    case 7 : DessinerLesAxes();
             glutWireTorus(0.5, 1.0, 20, 20);
             glutSetWindowTitle("Tore en fil de fer");
             break;
    case 8 : DessinerLesAxes();
             glutSolidTorus(0.5, 1.0, 20, 20);
             glutSetWindowTitle("Tore solide");
             break;

    case 9 : DessinerLesAxes();
             glutWireDodecahedron();
             glutSetWindowTitle("Dodécahèdre en fil de fer");
             break;
    case 10 : DessinerLesAxes();
             glutSolidDodecahedron();
              glutSetWindowTitle("Dodécahèdre solide");
              break;

    case 11 : DessinerLesAxes();
              glutWireOctahedron();
              glutSetWindowTitle("Octahèdre en fil de fer");
              break;
    case 12 : DessinerLesAxes();
              glutSolidOctahedron();
              glutSetWindowTitle("Octahèdre solide");
              break;

    case 13 : DessinerLesAxes();
              glutWireTetrahedron();
              glutSetWindowTitle("Tétrahèdre en fil de fer");
              break;
    case 14 : DessinerLesAxes();
              glutSolidTetrahedron();
              glutSetWindowTitle("Tétrahèdre solide");
              break;

    case 15 : DessinerLesAxes();
              glutWireIcosahedron();
              glutSetWindowTitle("Icosahèdre en fil de fer");
              break;
    case 16 : DessinerLesAxes();
              glutSolidIcosahedron();
              glutSetWindowTitle("Icosahèdre solide");
              break;

    case 17 : DessinerLesAxes();
              glutWireTeapot(1.0);
              glutSetWindowTitle("Teapot en fil de fer");
              break;
    case 18 : DessinerLesAxes();
              glutSolidTeapot(1.0);
              glutSetWindowTitle("Teapot solide");
              break;
  }
}

void DessinerLesAxes()
{
    glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);

        /* Axe X */
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.2f,0.0f,0.0f);

        /* Fleche */
		glVertex3f(1.2f,0.0f,0.0f);
		glVertex3f(1.0f,0.1f,0.0f);

		glVertex3f(1.2f,0.0f,0.0f);
		glVertex3f(1.0f,-0.1f,0.0f);

		glVertex3f(1.2f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,-0.1f);

		glVertex3f(1.2f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,+0.1f);


        /* Axe Y */
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.2f,0.0f);

        /* Fleche */
		glVertex3f(0.0f,1.2f,0.0f);
		glVertex3f(0.1f,1.0f,0.0f);

		glVertex3f(0.0f,1.2f,0.0f);
		glVertex3f(-0.1f,1.0f,0.0f);

		glVertex3f(0.0f,1.2f,0.0f);
		glVertex3f(0.0f,1.0f,0.1f);

		glVertex3f(0.0f,1.2f,0.0f);
		glVertex3f(0.0f,1.0f,-0.1f);


        /* Axe Z */
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.2f);

        /* Fleche */
        glVertex3f(0.0f,0.0f,1.2f);
        glVertex3f(0.0f,0.0f,1.0f);

        glVertex3f(0.0f,0.0f,1.2f);
        glVertex3f(0.0f,0.1f,1.0f);

        glVertex3f(0.0f,0.0f,1.2f);
        glVertex3f(0.0f,-0.1f,1.0f);

        glVertex3f(0.0f,0.0f,1.2f);
        glVertex3f(0.1f,0.0f,1.0f);

        glVertex3f(0.0f,0.0f,1.2f);
        glVertex3f(-0.1f,0.0f,1.0f);

		glColor3f(1.0f,0.0f,0.0f);
    glEnd();
}

