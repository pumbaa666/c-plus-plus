/*Ce fichier contient l'interface de la classe Segment
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef SEGMENT_H
#define SEGMENT_H

#include "LignePolygonale.h"

class Segment : public LignePolygonale {

private:
protected:
	
public:
	// constructeurs
	Segment() : LignePolygonale(2) { } 
	Segment(const Point3D &a,const Point3D &b) : LignePolygonale(2) { 
		modifierPoint(0,a);
		modifierPoint(1,b);
	} // 2 points suffise pour definir un segment
	
	// constructeur par recopie
	Segment(const Segment& s) : LignePolygonale(s) { } // comme il n'y a pas de données membres on peut utiliser celui de la classe mère 
	
	
};


#endif
