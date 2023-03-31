/*Ce fichier contient l'interface de la classe SurfaceAPoles
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/


#if !defined SURFACEAPOLES_H
#define SURFACEAPOLES_H


#include "Surface.h"
#include "SurfacePolyedrique.h"
#include "Point3D.h"

class SurfaceAPoles : public Surface 
{
	FXDECLARE(SurfaceAPoles)
public:
	//	Les méthodes liées à la surface de contrôle
	int fournirNbreColonnesCtl() const;
	int fournirNbreLignesCtl() const;
	virtual void insererColonneCtl(int pos,const ListePoints& l);
	virtual void insererLigneCtl(int pos,const ListePoints& l);
	virtual void supprimerColonneCtl(int pos);
	virtual void supprimerLigneCtl(int pos);
	Point3D retournerPointCtl(int s,int t);
	virtual Point3D fournirPointCtl(int i,int j);
	virtual void modifierPointCtl(int i,int j,Point3D &P);

	virtual Point3D retournerPoint(float s,float t);
	virtual void afficher();

	//Constructeurs /Destructeur
	SurfaceAPoles(MatricePoints &mp);
	SurfaceAPoles(const SurfaceAPoles&);
	SurfaceAPoles();
	virtual ~SurfaceAPoles();

	//Sauvegarde et Chargement d'une surface à pôles
	virtual void save(FXStream &store) const;
	virtual void load(FXStream &store);
	
	void calculerBoiteEnglobante();
	
	SurfaceAPoles & operator =(const SurfaceAPoles &s);
	
private:
	
	SurfacePolyedrique _surfaceCtl;
protected:
	float * retournerPtrCtl();
	//Cette méthode permet de retourner un pointeur 
	//sur un tableau,de l'objet _surfaceCtl, dédié à l'affichage OpenGL.
	bool _estModifie;
	//Ce booléen permet de savoir si l'on a modifié 
	//la surface depuis la dernière modification. 
};

#endif 
