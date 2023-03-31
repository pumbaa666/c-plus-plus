/*Ce fichier contient l'implémentation de la classe LignePolygonale
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "LignePolygonale.h"

FXIMPLEMENT(LignePolygonale,ListePoints,NULL,0)

void LignePolygonale::afficher ()  {
    ListePoints::afficher();
     
	glBegin(GL_LINE_STRIP);
    for (int i=0 ; i < _longueur ; i++) {
      glVertex3f(tab[i].x,tab[i].y,tab[i].z);
    }
	
    glEnd();
  }

Point3D LignePolygonale::calculePoint(float t) const { 
  // a faire
  return Point3D();
} 
 
