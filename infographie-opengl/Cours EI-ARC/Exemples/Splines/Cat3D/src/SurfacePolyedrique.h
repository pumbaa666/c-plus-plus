/*Ce fichier contient l'interface de la classe SurfacePolyedrique
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#ifndef SURFACEPOLYEDRIQUE_H
#define SURFACEPOLYEDRIQUE_H

#include "MatricePoints.h"

class SurfacePolyedrique : public MatricePoints {
FXDECLARE(SurfacePolyedrique);

private:
protected:
public:
  // constructeur
  SurfacePolyedrique(): MatricePoints() { } // voir MatricePoints
  SurfacePolyedrique(int lignes,int colonnes) : MatricePoints(lignes,colonnes) { }
  SurfacePolyedrique(const ListePoints t[],int lignes) : MatricePoints(t,lignes) { }
  SurfacePolyedrique(const MatricePoints &m) : MatricePoints(m) { }
  
  // destructeur 
  virtual ~SurfacePolyedrique();

  // methodes
  virtual void afficher() ;
  virtual Point3D calculePoint(float u,float v) const ; 
  // ce n'est pas la meme methode (signature différentes) que pour listePoints car c'est ici un abscisse curviligne compris entre 0.0 et 1.0
 
};





#endif
