/*Ce fichier contient l'implémentation de la classe Objet3D
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "Objet3D.h"
#include <stdlib.h>

int Objet3D::compteur=0;

extern FXColor fxcolorfromname(const FXchar* colorname);

const char *noms_couleurs[]={"Red",
			     "Orange",
			     "Yellow",
			     "Green",
			     "Blue",
			     "Violet",
			     "Gray",
			     "Cyan",
			     "DarkBlue",
			     "Pink",
			     "Purple",
			     "Turquoise",
			     "Wheat",
			     "Magenta",
			     "Gold",
			     "Firebrick",
			     "DarkRed",
			     "DarkGreen",
			     "LightGreen",
			     "LightBlue"};


FXIMPLEMENT_ABSTRACT(Objet3D,FXGLShape,NULL,0)

Objet3D::Objet3D() : FXGLShape(0,0,0,SURFACE_SINGLESIDED | SHADING_SMOOTH | FACECULLING_OFF |STYLE_SURFACE)
{
	// donne une couleur différente pour chaque objet créé
	material[0].diffuse=fxcolorfromname(noms_couleurs[rand()% ARRAYNUMBER(noms_couleurs)]);
	material[1].diffuse=fxcolorfromname(noms_couleurs[rand()% ARRAYNUMBER(noms_couleurs)]);

	range[0][0]=-1;  
	range[1][0]=-1;
	range[2][0]=-1;
	range[0][1]=1;  
	range[1][1]=1;
	range[2][1]=1;

ID_unique=compteur++;	
}


Objet3D::Objet3D(const Objet3D& o) : FXGLShape(o) {

transfoAssociee=o.transfoAssociee;
ID_unique=compteur++;
}


Objet3D::~Objet3D(){

}

void Objet3D::dimensionner(float x,float y,float z) {
  transfoAssociee.composeHomothetie(x,y,z);

}

void Objet3D::tourner(float x,float y,float z) {
  transfoAssociee.composeRotation(x,y,z);

}

void Objet3D::translater(float x,float y,float z) {
  transfoAssociee.composeTranslation(x,y,z);
}

void Objet3D::drawshape(FXGLViewer*) {
// glLoadMatrix(transfoAssociee.fournirMatrice);
	afficher();
}

void Objet3D::save(FXStream& store) const {
	FXGLShape::save(store);
	// sauvegarde de la transfoAssociee
	store << transfoAssociee.pos_x << transfoAssociee.pos_y << transfoAssociee.pos_z;
	store << transfoAssociee.rot_x << transfoAssociee.rot_y << transfoAssociee.rot_z;
	store << transfoAssociee.ech_x << transfoAssociee.ech_y << transfoAssociee.ech_z;

}


void Objet3D::load(FXStream& store) {
	FXGLShape::load(store);
	// chargement de la transfoAssociee
	store >> transfoAssociee.pos_x >> transfoAssociee.pos_y >> transfoAssociee.pos_z;
	store >> transfoAssociee.rot_x >> transfoAssociee.rot_y >> transfoAssociee.rot_z;
	store >> transfoAssociee.ech_x >> transfoAssociee.ech_y >> transfoAssociee.ech_z;

}


Objet3D& Objet3D::operator=(const Objet3D& o) {
  FXGLShape::operator=(o);

transfoAssociee=o.transfoAssociee;


  return *this;

}

