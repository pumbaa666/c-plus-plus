/*Ce fichier contient l'implémentation de la classe ListePoints
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "ListePoints.h"


FXIMPLEMENT(ListePoints,Objet3D,NULL,0)


ListePoints::ListePoints(int l) : tab_GL(NULL),tab(NULL) {
  if (l < 0 ) throw new Mauvaise_Dimension;
 
  _longueur=l;
  elem_libres=0;

  if (_longueur != 0)
    tab=new Point3D[_longueur]; // remplit la liste par des points valant (0,0,0)
  
}

ListePoints::ListePoints(Point3D t[],int l) : tab_GL(NULL),tab(NULL){
  if (l < 0 ) throw new Mauvaise_Dimension;
  _longueur=0;
  elem_libres=0;

  for (int i=0 ; i < l ;i++) 
    ajouter(t[i]);	
}

ListePoints::ListePoints(const ListePoints& lp) : tab_GL(NULL),tab(NULL) , Objet3D(lp) {
   
_longueur=lp._longueur;
  elem_libres=0;
  tab=new Point3D[_longueur];
  for (int i=0 ; i < _longueur ; i++) 
    tab[i]=lp.tab[i];
  
}

ListePoints::~ListePoints() {
  delete []tab;
  delete []tab_GL;
}


void ListePoints::actualise() {
  actualiseBoiteEnglobante();

  delete []tab_GL;
  tab_GL=NULL;
}

void ListePoints::actualiseBoiteEnglobante(){
  range[0][0] = range[0][1] = retournerPoint(0).x;
  range[1][0] = range[1][1] = retournerPoint(0).y;
  range[2][0] = range[2][1] = retournerPoint(0).z;

  for (int i=0;i < longueur() ; i++) {
    // calcul des pourtours de la boite englobante	
    Point3D tmp = retournerPoint(i);
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

void ListePoints::afficher () {
  glPointSize(4.0);
  glBegin(GL_POINTS);
  for (int i=0; i < _longueur ; i++) {
    glVertex3f(tab[i].x, tab[i].y, tab[i].z);
  }
  glEnd();
}

void ListePoints::modifierPoint(int i,const Point3D& p) {
  if ((i < 0 ) || (i >= _longueur)) 
    throw new Mauvaise_Dimension;
  
  tab[i]=p;
   
  actualise();
}

void ListePoints::supprimer(int i) {
  if ((i < 0 ) || (i >= _longueur)) 
    throw new Mauvaise_Dimension;

  for (int j=i+1 ; j < _longueur ; j++) 
    tab[j-1]=tab[j];
  
  elem_libres++;
  _longueur--;
 
  actualise();
}
 
void ListePoints::ajouter(const Point3D &p) {

  realloueListe();
  tab[_longueur]=p;
  elem_libres--;
  _longueur++;

  actualise();
}

void ListePoints::inserer(int i, const Point3D &p) {
  if ((i < 0 ) || (i > _longueur)) 
    throw new Mauvaise_Dimension;

  realloueListe();
  for (int j=_longueur ; j > i ; j--) {
    tab[j]=tab[j-1];
  }
  tab[i]=p;

  elem_libres--;
  _longueur++;
  
  actualise();
}

void ListePoints::realloueListe() { 
  // alloue de la place dans le tableau si nécessaire
  if (elem_libres == 0) {
    Point3D *tmp=new Point3D[_longueur+BUFF_SIZE];
    elem_libres=BUFF_SIZE;
    for (int i=0 ; i < _longueur ; i++) 
      tmp[i]=tab[i];
	
    delete [] tab;	
    tab=tmp;
  }
}

Point3D ListePoints::retournerPoint(int i) const {
  if ((i < 0 ) || (i >= _longueur))
    throw new Mauvaise_Dimension;

  return tab[i];
}



float *ListePoints::retournerTableauPoints() {
  if (tab_GL==NULL) {
    tab_GL=new float[_longueur][4];
    for (int i=0 ; i < _longueur ; i++) {
      tab_GL[i][0]=tab[i].x;
      tab_GL[i][1]=tab[i].y;
      tab_GL[i][2]=tab[i].z;
      tab_GL[i][3]=tab[i].w;
    }
    
  }
  
  return (float *)tab_GL;
}


int ListePoints::longueur() const {
  return _longueur;

}
 
void ListePoints::fusionne(const ListePoints& lp) {
  Point3D *tmp=new Point3D[_longueur+lp._longueur];
  for (int i=0 ; i < _longueur ; i++) {
    tmp[i]=tab[i];
  }
  for (int i2=0 ; i2 < lp._longueur ; i2++) {
    tmp[i2+_longueur]=lp.tab[i2];
  }
  delete []tab;
  tab=tmp;

  elem_libres=0;
  _longueur+=lp._longueur;

  actualise();
}

// surcharge de l'operateur affectation, les 2 methodes sont indispensables

ListePoints& ListePoints::operator=(const ListePoints& lp) {
  Objet3D::operator=(lp);
  // on appelle Objet3D::operator= pour copier les autres champs .
	
  delete []tab_GL;
  delete []tab;
 
 _longueur=lp._longueur;
  elem_libres=0;
  tab=new Point3D[_longueur];
  for (int i=0 ; i < _longueur ; i++)
    tab[i]=lp.tab[i];
  
  return *this;
}

Objet3D& ListePoints::operator=(const Objet3D& o) { // en fait, ici o est une liste de points car le type est dynamique
  const ListePoints &lp=dynamic_cast<const ListePoints &>(o);
  operator=(lp);
 
  return *this;
}


Point3D ListePoints::operator[](int i) const {
  return retournerPoint(i);
}

void ListePoints::save(FXStream& store) const {
	Objet3D::save(store);
	store << _longueur;
      for(int i=0; i<_longueur ; i++) {
	store << tab[i].x << tab[i].y << tab[i].z << tab[i].w ; 
      }
  
}

void ListePoints::load(FXStream& store) {	
  Objet3D::load(store);
  delete []tab_GL;
  delete []tab;
  

  store >> _longueur;
	 
  elem_libres=0;
  tab=new Point3D[_longueur];
 	
  for(int i=0; i<_longueur; i++)
    { 
      store >> tab[i].x >> tab[i].y >> tab[i].z >> tab[i].w; 
    
    }
  
}


