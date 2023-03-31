/*Ce fichier contient l'implémentation de la classe SurfacePolyedrique
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "SurfacePolyedrique.h"


FXIMPLEMENT(SurfacePolyedrique,MatricePoints,NULL,0)


SurfacePolyedrique::~SurfacePolyedrique() {

}

void SurfacePolyedrique::afficher()  {
   MatricePoints::afficher(); // affiche d'abord tout les sommets
   Point3D tmp;
    
      // d'abord les lignes horizontales
	for (int i=0 ; i < nb_lignes ; i++) {
		glBegin(GL_LINE_STRIP);	
	 for (int j=0 ; j < nb_colonnes ; j++) {
		tmp=retournerPoint(i,j);
		glVertex3f(tmp.x, tmp.y, tmp.z );
	  }
	glEnd();
	}
    
	
	// puis les lignes verticales
	for (int j=0 ; j < nb_colonnes ; j++) {
	glBegin(GL_LINE_STRIP);	for (int i=0 ; i < nb_lignes ; i++) {
    		tmp=retournerPoint(i,j);
			glVertex3f(tmp.x, tmp.y, tmp.z );
		 }
	 

    

    glEnd();
  }
	 
}

Point3D SurfacePolyedrique::calculePoint(float u,float v) const {
  // a faire
  return Point3D();
}
