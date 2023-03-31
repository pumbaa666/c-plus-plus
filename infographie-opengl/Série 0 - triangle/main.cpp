#include <GL/glut.h>
#include "evenements.h"
#include "global.h"
#include "geometrie.h"
int main(int argc, char** argv)
{
	GLint Xscreen = 800;
	GLint Yscreen = 600;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Xscreen, Yscreen);
	glutCreateWindow("Triangle");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();
	return 0;
}
