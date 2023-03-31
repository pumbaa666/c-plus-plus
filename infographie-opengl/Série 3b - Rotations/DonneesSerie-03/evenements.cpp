// Fichier Evenements.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"
#include "iostream.h"

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Efface le fond | nettoye le Depth Buffer
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef(angleX, 0.0f, 1.0f, 0.0f);
        glRotatef(angleY, 0.0f, 0.0f, 1.0f);
        DessinerLesAxes();
        DessinerLaScene();
    glPopMatrix();
    glutSwapBuffers(); // Remplace GLFlush en double buffering
}

void Reshape(int w, int h)
{
    if (h == 0) h = 1;
    if (w == 0) w = 1;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble aspect = (GLdouble) w / (GLdouble) h; // Respecte les proportions
	GLdouble angle_of_view = 45.0f;
	GLfloat face_avant = 1.0;
	GLfloat face_arriere = 10.0;
    gluPerspective(angle_of_view, aspect, face_avant, face_arriere);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Mouse(int button, int state, int, int)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
            switchFigure == true;
        else
        {
            if(switchFigure == true)
            {
                Figure++;
                if (Figure > 18)
                    Figure = 1;
                glutPostRedisplay();
            }
            else
                switchFigure = true;
        }
    }
    else
    {
        if(state == GLUT_DOWN)
            switchFigure == true;
        else
        {
            if(switchFigure == true)
            {
                Figure--;
                if (Figure < 1)
                    Figure = 18;
                glutPostRedisplay();
            }
            else
                switchFigure = true;
        }
    }
}

void Motion(int x, int y)
{
    switchFigure = false;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(x > oldX)
        angleX+=2;
    else if(x < oldX)
        angleX-=2;
    oldX = x;
    if(angleX >= 360)
        angleX -= 360;
    if(angleX <= -360)
        angleX += 360;

    if(y > oldY)
        angleY+=2;
    else if(y < oldY)
        angleY-=2;
    oldY = y;
    if(angleY >= 360)
        angleY -= 360;
    if(angleY <= -360)
        angleY += 360;

    char titre[80];
    sprintf(titre, "x = %1.2f, y = %1.2f", angleX, angleY);
    glutSetWindowTitle(titre);
    Display();
}

