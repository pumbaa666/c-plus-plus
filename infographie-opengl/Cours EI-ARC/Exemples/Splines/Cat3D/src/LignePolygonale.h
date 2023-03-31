/*Ce fichier contient l'interface de la classe LignePolygonale
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef LIGNEPOLYGONALE_H
#define LIGNEPOLYGONALE_H

#include "ListePoints.h"

class LignePolygonale : public ListePoints {
 FXDECLARE(LignePolygonale);
private:
protected:

public:
  // constructeurs
  LignePolygonale(int l=0) : ListePoints(l) { } 
  LignePolygonale(Point3D t[],int l): ListePoints(t,l) { } // pour creer une ligne polygonale de point à partir d'un tableau de point3D
  LignePolygonale(const ListePoints& lp) : ListePoints(lp) { }

  // destructeur
  virtual ~LignePolygonale() {}

  // méthodes
  virtual void afficher ();
 
  virtual Point3D calculePoint(float t) const ; 
 
};


#endif
