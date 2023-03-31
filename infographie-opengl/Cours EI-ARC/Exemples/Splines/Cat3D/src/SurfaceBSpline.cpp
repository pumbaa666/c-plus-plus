/*Ce fichier contient l'implémentation de la classe SurfaceBSpline
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#include "SurfaceBSpline.h"

FXIMPLEMENT(SurfaceBSpline,SurfaceNURBS,NULL,0)

SurfaceBSpline::SurfaceBSpline()
{

}

SurfaceBSpline::~SurfaceBSpline()
{

}

void SurfaceBSpline::modifierPointCtl(int i, int j,const Point3D &p)
{
	Point3D tmp=p;
	tmp.w = 1; //car c'est une B-Spline
	SurfaceNURBS::modifierPointCtl(i,j,tmp);
}

SurfaceBSpline::SurfaceBSpline(MatricePoints &mp, Tableau<float> tabNoeuds_s, Tableau<float> tabNoeuds_t, int options,float tolerance) : 
		SurfaceNURBS(mp,tabNoeuds_s,tabNoeuds_t,options,tolerance)
{
	//C'est une B-Spline donc on met tous les poids à 1
	Point3D p;
	for (int i=0 ; i < fournirNbreLignesCtl();i++)
	{
		for(int j=0 ; j< fournirNbreColonnesCtl();j++)
		{
			p = retournerPointCtl(i,j);
			modifierPointCtl(i,j,p);
		}
	}

}

Point3D SurfaceBSpline::retournerPoint(float s, float t)
/*cette fonction est la pratiquement identique à celle
de surfaceNURBS mais on enlève tous les calculs utilisant
les poids*/
{
	int is,it;
	float xx;
	int l = fournirNbreLignesCtl();
	int c = fournirNbreColonnesCtl();
	Point3D pcal,tmp;   /*Point calculé : pcal*/
	
	/*positionnement par rapport aux vecteurs de noeuds */
	is = posit_s(s);
	it = posit_t(t);;
	
	if ((is>0) && (it>0))
	{
	/*                  calcul des k bsplines non nulles                  */
		calbsp(_tabNoeuds_s,s,is,_ordre_s,_table_fonctions_s);
		calbsp(_tabNoeuds_t,t,it,_ordre_t,_table_fonctions_t);

		pcal.x = 0.0;
		pcal.y = 0.0;
		pcal.z = 0.0;

		for (int j=1 ; j <= _ordre_t ; j++)
		{
			//ical1=(*iv-kv+j)*(nu+1)+*iu-ku;
			for (int i=1 ; i <= _ordre_s ; i++)
			{
				xx = _table_fonctions_s[i] * _table_fonctions_t[j];
				//ical2=ical1+i;
				tmp = retournerPointCtl(is - _ordre_s + i , it - _ordre_t + j);
				pcal.x = pcal.x + xx * tmp.x; //xcontr[ical2];
				pcal.y = pcal.y + xx * tmp.y; //ycontr[ical2];
				pcal.z = pcal.z + xx * tmp.z; //zcontr[ical2];
			}
		}
	}
	return pcal;
}

SurfaceBSpline::SurfaceBSpline(const SurfaceBSpline &s) : SurfaceNURBS(s)
{
	//C'est une B-Spline donc on met tous les poids à 1
	Point3D p;
	for (int i=0 ; i < fournirNbreLignesCtl();i++)
	{
		for(int j=0 ; j< fournirNbreColonnesCtl();j++)
		{
			p = retournerPointCtl(i,j);
			modifierPointCtl(i,j,p);
		}
	}
}
