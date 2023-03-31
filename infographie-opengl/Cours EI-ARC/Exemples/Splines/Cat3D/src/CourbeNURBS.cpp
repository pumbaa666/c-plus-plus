/*Ce fichier contient l'implémentation de la classe CourbeNURBS
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#include "CourbeNURBS.h"

//Implémentation pour FOX
FXIMPLEMENT(CourbeNURBS,CourbeAPoles,NULL,0)

//Constructeurs
CourbeNURBS::CourbeNURBS()
{
	_ordre = 0;
	_tolEch = 25.0;
	_estModifie = true;
	_options=0;
	_idCourbe = 0;
}



CourbeNURBS::CourbeNURBS(ListePoints &lp, Tableau<float> tabNoeuds,int options,float tolerance) :
		CourbeAPoles(lp), 
		_tabNoeuds(tabNoeuds),
		_tolEch(tolerance),
		_options(options)
{
	_idCourbe = 0;
	int l = lp.longueur();
	_ordre = _tabNoeuds.taille() - l;
	_table_fonctions.taille(_ordre + 1);
		
	//Vérification du tableau de noeuds
	if(!_tabNoeuds.croissant())	throw NoeudsIncorrects();
	

}

//constructeur par recopie
CourbeNURBS::CourbeNURBS(const CourbeNURBS &c) : CourbeAPoles(c)
{
	
	_estModifie = true;
	_ordre = c._ordre;	
	_tabNoeuds = c._tabNoeuds;
	_table_fonctions.taille(_ordre + 1);
	_options = c._options;
	_tolEch = c._tolEch;
	_idCourbe = 0;
}

//Destructeur
CourbeNURBS::~CourbeNURBS()
{
	if(_idCourbe != 0) glDeleteLists(_idCourbe,1);  //on supprime la Display List d'OpenGL
}

//Cette fonction permet l'affichage OpenGL de la courbe grâce à une Display List
void CourbeNURBS::afficher()
{
	if((_options & DESSINER_LIGNE_POLYGONALE) !=0)
		CourbeAPoles::afficher();  //Ceci est utilisé pour visualiser la ligne polygonale
	if (_estModifie) 
	{
		calculerBoiteEnglobante();
		if(_idCourbe != 0) glDeleteLists(_idCourbe,1);  //on supprime la Display List d'OpenGL pour en créer une nouvelle
		_idCourbe = glGenLists (1);
		glNewList(_idCourbe,GL_COMPILE);
		
		GLUnurbsObj *theNurbs;
		theNurbs = gluNewNurbsRenderer();

		gluNurbsProperty(theNurbs,GLU_SAMPLING_TOLERANCE,_tolEch);
		
		if((_options & FIL_DE_FER) == 0)
			gluNurbsProperty(theNurbs,GLU_DISPLAY_MODE,GLU_FILL);
		else
			gluNurbsProperty(theNurbs,GLU_DISPLAY_MODE,GLU_OUTLINE_POLYGON);
		
		if(retournerPtrCtl() != NULL)  //Sinon il n'y a rien à afficher
		{		
			gluBeginCurve(theNurbs);
			gluNurbsCurve(theNurbs, 
				(GLint) _tabNoeuds.taille(),(GLfloat *) _tabNoeuds.list(),
				4,  //4 signifie que l'on est en coordonnée homogène sinon c'est 3 //(GLint) _stride
				retournerPtrCtl(), 
				(GLint) _ordre,
				GL_MAP1_VERTEX_4);
			gluEndCurve(theNurbs);
		}
		_estModifie = false;
		glEndList();
  }
  glCallList(_idCourbe);

}

//Les modifieurs
void CourbeNURBS::modifierNoeud(int pos, float val)
{
	_estModifie = true;
	try
	{
		_tabNoeuds[pos] = val;
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//on vérifie de plus si le tableau reste croissant

	if(!_tabNoeuds.croissant())	throw NoeudsIncorrects();
}


void CourbeNURBS::modifierTolEch(float t)
{
	_estModifie = true;
	if(t>=0)
		_tolEch = t;
	else
		throw ToleranceIncorrect();
}

void CourbeNURBS::options(int val)
{
	if(val !=  _options)
	{
		_estModifie = true;
		_options =val;
	}
}

//Les fournisseurs
float CourbeNURBS::fournirNoeud(int pos) const
{
	float tmp;
	try
	{
		tmp = _tabNoeuds[pos];
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	return tmp;
}

int CourbeNURBS::fournirNbreNoeuds() const
{
	return _tabNoeuds.taille();
}

int CourbeNURBS::fournirOrdre() const
{
	return _ordre;
}

float CourbeNURBS::fournirTolEch() const
{
	return _tolEch;
}

int CourbeNURBS::options() const
{
	return _options;
}


//Chargement d'une nurbs à partir d'un flux
void CourbeNURBS::load(FXStream &store)
{
	_estModifie = true;
	
	CourbeAPoles::load(store);
	_tabNoeuds.load(store);

	int l = fournirNbrePointsCtl();

	store >> _tolEch >> _options;
	
	_table_fonctions.supprimerTout();

	_ordre = _tabNoeuds.taille() - l;

	_table_fonctions.taille(_ordre + 1);

	//on calcule ensuite la boite englobante
	calculerBoiteEnglobante();
	
}

//Sauvegarde d'une nurbs dans un flux
void CourbeNURBS::save(FXStream &store) const
{
	
	CourbeAPoles::save(store);
	_tabNoeuds.save(store);
	
	store << _tolEch <<  _options;
}


/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*                     calcul des k fonctions de base non nulles en t
/* D'après Marc DANIEL
 */
