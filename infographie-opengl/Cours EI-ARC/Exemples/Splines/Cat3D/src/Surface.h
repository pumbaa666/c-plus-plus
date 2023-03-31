/*Ce fichier contient l'interface de la classe Surface
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined SURFACE_H
#define SURFACE_H


#include "Objet3D.h"
#include "Point3D.h"	

//Cette classe est abstraite
class Surface : public Objet3D  
{
	FXDECLARE_ABSTRACT(Surface)  
public:
	virtual Point3D retournerPoint(float s,float t) = 0;
	//Cette méthode prend pour argument une coordonnée paramétrique 
	//(i.e. deux floats pour une surface) et renvoie le point 
	//de la surface demandée. 
	
	Surface();
	virtual ~Surface();


};

#endif 
