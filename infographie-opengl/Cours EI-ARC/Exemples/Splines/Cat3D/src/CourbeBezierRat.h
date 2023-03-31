/*Ce fichier contient l'interface de la classe CourbeBezierRat
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined(COURBEBEZIERRAT_H)


#define COURBEBEZIERRAT_H


#include "CourbeNURBS.h"

class CourbeBezierRat :virtual public CourbeNURBS  //virtual car héritage multiple
{
	/*Cette courbe est une courbe NURBS sans la notion de noeuds. 
	En fait, le tableau de noeuds a une forme très particulière. 
	La longueur du tableau est constituée d'une première moitié 
	dont les éléments sont tous égaux à 0 et d'une deuxième moitié 
	dont tous les éléments sont égaux à 1. 
	De plus l' ordre est égal à la longueur de la liste de points de contrôle.
	*/
FXDECLARE(CourbeBezierRat)
public:
	virtual void insererPointCtl(int pos,const Point3D &p);
	virtual void supprimerPointCtl(int pos);

	//Constructeurs /Destructeur
	CourbeBezierRat(const CourbeBezierRat&);
	CourbeBezierRat(ListePoints &lp, int otpion=1,float tolerance = 25.0);
	CourbeBezierRat();
	virtual ~CourbeBezierRat();

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
