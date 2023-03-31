/*Ce fichier contient l'interface et l'implémentation de la classe CourbeBezier
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined COURBEBEZIER_H
#define COURBEBEZIER_H

#include "CourbeBezierRat.h"
#include "CourbeBSpline.h"

class CourbeBezier : 
	public CourbeBSpline, 
	public CourbeBezierRat  
{
	//C'est une courbe NURBS sans la notion de poids et de noeuds
	FXDECLARE(CourbeBezier)
public:

	CourbeBezier(const CourbeBezier& c) : CourbeBezierRat(c)
	{
		//C'est une B-Spline donc on met tous les poids à 1
		Point3D p;
		for (int i=0 ; i < fournirNbrePointsCtl();i++)
		{
			p = retournerPointCtl(i);
			p.w = 1;
			modifierPointCtl(i,p);
			
		}
	}

	CourbeBezier(ListePoints &lp, int option=0,float tolerance = 25.0) :
			CourbeNURBS(lp,
			Tableau<float>(2*lp.longueur(),0), //on initialise le tableau à 0
			option,tolerance),  // car classe virtuelle indirecte (éloignée de plus d'un niveau)
			CourbeBezierRat(lp,
			option,tolerance),  //seul le corps du constructeur de CourbeBezierRat sera exécuté
			CourbeBSpline(lp,
			Tableau<float>(),
			option,tolerance) //seul le corps du constructeur de CourbeBSpline sera exécuté
	{
	}

	CourbeBezier();
	virtual ~CourbeBezier();
	




	virtual void modifierPointCtl(int i,const Point3D &p)
	{
		CourbeBSpline::modifierPointCtl(i,p);
	}
	
	virtual Point3D retournerPoint(float s)
	{
		return CourbeBSpline::retournerPoint(s);
	}
	
	virtual void insererPointCtl(int pos,const Point3D& l)
	{
		CourbeBezierRat::insererPointCtl(pos,l);
	}

	virtual void supprimerPointCtl(int pos)
	{
		CourbeBezierRat::supprimerPointCtl(pos);
	}
	
protected:
private:
	/*on interdit l'accès à certaines fonctions héritées qui ne doivent plus servir dans cette classe
	les noeuds ne peuvent plus être modifiés*/
	void modifierNoeud(int,float) {}
	
	void fournirNoeud(int) {}

	void ajouterNoeud(float n) {}
	
	void insererNoeud(int,float) {}

	void supprimerNoeud(int) {}

	void fournirNbreNoeuds() const {}
};

#endif 
