/*Ce fichier contient l'interface de la classe Objet3D
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef OBJET3D_H
#define OBJET3D_H
#include "fx.h"
#include "fx3d.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "Transformation.h"

class Objet3D : public FXGLShape
{
	FXDECLARE_ABSTRACT(Objet3D);
private:
	static int compteur;
protected:
	int ID_unique;
	Transformation transfoAssociee;
	
public:
	// constructeur
	Objet3D() ;
	// constructeur par recopie 
	Objet3D(const Objet3D& o); 
	
	// destructeur
	virtual ~Objet3D();
	
	// methodes
	
	void tourner(float x, float y, float z);
	void dimensionner(float x,float y,float z);
	void translater(float x,float y, float z);
	
	virtual void afficher()  = 0;
	virtual void drawshape(FXGLViewer*);
	
	// pour sauvegarder/charger une liste sous FOX
	void save(FXStream& store) const;
	void load(FXStream& store);
	
	virtual Objet3D& operator=(const Objet3D&);
	
};

#endif
