/*Ce fichier contient l'interface de la classe MatricePoints
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef MATRICEPOINTS_H
#define MATRICEPOINTS_H
#include "Objet3D.h"
#include "Point3D.h"
#include "ListePoints.h"

#include <exception>

class MatricePoints : public Objet3D {
FXDECLARE(MatricePoints);
private:
  void actualise();
  void actualiseBoiteEnglobante();

protected:
  float (*tab_GL)[4]; 

  ListePoints *tab;
  int nb_lignes;
  int nb_colonnes;
public:
  class Mauvaise_Dimension : public exception {}; // une exception
	
  // constructeur
  MatricePoints(); // construction avec 0 lignes et 0 colonnes
  MatricePoints(int lignes,int colonnes); // construction d'une matrice vide avec lignes et colonnes
  MatricePoints(const ListePoints t[],int lignes); // construction avec un tableau de ListePoints
  
  // contructeur par recopie
  MatricePoints(const MatricePoints&);

  // destructeur 
  virtual ~MatricePoints();

  // methodes
  virtual void afficher ();
  float *retournerTableauPoints();
  
 

  // modificateurs
  void insererLigne(int i,const ListePoints& l);
  void insererColonne(int j,const ListePoints& l);
  void supprimerLigne(int i);
  void supprimerColonne(int j);
  void modifierPoint(int i,int j,const Point3D& p);
 
  // accesseurs
  Point3D retournerPoint(int i,int j) const;
  
  int fournirNb_lignes() const;
  int fournirNb_colonnes() const;
   
  // operateurs
  virtual  MatricePoints& operator=(const MatricePoints &mp); 
  virtual  Objet3D& operator=(const Objet3D &mp); 
 

  // pour sauvegarder/charger une matrice sous FOX
  virtual void save(FXStream& store) const;
  virtual void load(FXStream& store);


};






#endif
