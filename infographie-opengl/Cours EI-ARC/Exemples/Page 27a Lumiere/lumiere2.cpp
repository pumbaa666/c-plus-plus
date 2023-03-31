// Lumière 2
// Seule la lumière tourne.

#include <GL\glut.h>
#include <windows.h>

GLdouble a=0;

GLdouble AngleOuverture = 40.0;   // en degrés
GLdouble RapportAspect, PlanAvant = 1.0, PlanArriere = 500.0;

void DessinerLesAxes()
{
  glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.05f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.05f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.05f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.05f, 0.8f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.05f, 0.0f, 0.8f);
  glEnd();
}

void myinit()
{
  GLfloat lumiereAmbiente[] = {0.8, 0.8, 0.8, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, lumiereAmbiente);
  glEnable(GL_DEPTH_TEST); // Active le test de profondeur
  glEnable(GL_LIGHTING); // Active l'éclairage
  glEnable(GL_LIGHT0); // Allume la lumière n°1
}

void Animate()
{
  a+=1;
  Sleep(50);
  glutPostRedisplay(); // Uniquement pour GLUT
}
void myReshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  // Charger la matrice de projection identité

  // Calcul du rapport d'aspect de la fenêtre
  RapportAspect = (GLfloat)w / (GLfloat)h;
  gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);
}

void display()  // La lumière tourne autour du tore
{
   GLint LightPos[4] = {0,0,3,1};
   GLfloat materialAmbient[] = {0.0f, 0.0f, 1.0f, 1.0f};

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0,3,3,0,0,0,0,1,0);   // Avant Positionnement de la lampe
                                // La position de la lampe n'est pas affectée

   glRotated(a,0,1,0);
   glDisable(GL_LIGHTING); // Désactive l'éclairage
     glColor3f(0.0f, 1.0f, 0.0f);
     DessinerLesAxes();
   glEnable(GL_LIGHTING); // Active l'éclairage
   glLightiv(GL_LIGHT0,GL_POSITION,LightPos); // Positionner la lampe
   glRotated(-a,0,1,0);

   glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
   glutSolidTorus(0.25f, 0.5f, 20, 20);
   glutSwapBuffers();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowPosition(0, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Lumière 2");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutIdleFunc( Animate );
  glutMainLoop();
  return 0;
}
