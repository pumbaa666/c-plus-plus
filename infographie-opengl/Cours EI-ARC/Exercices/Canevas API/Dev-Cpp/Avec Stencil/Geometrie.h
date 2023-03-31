// Fichier Geometrie.h

#ifndef GEOMETRIE_H
#define GEOMETRIE_H

void DessinerLesAxes();
void DessinerLaScene();
void DessinerLeSol();
void ModeDeDessin(int mask);
void DessinerLesMurs();
void DessinerLeToit();
void PositionLumiere(float x, float y, float z, float w, bool visible = true);

#endif

