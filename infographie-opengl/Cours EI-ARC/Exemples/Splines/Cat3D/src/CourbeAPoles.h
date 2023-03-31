/*Ce fichier contient l'interface de la classe CourbeAPoles
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#if !defined COURBEAPOLES_H
#define COURBEAPOLES_H

#include "Point3D.h"
#include "Courbe.h"
#include "LignePolygonale.h"

class CourbeAPoles : public Courbe 
{
	FXDECLARE(CourbeAPoles)
public:
	//	Les méthodes liées à la Courbe de contrôle
	int fournirNbrePointsCtl() const;
	virtual void insererPointCtl(int pos,const Point3D &p);
	virtual void supprimerPointCtl(int pos);
	Point3D retournerPointCtl(int s);
	virtual Point3D fournirPointCtl(int i);

	virtual void modifierPointCtl(int i,Point3D &P);
	
	virtual Point3D retournerPoint(float s);

	virtual void afficher();

	//Constructeurs /Destructeur
	CourbeAPoles(ListePoints &);
	CourbeAPoles(const CourbeAPoles&);
	CourbeAPoles();
	virtual ~CourbeAPoles();

	//Sauvegarde et Chargement d'une Courbe à pôles
	virtual void save(FXStream &store) const;
	virtual void load(FXStream &store);
	
	void calculerBoiteEnglobante();
	
	CourbeAPoles & operator =(const CourbeAPoles &s);
	
private:
	
	LignePolygonale _CourbeCtl;
protected:
	float * retournerPtrCtl();
	//Cette méthode permet de retourner un pointeur 
	//sur un tableau,de l'objet _CourbeCtl, dédiée à l'affichage OpenGL.
	bool _estModifie;
	//Ce booléen permet de savoir si l'on a modifié 
	//la Courbe depuis la dernière modification. 
};

#endif 
