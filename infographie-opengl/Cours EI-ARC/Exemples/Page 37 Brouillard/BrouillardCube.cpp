// Fichier BrouillardCube.cpp

#include <gl\glut.h>
//#include <windows.h>
#include <stdio.h>

GLfloat total = 0.0;

// Lumière ambiente
GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};

// Lumière diffuse
GLfloat diffuseLight[] = {0.9f, 0.9f, 0.9f, 1.0f};

// La lumière est à l'infini et vient d'en haut
//                          x     y     z    0->infini
GLfloat positionLight[] = {0.0f, 5.0f, 0.0f, 0.0f};

// Valeurs pour le brouillard
#define FOG_COLOR 0.5f, 0.5f, 0.5f, 1.0f
GLfloat fogColor[] = {FOG_COLOR};
GLint fogMode = /*GL_EXP GL_EXP2*/ GL_LINEAR ;

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH);
//	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  // Lumière ambiente générale
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  // Lumière diffuse
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  // Lumière LIGHT 0
	glEnable(GL_LIGHT0);
  // Enclencher les lumières
	glEnable(GL_LIGHTING);

  // Brouillard
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, fogMode);
  printf("Le mode fog est GL_LINEAR\n");
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 0.3);
  glFogf(GL_FOG_START, 1.0); // Utile si fogMode = GL_LINEAR
  glFogf(GL_FOG_END, 5.0);   // Utile si fogMode = GL_LINEAR
	glClearColor (FOG_COLOR);  // Couleur du fog
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
	glutPostRedisplay();
}

void Animate()
{
   total += 50.0;
   Sleep(50);
   glutPostRedisplay(); // Uniquement pour GLUT
}

void Keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch(key)
  {
    case 'f' :
    case 'F' : if(fogMode == GL_EXP)
               {
                 fogMode = GL_EXP2;
                 glutSetWindowTitle("Le mode fog est GL_EXP2");
                 printf("Le mode fog est GL_EXP2\n");
               }
               else if(fogMode == GL_EXP2)
               {
                 fogMode = GL_LINEAR;
                 glutSetWindowTitle("Le mode fog est GL_LINEAR");
                 printf("Le mode fog est GL_LINEAR\n");
               }
               else if(fogMode == GL_LINEAR)
               {
                 fogMode = GL_EXP;
                 glutSetWindowTitle("Le mode fog est GL_EXP");
                 printf("Le mode fog est GL_EXP\n");
               }
               glFogi(GL_FOG_MODE, fogMode);
               glutPostRedisplay();
               break;
    case 27 :  exit(0);
               break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(250, 250);
  glutCreateWindow("Appuyer sur F");

  SetupRC();
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc( Animate );
  glutMainLoop();
  return 0;
}
