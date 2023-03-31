/*Ce fichier contient l'interface de la classe SurfaceBezierRat
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined(SURFACEBEZIERRAT_H)


#define SURFACEBEZIERRAT_H

#include "SurfaceNURBS.h"

class SurfaceBezierRat : virtual public SurfaceNURBS  
{
	/*Cette surface est une surface NURBS sans la notion de noeuds. 
	En fait, les tableaux de noeuds ont une forme très particulière. 
	La longueur du tableau est constitué d'une première moitié 
	dont les éléments sont tous égaux à 0 et d'une deuxième moitié 
	dont tous les éléments sont égaux à 1. 
	De plus les ordres sont égaux aux dimensions de la matrice de contrôle.
	*/
	FXDECLARE(SurfaceBezierRat)
public:
	virtual void insererColonneCtl(int pos,const ListePoints& l);
	virtual void insererLigneCtl(int pos,const ListePoints& l);
	virtual void supprimerColonneCtl(int pos);
	virtual void supprimerLigneCtl(int pos);
	
	//Constructeurs /Destructeur
	SurfaceBezierRat(const SurfaceBezierRat&);
	SurfaceBezierRat(MatricePoints &mp, int options=0,float tolerance = 25.0);
	SurfaceBezierRat();
	virtual ~SurfaceBezierRat();

protected:
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
