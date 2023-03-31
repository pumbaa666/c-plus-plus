/*Ce fichier contient l'interface de la classe abstraite Courbe
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/


#if !defined COURBE_H
#define COURBE_H


#include "Objet3D.h"
#include "Point3D.h"

//Cette classe est abstraite
class Courbe  : public Objet3D
{
	FXDECLARE_ABSTRACT(Courbe)  
public:
	virtual Point3D retournerPoint(float s) = 0;
	//Cette méthode prend pour argument une coordonnée paramétrique 
	//(i.e. un float pour une courbe) et renvoie le point 
	//de la courbe demandée. 
	Courbe();
	virtual ~Courbe();
	

};

#endif 
