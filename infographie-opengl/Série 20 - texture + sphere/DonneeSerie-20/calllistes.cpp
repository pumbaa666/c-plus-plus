// Fichier CallListes.cpp

#include <GL\glut.h>
#include <math.h>
#include "global.h"
#include "calllistes.h"
#include "sphere.h"
#include <stdio.h>
// Permet de calculer cos et sin avec des angles en degrés.
#define COS(X) cos( (X) * M_PI/180.0)
#define SIN(X) sin( (X) * M_PI/180.0)

void Make_CallListes()
{
    int nbFacetteH = 200;
    int nbFacetteV = 200;

    float   deltaTheta = 180/(float)nbFacetteV,
            deltaPhi = 360/(float)nbFacetteH,
            theta, phi,

            deltaT = 1/(float)nbFacetteV,
            deltaS = 1/(float)nbFacetteH,
            s, t = 1,

            x, y, z;

    int r = 1;


    terre = glGenLists(1);

    glNewList(terre, GL_COMPILE);

        for(theta = 0; theta <= 180; theta+=deltaTheta)
        {
            s = 0;
            glBegin(GL_QUAD_STRIP);
            for(phi = 0; phi <= 360; phi+=deltaPhi)
            {
                x = r*SIN(theta)*COS(phi);
                y = r*SIN(theta)*SIN(phi);
                z = r*COS(theta);
                glNormal3f(x, y, z);
                glTexCoord2f(s, t); glVertex3f(x, y, z);

                x = r*SIN(theta+deltaTheta)*COS(phi);
                y = r*SIN(theta+deltaTheta)*SIN(phi);
                z = r*COS(theta+deltaTheta);
                glNormal3f(x, y, z);
                glTexCoord2f(s, t); glVertex3f(x, y, z);

                s += deltaS;
            }
            t -= deltaT;
            glEnd();
        }
    glEndList();
}


