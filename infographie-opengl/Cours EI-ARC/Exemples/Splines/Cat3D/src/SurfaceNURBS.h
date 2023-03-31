/*Ce fichier contient l'interface de la classe SurfaceNURBS
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined SURFACENURBS_H
#define SURFACENURBS_H

#include <exception>
#include "SurfaceAPoles.h"
#include "GL/glu.h"
#include "GL/gl.h"
#include "Tableau.h"
#define SURFACENURBS 5

#include "Point3D.h"	

//les options d'affichage d'une surface NURBS
#define		FIL_DE_FER  1
#define		DESSINER_SURFACE_POLYEDRIQUE  2


class SurfaceNURBS : public SurfaceAPoles 
//Cette classe permet la définition d'une surface B-Spline rationnelle. 
{
	FXDECLARE(SurfaceNURBS)
public:
	//Les exceptions
	class DepassementTableau : public exception {};
	class ToleranceIncorrect : public exception{};
	class NoeudsIncorrects :  public exception {};

	//procédures permettant les manipulations sur les tableaux de noeuds	
	void ajouterNoeud_t(float n);
	void ajouterNoeud_s(float n);
	void insererNoeud_t(int,float);
	void insererNoeud_s(int,float);
	void supprimerNoeud_t(int);
	void supprimerNoeud_s(int);

	//procédure permettant les manipulations sur la matrice de contrôle
	virtual void insererColonneCtl(int pos,const ListePoints& l);
	virtual void insererLigneCtl(int pos,const ListePoints& l);
	virtual void supprimerColonneCtl(int pos);
	virtual void supprimerLigneCtl(int pos);
	
	//Constructeurs /Destructeur
	SurfaceNURBS(const SurfaceNURBS& s);
	SurfaceNURBS(
		MatricePoints &mp,
		Tableau<float> tabNoeuds_s,
		Tableau<float> tabNoeuds_t,
		int options = 0, float tolerance = 25.0);
	SurfaceNURBS();
	virtual ~SurfaceNURBS();
	
	//Modifieurs
	void modifierTolEch(float t);
	void modifierNoeud_t(int pos,float val);
	void modifierNoeud_s(int pos,float val);


	//Fournisseurs
	float fournirTolEch(void) const;
	int fournirOrdre_t(void) const;
	int fournirOrdre_s(void) const;
	float fournirNoeud_t(int pos) const;
	float fournirNoeud_s(int pos) const;
	int fournirNbreNoeuds_t() const;
	int fournirNbreNoeuds_s() const;
	
	int options() const;  //retourne les options de la surface
	void options(int val); //modifie les options 
	
	
	virtual Point3D retournerPoint(float s,float t);
	virtual void save(FXStream &store) const;
	virtual void load(FXStream &store);
	virtual void afficher(void);
	
	SurfaceNURBS & operator =(SurfaceNURBS &s);

protected:
	
	int _options;      //Si l'affichage de la NURBS est Pleine ou en fil de fer, etc...
	Tableau<float> _tabNoeuds_t;
	Tableau<float> _tabNoeuds_s;
	int _ordre_s;
	int _ordre_t;	
	Tableau<float> _table_fonctions_t;  //pour la méthode qui calcule un point de la surface
	Tableau<float> _table_fonctions_s;
	int posit_s(float);  //ces methodes sont utilisées afin de calculer un point de la surface
	int posit_t(float);
	void calbsp(Tableau<float>& vknot,float t,int i,int k,Tableau<float>& b);
	float _tolEch;
private:
	int  _idSurface;  //Numéro d'identification de DisplayList
};

#endif
