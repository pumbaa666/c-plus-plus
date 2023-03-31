/*Ce fichier contient l'interface de la classe CourbeeBSpline
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined COURBEBSPLINE_H
#define COURBEBSPLINE_H


#include "CourbeNURBS.h"

class CourbeBSpline : virtual public CourbeNURBS  //virtual car héritage multiple
{
	FXDECLARE(CourbeBSpline)
	/*Une courbe B-Spline est une NURBS sans notion de poids
	ou de manière équivalente, une B-Spline est une NURBS dont
	tous les poids sont égaux à 1*/

public:
	
	CourbeBSpline(const CourbeBSpline&);
	CourbeBSpline();
	CourbeBSpline(
		ListePoints &lp,
		Tableau<float> tabNoeuds, 
		int option = 1, float tolerance = 25.0
		);
	virtual ~CourbeBSpline();
	
	virtual void modifierPointCtl(int i,const Point3D &p);
	
	virtual Point3D retournerPoint(float s);
	

protected:

private:
	

};

#endif 



