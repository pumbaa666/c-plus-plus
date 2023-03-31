/*Ce fichier contient la classe générique Tableau
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/


/*Ce Tableau est représenté en mémoire comme un tableau C, ce Tableau
sera donc utile lorsque on utilise OpenGl (pour les NURBS)*/
#ifndef TABLEAU_H
#define TABLEAU_H
#include <fx.h>
#include <exception>
#define TAILLE 32


template<class TYPE>
class Tableau {
protected:
	TYPE*	_data;		// Le Tableau 
	int     _num;		// Nbre d'élements utilisés
	int     _max;		// Nbre total d'éléments alloués
public:
	class DepassementTableau : public exception {};
	
	Tableau<TYPE>()
	{
		_data=NULL;
		_num=0;
		_max=0;
	}
	Tableau<TYPE>(int n)
	{
		_data=NULL;
		_num=0;
		_max=0;
		taille(n);
	}
	
	Tableau<TYPE>(int n,TYPE init)
	/*ce constructeur permet d'initialiser chaque case du tableau à
	une valeur précise "init"
	Ce constructeur est utilisé pour le constructeur de SurfaceBezierRat
	*/
	{
		_data=NULL;
		_num=0;
		_max=0;
		taille(n);
		for(int i=0;i<n;i++)
			_data[i] = init;
	}
	
	Tableau<TYPE> (Tableau<TYPE> &l)
	{
		_num = l._num;
		_max = l._max;
		_data = new TYPE[_max];
		for(int i=0;i<_num;i++)
			_data[i] = l._data[i];
	}
	
	Tableau<TYPE>& operator=(const Tableau<TYPE>& l)
	{
		delete [] _data;
		_num = l._num;
		_max = l._max;
		_data = new TYPE[_max];
		for(int i=0;i < _num;i++)
			_data[i] = l._data[i];
		return *this;
	}
	
	int taille() const { return _num; }
	
	
	void taille(int n)
	{
		if(n>_max) tailleMem(n);
		_num=n;
	}
	
	TYPE& operator[](int i)
	{ 
		if(i>=_num) throw DepassementTableau(); 
		return _data[i]; 
	}
	TYPE& operator[](int i) const 
	{ 
		if(i>=_num) throw DepassementTableau(); 
		return _data[i]; 
	}
	
	TYPE* list() const { return _data; }
	
	void inserer(int pos,TYPE p)
	{
		int i;
		if(pos>_num) throw DepassementTableau();
		if(_num==_max) tailleMem(_num+TAILLE);
		for(i=_num; pos<i; i--) 
			_data[i]=_data[i-1];
		_data[pos]=p;
		_num++;
	}
	
	void ajouter(TYPE p)
	{
		if(_num==_max) tailleMem(_num+TAILLE);
		_data[_num]=p;
		_num++;
	}
	
	void supprimer(int pos)
	{
		int i;
		if(pos>=_num) throw DepassementTableau();
		for(i=pos+1; i<_num; i++) 
			_data[i-1]=_data[i];
		_num--;
	}
	
	
	void supprimerElem(TYPE p)
	{
		int i;
		bool fin = false;
		for(i=0; (i<_num)&& !fin; i++)
		{ 
			if(_data[i]==p)
			{ 
				while(i<_num-1)
				{ 
					_data[i]=_data[i+1];
					i++; 
				}
				_num--;
				fin = true;
			}
		}
	}
	
	
	void supprimerTout()
	{
		delete [] _data;
		_num=0;
		_max=0;
	}
	
	void save(FXStream& store) const
	{
		store << _num;
		for(int i=0; i<_num; i++)
		{ 
			store << _data[i]; 
		}
	}
	
	void load(FXStream& store)
	{
		int num;
		store >> num;
		taille(num);
		for(int i=0; i<num; i++)
		{ 
			store >> _data[i]; 
		}
	}
	
	bool croissant()
	{
	/*cette fonction permet de savoir si un tableau est croissant
		->utile pour les tableaux de noeuds*/
		bool res = true;
		if(_num > 0)
		{
			TYPE tmp = _data[0];
			for(int i=0; (i<_num) && res;i++)
			{
				res = (tmp <= _data[i]);
				tmp = _data[i];
			}
		}
		return res;
	}
	
	virtual ~Tableau<TYPE>()
	{
		delete [] _data;
	}
	
	int tailleMem() const { return _max; }
private:
	void tailleMem(int n)
	{
		TYPE *tmp = new TYPE[n];
		if(_num != 0)
		{
			//c'est une réallocation
			for(int i=0 ; (i< _num)&&(i<n) ; i++)
				tmp[i] = _data[i];
			delete [] _data;
		}
		if(_num>n) _num=n;
		_max=n;
		_data = tmp;
	}
};


#endif
