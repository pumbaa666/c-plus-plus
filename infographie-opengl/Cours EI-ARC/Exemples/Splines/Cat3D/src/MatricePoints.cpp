/*Ce fichier contient l'implémentation de la classe MatricePoints
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "MatricePoints.h"


FXIMPLEMENT(MatricePoints,Objet3D,NULL,0)



MatricePoints::MatricePoints() : tab_GL(NULL),tab(NULL) {
  nb_lignes=0;
  nb_colonnes=0;
}
 
MatricePoints::MatricePoints(int lignes,int colonnes)  : tab_GL(NULL),tab(NULL) {
  if ((lignes<=0) || (colonnes<=0))
    throw new Mauvaise_Dimension;

  nb_lignes=lignes;
  nb_colonnes=colonnes;
  
  
  tab=new ListePoints[nb_lignes]; // nécessite un constructeur par defaut de ListePoints
  for (int i=0 ; i < nb_lignes ; i++) 
    tab[i]=ListePoints(nb_colonnes); // initialise la matrice avec des lignes des points valant (0,0,0)

}

MatricePoints::MatricePoints(const ListePoints t[],int lignes) : tab_GL(NULL),tab(NULL){
  if (lignes<=0) 
    throw new Mauvaise_Dimension;
  if (t[0].longueur() == 0) // on suppose pour le moment que toutes les ListePoints ont la meme longueur
    throw new Mauvaise_Dimension;
	
  tab=new ListePoints[lignes]; // nécessite un constructeur par defaut de ListePoints
  nb_lignes=lignes; 
  nb_colonnes=t[0].longueur(); 
  
 
  for (int i=0; i < lignes ; i++) {
    if (t[i].longueur() != nb_colonnes)
      throw new Mauvaise_Dimension;
    tab[i]=t[i];  // nécessite l'operateur d'affectation de ListePoints
  }	

 actualiseBoiteEnglobante();
}	

MatricePoints::MatricePoints(const MatricePoints& mp) : tab_GL(NULL),tab(NULL),Objet3D(mp) {
 
  nb_lignes=mp.nb_lignes;
  nb_colonnes=mp.nb_colonnes;

  tab=new ListePoints[nb_lignes];
  for (int i=0 ; i < nb_lignes ; i++) {
    tab[i]=mp.tab[i];
  }
 
}

MatricePoints::~MatricePoints() {
  delete []tab;
  delete []tab_GL;
}


void MatricePoints::insererLigne(int i,const ListePoints& l) {
  // la ListePoints doit avoir nb_colonnes comme longueur
  if (l.longueur() != nb_colonnes) 
    throw new Mauvaise_Dimension;
  if ((i < 0) || (i > nb_lignes))
    throw new Mauvaise_Dimension;

  ListePoints *tmp=new ListePoints[nb_lignes+1];

  // on copie les i premières lignes du tableau de points
  for (int j=0 ; j < i ; j++) {
    tmp[j]=tab[j];
  }

  // on copie la ligne qu'on souhaite inserer
  tmp[i]=l;
  
  
  // on copie le reste des lignes de points
  for (int j2=i ; j2 < nb_lignes ; j2++) {
    tmp[j2+1]=tab[j2];
  }
  delete []tab;
  tab=tmp;
  nb_lignes++; // on ajoute une ligne

  actualise();

}

void MatricePoints::insererColonne(int j,const ListePoints& l) {
  // la ListePoints doit avoir nb_lignes comme longueur
  if (l.longueur() != nb_lignes) 
    throw new Mauvaise_Dimension;
  if ((j < 0) || (j > nb_colonnes))
    throw new Mauvaise_Dimension;

  // dans chaque ligne copiée on ajoute le point en j-ieme position
  for (int i=0 ; i < nb_lignes ; i++) {
    tab[i].inserer(j,l[i]);
  }
  nb_colonnes++;

  actualise();
}

float *MatricePoints::retournerTableauPoints() {
  if (tab_GL == NULL) {
    delete []tab_GL;
    tab_GL=new float[nb_lignes * nb_colonnes][4];
    for (int i=0 ; i < nb_lignes ; i++) {
      for (int j=0 ; j < nb_colonnes ; j++) {
	tab_GL[i*nb_colonnes+j][0]=tab[i][j].x;
	tab_GL[i*nb_colonnes+j][1]=tab[i][j].y;
	tab_GL[i*nb_colonnes+j][2]=tab[i][j].z;
	tab_GL[i*nb_colonnes+j][3]=tab[i][j].w;    
      }		
    }
   
  }
  return (float *)tab_GL;
}

void MatricePoints::afficher ()  {
  for (int i=0 ; i < nb_lignes ; i++) {
    tab[i].afficher();
  }
}

Point3D MatricePoints::retournerPoint(int i,int j) const {
  if ((i >= nb_lignes) || (i < 0)  || (j >= nb_colonnes)|| (j<0))
    throw new Mauvaise_Dimension;
  return tab[i].retournerPoint(j);
}
 
void MatricePoints::modifierPoint(int i,int j,const Point3D& p){
  if ((i >= nb_lignes) || (i < 0)  || (j >= nb_colonnes)|| (j<0))
    throw new Mauvaise_Dimension;

  tab[i].modifierPoint(j,p);
  actualise();
}


void MatricePoints::actualise() {
  actualiseBoiteEnglobante();
  delete []tab_GL;
  tab_GL = NULL;  
}

void MatricePoints::actualiseBoiteEnglobante(){
  range[0][0] = range[0][1] = retournerPoint(0,0).x;
  range[1][0] = range[1][1] = retournerPoint(0,0).y;
  range[2][0] = range[2][1] = retournerPoint(0,0).z;

  for (int i=0;i < nb_lignes ; i++) {
    for (int j=0;j < nb_colonnes ; j++) {
      
      Point3D tmp = retournerPoint(i,j);
      if (tmp.x < range[0][0])
	range[0][0] = tmp.x;
      if (tmp.y < range[1][0])
	range[1][0] = tmp.y;
      if (tmp.z < range[2][0])
	range[2][0] = tmp.z;
      if (tmp.x > range[0][1])
	range[0][1] = tmp.x;
      if (tmp.y > range[1][1])
	range[1][1] = tmp.y;
      if (tmp.z > range[2][1])
	range[2][1] = tmp.z;
      
    }
  }
}

 

Objet3D& MatricePoints::operator=(const Objet3D &o) {
  const MatricePoints &mp=dynamic_cast<const MatricePoints &>(o);
  operator=(mp);

  return *this;
}

MatricePoints& MatricePoints::operator=(const MatricePoints &mp) {
 // on appelle Objet3D::operator= pour copier les autres champs
  Objet3D::operator=(mp);

 nb_lignes=mp.nb_lignes;
  nb_colonnes=mp.nb_colonnes;

  delete []tab;
   delete []tab_GL;
 
 tab=new ListePoints[nb_lignes];
  for (int i=0 ; i < nb_lignes ; i++) {
    tab[i]=mp.tab[i];
  }
 
  
 return *this;
}

void MatricePoints::supprimerLigne(int i) {
  if ((i < 0) || (i >= nb_lignes))
    throw new Mauvaise_Dimension;

  // la ListePoints doit avoir nb_colonnes comme longueur
  ListePoints *tmp=new ListePoints[nb_lignes-1];

  // on copie les i premières lignes du tableau de points
  for (int j=0 ; j < i ; j++) {
    tmp[j]=tab[j];
  }

  // on copie le reste des lignes de points
  for (int j2=i+1 ; j2 < nb_lignes ; j2++) {
    tmp[j2-1] =tab[j2];
  }
  delete []tab;
  tab=tmp;
  nb_lignes--; // supprime une ligne

  actualise();
}

void MatricePoints::supprimerColonne(int j) {
  if ((j < 0) || (j >= nb_colonnes))
    throw new Mauvaise_Dimension;

  for (int i=0 ; i < nb_lignes ; i++) {
    tab[i].supprimer(j);
  }
  nb_colonnes--;

  actualise();
}
 

int MatricePoints::fournirNb_lignes() const {
  return nb_lignes;
}

int MatricePoints::fournirNb_colonnes() const {
  return nb_colonnes; 
}
 
void MatricePoints::save(FXStream& store) const {
  Objet3D::save(store);
  store << nb_lignes << nb_colonnes  ;
  for(int i=0; i< nb_lignes  ; i++) 
    tab[i].save(store);

}

void MatricePoints::load(FXStream& store) {
 Objet3D::load(store);
 
 delete []tab_GL;
 delete []tab;
 store >> nb_lignes >> nb_colonnes  ;
  
 tab=new ListePoints[nb_lignes]; // nécessite un constructeur par defaut de ListePoints
 for (int i=0 ; i < nb_lignes ; i++) 
   tab[i].load(store);

}
