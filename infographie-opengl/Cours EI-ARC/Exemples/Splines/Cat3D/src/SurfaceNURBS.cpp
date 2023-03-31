/*Ce fichier contient l'implémentation de la classe SurfaceNURBS
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "SurfaceNURBS.h"


//Implémentation pour FOX
FXIMPLEMENT(SurfaceNURBS,SurfaceAPoles,NULL,0)

//Constructeurs
SurfaceNURBS::SurfaceNURBS()
{
	_ordre_s = 0;
	_ordre_t = 0;
	_tolEch = 25.0;
	_options = 0;
	_estModifie = true;
	_idSurface = 0;
}

SurfaceNURBS::SurfaceNURBS(MatricePoints &mp, Tableau<float> tabNoeuds_s, Tableau<float> tabNoeuds_t,int options,float tolerance) :
		SurfaceAPoles(mp), 
		_tabNoeuds_s(tabNoeuds_s),
		_tabNoeuds_t(tabNoeuds_t),
		_tolEch(tolerance),
		_options(options)
{
	_idSurface = 0;
	int l = mp.fournirNb_lignes();
	int c = mp.fournirNb_colonnes();
	_ordre_s = _tabNoeuds_s.taille() - l;
	_ordre_t = _tabNoeuds_t.taille() - c;
	_table_fonctions_s.taille(_ordre_s + 1);
	_table_fonctions_t.taille(_ordre_t + 1);
	
	//Vérifications des deux tableaux de noeuds
	if(!_tabNoeuds_s.croissant())	throw NoeudsIncorrects();
	if(!_tabNoeuds_t.croissant())	throw NoeudsIncorrects();

}

SurfaceNURBS::SurfaceNURBS(const SurfaceNURBS &s) : SurfaceAPoles(s)
{
	
	_estModifie = true;
	_ordre_s = s._ordre_s;
	_ordre_t = s._ordre_t;
	
	_tabNoeuds_s = s._tabNoeuds_s;
	_tabNoeuds_t = s._tabNoeuds_t;
	
	_table_fonctions_s.taille(_ordre_s + 1);
	_table_fonctions_t.taille(_ordre_t + 1);
	
	_options = s._options;
	_tolEch = s._tolEch;
	_idSurface = 0;
}


//Destructeur
SurfaceNURBS::~SurfaceNURBS()
{
	if(_idSurface != 0) glDeleteLists(_idSurface,1);  //on supprime la Display List d'OpenGL
}

//Cette fonction permet l'affichage OpenGL de la surface grâce à une Display List
void SurfaceNURBS::afficher()
{
	if((_options & DESSINER_SURFACE_POLYEDRIQUE) !=0)
		SurfaceAPoles::afficher();  //Ceci est utilisé pour visualiser la surface polyedrique
	//si la surface a été modifiée, on recrée la Display List
	if (_estModifie) 
	{
		calculerBoiteEnglobante();
		if(_idSurface != 0) glDeleteLists(_idSurface,1);  //on supprime la Display List d'OpenGL pour en créer une nouvelle
		_idSurface = glGenLists (1);  //on demande un nouvel identifiant de DisplayList
		glNewList(_idSurface,GL_COMPILE);
		
		GLUnurbsObj *theNurbs;
		theNurbs = gluNewNurbsRenderer();

		gluNurbsProperty(theNurbs,GLU_SAMPLING_TOLERANCE,_tolEch);

		if((_options & FIL_DE_FER) == 0)
			gluNurbsProperty(theNurbs,GLU_DISPLAY_MODE,GLU_FILL);
		else
			gluNurbsProperty(theNurbs,GLU_DISPLAY_MODE,GLU_OUTLINE_POLYGON);

		if(retournerPtrCtl() != NULL)  //Sinon il n'y a rien à afficher
		{		
			gluBeginSurface(theNurbs);
			gluNurbsSurface(theNurbs, 
				(GLint) _tabNoeuds_s.taille(),(GLfloat *) _tabNoeuds_s.list(),
				(GLint) _tabNoeuds_t.taille(),(GLfloat *) _tabNoeuds_t.list(),
				4,4 * fournirNbreLignesCtl(),  //4 signifie que l'on est en coordonnée homogène sinon c'est 3 //(GLint) _stride_s, (GLint) _stride_t,
				retournerPtrCtl(), 
				(GLint) _ordre_s,(GLint) _ordre_t,
				GL_MAP2_VERTEX_4);
			gluEndSurface(theNurbs);
		}
		_estModifie = false;
		glEndList();
  }
  glCallList(_idSurface);

}


//Les modifieurs
void SurfaceNURBS::modifierNoeud_s(int pos, float val)
{
	_estModifie = true;
	try
	{
		_tabNoeuds_s[pos] = val;
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//on vérifie de plus si le tableau reste croissant

	if(!_tabNoeuds_s.croissant())	throw NoeudsIncorrects();
}

void SurfaceNURBS::modifierNoeud_t(int pos, float val)
{
	_estModifie = true;
	try
	{
		_tabNoeuds_t[pos] = val;
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}

	//on vérifie de plus si le tableau reste croissant
	if(!_tabNoeuds_t.croissant())	throw NoeudsIncorrects();
}

void SurfaceNURBS::modifierTolEch(float t)
{
	_estModifie = true;
	if(t>=0)
		_tolEch = t;
	else
		throw ToleranceIncorrect();
}

void SurfaceNURBS::options(int val)
{
	if(val !=  _options)
	{
		_estModifie = true;
		_options =val;
	}
}


//Les fournisseurs
float SurfaceNURBS::fournirNoeud_s(int pos) const
{
	float tmp;
	try
	{
		tmp = _tabNoeuds_s[pos];
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	return tmp;
}

float SurfaceNURBS::fournirNoeud_t(int pos) const
{
	float tmp;
	try
	{
		tmp = _tabNoeuds_t[pos];
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	return tmp;
}

int SurfaceNURBS::fournirOrdre_s() const
{
	return _ordre_s;
}

int SurfaceNURBS::fournirOrdre_t() const
{
	return _ordre_t;
}

float SurfaceNURBS::fournirTolEch() const
{
	return _tolEch;
}

int SurfaceNURBS::fournirNbreNoeuds_s() const
{
	return _tabNoeuds_s.taille();
}

int SurfaceNURBS::fournirNbreNoeuds_t() const
{
	return _tabNoeuds_t.taille();
}

int SurfaceNURBS::options() const
{
	return _options;
}

//Chargement d'une nurbs à partir d'un flux
void SurfaceNURBS::load(FXStream &store)
{
	_estModifie = true;
	
	SurfaceAPoles::load(store);
	_tabNoeuds_s.load(store);
	_tabNoeuds_t.load(store);
	int l = fournirNbreLignesCtl();
	int c = fournirNbreColonnesCtl();

	store >> _tolEch >> _options;
	
	_table_fonctions_s.supprimerTout();
	_table_fonctions_t.supprimerTout();
	_ordre_s = _tabNoeuds_s.taille() - l;
	_ordre_t = _tabNoeuds_t.taille() - c;
	_table_fonctions_s.taille(_ordre_s + 1);
	_table_fonctions_t.taille(_ordre_t + 1);
	//on calcule ensuite la boite englobante
	calculerBoiteEnglobante();
}

//Sauvegarde d'une nurbs dans un flux
void SurfaceNURBS::save(FXStream &store) const
{	
	SurfaceAPoles::save(store);
	_tabNoeuds_s.save(store);
	_tabNoeuds_t.save(store);
	
	store << _tolEch <<  _options;
}


/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*                     calcul des k fonctions de base non nulles en t
/* D'après Marc DANIEL
 */
