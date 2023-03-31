// Fichier EclairageCube.cpp

// Avec glMaterial et une une carte graphique Intel,
// L'illumination ne fonctionne pas correctement.
// Le programme se plante sous Borland, mais pas sous DEV-C++.

// Avec le Color Tracking, le cube est correctement illuminé

#include <gl\glut.h>
//#include <windows.h>

GLfloat total = 0.0;

// Lumière ambiente
GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};

// Lumière diffuse
GLfloat diffuseLight[] = {0.9f, 0.9f, 0.9f, 1.0f};

// La lumière est à l'infini et vient d'en haut
//                          x     y     z    0->infini
GLfloat positionLight[] = {0.0f, 5.0f, 0.0f, 0.0f};

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  // Lumière ambiente générale
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  // Lumière diffuse
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  // Lumière LIGHT 0
	glEnable(GL_LIGHT0);
  // Enclencher les lumières
	glEnable(GL_LIGHTING);
}

void Display (void)
{
	GLfloat Rouge[] = {0.8f, 0.0f, 0.0f, 1.0f};
	GLfloat Vert[] = {0.0f, 0.8f, 0.0f, 1.0f};
	GLfloat Bleu[] = {0.0f, 0.0f, 0.8f, 1.0f};
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Positionner la lumière zéro
  // Cet appel est fait après gluLookAt !!!
  // Donc la lampe n'est pas accrochée à la caméra.
	glLightfv( GL_LIGHT0, GL_POSITION, positionLight);

   // La version ci-dessous fonctionne même avec une carte graphique Intel !
   // Les appels à glMaterial sont en dehors du bloc glBegin - glEnd !

	glPushMatrix();
		glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
		glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Rouge);
		glBegin(GL_QUADS);
			glNormal3d(0.0,0.0,1.0);
			glVertex3d(-1, 1, 1);
			glVertex3d(-1, -1, 1);
			glVertex3d( 1, -1, 1);
			glVertex3d( 1, 1, 1);
			glNormal3d(0.0,0.0,-1.0);
			glVertex3d( 1, 1, -1);
			glVertex3d( 1, -1, -1);
			glVertex3d( -1, -1, -1);
			glVertex3d( -1, 1, -1);
		glEnd();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Vert);
		glBegin(GL_QUADS);
			glNormal3d(1.0,0.0,0.0);
			glVertex3d( 1, 1, 1);
			glVertex3d( 1, -1, 1);
			glVertex3d( 1, -1, -1);
			glVertex3d( 1, 1, -1);
			glNormal3d(-1.0,0.0,0.0);
			glVertex3d( -1, 1, 1);
			glVertex3d( -1, 1, -1);
			glVertex3d( -1, -1, -1);
			glVertex3d( -1, -1, 1);
		glEnd();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Bleu);
		glBegin(GL_QUADS);
			glNormal3d(0.0,-1.0,0.0);
			glVertex3d( -1, -1, 1);
			glVertex3d( -1, -1, -1);
			glVertex3d( 1, -1, -1);
			glVertex3d( 1, -1, 1);
			glNormal3d(0.0,1.0,0.0);
			glVertex3d( -1, 1, 1);
			glVertex3d( 1, 1, 1);
			glVertex3d( 1, 1, -1);
			glVertex3d( -1, 1, -1);
		glEnd();
	glPopMatrix();

   // La version ci-dessous ne fonctionne pas avec une carte graphique Intel !
/*
	glPushMatrix();
		glRotatef((total/30.0f), 0.5f, 0.3f, 0.8f);
		glRotatef((total/50.0f), 0.5f, -0.3f, 0.8f);
		glBegin(GL_QUADS);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Rouge);
			glNormal3d(0.0,0.0,1.0);
			glVertex3d(-1, 1, 1);
			glVertex3d(-1, -1, 1);
			glVertex3d( 1, -1, 1);
			glVertex3d( 1, 1, 1);
			glNormal3d(0.0,0.0,-1.0);
			glVertex3d( 1, 1, -1);
			glVertex3d( 1, -1, -1);
			glVertex3d( -1, -1, -1);
			glVertex3d( -1, 1, -1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Vert);
			glNormal3d(1.0,0.0,0.0);
			glVertex3d( 1, 1, 1);
			glVertex3d( 1, -1, 1);
			glVertex3d( 1, -1, -1);
			glVertex3d( 1, 1, -1);
			glNormal3d(-1.0,0.0,0.0);
			glVertex3d( -1, 1, 1);
			glVertex3d( -1, 1, -1);
			glVertex3d( -1, -1, -1);
			glVertex3d( -1, -1, 1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Bleu);
			glNormal3d(0.0,-1.0,0.0);
			glVertex3d( -1, -1, 1);
			glVertex3d( -1, -1, -1);
			glVertex3d( 1, -1, -1);
			glVertex3d( 1, -1, 1);
			glNormal3d(0.0,1.0,0.0);
			glVertex3d( -1, 1, 1);
			glVertex3d( 1, 1, 1);
			glVertex3d( 1, 1, -1);
			glVertex3d( -1, 1, -1);
		glEnd();
	glPopMatrix();
*/
	glutSwapBuffers();
}

void Reshape (int width, int height)
{
  if(width == 0) width = 1;
  if(height == 0) height = 1;
	glViewport (0, 0, width, height);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45.0, ((GLdouble) width) / ((GLdouble) height),1.0,10.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (0.0f, 0.0f, 5.0f,   // La caméra est placée à 5 unités
	           0.0f, 0.0f, 0.0f,   // le long de l'axe Oz
	           0.0f, 1.0f, 0.0f);
}

void Animate()
{
   total += 50.0;
   Sleep(50);
   glutPostRedisplay(); // Uniquement pour GLUT
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(350, 350);
  glutCreateWindow("EclairageCube avec glMaterial");

  SetupRC();
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
  glutIdleFunc( Animate );
  glutMainLoop();
  return 0;
}
