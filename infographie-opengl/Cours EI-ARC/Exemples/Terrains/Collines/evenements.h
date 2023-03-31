// Fichier Evenenements.h
#ifndef EVENEMENTS_H
#define EVENEMENTS_H

void Afficher(int);
void display();
void myReshape(int, int);
void Souris(int, int, int, int);
void DeplacerSouris(int, int);
void Key(unsigned char key, int x, int y );
void ToucheSpecial(int, int, int);
void DeplacerLaCamera(GLfloat d, GLfloat Theta);

#endif