void SurfaceNURBS::calbsp(Tableau<float>& vknot,float t,int i,int k,Tableau<float> &b)
{
int    l,m,i1,im,ilm;
float  bb,bh;

b[1]=1;
i1=i+1;
bb=b[1];
if (k>1)
   {   /* ce test est inutile si l'on peut s'assurer que l'utilisateur n'utilisera jamais
          l'ordre "idiot" k=1.
          On calcule ici les fonctions pour l'ordre 2 */
   b[1]=bb*(vknot[i1]-t)/(vknot[i1]-vknot[i]);
   b[2]=bb*(t-vknot[i])/(vknot[i1]-vknot[i]);
   }
 
for (l=3;l<=k;l=l+1)
   {
   bb=b[1];
   b[1]=bb*(vknot[i1]-t)/(vknot[i1]-vknot[i-l+2]);
   for (m=2;m<=l-1;m=m+1)
      {
      im=i+m;
      ilm=i-l+m;
      bh=bb;
      bb=b[m];
      b[m]=bh*(t-vknot[ilm])/(vknot[im-1]-vknot[ilm]);
      b[m]=b[m]+bb*(vknot[im]-t)/(vknot[im]-vknot[ilm+1]);
      }
   b[l]=bb*(t-vknot[i])/(vknot[i+l-1]-vknot[i]);
   }
}
/*---------------------------------------------------------------------------------------*/

