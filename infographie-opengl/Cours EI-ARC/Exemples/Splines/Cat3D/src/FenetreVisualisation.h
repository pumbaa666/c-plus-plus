/*Ce fichier contient l'interface de la classe FenetreVisualisation
**Projet de POO 2001 : Listes d'objets 3D
**Auteurs : Avril   BLAISE
**          Thomas  ROUCH
**          Cyrille HEIT
**ESIL, Département ES2I, Promotion 2002
*/
#ifndef FENETREVISUALISATION_H
#define FENETREVISUALISATION_H

#include <iostream>
#include "fx.h"
#include "fx3d.h"
#include "Objet3D.h"
#include "Point3D.h"
#include "LignePolygonale.h"
#include "SurfaceBezier.h"
#include "Polygone.h"

#include <stdio.h>
using  std::cout;

// Fenêtre Principale
class FenetreVisualisation : public FXMainWindow {
	FXDECLARE(FenetreVisualisation)
private:
	FXToolbar         *toolbar;                 
	FXMenuBar         *menubar;                 
	FXMDIClient       *mdiclient;               
	FXStatusbar       *statusbar;              
                  
	FXGIFIcon         *mdiicon;                 
	FXMenuPane        *mdimenu;                 
	FXGLVisual        *glvisual;                
	FXMenuPane        *filemenu;
	FXMenuPane        *editmenu;
	FXMenuPane        *viewmenu;
	FXMenuPane        *rendermenu;
	FXMenuPane        *windowmenu;
	FXMenuPane        *menuAide;
	FXString			nom_fichier;
	//FXGLGroup			*gp2;
	FXMenuPane        *menuCreation;
	FXGLContext       *glcontext;
	
protected:
	FenetreVisualisation(){}
public:
	
	enum{
		ID_ABOUT=FXMainWindow::ID_LAST,
			ID_OPEN,
			ID_NEWVIEWER,
			ID_QUERY_MODE,
			ID_GLVIEWER,
			ID_FEN_PROP_NURBS,
			ID_CREER_SURF_NURBS,
			ID_CREER_SURF_BEZIERRAT,
			ID_CREER_SURF_BSPLINE,
			ID_CREER_SURF_BEZIER,
			ID_CREER_SURF_POLYEDRIQUE,
			ID_CREER_LIGNE,
			ID_CREER_SEGMENT,
			ID_CREER_POLYGONE,
			ID_SUPPRIMER_OBJET3D,
			ID_ENREGISTRER,
			ID_ENREGISTRER_SOUS,
			ID_CREER_COURBE_NURBS,
			ID_CREER_COURBE_BEZIERRAT,
			ID_CREER_COURBE_BSPLINE,
			ID_CREER_COURBE_BEZIER,
			ID_NOUVEAU
    };
	
	long onCmdOpen(FXObject*,FXSelector,void*);
	long onCmdNewViewer(FXObject*,FXSelector,void*);
	long onCmdAbout(FXObject*,FXSelector,void*);
	long onUpdMode(FXObject*,FXSelector,void*);
	long onQueryMenu(FXObject*,FXSelector,void*);
	long onChangedCurrentGLObject(FXObject*,FXSelector,void*);
	long onCreerSurfNURBS(FXObject*,FXSelector,void*);
	long onCreerSurfBezier(FXObject *,FXSelector,void *);
	long onCreerSurfBezierRat(FXObject *,FXSelector,void *);
	long onCreerSurfBSpline(FXObject *,FXSelector,void *);
	long onCreerLigne(FXObject*,FXSelector,void*);
	long onCreerSegment(FXObject*,FXSelector,void*);
	long onCreerSurfacePolyedrique(FXObject*,FXSelector,void*);
	long onCreerPolygone(FXObject*,FXSelector,void*);
	long onSupprimerObjet3D(FXObject*,FXSelector,void*);
	long onEnregistrer(FXObject*,FXSelector,void*);
	long onEnregistrerSous(FXObject*,FXSelector,void*);
	long onNouveau(FXObject*,FXSelector,void*);
	long onCreerCourbeNURBS(FXObject*,FXSelector,void*);
	long onCreerCourbeBezier(FXObject *,FXSelector,void *);
	long onCreerCourbeBezierRat(FXObject *,FXSelector,void *);
	long onCreerCourbeBSpline(FXObject *,FXSelector,void *);
	
	
	
	FXGLViewer *viewer;
	FXGLGroup  *scene; 
	long onCmdPropNurbs(FXObject *,FXSelector,void*);
	
	FenetreVisualisation(FXApp* a);
	
	virtual void create();
	virtual ~FenetreVisualisation();
};
#endif
