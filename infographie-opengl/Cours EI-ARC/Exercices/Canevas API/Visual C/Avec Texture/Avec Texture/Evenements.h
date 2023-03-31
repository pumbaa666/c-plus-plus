// Fichier Evenements.h

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

void ReSizeGLScene(int width, int height);
void Display(void);
void EvKeyDown(unsigned char key);
void Animation(int);
void EvMouseMove(int x, int y, int & xOld, int & yOld, bool, bool);
void DeplacerLaCamera(float d, float Theta);

#endif

