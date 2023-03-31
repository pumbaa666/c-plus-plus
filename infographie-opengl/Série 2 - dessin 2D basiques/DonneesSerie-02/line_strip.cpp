// Fichier Line_Strip.CPP
#include <GL\glut.h>
#include "Line_strip.h"

void DessinerLesLine_strip()
{
    GLfloat sizes[2];
    GLfloat step;
    GLfloat curWidth;

    glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);// Trouver la largeur la plus petite et la plus grande des lignes
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &step);// Trouver le pas minimum entre deux largeurs
    curWidth = (sizes[1] - sizes[0]) / 2.0f;

    GLint factor = 5;  // 5 pixels par bit
    GLushort pattern = 0xFFFF;  // Chaque bit � 1 dessine le pixel (16 bits)
    glLineStipple(factor, pattern);

    glLineWidth(curWidth);     // Largeur de ligne curWidth
    glEnable(GL_LINE_STIPPLE); // Activer le type de ligne


    glBegin(GL_LINE_STRIP);
		glColor3f(0.0f,0.0f,1.0f);

		glVertex2f(15.0f,15.0f);
		glVertex2f(-15.0f,15.0f);

		glVertex2f(-15.0f,15.0f);
		glVertex2f(0.0f,-15.0f);

		glVertex2f(0.0f,-15.0f);
		glVertex2f(15.0f,15.0f);
    glEnd();

    glDisable(GL_LINE_STIPPLE); // D�sactiver le type de ligne
    glLineWidth(1);     // Largeur de ligne curWidth}

}