/*Ce fichier contient l'interface de la classe ListePoints
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#ifndef LISTEPOINTS_H
#define LISTEPOINTS_H
#include "Objet3D.h"
#include "Point3D.h"

#include <exception>

#define BUFF_SIZE 20

class ListePoints : public Objet3D {
 FXDECLARE(ListePoints);

  private:
  int elem_libres;
  void realloueListe();

  void actualise();
  void actualiseBoiteEnglobante();
 protected:
 float (*tab_GL)[4];
 
  Point3D *tab;
  int _longueur;

 public:
  class Mauvaise_Dimension : public exception {}; // une exception
	
 // constructeur
  ListePoints(int l=0); // constructeur par defaut
  ListePoints(Point3D t[],int l); // pour creer une liste de point à partir d'un tableau de point3D
  ListePoints(const ListePoints&); // constructeur par recopie

  // destructeur 
  virtual ~ListePoints();

  // methodes
  virtual void afficher ();
  float *retournerTableauPoints();
  
  // modificateurs
  void supprimer(int i); // supprime le i-eme point
  void modifierPoint(int i,const Point3D& p); // remplace le i-eme point par p
  void ajouter(const Point3D &); // ajoute un point en fin de liste
  void inserer(int i, const Point3D &p); // inserer le point p a la i-eme position
  void fusionne(const ListePoints& lp); // fusionne 2 listes

  // accesseurs
  int longueur() const;
  Point3D retournerPoint(int i) const ;
  
  // pour sauvegarder/charger une liste sous FOX
  void save(FXStream& store) const;
  void load(FXStream& store);

   
  // les operateurs
  virtual Objet3D& operator=(const Objet3D& o); // voir la technique
  virtual ListePoints& operator=(const ListePoints& o); 
 
 Point3D operator[](int i) const;
};



#endif
