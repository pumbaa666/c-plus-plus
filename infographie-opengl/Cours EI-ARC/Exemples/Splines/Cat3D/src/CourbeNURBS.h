/*Ce fichier contient l'interface de la classe CourbeNURBS
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#if !defined COURBENURBS_H
#define COURBENURBS_H

#include "CourbeAPoles.h"
#include <exception>
#include "GL/glu.h"
#include "GL/gl.h"

#include "Point3D.h"

#include "Tableau.h" 

//les options d'affichage d'une courbe NURBS
#define		FIL_DE_FER  1
#define		DESSINER_LIGNE_POLYGONALE  2

class CourbeNURBS : public CourbeAPoles  
{
//Cette classe permet la définition d'une courbe B-Spline rationnelle.
	FXDECLARE(CourbeNURBS)
public:
	//Les exceptions
	class DepassementTableau : public exception {};
	class ToleranceIncorrect : public exception{};
	class NoeudsIncorrects :  public exception {};
	
	//procédures permettant les manipulations sur le tableau de noeuds
	void ajouterNoeud(float n);
	void insererNoeud(int,float);
	void supprimerNoeud(int);
	
	//procédure permettant les manipulations sur la liste de contrôle
	virtual void insererPointCtl(int pos,const Point3D &p);
	virtual void supprimerPointCtl(int pos);
		
	//Constructeurs /Destructeur
	CourbeNURBS(const CourbeNURBS& l);
	
	CourbeNURBS(
		ListePoints &lp,
		Tableau<float> tabNoeuds,
		int options = 0,
		float tolerance = 25.0
		);
	CourbeNURBS();
	virtual ~CourbeNURBS();
	
	int options() const;  //retourne les options de la courbe
	void options(int val); //modifie les options 
	
	//Modifieurs
	void modifierTolEch(float t);
	void modifierNoeud(int pos,float val);

	//Fournisseurs
	float fournirTolEch(void) const;
	int fournirOrdre(void) const;
	float fournirNoeud(int pos) const;
	int fournirNbreNoeuds() const;
	
	CourbeNURBS & operator =(CourbeNURBS &s);
	
	
	virtual Point3D retournerPoint(float s);
	virtual void save(FXStream &store) const;
	virtual void load(FXStream &store);
	virtual void afficher(void);
	
protected:

	int _options; 
	Tableau<float> _tabNoeuds;
	int _ordre;
	Tableau<float> _table_fonctions;
	int posit(float);
	void calbsp(Tableau<float>& vknot,float t,int i,int k,Tableau<float>& b);
	float _tolEch;
private:
	int  _idCourbe;
};

#endif
