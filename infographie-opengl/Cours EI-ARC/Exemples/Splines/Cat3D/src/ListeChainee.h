/*Ce fichier contient la classe générique ListeChainee
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H


template <class Element>
class ListeChainee {
private :
  // données membres
  struct chainon {
    Element elem;
    chainon *prev,*next;
  };
  
  int length;
  chainon *teteListe,*queueListe,*marqueurListe;
protected:

public :
  // constructeur
  ListeChainee() ;
  
  ListeChainee (Element &e) ;
  // destructeur

  virtual ~ListeChainee() { }

  // predicat 

  bool estVide() const;
  // modificateur 
   
  void ajouter(Element& e); // ajoute l'element e en tete de liste

  void enlever(int i); // supprime l'element e de la liste
  
  void inserer(Element& e,int i); // insère l'element e à la i-eme place   

   void deplacerMarqueurListe(int i);
  
  void fusionner(ListeChainee& dll);
  
  // accesseur
  Element& retournerElement(int i) const; // retourne l'élément à la i-eme place 
 
 Element& ElementSuivant();
  Element& ElementPrecedent();

};




template <class Element>
ListeChainee<Element>::ListeChainee() {
  teteListe=NULL;
  queueListe=NULL;
  marqueurListe=NULL;
  length=0;
}

template <class Element>
ListeChainee<Element>::ListeChainee (Element& e) {
  teteListe=new chainon;
  teteListe->elem=e; // copie profonde
  teteListe->prev=NULL;
  teteListe->next=NULL;
  
  queueListe=teteListe;
  marqueurListe=teteListe;
  length=1;
}

template <class Element>
bool ListeChainee<Element>::estVide() const{
  return (teteListe==NULL);
}

template <class Element>
void ListeChainee<Element>::ajouter(Element& e) {
  inserer(e,0);
}


template <class Element>
void ListeChainee<Element>::enlever(int i) {
  int j; 
  chainon *runner;
  for (j=0, runner=teteListe  ; j < i ; j++, runner=runner->next);
  if (runner->prev == NULL) {  // on enleve la tete de liste
    teteListe=runner->next;
  }
  else 
    runner->prev->next=runner->next;
  
  if (runner -> next == NULL) { // on enleve la queue de liste
    queueListe=runner->prev;
  }
  else 
    runner->next->prev=runner->prev;
  
  
  delete runner;
  length--;
}

template <class Element>
void ListeChainee<Element>::inserer(Element& e,int i) {
  int j; 
  chainon *runner;
  for (j=0, runner=teteListe  ; j < i ; j++, runner=runner->next);
  chainon *tmp=runner;
  runner=new chainon;
  runner->elem=e;
  runner->next=tmp;

  if (tmp!= NULL) {
    runner->prev=tmp->prev;
    tmp->prev=runner;
  }
  if (runner->prev != NULL)
    runner->prev->next=runner;

  length++;
  
  if (runner->next == NULL)  // on a insere en queue de liste 
    queueListe=runner;
  if (runner->prev == NULL) {// on a insere en tete de liste 
    teteListe=runner;
    marqueurListe=teteListe;
  }

}

template <class Element>
void ListeChainee<Element>::deplacerMarqueurListe(int i) {
  int j; 
  chainon *runner;
  for (j=0, runner=teteListe  ; j < i ; j++, runner=runner->next);
  marqueurListe=runner;
}

 
template <class Element>
void ListeChainee<Element>::fusionner(ListeChainee& dll) {
// a faire 
}

template <class Element>
Element& ListeChainee<Element>::retournerElement(int i) const {
  int j; 
  chainon *runner;
  for (j=0, runner=teteListe  ; j < i ; j++, runner=runner->next);
  return runner->elem;
}

template <class Element>
Element& ListeChainee<Element>::ElementSuivant() {
  if (marqueurListe != NULL) {
    marqueurListe=marqueurListe->next;
    return marqueurListe->elem;
  }
  return teteListe->elem;
}

template <class Element>
Element& ListeChainee<Element>::ElementPrecedent() {
  marqueurListe=marqueurListe->prev;
  return marqueurListe->elem;
}


#endif







