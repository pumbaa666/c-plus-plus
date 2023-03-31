/*Ce fichier contient l'implémentation de la classe SurfaceBSpline
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "CourbeBSpline.h"

FXIMPLEMENT(CourbeBSpline,CourbeNURBS,NULL,0)

CourbeBSpline::CourbeBSpline()
{

}

CourbeBSpline::~CourbeBSpline()
{

}

void CourbeBSpline::modifierPointCtl(int i,const Point3D &p)
{
	Point3D tmp=p;
	tmp.w = 1; //car c'est une B-Spline
	CourbeNURBS::modifierPointCtl(i,tmp);
}

CourbeBSpline::CourbeBSpline(ListePoints &lp, Tableau<float> tabNoeuds, int option,float tolerance) : 
		CourbeNURBS(lp,tabNoeuds,option,tolerance)
{
	//C'est une B-Spline donc on met tous les poids à 1
	Point3D p;
	for (int i=0 ; i < fournirNbrePointsCtl();i++)
	{
		p = retournerPointCtl(i);
		modifierPointCtl(i,p);

	}

}

Point3D CourbeBSpline::retournerPoint(float s)
/*cette fonction est pratiquement identique à celle
de CourbeNURBS mais on enlève tous les calculs utilisant
les poids*/
{
	int i;
	float xx;
	int l = fournirNbrePointsCtl();
	Point3D pcal,tmp;   /*Point calculé : pcal*/
	
	/*positionnement par rapport aux vecteurs de noeuds */
	i = posit(s);
	
	
	if (i>0) 
	{
	/*         calcul des k bsplines non nulles                  */
		calbsp(_tabNoeuds,s,i,_ordre,_table_fonctions);
		
		pcal.x = 0.0;
		pcal.y = 0.0;
		pcal.z = 0.0;

		
			//ical1=(*iv-kv+j)*(nu+1)+*iu-ku;
			for (int i=1 ; i <= _ordre ; i++)
			{
				xx = _table_fonctions[i]; //à vérifier
				//ical2=ical1+i;
				tmp = retournerPointCtl(i - _ordre + i );
				pcal.x = pcal.x + xx * tmp.x; //xcontr[ical2];
				pcal.y = pcal.y + xx * tmp.y; //ycontr[ical2];
				pcal.z = pcal.z + xx * tmp.z; //zcontr[ical2];
			}
		
	}
	return pcal;
}

CourbeBSpline::CourbeBSpline(const CourbeBSpline &c) : CourbeNURBS(c)
{
	//C'est une B-Spline donc on met tous les poids à 1
	Point3D p;
	for (int i=0 ; i < fournirNbrePointsCtl();i++)
	{
		p = retournerPointCtl(i);
		modifierPointCtl(i,p);
	
	}
}
