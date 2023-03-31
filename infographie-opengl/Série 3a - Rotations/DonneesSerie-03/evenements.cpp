// Fichier Evenements.cpp

#include <GL\glut.h>
#include "geometrie.h"
#include "evenements.h"
#include "global.h"
#include <iostream.h>

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef((float)angleX, 0.0f, 1.0f, 0.0f);
    glRotatef((float)angleY, 0.0f, 0.0f, 1.0f);
    DessinerLaScene();
    glPopMatrix();
    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    if (h == 0) h = 1;
    if (w == 0) w = 1;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble aspect = (GLdouble) w / (GLdouble) h;
	GLdouble angle_of_view = 45.0f;
    gluPerspective(angle_of_view, aspect, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Mouse(int button, int state, int, int)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        cout << "\nleft";
        if(state == GLUT_DOWN)
        {
            switchFigure == true;
            mouseLeft = true;
            cout << " down";
        }
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
            mouseLeft = false;
            cout << " up";
        }
    }
    if(button == GLUT_RIGHT_BUTTON)
    {
        cout << "\nright";
        if(state == GLUT_DOWN)
        {
            switchFigure == true;
            mouseRight = true;
            cout << " down";
        }
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
            mouseRight = false;
            cout << " up";
        }
    }
}

void Motion(int x, int y)
{
    cout << "\nmotion";
    switchFigure = false;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(mouseLeft == true)
    {
        cout << " left";
        if(x > oldX)
            angleX+=2;
        else if(x < oldX)
            angleX-=2;
        oldX = x;
    }
    else
    {
        cout << " right";
        if(y > oldY)
            angleY+=2;
        else if(y < oldY)
            angleY-=2;
        oldY = y;
    }
    Display();
}

