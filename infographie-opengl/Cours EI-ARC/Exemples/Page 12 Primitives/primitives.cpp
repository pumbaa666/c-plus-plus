// Fichier Primitives.CPP
#include <GL/glut.h>
#include <iostream.h>
// Remarque concernant #include <iostream.h> et <iostream> :

// Utiliser l'option -Wno-deprecated
// pour éviter le warning suivant :
// #warning This file includes at least one deprecated or antiquated header.
// Please consider using one of the 32 headers found in section 17.4.1.2
// of the C++ standard. Examples include substituting the <X> header
// for the <X.h> header for C++ includes, or <iostream> instead of
// the deprecated header <iostream.h>.
// To disable this warning use -Wno-deprecated. 

#include "Primitives.h"

void DessinerPrimitives()
{
    GLfloat dx, dy;
    //
    // Enable depth testing and clear the color and depth
    //  buffers.
    //
    glEnable( GL_DEPTH_TEST );
    glClearColor(0.0, 0.0, 1.0, 0.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLineWidth(5.0);
    glBegin(GL_LINES);
      glColor3f( 1.0f, 1.0f, 1.0f );
      glVertex3f( 0.0, 275.0, 1.0);   // z = +1, donc devant z = 0 !
      glVertex3f( 800.0, 275.0, 1.0);
      glVertex3f( 160.0, 0.0, 1.0);
      glVertex3f( 160.0, 550.0, 1.0);
      glVertex3f( 320.0, 0.0, 1.0);
      glVertex3f( 320.0, 550.0, 1.0);
      glVertex3f( 480.0, 0.0, 1.0);
      glVertex3f( 480.0, 550.0, 1.0);
      glVertex3f( 640.0, 0.0, 1.0);
      glVertex3f( 640.0, 550.0, 1.0);
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
      glColor3f( 0.0f, 1.0f, 0.0f ); // Vert
      glVertex3f( 40.0, 400.0, 0.0);
      glVertex3f( 50.0, 350.0, 0.0);
      glVertex3f( 80.0, 300.0, 0.0);
      glVertex3f( 110.0, 350.0, 0.0);
      glVertex3f( 120.0, 400.0, 0.0);
      glVertex3f( 140.0, 450.0, 0.0);
      glVertex3f( 120.0, 500.0, 0.0);
      glVertex3f( 100.0, 440.0, 0.0);
    glEnd();

    dx = 160.0;
    glBegin(GL_LINES);
      glColor3f( 1.0f, 1.0f, 1.0f );
      glVertex3f( 40.0+dx, 400.0, 0.0);
      glVertex3f( 50.0+dx, 350.0, 0.0);
      glVertex3f( 80.0+dx, 300.0, 0.0);
      glVertex3f( 110.0+dx, 350.0, 0.0);
      glVertex3f( 120.0+dx, 400.0, 0.0);
      glVertex3f( 140.0+dx, 450.0, 0.0);
      glVertex3f( 120.0+dx, 500.0, 0.0);
      glVertex3f( 100.0+dx, 440.0, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_LINE_STRIP);
      glColor3f( 1.0f, 1.0f, 1.0f );
      glVertex3f( 40.0+dx, 400.0, 0.0);
      glVertex3f( 50.0+dx, 350.0, 0.0);
      glVertex3f( 80.0+dx, 300.0, 0.0);
      glVertex3f( 110.0+dx, 350.0, 0.0);
      glVertex3f( 120.0+dx, 400.0, 0.0);
      glVertex3f( 140.0+dx, 450.0, 0.0);
      glVertex3f( 120.0+dx, 500.0, 0.0);
      glVertex3f( 100.0+dx, 440.0, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_LINE_LOOP);
      glColor3f( 1.0f, 1.0f, 1.0f );
      glVertex3f( 40.0+dx, 400.0, 0.0);
      glVertex3f( 50.0+dx, 350.0, 0.0);
      glVertex3f( 80.0+dx, 300.0, 0.0);
      glVertex3f( 110.0+dx, 350.0, 0.0);
      glVertex3f( 120.0+dx, 400.0, 0.0);
      glVertex3f( 140.0+dx, 450.0, 0.0);
      glVertex3f( 120.0+dx, 500.0, 0.0);
      glVertex3f( 100.0+dx, 440.0, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_POLYGON);
      glColor3f( 1.0f, 1.0f, 1.0f );
      glVertex3f( 40.0+dx, 400.0, 0.0);
      glVertex3f( 50.0+dx, 350.0, 0.0);
      glVertex3f( 80.0+dx, 300.0, 0.0);
      glVertex3f( 110.0+dx, 350.0, 0.0);
      glVertex3f( 120.0+dx, 400.0, 0.0);
      glVertex3f( 140.0+dx, 450.0, 0.0);
      glVertex3f( 120.0+dx, 500.0, 0.0);
      glVertex3f( 40.0+dx, 460.0, 0.0);
    glEnd();

    dx = 0.0;
    dy = -275.0;
    glBegin(GL_QUADS);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 40.0+dx, 400.0+dy, 0.0);
      glVertex3f( 50.0+dx, 350.0+dy, 0.0);
      glVertex3f( 80.0+dx, 300.0+dy, 0.0);
      glVertex3f( 110.0+dx, 350.0+dy, 0.0);
      glVertex3f( 120.0+dx, 400.0+dy, 0.0);
      glVertex3f( 140.0+dx, 450.0+dy, 0.0);
      glVertex3f( 120.0+dx, 500.0+dy, 0.0);
      glVertex3f( 100.0+dx, 440.0+dy, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_QUAD_STRIP);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 40.0+dx, 400.0+dy, 0.0);
      glVertex3f( 50.0+dx, 350.0+dy, 0.0);
      glVertex3f( 80.0+dx, 300.0+dy, 0.0);
      glVertex3f( 110.0+dx, 350.0+dy, 0.0);
      glVertex3f( 120.0+dx, 400.0+dy, 0.0);
      glVertex3f( 140.0+dx, 450.0+dy, 0.0);
      glVertex3f( 120.0+dx, 500.0+dy, 0.0);
      glVertex3f( 100.0+dx, 440.0+dy, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_TRIANGLES);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 40.0+dx, 400.0+dy, 0.0);
      glVertex3f( 50.0+dx, 350.0+dy, 0.0);
      glVertex3f( 80.0+dx, 300.0+dy, 0.0);
      glVertex3f( 110.0+dx, 350.0+dy, 0.0);
      glVertex3f( 120.0+dx, 400.0+dy, 0.0);
      glVertex3f( 140.0+dx, 450.0+dy, 0.0);
      glVertex3f( 120.0+dx, 500.0+dy, 0.0);
      glVertex3f( 100.0+dx, 440.0+dy, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_TRIANGLE_STRIP);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 40.0+dx, 400.0+dy, 0.0);
      glColor3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 50.0+dx, 350.0+dy, 0.0);
      glColor3f( 0.0f, 1.0f, 1.0f );
      glVertex3f( 80.0+dx, 300.0+dy, 0.0);
      glColor3f( 1.0f, 0.0f, 0.0f );
      glVertex3f( 110.0+dx, 350.0+dy, 0.0);
      glColor3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 120.0+dx, 400.0+dy, 0.0);
      glColor3f( 1.0f, 0.0f, 0.0f );
      glVertex3f( 140.0+dx, 450.0+dy, 0.0);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 120.0+dx, 500.0+dy, 0.0);
      glColor3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 100.0+dx, 440.0+dy, 0.0);
    glEnd();

    dx += 160.0;
    glBegin(GL_TRIANGLE_FAN);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 40.0+dx, 400.0+dy, 0.0);
      glColor3f( 0.0f, 1.0f, 1.0f );
      glVertex3f( 50.0+dx, 350.0+dy, 0.0);
      glColor3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 80.0+dx, 300.0+dy, 0.0);
      glColor3f( 1.0f, 0.0f, 0.0f );
      glVertex3f( 110.0+dx, 350.0+dy, 0.0);
      glColor3f( 0.0f, 1.0f, 0.0f );
      glVertex3f( 120.0+dx, 400.0+dy, 0.0);
      glColor3f( 1.0f, 0.0f, 1.0f );
      glVertex3f( 140.0+dx, 450.0+dy, 0.0);
      glColor3f( 0.0f, 1.0f, 1.0f );
      glVertex3f( 120.0+dx, 500.0+dy, 0.0);
      glColor3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 100.0+dx, 440.0+dy, 0.0);
    glEnd();

    glColor3f( 1.0, 0.0, 0.0 );
    glRectf(320.0, 290.0, 480.0, 260.0); // Rectangle en z = 0

}

