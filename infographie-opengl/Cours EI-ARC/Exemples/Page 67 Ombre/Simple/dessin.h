// Fichier Dessin.h

#ifndef DESSIN_H
#define DESSIN_H

void Vecteur_Unite(float vector[3]);
void Normale(float v[3][3], float out[3]);
void MakeShadowMatrix(GLfloat points_plan[3][3],
                      GLfloat lightPos[4],
                      GLfloat destMat[4][4]);
void cube(int ombre);
void drawFloor();

#endif
