/*Ce fichier contient l'interface de la classe CourbeBezierRat
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, D�partement ES2I, Promotion 2002
*/

#if !defined(COURBEBEZIERRAT_H)


#define COURBEBEZIERRAT_H


#include "CourbeNURBS.h"

class CourbeBezierRat :virtual public CourbeNURBS  //virtual car h�ritage multiple
{
	/*Cette courbe est une courbe NURBS sans la notion de noeuds. 
	En fait, le tableau de noeuds a une forme tr�s particuli�re. 
	La longueur du tableau est constitu�e d'une premi�re moiti� 
	dont les �l�ments sont tous �gaux � 0 et d'une deuxi�me moiti� 
	dont tous les �l�ments sont �gaux � 1. 
	De plus l' ordre est �gal � la longueur de la liste de points de contr�le.
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
	/*on interdit l'acc�s � certaines fonctions h�rit�es qui ne doivent plus servir dans cette classe
	les noeuds ne peuvent plus �tre modifi�s*/
	void modifierNoeud(int,float) {}

	void fournirNoeud(int) {}
	
	void ajouterNoeud(float n) {}
	
	void insererNoeud(int,float) {}
	
	void supprimerNoeud(int) {}
	
	void fournirNbreNoeuds() const {}

};

#endif 
