// Fichier Dessin.cpp

#include <gl\glut.h>                // Librairie GLUT
#include <math.h>
#include "dessin.h"

void Vecteur_Unite(float vector[3])
{
       float length;

			// Calcul de la norme du vecteur
       length = (float)sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));

       if(length == 0.0f) length = 1.0f;  //évite une violente erreur !!!
       vector[0] /= length;
       vector[1] /= length;
       vector[2] /= length;
}

// Points p1, p2, & p3 spécifiés dans le sens trigonométrique
void Normale(float v[3][3], float out[3])
{
       float v1[3],v2[3];
       static const int x = 0;
       static const int y = 1;
       static const int z = 2;

			// Calcul de 2 vecteurs à partir des 3 points
       v1[x] = v[0][x] - v[1][x];
       v1[y] = v[0][y] - v[1][y];
       v1[z] = v[0][z] - v[1][z];
       v2[x] = v[1][x] - v[2][x];
       v2[y] = v[1][y] - v[2][y];
       v2[z] = v[1][z] - v[2][z];

			// calcul du produit vectoriel
       out[x] = (v1[y]*v2[z] - v1[z]*v2[y]);
       out[y] = (v1[z]*v2[x] - v1[x]*v2[z]);
       out[z] = (v1[x]*v2[y] - v1[y]*v2[x]);

		// on le réduit à un vecteur unité
       Vecteur_Unite(out);
}

void MakeShadowMatrix(GLfloat points_plan[3][3], GLfloat lightPos[4], GLfloat destMat[4][4])
{
	GLfloat planeCoeff[4];
	GLfloat dot;


		//on calcule un vecteur normal à ce plan
	Normale(points_plan,planeCoeff);


		// le dernier coefficient se calcule par substitution
	planeCoeff[3] = - ( (planeCoeff[0]*points_plan[2][0]) + (planeCoeff[1]*points_plan[2][1]) + (planeCoeff[2]*points_plan[2][2]));
	dot = planeCoeff[0] * lightPos[0] + planeCoeff[1] * lightPos[1] + planeCoeff[2] * lightPos[2] + planeCoeff[3] * lightPos[3];


		// maintenant, on projète
		// 1ère colonne
	destMat[0][0] = dot - lightPos[0] * planeCoeff[0];
	destMat[1][0] = 0.0f - lightPos[0] * planeCoeff[1];
	destMat[2][0] = 0.0f - lightPos[0] * planeCoeff[2];
	destMat[3][0] = 0.0f - lightPos[0] * planeCoeff[3];


		// 2ème colonne
	destMat[0][1] = 0.0f - lightPos[1] * planeCoeff[0];
	destMat[1][1] = dot - lightPos[1] * planeCoeff[1];
	destMat[2][1] = 0.0f - lightPos[1] * planeCoeff[2];
	destMat[3][1] = 0.0f - lightPos[1] * planeCoeff[3];


		// 3ème colonne
	destMat[0][2] = 0.0f - lightPos[2] * planeCoeff[0];
	destMat[1][2] = 0.0f - lightPos[2] * planeCoeff[1];
	destMat[2][2] = dot - lightPos[2] * planeCoeff[2];
	destMat[3][2] = 0.0f - lightPos[2] * planeCoeff[3];


		// 4ème colonne
	destMat[0][3] = 0.0f - lightPos[3] * planeCoeff[0];
	destMat[1][3] = 0.0f - lightPos[3] * planeCoeff[1];
	destMat[2][3] = 0.0f - lightPos[3] * planeCoeff[2];
	destMat[3][3] = dot - lightPos[3] * planeCoeff[3];
}

void cube(int ombre)
{
	GLfloat Rouge[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat Vert[]  = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat Bleu[]  = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat Jaune[]  = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat Rose[]  = {1.0f, 0.0f, 1.0f, 1.0f};
	GLfloat	Cyan[]  = {0.0f, 1.0f, 1.0f, 1.0f};

	glBegin(GL_QUADS);
			//Si il s'agit de l'ombre,
			//on dessine le cube noir légèrement transparent
		if (!ombre) glColor4fv(Rouge); else glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
		glNormal3d(0.0,0.0,1.0);
		glVertex3d(-1,  1, 1);
		glVertex3d(-1, -1, 1);
		glVertex3d( 1, -1, 1);
		glVertex3d( 1,  1, 1);
		if (!ombre) glColor4fv(Jaune);
		glNormal3d(-1.0,0.0,0.0);
		glVertex3d( -1,  1,  1);
		glVertex3d( -1,  1, -1);
		glVertex3d( -1, -1, -1);
		glVertex3d( -1, -1,  1);
		if (!ombre) glColor4fv( Vert);
		glNormal3d(1.0,0.0,0.0);
		glVertex3d( 1,  1,  1);
		glVertex3d( 1, -1,  1);
		glVertex3d( 1, -1, -1);
		glVertex3d( 1,  1, -1);
		if (!ombre) glColor4fv( Rose);
		glNormal3d(0.0,1.0,0.0);
		glVertex3d( -1, 1,  1);
		glVertex3d(  1, 1,  1);
		glVertex3d(  1, 1, -1);
		glVertex3d( -1, 1, -1);
		if (!ombre) glColor4fv( Bleu);
		glNormal3d(0.0,-1.0,0.0);
		glVertex3d( -1, -1,  1);
		glVertex3d( -1, -1, -1);
		glVertex3d(  1, -1, -1);
		glVertex3d(  1, -1,  1);
		if (!ombre) glColor4fv( Cyan);
		glNormal3d(0.0,0.0,-1.0);
		glVertex3d(  1,  1, -1);
		glVertex3d(  1, -1, -1);
		glVertex3d( -1, -1, -1);
		glVertex3d( -1,  1, -1);
	glEnd();
}

void drawFloor()
{
	GLfloat Gris[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glColor4fv(Gris);
	glBegin(GL_QUADS);
		  glVertex3f(-4.0,  4.0, 0.0);
		  glVertex3f( 4.0,  4.0, 0.0);
		  glVertex3f( 4.0, -4.0, 0.0);
		  glVertex3f(-4.0, -4.0, 0.0);
	glEnd();
}

