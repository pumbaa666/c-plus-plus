// Fichier pour projet GLUT vide

#include <GL/glut.h>
#include <stdlib.h>

/* Program entry point */
int 
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Programme GLUT");

    glutMainLoop();

    return EXIT_SUCCESS;
}

