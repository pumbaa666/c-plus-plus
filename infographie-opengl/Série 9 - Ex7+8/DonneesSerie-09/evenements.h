// Fichier Evenements.h
#ifndef EVENEMENTS_H
#define EVENEMENTS_H

void Animate();
void evTimer(int valeur);
void Display();
void Reshape(int, int);
void Mouse(int, int, int, int);
void Motion(int, int);
void Keyboard(unsigned char key, int x, int y );
void ToucheSpecial(int, int, int);
void DeplacerLaCamera(GLfloat d, GLfloat Theta);

#endif
