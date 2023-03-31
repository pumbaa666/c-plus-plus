// Loïc Correvon
// Fichier Evenements.h
#ifndef EVENEMENTS_H
#define EVENEMENTS_H

void evTimer(int valeur);
void Display();
void MyReshape(int, int);
void Souris(int, int, int, int);
void DeplacerSouris(int, int);
void Key(unsigned char key, int x, int y );
void ToucheSpecial(int, int, int);
void DeplacerLaCamera(GLfloat d, GLfloat Theta);

#endif
