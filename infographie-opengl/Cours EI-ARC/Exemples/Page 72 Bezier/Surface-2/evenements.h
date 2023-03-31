// Fichier Evenements.h

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

void Display (void);
void Reshape (int w, int h);
void Keyboard(unsigned char key, int /*x*/, int /*y*/);
void Souris(int, int, int, int);
void DeplacerSouris(int, int);
void ToucheSpecial(int, int, int);
void DeplacerLaCamera(GLfloat d, GLfloat Theta);

#endif
