/*Ce fichier contient l'ilplémentation de la classe CourbeAPoles
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "CourbeAPoles.h"

FXIMPLEMENT(CourbeAPoles,Courbe,NULL,0)

CourbeAPoles::CourbeAPoles()
{

}

CourbeAPoles::~CourbeAPoles()
{

}

CourbeAPoles::CourbeAPoles(ListePoints &lp) : _CourbeCtl(lp) 
{
	_estModifie = true;
	calculerBoiteEnglobante();
}

void CourbeAPoles::modifierPointCtl(int i,Point3D &P)
{
	
	_estModifie = true;
	_CourbeCtl.modifierPoint(i,P);


}

Point3D CourbeAPoles::fournirPointCtl(int i)
{
	return _CourbeCtl.retournerPoint(i);
}

void CourbeAPoles::load(FXStream &store)
{
	Courbe::load(store);
	_CourbeCtl.load(store);

}

void CourbeAPoles::save(FXStream &store) const
{
	Courbe::save(store);
	_CourbeCtl.save(store);
}


CourbeAPoles::CourbeAPoles(const CourbeAPoles &c) : _CourbeCtl(c._CourbeCtl)
{
	_CourbeCtl = c._CourbeCtl;
}

CourbeAPoles & CourbeAPoles::operator =(const CourbeAPoles &c)
{
	if(this != &c)
	{
		Courbe::operator =(c);
		_CourbeCtl = c._CourbeCtl;
	}
	return *this;
}

void CourbeAPoles::afficher()
{
	//if(_estModifie) calculerBoiteEnglobante();
	_CourbeCtl.afficher();
}

Point3D CourbeAPoles::retournerPointCtl(int s)
{
	return _CourbeCtl.retournerPoint((int) s);
}

Point3D CourbeAPoles::retournerPoint(float s)
{
	return _CourbeCtl.retournerPoint((int) s);
}

void CourbeAPoles::insererPointCtl(int pos,const Point3D& p)
{
	_estModifie = true;
	_CourbeCtl.inserer(pos,p);
	
}


void CourbeAPoles::supprimerPointCtl(int pos)
{
	_estModifie = true;
	_CourbeCtl.supprimer(pos);
	
}


int CourbeAPoles::fournirNbrePointsCtl() const
{
	return _CourbeCtl.longueur();
}


float * CourbeAPoles::retournerPtrCtl()
{
	return _CourbeCtl.retournerTableauPoints();
}

void CourbeAPoles::calculerBoiteEnglobante()
{
	Point3D min,max;
	min = _CourbeCtl.retournerPoint(0);
	max = min;
	/*on calcule le point minimum et maximum pour la construction de la
	boite englobante héritée de FXGLShape*/
	
	for (int j=0;j < _CourbeCtl.longueur() ; j++)
	{
		Point3D tmp = _CourbeCtl[j];
		if (tmp.x < min.x)
			min.x = tmp.x;
		if (tmp.y < min.y)
			min.y = tmp.y;
		if (tmp.z < min.z)
			min.z = tmp.z;
		if (tmp.x > max.x)
			max.x = tmp.x;
		if (tmp.y > max.y)
			max.y = tmp.y;
		if (tmp.z > max.z)
			max.z = tmp.z;
	}
	/*position correspond à la position du centre de gravité de l'objet
	cette variable a été héritée de FXGLShape*/
	position[0] = (min.x + max.x)/2;
	position[1] = (min.y + max.y)/2;
	position[2] = (min.z + max.z)/2;
	/*Boite englobante*/
	range[0][0]=min.x;  
	range[1][0]=min.y;
	range[2][0]=min.z;
	range[0][1]=max.x;  
	range[1][1]=max.y;
	range[2][1]=max.z;
}
