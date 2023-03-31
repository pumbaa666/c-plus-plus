/*Ce fichier contient l'interface et l'implémentation de la classe SurfaceBezier
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined(SURFACEBEZIER_H)
#define SURFACEBEZIER_H

#include "SurfaceBezierRat.h"
#include "SurfaceBSpline.h"

class SurfaceBezier : 
	public SurfaceBezierRat, 
	public SurfaceBSpline  
{
	
	//C'est une surface NURBS sans la notion de poids et de noeuds
	FXDECLARE(SurfaceBezier)
public:
	SurfaceBezier(const SurfaceBezier& s) : SurfaceBezierRat(s)
	{
		//C'est une B-Spline donc on met tous les poids à 1
		Point3D p;
		for (int i=0 ; i < fournirNbreLignesCtl();i++)
		{
			for(int j=0 ; j< fournirNbreColonnesCtl();j++)
			{
				p = retournerPointCtl(i,j);
				p.w = 1;
				modifierPointCtl(i,j,p);
			}
		}
	}

	SurfaceBezier(MatricePoints &mp, int options=0,float tolerance = 25.0) :
			SurfaceNURBS(mp,
			Tableau<float>(2*mp.fournirNb_lignes(),0), //on initialise les deux tableaux à 0
			Tableau<float>(2*mp.fournirNb_colonnes(),0),
			options,tolerance),  // car classe virtuelle indirecte (éloignée de plus d'un niveau)
			SurfaceBezierRat(mp,options,tolerance),  //seul le corps du constructeur de SurfaceBezierRat sera exécuté
			SurfaceBSpline(mp,
			Tableau<float>(), //on initialise les deux tableaux à 0
			Tableau<float>(),
			options,tolerance) //seul le corps du constructeur de SurfaceBSpline sera exécuté
	{
	}

	SurfaceBezier();
	virtual ~SurfaceBezier();
	
	virtual void modifierPointCtl(int i,int j,const Point3D &p)
	{
		SurfaceBSpline::modifierPointCtl(i,j,p);
	}
	
	virtual Point3D retournerPoint(float s,float t)
	{
		return SurfaceBSpline::retournerPoint(s,t);
	}
	
	virtual void insererColonneCtl(int pos,const ListePoints& l)
	{
		SurfaceBezierRat::insererColonneCtl(pos,l);
	}
	virtual void insererLigneCtl(int pos,const ListePoints& l)
	{
		SurfaceBezierRat::insererLigneCtl(pos,l);
	}
	virtual void supprimerColonneCtl(int pos)
	{
		SurfaceBezierRat::supprimerColonneCtl(pos);
	}
	virtual void supprimerLigneCtl(int pos)
	{
		SurfaceBezierRat::supprimerLigneCtl(pos);
	}
	
private:
	/*on interdit l'accès à certaines fonctions héritées qui ne doivent plus servir dans cette classe
	les noeuds ne peuvent plus être modifiés*/
	void modifierNoeud_s(int,float) {}
	void modifierNoeud_t(int,float) {}
	void fournirNoeud_s(int) {}
	void fournirNoeud_t(int) {}
	void ajouterNoeud_t(float n) {}
	void ajouterNoeud_s(float n) {}
	void insererNoeud_t(int,float) {}
	void insererNoeud_s(int,float) {}
	void supprimerNoeud_t(int) {}
	void supprimerNoeud_s(int) {}
	void fournirNbreNoeuds_t() const {}
	void fournirNbreNoeuds_s() const {}

};

#endif 