void myinit()
{
  glShadeModel(/*GL_SMOOTH*/ GL_FLAT);
    cout << "GL_LINES, pour les séparations" << endl;
    cout << "GL_POINTS" << endl;
    cout << "GL_LINES" << endl;
    cout << "GL_LINE_STRIP" << endl;
    cout << "GL_LINE_LOOP" << endl;
    cout << "GL_POLYGON" << endl;
    cout << "GL_QUADS" << endl;
    cout << "GL_QUAD_STRIP" << endl;
    cout << "GL_TRIANGLES" << endl;
    cout << "GL_TRIANGLE_STRIP" << endl;
    cout << "GL_TRIANGLE_FAN" << endl;
}

void display()
{
  DessinerPrimitives();
  glFlush();
}

void myReshape(int w, int h)
{
  w = (w == 0) ? 1 : w;
  h = (h == 0) ? 1 : h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  gluOrtho2D(0.0, 800.0, 0.0, 550.0);
  // Valeur < 0 (-2.5) --> Le plan est derrière la caméra.
  // Valeur > 0 (2.5)  --> Le plan est devant la caméra.
  glOrtho(0.0, 800.0, 0.0, 550.0, -2.5, 2.5);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 550);
  glutCreateWindow("Exemple de primitives avec GLUT");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
