#include "Polygone.h"

FXIMPLEMENT(Polygone,LignePolygonale,NULL,0)

void Polygone::afficher ()  {
   
    ListePoints::afficher(); // affiche les sommets
 
    glBegin(GL_LINE_LOOP);
    for (int i=0 ; i < _longueur ; i++) {
      glVertex3f(tab[i].x,tab[i].y,tab[i].z);
    }
    glEnd();
 }

Point3D Polygone::calculePoint(float t) const { 
  // a faire
  return Point3D();
} 
 
