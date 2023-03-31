// Fichier Dessin.h

#ifndef DESSIN_H
#define DESSIN_H

void shadowMatrix(	GLfloat shadowMat[4][4],
								GLfloat groundplane[4],
								GLfloat lightpos[4]);
void findPlane(GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);

void Vecteur_Unite(float vector[3]);
void Normale(float v[3][3], float out[3]);
void MakeShadowMatrix(GLfloat points_plan[3][3],
                      GLfloat lightPos[4],
                      GLfloat destMat[4][4]);
void cube(int ombre);

#endif
