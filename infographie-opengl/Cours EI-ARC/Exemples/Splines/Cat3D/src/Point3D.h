/*Ce fichier contient l'interface de la classe Point3D
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef POINT3D_H
#define POINT3D_H

class Point3D {
public:
  Point3D(float x=0,float y=0,float z=0,float w=1.0) : x(x), y(y), z(z), w(w) { }
  float x,y,z,w; // coordonnées x,y,z et le poids w
};


#endif
