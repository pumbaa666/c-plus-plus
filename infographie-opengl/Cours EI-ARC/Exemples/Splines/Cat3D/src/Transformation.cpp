/*Ce fichier contient l'implémentation de la classe Transformation
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "Transformation.h"


Transformation::Transformation( float x, 
							   float y, 
							   float z,
							   float rx, 
							   float ry, 
							   float rz, 
							   float ex, 
							   float ey, 
							   float ez) : pos_x(x),pos_y(y),pos_z(z),
							   rot_x(rx),rot_y(ry),rot_z(rz),
							   ech_x(ex),ech_y(ey),ech_z(ez) { }

Transformation::~Transformation(){ }

void Transformation::chargeIdentite(){ 
	// a faire
}

void Transformation::composeRotation(float x, float y, float z){ 
	// a faire
}

void Transformation::composeTranslation(float x, float y, float z){ 
	// a faire
}

void Transformation::composeHomothetie(float x, float y, float z){ 
	// a faire
}

Transformation& Transformation::operator=(const Transformation &t) {
	// a faire
	pos_x=t.pos_x;
	pos_y=t.pos_y;
	pos_z=t.pos_z;
	
	rot_x=t.rot_x;
	rot_y=t.rot_y;
	rot_z=t.rot_z;
	
	ech_x=t.ech_x;
	ech_y=t.ech_y;
	ech_z=t.ech_z;
	
	
	
	return *this;
}
