/*Ce fichier contient l'interface de la classe SurfaceBSpline
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined(SURFACEBSPLINE_H)
#define SURFACEBSPLINE_H

#include "SurfaceNURBS.h"

class SurfaceBSpline : virtual public SurfaceNURBS  
{
	FXDECLARE(SurfaceBSpline)
	/*Une surface B-Spline est une NURBS sans notion de poids
	ou de manière équivalente, une B-Spline est une NURBS dont
	tous les poids sont égaux à 1*/
public:
	SurfaceBSpline(const SurfaceBSpline&);
	SurfaceBSpline();
	SurfaceBSpline(
		MatricePoints &mp,
		Tableau<float> tabNoeuds_s, Tableau<float> tabNoeuds_t,
		int options = 0, float tolerance = 25.0
		);
	virtual ~SurfaceBSpline();
	
	virtual void modifierPointCtl(int i,int j,const Point3D &p);
	
	virtual Point3D retournerPoint(float s,float t);
	
};

#endif 