//Cette fonction permet le retour d'un point de la surface
//à partir des coordonnées paramétriques
Point3D SurfaceNURBS::retournerPoint(float s, float t)
{
	int is,it;
	float xx;
	int l = fournirNbreLignesCtl();
	int c = fournirNbreColonnesCtl();
	Point3D pcal,tmp;   /*Point calculé : pcal*/
	
	/*positionnement par rapport aux vecteurs de noeuds */
	is = posit_s(s);
	it = posit_t(t);;
	
	if ((is>0) && (it>0))
	{
	/*                  calcul des k bsplines non nulles                  */
		calbsp(_tabNoeuds_s,s,is,_ordre_s,_table_fonctions_s);
		calbsp(_tabNoeuds_t,t,it,_ordre_t,_table_fonctions_t);

		pcal.x = 0.0;
		pcal.y = 0.0;
		pcal.z = 0.0;
		pcal.w = 0.0;

		for (int j=1 ; j <= _ordre_t ; j++)
		{
			//ical1=(*iv-kv+j)*(nu+1)+*iu-ku;
			for (int i=1 ; i <= _ordre_s ; i++)
			{
				xx = _table_fonctions_s[i] * _table_fonctions_t[j];
				//ical2=ical1+i;
				tmp = retournerPointCtl(is - _ordre_s + i , it - _ordre_t + j);
				pcal.x = pcal.x + xx * tmp.x; //xcontr[ical2];
				pcal.y = pcal.y + xx * tmp.y; //ycontr[ical2];
				pcal.z = pcal.z + xx * tmp.z; //zcontr[ical2];
				pcal.w = pcal.w + xx * tmp.w;
			}
		}
	}
	pcal.x = pcal.x / pcal.w;
	pcal.y = pcal.y / pcal.w;
	pcal.z = pcal.z / pcal.w;
	return pcal;
}

int SurfaceNURBS::posit_s(float t)
/*Positionnement du paramètre dans le vecteur de noeuds de la dimension s
  Voir l'algo de M.Daniel
*/
{
	float  tmin,tmax;
	int res;   //résultat de la fonction
	tmin = _tabNoeuds_s[0];
	tmax = _tabNoeuds_s[_tabNoeuds_s.taille()-1];
 
	if ((t < tmin) || ( t > tmax))
	   res = -1;                       /* en dehors de l'intervalle parametrique    */
	else
	{
		if (t==tmax)
		{
			res = _tabNoeuds_s.taille() - 1 - _ordre_s;                       
			while ((_tabNoeuds_s[res]==_tabNoeuds_s[res+1]) && (res>0))
			 res=res-1;
			if (res==0)
			 res=-2;                 /* erreur dans le vecteur de noeuds          */
		}
		else
		{
			res=_ordre_s-1;                   /* cas general : recherche a partir du debut */
			while ((t>=_tabNoeuds_s[res]) && (res < _tabNoeuds_s.taille()-1))
			 res=res+1;
			if (res == _tabNoeuds_s.taille()-1)
			 res=-2;
			else
			 res=res-1;
		}
	}
	return res;
}

int SurfaceNURBS::posit_t(float t)
/*Positionnement du paramètre dans le vecteur de noeuds de la dimension s
  Voir l'algo de M.Daniel
*/
{
	float  tmin,tmax;
	int res;   //résultat de la fonction
	tmin = _tabNoeuds_t[0];
	tmax = _tabNoeuds_t[_tabNoeuds_t.taille()-1];
 
	if ((t < tmin) || ( t > tmax))
	   res = -1;                       /* en dehors de l'intervalle parametrique    */
	else
	{
		if (t==tmax)
		{
			res = _tabNoeuds_t.taille() - 1 - _ordre_t;                       
			while ((_tabNoeuds_t[res]==_tabNoeuds_t[res+1]) && (res>0))
			 res=res-1;
			if (res==0)
			 res=-2;                 /* erreur dans le vecteur de noeuds          */
		}
		else
		{
			res=_ordre_t-1;                   /* cas general : recherche a partir du debut */
			while ((t>=_tabNoeuds_t[res]) && (res < _tabNoeuds_t.taille()-1))
			 res=res+1;
			if (res == _tabNoeuds_t.taille()-1)
			 res=-2;
			else
			 res=res-1;
		}
	}
	return res;
}





