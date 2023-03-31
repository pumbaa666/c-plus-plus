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
             if(switchFigure) glutSetWindowTitle("Sphère en fil de fer");
             break;
    case 2 : glutSolidSphere(1.0, 50, 50);
             if(switchFigure) glutSetWindowTitle("Sphère solide");
             break;

    case 3 : glutWireCube(1.0);
             if(switchFigure) glutSetWindowTitle("Cube en fil de fer");
             break;
    case 4 : glutSolidCube(1.0);
             if(switchFigure) glutSetWindowTitle("Cube solide");
             break;

    case 5 : glutWireCone(1.0, 1.5, 20, 20);
             if(switchFigure) glutSetWindowTitle("Cône en fil de fer");
             break;
    case 6 : glutSolidCone(1.0, 1.5, 20, 20);
             if(switchFigure) glutSetWindowTitle("Cône solide");
             break;

    case 7 : glutWireTorus(0.5, 1.0, 20, 20);
             if(switchFigure) glutSetWindowTitle("Tore en fil de fer");
             break;
    case 8 : glutSolidTorus(0.5, 1.0, 20, 20);
             if(switchFigure) glutSetWindowTitle("Tore solide");
             break;

    case 9 : glutWireDodecahedron();
             if(switchFigure) glutSetWindowTitle("Dodécahèdre en fil de fer");
             break;
    case 10 : glutSolidDodecahedron();
              if(switchFigure) glutSetWindowTitle("Dodécahèdre solide");
              break;

    case 11 : glutWireOctahedron();
              if(switchFigure) glutSetWindowTitle("Octahèdre en fil de fer");
              break;
    case 12 : glutSolidOctahedron();
              if(switchFigure) glutSetWindowTitle("Octahèdre solide");
              break;

    case 13 : glutWireTetrahedron();
              if(switchFigure) glutSetWindowTitle("Tétrahèdre en fil de fer");
              break;
    case 14 : glutSolidTetrahedron();
              if(switchFigure) glutSetWindowTitle("Tétrahèdre solide");
              break;

    case 15 : glutWireIcosahedron();
              if(switchFigure) glutSetWindowTitle("Icosahèdre en fil de fer");
              break;
    case 16 : glutSolidIcosahedron();
              if(switchFigure) glutSetWindowTitle("Icosahèdre solide");
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
    glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);

        /* Axe X */
		glVertex3f(-0.1f,0.0f,0.0f);
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
		glVertex3f(0.0f,-0.1f,0.0f);
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
		glVertex3f(0.0f,0.0f,-0.1f);
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

