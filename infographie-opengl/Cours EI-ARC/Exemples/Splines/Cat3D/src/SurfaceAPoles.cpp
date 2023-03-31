/*Ce fichier contient l'implémentation de la classe SurfaceAPoles
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/

#include "SurfaceAPoles.h"

FXIMPLEMENT(SurfaceAPoles,Surface,NULL,0)

SurfaceAPoles::SurfaceAPoles()
{

}

SurfaceAPoles::~SurfaceAPoles()
{

}

SurfaceAPoles::SurfaceAPoles(MatricePoints &mp) : _surfaceCtl(mp) 
{
	_estModifie = true;
	calculerBoiteEnglobante();
}

void SurfaceAPoles::modifierPointCtl(int i, int j,Point3D &P)
{
	
	_estModifie = true;
	_surfaceCtl.modifierPoint(i,j,P);


}

Point3D SurfaceAPoles::fournirPointCtl(int i, int j)
{
	return _surfaceCtl.retournerPoint(i,j);
}

void SurfaceAPoles::load(FXStream &store)
{
	Surface::load(store);
	_surfaceCtl.load(store);

}

void SurfaceAPoles::save(FXStream &store) const
{
	Surface::save(store);
	_surfaceCtl.save(store);
}


SurfaceAPoles::SurfaceAPoles(const SurfaceAPoles &s) : _surfaceCtl(s._surfaceCtl)
{
	_surfaceCtl = s._surfaceCtl;
}

SurfaceAPoles & SurfaceAPoles::operator =(const SurfaceAPoles &s)
{
	if(this != &s)
	{
		Surface::operator =(s);
		_surfaceCtl = s._surfaceCtl;
	}
	return *this;
}

void SurfaceAPoles::afficher()
{
	//if(_estModifie) calculerBoiteEnglobante();
	_surfaceCtl.afficher();
}

Point3D SurfaceAPoles::retournerPointCtl(int s, int t)
{
	return _surfaceCtl.retournerPoint((int) s,(int) t);
}

Point3D SurfaceAPoles::retournerPoint(float s, float t)
{
	return _surfaceCtl.retournerPoint((int) s,(int) t);
}

void SurfaceAPoles::insererColonneCtl(int pos,const ListePoints& l)
{
	_estModifie = true;
	_surfaceCtl.insererColonne(pos,l);
	
}

void SurfaceAPoles::insererLigneCtl(int pos,const ListePoints& l)
{
	_estModifie = true;
	_surfaceCtl.insererLigne(pos,l);
	
}

void SurfaceAPoles::supprimerColonneCtl(int pos)
{
	_estModifie = true;
	_surfaceCtl.supprimerColonne(pos);
	
}

void SurfaceAPoles::supprimerLigneCtl(int pos)
{
	_estModifie = true;
	_surfaceCtl.supprimerLigne(pos);
	
}

int SurfaceAPoles::fournirNbreLignesCtl() const
{
	return _surfaceCtl.fournirNb_lignes();
}

int SurfaceAPoles::fournirNbreColonnesCtl() const
{
	return _surfaceCtl.fournirNb_colonnes();
}

float * SurfaceAPoles::retournerPtrCtl()
{
	return _surfaceCtl.retournerTableauPoints();
}

void SurfaceAPoles::calculerBoiteEnglobante()
{
	Point3D min,max;
	min = _surfaceCtl.retournerPoint(0,0);
	max = min;
	/*on calcul le point miniumu et maximum pour la construction de la
	boite englobante héritée de FXGLShape*/
	for (int i=0;i < _surfaceCtl.fournirNb_lignes() ; i++)
	{
		for (int j=0;j < _surfaceCtl.fournirNb_colonnes() ; j++)
		{
			Point3D tmp = _surfaceCtl.retournerPoint(i,j);
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
