// Fichier Geometrie.h
#ifndef GEOMETRIE_H
#define GEOMETRIE_H

void drawFloor();
void DessinerLesAxes();
void DessinerLaScene();
void DessinerLesMurs();
void DessinerLeToit();
void DessinerLeSol();
void ModeDeDessin(int mask);
void PositionLumiere(float x, float y, float z, float w, bool visible);

#endif
