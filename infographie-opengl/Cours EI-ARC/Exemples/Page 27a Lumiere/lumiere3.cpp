// Lumi�re 3
// Ce programme utilise la librairie GLUT.
// L'objet tourne, mais pas la lumi�re.

#include <GL\glut.h>
#include <windows.h>

GLdouble a=0;

GLdouble AngleOuverture = 40.0;   // en degr�s
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
  glEnable(GL_LIGHTING); // Active l'�clairage
  glEnable(GL_LIGHT0); // Allume la lumi�re n�1
}

void Animate()
{
  a+=1;
  Sleep(30);
  glutPostRedisplay(); // Uniquement pour GLUT
}
void myReshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  // Charger la matrice de projection identit�

  // Calcul du rapport d'aspect de la fen�tre
  RapportAspect = (GLfloat)w / (GLfloat)h;
  gluPerspective(AngleOuverture, RapportAspect, PlanAvant, PlanArriere);
}

void display()  // Lumi�re relative au point de vue
{
   GLint LightPos[4] = {0,0,0,1}; // Position de la lampe (0, 0, 0)
   GLfloat materialAmbient[] = {0.0f, 0.0f, 1.0f, 1.0f};

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glLightiv(GL_LIGHT0,GL_POSITION,LightPos); // Position de la lampe
   gluLookAt(0,3,3,0,0,0,0,1,0);  // Position de la cam�ra apr�s la lampe
                                  // La position de la lampe change.
                                  // Elle n'est plus en (0, 0, 0)

   glDisable(GL_LIGHTING); // D�sactive l'�clairage
     glColor3f(0.0f, 1.0f, 0.0f);
     DessinerLesAxes();
   glEnable(GL_LIGHTING); // Active l'�clairage

   glRotated(a,0,1,0);
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
  glutCreateWindow("Lumi�re 3");

  myinit();
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutIdleFunc( Animate );
  glutMainLoop();
  return 0;
}
