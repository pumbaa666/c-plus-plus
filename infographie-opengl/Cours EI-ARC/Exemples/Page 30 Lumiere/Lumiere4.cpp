#include <gl\glut.h>
//#include <windows.h>

GLfloat total = 0.0;

void myinit ()
{
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_POLYGON_SMOOTH); // !!!!! Ralenti énormément !!!!
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	GLfloat ambientProperties[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat positionProperties[] = {0.0f, -5.0f, 0.0f, 0.0f};

  // Modèle de lumière, PAS de lumière ambiente !!!
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientProperties); // Zéro !

	glLightfv( GL_LIGHT0, GL_DIFFUSE, ambientProperties);
	glLightfv( GL_LIGHT0, GL_POSITION, positionProperties);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_COLOR_MATERIAL);

  glColorMaterial(GL_FRONT, GL_EMISSION);
  glColor4f(0.0, 0.0, 0.0, 0.0);
  glColorMaterial(GL_FRONT, GL_SPECULAR); // Spéculaire uniquement
  glColor4f(1.0, 0.0, 0.0, 0.0);
	glPushMatrix();
    glTranslatef(-1.0,0.0,0.0);
    glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
    glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
    glutSolidCube(1.0f);
	glPopMatrix();

  glColorMaterial(GL_FRONT, GL_EMISSION); // Emission uniquement
  glColor4f(0.0, 1.0, 0.0, 0.0);
  glColorMaterial(GL_FRONT, GL_SPECULAR);
  glColor4f(0.0, 0.0, 0.0, 0.0);
	glPushMatrix();
    glTranslatef(1.0,0.0,0.0);
    glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
    glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
    glutSolidCube(1.0f);
	glPopMatrix();

//  glDisable(GL_COLOR_MATERIAL);
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
  glutCreateWindow("Lumière ambiente nulle !");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutIdleFunc( Animate );
  glutMainLoop();
  return 0;
}