SurfaceNURBS & SurfaceNURBS::operator =(SurfaceNURBS &s)
{
	SurfaceAPoles::operator =(s);
	_estModifie = true;
	_ordre_s = s._ordre_s;
	_ordre_t = s._ordre_t;
	
	_tabNoeuds_s = s._tabNoeuds_s;
	_tabNoeuds_t = s._tabNoeuds_t;
	
	_table_fonctions_s.taille(_ordre_s + 1);
	_table_fonctions_t.taille(_ordre_t + 1);
	
	_options = s._options;
	_tolEch = s._tolEch;
	_idSurface = 0;
	return *this;
}


//Ces deux fonctions permettent de rajouter un noeud
void SurfaceNURBS::ajouterNoeud_s(float n)
{
	_estModifie = true;
	_tabNoeuds_s.ajouter(n);
	//pour rester cohérent avec la matrice de points de contrôle, l'ordre augmente de 1
	_ordre_s++;
	if(!_tabNoeuds_s.croissant())	throw NoeudsIncorrects();
}

void SurfaceNURBS::ajouterNoeud_t(float n)
{
	_estModifie = true;
	_tabNoeuds_t.ajouter(n);
	//pour rester cohérent avec la matrice de points de contrôle, l'ordre augmente de 1
	_ordre_t++;
	//on vérifie de plus si le tableau reste bien croissant
	if(!_tabNoeuds_t.croissant())	throw NoeudsIncorrects();
}

//Ces deux fonctions permettent d'inserer un noeud à une position spécifique
void SurfaceNURBS::insererNoeud_s(int pos,float n)
{
	_estModifie = true;
	try
	{
		_tabNoeuds_s.inserer(pos,n);
		//pour rester cohérent avec la matrice de points de contrôle, l'ordre augmente de 1
		_ordre_s++;

	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//on vérifie de plus si le tableau reste croissant

	if(!_tabNoeuds_s.croissant())	throw NoeudsIncorrects();
}

void SurfaceNURBS::insererNoeud_t(int pos,float n)
{
	_estModifie = true;
	try
	{
		_tabNoeuds_t.inserer(pos,n);
		//pour rester cohérent avec la matrice de points de contrôle, l'ordre augmente de 1
		_ordre_t++;
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}

	//on vérifie de plus si le tableau reste croissant
	if(!_tabNoeuds_t.croissant())	throw NoeudsIncorrects();
}

//Ces deux fonctions permettent de supprimer un noeud à un position donné
void SurfaceNURBS::supprimerNoeud_s(int pos)
{
	_estModifie = true;
	try
	{
		_tabNoeuds_s.supprimer(pos);
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//pour rester cohérent avec la matrice de points de contrôle, l'ordre diminue de 1
	_ordre_s--;
	//on vérifie de plus que l'ordre ne devienne pas négatif
	if(_ordre_s < 0) throw NoeudsIncorrects();
}

void SurfaceNURBS::supprimerNoeud_t(int pos)
{
	_estModifie = true;
	try
	{
		_tabNoeuds_t.supprimer(pos);
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//pour rester cohérent avec la matrice de points de contrôle, l'ordre diminue de 1
	_ordre_s--;
	//on vérifie de plus que l'ordre ne devienne pas négatif
	if(_ordre_s < 0) throw NoeudsIncorrects();
}


//Les fonctions suivantes permettent des manipulations sur la matrice
//de contrôle
void SurfaceNURBS::insererColonneCtl(int pos,const ListePoints& l)
{
	_estModifie = true;
	SurfaceAPoles::insererColonneCtl(pos,l);
	//pour rester cohérent avec les ordres on diminue l'ordre de 1
	_ordre_t--;
	//on vérifie de plus que l'ordre ne devienne pas négatif
	if(_ordre_t < 0) throw NoeudsIncorrects();
}

void SurfaceNURBS::insererLigneCtl(int pos,const ListePoints& l)
{
	_estModifie = true;
	SurfaceAPoles::insererLigneCtl(pos,l);
	//pour rester cohérent avec les ordres on diminue l'ordre de 1
	_ordre_s--;
	//on vérifie de plus que l'ordre ne devienne pas négatif
	if(_ordre_s < 0) throw NoeudsIncorrects();
}

void SurfaceNURBS::supprimerColonneCtl(int pos)
{
	_estModifie = true;
	SurfaceAPoles::supprimerColonneCtl(pos);
	//pour rester cohérent avec les ordres on augmente l'ordre de 1
	_ordre_t ++;
}

void SurfaceNURBS::supprimerLigneCtl(int pos)
{
	_estModifie = true;
	SurfaceAPoles::supprimerLigneCtl(pos);
	//pour rester cohérent avec les ordres on augmente l'ordre de 1
	_ordre_s ++;
}