void CourbeNURBS::calbsp(Tableau<float>& vknot,float t,int i,int k,Tableau<float> &b)
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
//Cette fonction permet le retour d'un point de la courbe
//à partir d'une coordonnée paramétrique
Point3D CourbeNURBS::retournerPoint(float s)
{
	int i;
	float xx;
	int l = fournirNbrePointsCtl();
	Point3D pcal,tmp;   /*Point calculé : pcal*/
	
	/*positionnement par rapport aux vecteurs de noeuds */
	i = posit(s);
	 
	
	if (i>0) 
	{
	/*                  calcul des k bsplines non nulles                  */
		calbsp(_tabNoeuds,s,i,_ordre,_table_fonctions);
		

		pcal.x = 0.0;
		pcal.y = 0.0;
		pcal.z = 0.0;
		pcal.w = 0.0;

		
			//ical1=(*iv-kv+j)*(nu+1)+*iu-ku;
			for (int i=1 ; i <= _ordre ; i++)
			{
				xx = _table_fonctions[i] ;//à vérifier
				//ical2=ical1+i;
				tmp = retournerPointCtl(i - _ordre + i);
				pcal.x = pcal.x + xx * tmp.x; //xcontr[ical2];
				pcal.y = pcal.y + xx * tmp.y; //ycontr[ical2];
				pcal.z = pcal.z + xx * tmp.z; //zcontr[ical2];
				pcal.w = pcal.w + xx * tmp.w;
			}
		
	}
	pcal.x = pcal.x / pcal.w;
	pcal.y = pcal.y / pcal.w;
	pcal.z = pcal.z / pcal.w;
	return pcal;
}

int CourbeNURBS::posit(float t)
/*Positionnement du paramètre dans le vecteur de noeuds 
  Voir l'algo de M.Daniel
*/
{
	float  tmin,tmax;
	int res;   //résultat de la fonction
	tmin = _tabNoeuds[0];
	tmax = _tabNoeuds[_tabNoeuds.taille()-1];
 
	if ((t < tmin) || ( t > tmax))
	   res = -1;                       /* en dehors de l'intervalle parametrique    */
	else
	{
		if (t==tmax)
		{
			res = _tabNoeuds.taille() - 1 - _ordre;                       
			while ((_tabNoeuds[res]==_tabNoeuds[res+1]) && (res>0))
			 res=res-1;
			if (res==0)
			 res=-2;                 /* erreur dans le vecteur de noeuds          */
		}
		else
		{
			res=_ordre-1;                   /* cas general : recherche a partir du debut */
			while ((t>=_tabNoeuds[res]) && (res < _tabNoeuds.taille()-1))
			 res=res+1;
			if (res == _tabNoeuds.taille()-1)
			 res=-2;
			else
			 res=res-1;
		}
	}
	return res;
}


CourbeNURBS & CourbeNURBS::operator =(CourbeNURBS &s)
{
	CourbeAPoles::operator =(s);
	_estModifie = true;
	_ordre = s._ordre;
	
	_tabNoeuds = s._tabNoeuds;
	
	_table_fonctions.taille(_ordre + 1);
	
	_options = s._options;
	_tolEch = s._tolEch;
	_idCourbe = 0;
	return *this;
}

void CourbeNURBS::ajouterNoeud(float n)
{
	_estModifie = true;
	_tabNoeuds.ajouter(n);
	//pour rester cohérent avec la liste de points de contrôle, l'ordre augmente de 1
	_ordre ++;
	if(!_tabNoeuds.croissant())	throw NoeudsIncorrects();
}



void CourbeNURBS::insererNoeud(int pos,float n)
{
	_estModifie = true;
	try
	{
		_tabNoeuds.inserer(pos,n);
		//pour rester cohérent avec la liste de points de contrôle, l'ordre augmente de 1
		_ordre ++;

	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//on vérifie de plus si le tableau reste croissant

	if(!_tabNoeuds.croissant())	throw NoeudsIncorrects();
}



void CourbeNURBS::supprimerNoeud(int pos)
{
	_estModifie = true;
	try
	{
		_tabNoeuds.supprimer(pos);
	}
	catch(Tableau<float>::DepassementTableau &)
	{
		throw DepassementTableau();
	}
	//pour rester cohérent avec la liste de points de contrôle, l'ordre diminue de 1
	_ordre--;
	//on vérifie de plus que l'ordre ne devienne pas négatif
	if(_ordre < 0) throw NoeudsIncorrects();
}






void CourbeNURBS::insererPointCtl(int pos,const Point3D& p)
{
	_estModifie = true;
	CourbeAPoles::insererPointCtl(pos,p);
	//pour rester cohérent  on diminue l'ordre de 1
	_ordre--;
	//on vérifie de plus que l'ordre ne devienne pas négatif
	if(_ordre< 0) throw NoeudsIncorrects();
}


void CourbeNURBS::supprimerPointCtl(int pos)
{
	_estModifie = true;
	CourbeAPoles::supprimerPointCtl(pos);
	//pour rester cohérent  on augmente l'ordre de 1
	_ordre ++;
}











