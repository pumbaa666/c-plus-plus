/*Ce fichier contient l'implémentation de la classe SurfaceBezierRat
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#include "SurfaceBezierRat.h"

FXIMPLEMENT(SurfaceBezierRat,SurfaceNURBS,NULL,0)

SurfaceBezierRat::SurfaceBezierRat()
{

}

SurfaceBezierRat::~SurfaceBezierRat()
{

}

SurfaceBezierRat::SurfaceBezierRat(MatricePoints &mp, int options, float tolerance):
		SurfaceNURBS(mp,
			Tableau<float>(2*mp.fournirNb_lignes(),0), //on initialise les deux tableaux à 0
			Tableau<float>(2*mp.fournirNb_colonnes(),0),
			options,tolerance)
{
	/*pour une bézier, les deux tableaux de noeuds ont pour dimension le double des dimensions de la
	matrice de contrôle. De plus chaque tableau est rempli de la manière suivante {0,0,0,0,...,0,1,...,1,1,1,1}*/
	int n = _tabNoeuds_s.taille();
	int i;
	for(i = n/2 ;i < n ;i++)
	{
		_tabNoeuds_s[i] = 1;
	}
	n = _tabNoeuds_t.taille();
	for(i= n/2 ;i < n ;i++)
	{
		_tabNoeuds_t[i] = 1;
	}	
}

SurfaceBezierRat::SurfaceBezierRat(const SurfaceBezierRat &s) : SurfaceNURBS(s)
{

}

void SurfaceBezierRat::insererColonneCtl(int pos,const ListePoints& l)
{
	SurfaceAPoles::insererColonneCtl(pos,l);
	//pour rester cohérent avec les ordres on augmente l'ordre de 1
	_ordre_t++;
	//le tableau de noeud est augmenté de 2 éléments
	_tabNoeuds_t.ajouter(1);
	_tabNoeuds_t.inserer(0,0);
}

void SurfaceBezierRat::insererLigneCtl(int pos,const ListePoints& l)
{
	SurfaceAPoles::insererLigneCtl(pos,l);
	//pour rester cohérent avec les ordres on augmente l'ordre de 1
	_ordre_s++;
	//le tableau de noeud est augmenté de 2 éléments
	_tabNoeuds_s.ajouter(1);
	_tabNoeuds_s.inserer(0,0);
}

void SurfaceBezierRat::supprimerColonneCtl(int pos)
{
	SurfaceAPoles::supprimerColonneCtl(pos);
	//pour rester cohérent avec les ordres on diminue l'ordre de 1
	_ordre_t--;
	_tabNoeuds_t.supprimer(0);
	_tabNoeuds_t.supprimer(_tabNoeuds_t.taille() -1);
}

void SurfaceBezierRat::supprimerLigneCtl(int pos)
{
	SurfaceAPoles::supprimerLigneCtl(pos);
	//pour rester cohérent avec les ordres on diminue l'ordre de 1
	_ordre_s--;
	_tabNoeuds_s.supprimer(0);
	_tabNoeuds_s.supprimer(_tabNoeuds_s.taille() -1);
}

