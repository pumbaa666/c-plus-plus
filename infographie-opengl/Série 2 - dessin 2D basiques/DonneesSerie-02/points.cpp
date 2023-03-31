// Fichier Points.cpp

#include <GL\glut.h>

void DessinerLesPoints()
{
    GLfloat sizes[2];
    GLfloat step;
    GLfloat curSize;
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);// Trouver la taille la plus petite et la plus grande des points
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);// Trouver le pas minimum entre deux tailles
    curSize = (sizes[1] - sizes[0]) / 2.0f;// La taille courante est le milieu des deux tailles extrêmes
    glEnable(GL_POINT_SMOOTH);// Les points sont dessinés sous forme de cercles
    glPointSize(curSize);

    glBegin(GL_POINTS);
		glColor3f(0.0f,0.0f,1.0f);

		glVertex2f(-15.0f,15.0f);
		glVertex2f(15.0f,15.0f);
		glVertex2f(0.0f,-15.0f);

    glEnd();
}

