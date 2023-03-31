/*Ce fichier contient l'interface de la classe Transformation
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef TRANSFO_H
#define TRANSFO_H

class Transformation {
private:
protected:
public: 
  float rot_x, rot_y, rot_z; // rotation 
  float ech_x, ech_y, ech_z; // echelle
  float pos_x, pos_y, pos_z; // position
public: 

  Transformation( float x=0.0, 
		  float y=0.0, 
		  float z=0.0,
		  float rx=0.0, 
		  float ry=0.0, 
		  float rz=0.0, 
		  float ex=1.0, 
		  float ey=1.0, 
		  float ez=1.0);

  // destructeur
  virtual ~Transformation();


  void chargeIdentite();

  void composeRotation(float x, float y, float z);
  void composeTranslation(float x, float y, float z);
  void composeHomothetie(float x, float y, float z);
  
  void compose(const Transformation &);
  
  virtual Transformation &operator=(const Transformation &t);
};

#endif


