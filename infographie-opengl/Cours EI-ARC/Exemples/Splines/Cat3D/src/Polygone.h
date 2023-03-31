/*Ce fichier contient l'interface de la classe Polygone
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef POLYGONE_H
#define POLYGONE_H

#include "LignePolygonale.h"

class Polygone : public LignePolygonale {
 FXDECLARE(Polygone);

private:
protected:
public:
  // constructeurs
  Polygone(int l=0) : LignePolygonale(l) { } // en temps normal, il faudrait verifier que l'argument a une bonne valeur
  Polygone(Point3D t[],int l): LignePolygonale(t,l) { } 
// pour creer une ligne polygonale de point à partir d'un tableau de point3D
  Polygone(const ListePoints& lp) : LignePolygonale(lp) { }

  // destructeur
  virtual ~Polygone() { }


 virtual void afficher ();
  
 virtual Point3D calculePoint(float t) const; 

};


#endif
