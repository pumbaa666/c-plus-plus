/*Ce fichier contient l'interface de la classe Surface
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, D�partement ES2I, Promotion 2002
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
	//Cette m�thode prend pour argument une coordonn�e param�trique 
	//(i.e. deux floats pour une surface) et renvoie le point 
	//de la surface demand�e. 
	
	Surface();
	virtual ~Surface();


};

#endif 
