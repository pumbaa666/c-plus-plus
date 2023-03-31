/*Ce fichier contient l'implémentation de la classe CourbeBezierRat
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#include "CourbeBezierRat.h"


FXIMPLEMENT(CourbeBezierRat,CourbeNURBS,NULL,0)

CourbeBezierRat::CourbeBezierRat()
{

}

CourbeBezierRat::~CourbeBezierRat()
{

}

CourbeBezierRat::CourbeBezierRat(ListePoints &lp, int option, float tolerance):
		CourbeNURBS(lp,
			Tableau<float>(2*lp.longueur(),0), //on initialise le tableau à 0
						option,tolerance)
{
	/*pour une bézier, les deux tableaux de noeuds ont pour dimension le double des dimensions de la
	liste de contrôle. Le tableau est rempli de la manière suivante {0,0,0,0,...,0,1,...,1,1,1,1}*/
	int n = _tabNoeuds.taille();
	int i;
	for(i = n/2 ;i < n ;i++)
	{
		_tabNoeuds[i] = 1;
	}
	
}

CourbeBezierRat::CourbeBezierRat(const CourbeBezierRat &c) : CourbeNURBS(c)
{

}

void CourbeBezierRat::insererPointCtl(int pos,const Point3D& p)
{
	CourbeAPoles::insererPointCtl(pos,p);
	//pour rester cohérent avec les ordres on augmente l'ordre de 1
	_ordre++;
	//le tableau de noeud est augmenté de 2 éléments
	_tabNoeuds.ajouter(1);
	_tabNoeuds.inserer(0,0);
}



void CourbeBezierRat::supprimerPointCtl(int pos)
{
	CourbeAPoles::supprimerPointCtl(pos);
	//pour rester cohérent on diminue l'ordre de 1
	_ordre--;
	_tabNoeuds.supprimer(0);
	_tabNoeuds.supprimer(_tabNoeuds.taille() -1);
}



