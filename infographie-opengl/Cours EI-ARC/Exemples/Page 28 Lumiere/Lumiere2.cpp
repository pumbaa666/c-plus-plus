#include <gl\glut.h>
//#include <windows.h>

GLfloat total = 0.0;

void myinit ()
{
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_POLYGON_SMOOTH); // !!!!! Ralenti énormément !!!!
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	GLfloat ambientProperties[] = {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat positionProperties[] = {0.0f, -5.0f, 0.0f, 0.0f};
	glLightfv( GL_LIGHT0, GL_DIFFUSE, ambientProperties);
	glLightfv( GL_LIGHT0, GL_POSITION, positionProperties);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLfloat mat_lumineux0[]={0.0, 0.0, 0.0, 0.0};	// Noir
  GLfloat mat_lumineux1[]={1.0, 0.0, 0.0, 0.0};	// Rouge
  GLfloat mat_lumineux2[]={0.0, 1.0, 0.0, 0.0};	// Vert

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_lumineux1);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_lumineux0);
	glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
    glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
    glutSolidCube(1.0f);
	glPopMatrix();

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_lumineux0);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_lumineux2);
	glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
    glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
    glutSolidCube(1.0f);
	glPopMatrix();

	glutSwapBuffers();
}

void myReshape (int width, int height)
{
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.0, ((GLfloat) width) / ((GLfloat) height),1.0,10.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (0.0, 0.0, 5.0,
	           0.0, 0.0, 0.0,
	           0.0, 1.0, 0.0);
}

void Animate()

{
   total += 60.0;
   Sleep(20);
   glutPostRedisplay(); // Uniquement pour GLUT
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(250, 250);
  glutCreateWindow("Lumières");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutIdleFunc( Animate );
  glutMainLoop();
  return 0;
}

