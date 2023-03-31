/*Ce fichier contient l'interface de la classe FenetrePropriete
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#ifndef FENETREPROPRIETE_H
#define FENETREPROPRIETE_H

#include <iostream>
#include "FenetreVisualisation.h"
#include "fx.h"
#include "fx3d.h"
#include "Objet3D.h"
#include "Point3D.h"
#include "LignePolygonale.h"
#include "SurfaceBezier.h"
#include "CourbeBezier.h"

using  std::cout;

class FenetrePropriete : public FXDialogBox 
{
	FXDECLARE(FenetrePropriete)
private:
	FenetrePropriete(){}
	FenetrePropriete(const FenetrePropriete&);
	FXTable *_tableCtl;
	FXTable *_tableNoeuds1;
	FXTable *_tableNoeuds2;
	FXTextField* caseCtlZ;
	FXTextField* caseCtlY;
	FXTextField* caseCtlX;
	FXTextField* caseCtlPoids;
	FXTextField* caseNoeuds1;
	FXTextField* caseNoeuds2;
	FXTextField* caseTolerance;
	FXCheckButton* chkFilDeFer;
	FXCheckButton* chkDessinerSurfCtl;
	FenetreVisualisation *_owner;
	SurfaceNURBS * _pSurfaceNURBS;
	Objet3D *_pObjet3D;
	LignePolygonale *_pLignePoly;
	SurfacePolyedrique * _pSurfPoly;

	// plein de variables
	ListePoints *_pLPoints;
	MatricePoints *_pMPoints;
	CourbeNURBS * _pCNurbs;
	bool _ontChanges;   //Si on a modifié les propriétés d'un Objet3D
public:
	FenetrePropriete(FenetreVisualisation *owner,const FXString& title);
	virtual ~FenetrePropriete();

	long onChgtCellCtl(FXObject*,FXSelector,void*);
	long onChgtCaseCtl(FXObject*,FXSelector,void*);
	long onChgtCaseNoeuds1(FXObject*,FXSelector,void*);
	long onChgtCaseNoeuds2(FXObject*,FXSelector,void*);
	long onChgtCellNoeuds1(FXObject*,FXSelector,void*);
	long onChgtCellNoeuds2(FXObject*,FXSelector,void*);
	long onChgtChkFilDeFer(FXObject*,FXSelector,void*);
	
	long onChgtchkDessinerSurfCtl(FXObject*,FXSelector,void*);
	long onChgtCaseTolerance(FXObject*,FXSelector,void*);
	long onModifier(FXObject*,FXSelector,void*);
	long onInsererColonneCtl(FXObject *,FXSelector,void*);
	long onInsererLigneCtl(FXObject *,FXSelector,void*);
	long onSupprimerColonneCtl(FXObject *,FXSelector,void*);
	long onSupprimerLigneCtl(FXObject *,FXSelector,void*);
	long onSupprimerCaseNoeud1(FXObject *,FXSelector,void*);
	long onInsererCaseNoeud1(FXObject *,FXSelector,void*);
	long onSupprimerCaseNoeud2(FXObject *,FXSelector,void*);
	long onInsererCaseNoeud2(FXObject *,FXSelector,void*);

	enum{
		ID_TABLE_CTL=FXDialogBox::ID_LAST,
		ID_CASE_CTL_X,
		ID_CASE_CTL_Y,
		ID_CASE_CTL_Z,
		ID_CASE_CTL_POIDS,
		ID_CASE_NOEUDS1,
		ID_CASE_NOEUDS2,
		ID_TABLE_NOEUDS1,
		ID_TABLE_NOEUDS2,
		ID_OPT_FIL_DE_FER,
		ID_CASE_TOLERANCE,
		ID_MODIFIER,
		ID_INSERER_COLONNE_CTL,
		ID_INSERER_LIGNE_CTL,
		ID_SUPPRIMER_COLONNE_CTL,
		ID_SUPPRIMER_LIGNE_CTL,
		ID_INSERER_CASE_NOEUD1,
		ID_SUPPRIMER_CASE_NOEUD1,
		ID_INSERER_CASE_NOEUD2,
		ID_SUPPRIMER_CASE_NOEUD2,
		ID_DESSINER_SURFACE_POLYEDRIQUE,
		ID_LAST
	};
};



#endif
