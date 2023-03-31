#include "FenetrePropriete.h"

FXDEFMAP(FenetrePropriete) FenetreProprieteMap[]={
	FXMAPFUNC(SEL_CLICKED,FenetrePropriete::ID_TABLE_CTL,FenetrePropriete::onChgtCellCtl),
		FXMAPFUNCS(SEL_FOCUSOUT,FenetrePropriete::ID_CASE_CTL_X,FenetrePropriete::ID_CASE_CTL_POIDS,FenetrePropriete::onChgtCaseCtl),  //le "S" est important-> plusieurs maps en même temps
		FXMAPFUNC(SEL_FOCUSOUT,FenetrePropriete::ID_CASE_NOEUDS1,FenetrePropriete::onChgtCaseNoeuds1),
		FXMAPFUNC(SEL_FOCUSOUT,FenetrePropriete::ID_CASE_NOEUDS2,FenetrePropriete::onChgtCaseNoeuds2),
		FXMAPFUNC(SEL_CLICKED,FenetrePropriete::ID_TABLE_NOEUDS1,FenetrePropriete::onChgtCellNoeuds1),
		FXMAPFUNC(SEL_CLICKED,FenetrePropriete::ID_TABLE_NOEUDS2,FenetrePropriete::onChgtCellNoeuds2),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_MODIFIER,FenetrePropriete::onModifier),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_OPT_FIL_DE_FER,FenetrePropriete::onChgtChkFilDeFer),
		FXMAPFUNC(SEL_FOCUSOUT,FenetrePropriete::ID_CASE_TOLERANCE,FenetrePropriete::onChgtCaseTolerance),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_INSERER_COLONNE_CTL,FenetrePropriete::onInsererColonneCtl),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_INSERER_LIGNE_CTL,FenetrePropriete::onInsererLigneCtl),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_SUPPRIMER_COLONNE_CTL,FenetrePropriete::onSupprimerColonneCtl),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_SUPPRIMER_LIGNE_CTL,FenetrePropriete::onSupprimerLigneCtl),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_SUPPRIMER_CASE_NOEUD1,FenetrePropriete::onSupprimerCaseNoeud1),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_INSERER_CASE_NOEUD1,FenetrePropriete::onInsererCaseNoeud1),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_SUPPRIMER_CASE_NOEUD2,FenetrePropriete::onSupprimerCaseNoeud2),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_INSERER_CASE_NOEUD2,FenetrePropriete::onInsererCaseNoeud2),
		FXMAPFUNC(SEL_COMMAND,FenetrePropriete::ID_DESSINER_SURFACE_POLYEDRIQUE,FenetrePropriete::onChgtchkDessinerSurfCtl),
		
};


FXIMPLEMENT(FenetrePropriete,FXDialogBox,FenetreProprieteMap,ARRAYNUMBER(FenetreProprieteMap))


FenetrePropriete::FenetrePropriete(FenetreVisualisation *owner,const FXString& title):
FXDialogBox(owner,title,DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
{
	_ontChanges = false;
	_pObjet3D = (Objet3D *) (owner->viewer->getSelection());
	_owner =owner;
	FXVerticalFrame *frameGenerale;
	if (_pObjet3D == NULL)
    {
		//on a pas selectionné un objet graphique
		frameGenerale=new FXVerticalFrame(this,LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
		new FXLabel(frameGenerale,"Vous devez selectionner un objet 3D !!!",NULL,JUSTIFY_LEFT|ICON_BEFORE_TEXT|LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
		new FXButton(frameGenerale,"&OK\t",NULL,this,ID_CANCEL,FRAME_THICK|FRAME_RAISED|LAYOUT_CENTER_X);
		
    }
	else
    {
		
        if (_pObjet3D->getClassName() == FXString("LignePolygonale") 
            || _pObjet3D->getClassName() == FXString("Segment")
            || _pObjet3D->getClassName() == FXString("Polygone")) 
        {
		    frameGenerale=new FXVerticalFrame(this,LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
            FXHorizontalFrame *frame=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
            FXVerticalFrame *frameG=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
            //   
            new FXLabel(frameG,_pObjet3D->getClassName(),NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
			_tableCtl =new FXTable(frameG,2,5,this,ID_TABLE_CTL,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
			_pLPoints=(ListePoints *) _pObjet3D;
			
			
			_tableCtl->setTableSize(1,_pLPoints->longueur());
			
			for(int i = 0;i< _pLPoints->longueur();i++) {
				_pLPoints->retournerPoint(i);
				
				_tableCtl->setItemText(0,i,FXStringVal(_pLPoints->retournerPoint(i).x)
					+","+FXStringVal(_pLPoints->retournerPoint(i).y)
					+","+FXStringVal(_pLPoints->retournerPoint(i).z)
					+","+FXStringVal(_pLPoints->retournerPoint(i).w));
			}
			
			FXHorizontalFrame *frameBoutonListe=new FXHorizontalFrame(frameG,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			
			new FXButton(frameBoutonListe,"&Inserer point\t",
				NULL,this,
				ID_INSERER_COLONNE_CTL, 
				FRAME_THICK|FRAME_RAISED);
			new FXButton(frameBoutonListe,"&Supprimer point\t",
				NULL,this,
				ID_SUPPRIMER_COLONNE_CTL, 
				FRAME_THICK|FRAME_RAISED);
			
			
			
			FXVerticalFrame *frameCaseCtl=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			new FXLabel(frameCaseCtl,"Point :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
			FXMatrix *matriceCaseCtl=new FXMatrix(frameCaseCtl,2,MATRIX_BY_COLUMNS|LAYOUT_FILL_Y|LAYOUT_CENTER_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);
			
			new FXLabel(matriceCaseCtl,"X :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlX=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_X,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlX->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Y :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlY=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Y,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlY->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Z :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlZ=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Z,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlZ->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Poids :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlPoids=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_POIDS,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlPoids->setTipText("Case correspondant à ...");
			caseCtlPoids->disable(); //Il n'y a pas ici de notion de poids

			
		}
		else if (_pObjet3D->getClassName() == FXString("SurfacePolyedrique")) 
		{
			_pSurfPoly = (SurfacePolyedrique *) _pObjet3D;
			
			frameGenerale=new FXVerticalFrame(this,LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			FXHorizontalFrame *frame=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			FXVerticalFrame *frameG=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			//Matrice de Points	 
			new FXLabel(frameG,"Matrice des points",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
			_tableCtl =new FXTable(frameG,5,5,this,ID_TABLE_CTL,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
			_tableCtl->setTableSize(_pSurfPoly->fournirNb_lignes(),_pSurfPoly->fournirNb_colonnes());
			for(int i = 0;i< _pSurfPoly->fournirNb_lignes();i++)
			{
				for(int j=0;j<_pSurfPoly->fournirNb_colonnes();j++)
					_tableCtl->setItemText(i,j,FXStringVal(_pSurfPoly->retournerPoint(i,j).x)
					+","+FXStringVal(_pSurfPoly->retournerPoint(i,j).y)
					+","+FXStringVal(_pSurfPoly->retournerPoint(i,j).z)
					+","+FXStringVal(_pSurfPoly->retournerPoint(i,j).w));
			}	
			FXHorizontalFrame *frameBoutonMatriceCtl=new FXHorizontalFrame(frameG,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			
			new FXButton(frameBoutonMatriceCtl,"&Inserer colonne\t",
				NULL,this,
				ID_INSERER_COLONNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			new FXButton(frameBoutonMatriceCtl,"&Inserer ligne\t",
				NULL,this,
				ID_INSERER_LIGNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			
			new FXButton(frameBoutonMatriceCtl,
				"&Supprimer colonne\t",
				NULL,
				this,
				ID_SUPPRIMER_COLONNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			new FXButton(frameBoutonMatriceCtl,
				"&Supprimer ligne\t",
				NULL,
				this,
				ID_SUPPRIMER_LIGNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			
			
			FXVerticalFrame *frameCaseCtl=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			new FXLabel(frameCaseCtl,"Point de Contrôle :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
			FXMatrix *matriceCaseCtl=new FXMatrix(frameCaseCtl,2,MATRIX_BY_COLUMNS|LAYOUT_FILL_Y|LAYOUT_CENTER_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);
			
			new FXLabel(matriceCaseCtl,"X :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlX=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_X,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlX->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Y :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlY=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Y,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlY->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Z :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlZ=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Z,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlZ->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Poids :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlPoids=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_POIDS,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlPoids->setTipText("Case correspondant à ...");	
			caseCtlPoids->disable(); //Il n'y a pas ici de notion de poids
			
			
		}
		else if (_pObjet3D->getClassName() == FXString("CourbeBezier") 
			|| _pObjet3D->getClassName() == FXString("CourbeBSpline") 
			||  _pObjet3D->getClassName() == FXString("CourbeNURBS") 
			|| _pObjet3D->getClassName() == FXString("CourbeBezierRat")) 
		{
			_pCNurbs = (CourbeNURBS *) _pObjet3D;
			
			frameGenerale=new FXVerticalFrame(this,LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			FXHorizontalFrame *frame=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			FXVerticalFrame *frameG=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			//Tableau de Controle	 
			new FXLabel(frameG,"Tableau des points de contrôles",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
			_tableCtl =new FXTable(frameG,2,5,this,ID_TABLE_CTL,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
			_tableCtl->setTableSize(1,_pCNurbs->fournirNbrePointsCtl());
			
			for(int j=0;j<_pCNurbs->fournirNbrePointsCtl();j++)
				_tableCtl->setItemText(0,j,FXStringVal(_pCNurbs->fournirPointCtl(j).x)
				+","+FXStringVal(_pCNurbs->fournirPointCtl(j).y)
				+","+FXStringVal(_pCNurbs->fournirPointCtl(j).z)
				+","+FXStringVal(_pCNurbs->fournirPointCtl(j).w));
			
			FXHorizontalFrame *frameBoutonMatriceCtl=new FXHorizontalFrame(frameG,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			
			new FXButton(frameBoutonMatriceCtl,"&Inserer case\t",
				NULL,this,
				ID_INSERER_COLONNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			new FXButton(frameBoutonMatriceCtl,
				"&Supprimer case\t",
				NULL,
				this,
				ID_SUPPRIMER_COLONNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			
			
			FXVerticalFrame *frameCaseCtl=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			new FXLabel(frameCaseCtl,"Point de Contrôle :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
			FXMatrix *matriceCaseCtl=new FXMatrix(frameCaseCtl,2,MATRIX_BY_COLUMNS|LAYOUT_FILL_Y|LAYOUT_CENTER_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);
			
			new FXLabel(matriceCaseCtl,"X :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlX=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_X,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlX->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Y :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlY=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Y,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlY->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Z :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlZ=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Z,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlZ->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Poids :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlPoids=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_POIDS,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlPoids->setTipText("Case correspondant à ...");
			
			if(_pObjet3D->getClassName() == FXString("CourbeBezier") || _pObjet3D->getClassName() == "CourbeBSpline")
			{
				caseCtlPoids->disable();  //car le poids n'a aucune importance pour ces surfaces !!!
			}
			
			if(_pObjet3D->getClassName() == FXString("CourbeNURBS") || _pObjet3D->getClassName() == "CourbeBSpline")
			{
				//Tableau des noeuds
				FXHorizontalFrame *frame2=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
				FXVerticalFrame *frameNoeuds1=new FXVerticalFrame(frame2,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
				
				new FXLabel(frameNoeuds1,"Tableau des Noeuds",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
				
				_tableNoeuds1 =new FXTable(frameNoeuds1,2,5,this,ID_TABLE_NOEUDS1,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
				_tableNoeuds1->setTableSize(1,_pCNurbs->fournirNbreNoeuds());
				int j;
				for(j=0;j<_pCNurbs->fournirNbreNoeuds();j++)
					_tableNoeuds1->setItemText(0,j,FXStringVal(_pCNurbs->fournirNoeud(j)));
				
				FXHorizontalFrame *frameBoutonTabNoeuds1=new FXHorizontalFrame(frameNoeuds1,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
				new FXButton(frameBoutonTabNoeuds1,"&Inserer case\t",NULL,this,ID_INSERER_CASE_NOEUD1,FRAME_THICK|FRAME_RAISED);
				new FXButton(frameBoutonTabNoeuds1,"&Supprimer case\t",NULL,this,ID_SUPPRIMER_CASE_NOEUD1,FRAME_THICK|FRAME_RAISED);
				
				
				FXVerticalFrame *frameCaseNoeud1=new FXVerticalFrame(frame2,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
				new FXLabel(frameCaseNoeud1,"Noeud :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
				
				caseNoeuds1=new FXTextField(frameCaseNoeud1,10,this,ID_CASE_NOEUDS1,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
				
			}
			
			//options de la NURBS
			FXVerticalFrame *frameOptions=new FXVerticalFrame(frameGenerale,FRAME_THICK|LAYOUT_FILL_X|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			
			//new FXLabel(frameOptions,"Options :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
			
			FXMatrix *matriceOptions=new FXMatrix(frameOptions,7,MATRIX_BY_COLUMNS|LAYOUT_FILL_Y|LAYOUT_CENTER_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);
			
			//chkFilDeFer = new FXCheckButton(matriceOptions,"Fil de fer",this,ID_OPT_FIL_DE_FER,LAYOUT_LEFT|ICON_AFTER_TEXT);
			//chkFilDeFer->setCheck((_pCNurbs->options()&FIL_DE_FER)!=0);
			
			chkDessinerSurfCtl = new FXCheckButton(matriceOptions,"Dessiner courbe de contrôle",this,ID_DESSINER_SURFACE_POLYEDRIQUE,LAYOUT_LEFT|ICON_AFTER_TEXT);
			chkDessinerSurfCtl->setCheck((_pCNurbs->options()&DESSINER_LIGNE_POLYGONALE)!=0);
			
			new FXLabel(matriceOptions,"Tolérance :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseTolerance=new FXTextField(matriceOptions,10,this,ID_CASE_TOLERANCE,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseTolerance->setTipText("Case correspondant à ...");
			caseTolerance->setText(FXStringVal(_pCNurbs->fournirTolEch()));	
			
		}
		else if (_pObjet3D->getClassName() == FXString("SurfaceBezier") 
			|| _pObjet3D->getClassName() == FXString("SurfaceBSpline") 
			||  _pObjet3D->getClassName() == FXString("SurfaceNURBS") 
			|| _pObjet3D->getClassName() == FXString("SurfaceBezierRat")) 
		{
			
			_pSurfaceNURBS = (SurfaceNURBS *) _pObjet3D;
			
			frameGenerale=new FXVerticalFrame(this,LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			FXHorizontalFrame *frame=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			FXVerticalFrame *frameG=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			//Matrice de Controle	 
			new FXLabel(frameG,"Matrice des points de contrôles",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
			_tableCtl =new FXTable(frameG,5,5,this,ID_TABLE_CTL,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
			_tableCtl->setTableSize(_pSurfaceNURBS->fournirNbreLignesCtl(),_pSurfaceNURBS->fournirNbreColonnesCtl());
			for(int i = 0;i< _pSurfaceNURBS->fournirNbreLignesCtl();i++)
			{
				for(int j=0;j<_pSurfaceNURBS->fournirNbreColonnesCtl();j++)
					_tableCtl->setItemText(i,j,FXStringVal(_pSurfaceNURBS->fournirPointCtl(i,j).x)
					+","+FXStringVal(_pSurfaceNURBS->fournirPointCtl(i,j).y)
					+","+FXStringVal(_pSurfaceNURBS->fournirPointCtl(i,j).z)
					+","+FXStringVal(_pSurfaceNURBS->fournirPointCtl(i,j).w));
			}	
			FXHorizontalFrame *frameBoutonMatriceCtl=new FXHorizontalFrame(frameG,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
			
			new FXButton(frameBoutonMatriceCtl,"&Inserer colonne\t",
				NULL,this,
				ID_INSERER_COLONNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			new FXButton(frameBoutonMatriceCtl,"&Inserer ligne\t",
				NULL,this,
				ID_INSERER_LIGNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			
			new FXButton(frameBoutonMatriceCtl,
				"&Supprimer colonne\t",
				NULL,
				this,
				ID_SUPPRIMER_COLONNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			new FXButton(frameBoutonMatriceCtl,
				"&Supprimer ligne\t",
				NULL,
				this,
				ID_SUPPRIMER_LIGNE_CTL,
				FRAME_THICK|FRAME_RAISED);
			
			
			FXVerticalFrame *frameCaseCtl=new FXVerticalFrame(frame,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			new FXLabel(frameCaseCtl,"Point de Contrôle :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
			FXMatrix *matriceCaseCtl=new FXMatrix(frameCaseCtl,2,MATRIX_BY_COLUMNS|LAYOUT_FILL_Y|LAYOUT_CENTER_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);
			
			new FXLabel(matriceCaseCtl,"X :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlX=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_X,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlX->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Y :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlY=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Y,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlY->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Z :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlZ=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_Z,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlZ->setTipText("Case correspondant à ...");
			new FXLabel(matriceCaseCtl,"Poids :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseCtlPoids=new FXTextField(matriceCaseCtl,10,this,ID_CASE_CTL_POIDS,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseCtlPoids->setTipText("Case correspondant à ...");
			
			if(_pObjet3D->getClassName() == FXString("SurfaceBezier") || _pObjet3D->getClassName() == "SurfaceBSpline")
			{
				caseCtlPoids->disable();  //car le poids n'a aucune importance pour ces surfaces !!!
			}
			
			if(_pObjet3D->getClassName() == FXString("SurfaceNURBS") || _pObjet3D->getClassName() == "SurfaceBSpline")
			{
				//Tableau des noeuds 1
				FXHorizontalFrame *frame2=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
				FXVerticalFrame *frameNoeuds1=new FXVerticalFrame(frame2,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
				
				new FXLabel(frameNoeuds1,"Tableau des Noeuds 1",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
				
				_tableNoeuds1 =new FXTable(frameNoeuds1,2,5,this,ID_TABLE_NOEUDS1,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
				_tableNoeuds1->setTableSize(1,_pSurfaceNURBS->fournirNbreNoeuds_s());
				int j;
				for(j=0;j<_pSurfaceNURBS->fournirNbreNoeuds_s();j++)
					_tableNoeuds1->setItemText(0,j,FXStringVal(_pSurfaceNURBS->fournirNoeud_s(j)));
				
				FXHorizontalFrame *frameBoutonTabNoeuds1=new FXHorizontalFrame(frameNoeuds1,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
				new FXButton(frameBoutonTabNoeuds1,"&Inserer case\t",NULL,this,ID_INSERER_CASE_NOEUD1,FRAME_THICK|FRAME_RAISED);
				new FXButton(frameBoutonTabNoeuds1,"&Supprimer case\t",NULL,this,ID_SUPPRIMER_CASE_NOEUD1,FRAME_THICK|FRAME_RAISED);
				
				
				FXVerticalFrame *frameCaseNoeud1=new FXVerticalFrame(frame2,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
				new FXLabel(frameCaseNoeud1,"Noeud :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
				
				caseNoeuds1=new FXTextField(frameCaseNoeud1,10,this,ID_CASE_NOEUDS1,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
				
				//Tableau des noeuds 2
				FXHorizontalFrame *frame3=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
				FXVerticalFrame *frameNoeuds2=new FXVerticalFrame(frame3,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
				
				new FXLabel(frameNoeuds2,"Tableau des Noeuds 2",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);
				
				_tableNoeuds2 =new FXTable(frameNoeuds2,2,5,this,ID_TABLE_NOEUDS2,TABLE_HOR_GRIDLINES|TABLE_VER_GRIDLINES,0,0,0,0, 2,2,2,2);
				_tableNoeuds2->setTableSize(1,_pSurfaceNURBS->fournirNbreNoeuds_t());
				for(j=0;j<_pSurfaceNURBS->fournirNbreNoeuds_t();j++)
					_tableNoeuds2->setItemText(0,j,FXStringVal(_pSurfaceNURBS->fournirNoeud_t(j)));
				
				FXHorizontalFrame *frameBoutonTabNoeuds2=new FXHorizontalFrame(frameNoeuds2,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
				new FXButton(frameBoutonTabNoeuds2,"&Inserer case\t",NULL,this,ID_INSERER_CASE_NOEUD2,FRAME_THICK|FRAME_RAISED);
				new FXButton(frameBoutonTabNoeuds2,"&Supprimer case\t",NULL,this,ID_SUPPRIMER_CASE_NOEUD2,FRAME_THICK|FRAME_RAISED);
				
				FXVerticalFrame *frameCaseNoeud2=new FXVerticalFrame(frame3,FRAME_THICK|LAYOUT_FILL_Y|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
				new FXLabel(frameCaseNoeud2,"Noeud :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
				
				caseNoeuds2=new FXTextField(frameCaseNoeud2,10,this,ID_CASE_NOEUDS2,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			}
			
			//options de la NURBS
			FXVerticalFrame *frameOptions=new FXVerticalFrame(frameGenerale,FRAME_THICK|LAYOUT_FILL_X|LAYOUT_LEFT,0,0,0,0, 0,0,0,0);
			
			//new FXLabel(frameOptions,"Options :",NULL,JUSTIFY_RIGHT|LAYOUT_CENTER_X);
			
			FXMatrix *matriceOptions=new FXMatrix(frameOptions,7,MATRIX_BY_COLUMNS|LAYOUT_FILL_Y|LAYOUT_CENTER_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,10,10);
			
			chkFilDeFer = new FXCheckButton(matriceOptions,"Fil de fer",this,ID_OPT_FIL_DE_FER,LAYOUT_LEFT|ICON_AFTER_TEXT);
			chkFilDeFer->setCheck((_pSurfaceNURBS->options()&FIL_DE_FER)!=0);
			
			chkDessinerSurfCtl = new FXCheckButton(matriceOptions,"Dessiner surface contrôle",this,ID_DESSINER_SURFACE_POLYEDRIQUE,LAYOUT_LEFT|ICON_AFTER_TEXT);
			chkDessinerSurfCtl->setCheck((_pSurfaceNURBS->options()&DESSINER_SURFACE_POLYEDRIQUE)!=0);
			
			new FXLabel(matriceOptions,"Tolérance :",NULL,JUSTIFY_RIGHT|LAYOUT_RIGHT);
			caseTolerance=new FXTextField(matriceOptions,10,this,ID_CASE_TOLERANCE,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK);
			caseTolerance->setTipText("Case correspondant à ...");
			caseTolerance->setText(FXStringVal(_pSurfaceNURBS->fournirTolEch()));
			
		}
		
		//boutons de la fenêtre de dialogue
		new FXHorizontalSeparator(frameGenerale,SEPARATOR_RIDGE|LAYOUT_FILL_X);
		FXHorizontalFrame *frameBoutonDialogue=new FXHorizontalFrame(frameGenerale,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
		new FXButton(frameBoutonDialogue,"&Modifier\t",NULL,this,ID_MODIFIER,FRAME_THICK|FRAME_RAISED|LAYOUT_RIGHT);	  
		new FXButton(frameBoutonDialogue,"&Annuler\t",NULL,this,ID_CANCEL,FRAME_THICK|FRAME_RAISED|LAYOUT_RIGHT);
		
		
    }
}

long FenetrePropriete::onChgtCellCtl(FXObject* a,FXSelector b,void* c)
{
	
	int col = _tableCtl->getCurrentColumn();
	int lig = _tableCtl->getCurrentRow();
	int prem = _tableCtl->getItemText(lig,col).findf(",");
	int snd = _tableCtl->getItemText(lig,col).findf(",",prem+1);
	int trois = _tableCtl->getItemText(lig,col).findf(",",snd+1); 
	int fin = _tableCtl->getItemText(lig,col).size() - 1;
	caseCtlX->setText(_tableCtl->getItemText(lig,col).left(prem));
	caseCtlY->setText(_tableCtl->getItemText(lig,col).mid(prem+1,snd-prem-1));
	caseCtlZ->setText(_tableCtl->getItemText(lig,col).mid(snd+1,trois-snd-1));
	caseCtlPoids->setText(_tableCtl->getItemText(lig,col).right(fin - trois -1));
	return 1;
}

long FenetrePropriete::onChgtCellNoeuds1(FXObject* a,FXSelector b,void* c)
{
	int col = _tableNoeuds1->getCurrentColumn();
	caseNoeuds1->setText(_tableNoeuds1->getItemText(0,col));
	return 1;
}

long FenetrePropriete::onChgtCellNoeuds2(FXObject* a,FXSelector b,void* c)
{
	int col = _tableNoeuds2->getCurrentColumn();
	caseNoeuds2->setText(_tableNoeuds2->getItemText(0,col));
	return 1;
}

long FenetrePropriete::onChgtCaseCtl(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	int col = _tableCtl->getCurrentColumn();
	int lig = _tableCtl->getCurrentRow();
	_tableCtl->setItemText(lig,col,caseCtlX->getText() + "," + caseCtlY->getText() + "," + caseCtlZ->getText()+ "," + caseCtlPoids->getText());
	return 1;
}

long FenetrePropriete::onChgtCaseNoeuds1(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	int col = _tableNoeuds1->getCurrentColumn();
	_tableNoeuds1->setItemText(0,col,caseNoeuds1->getText());
	return 1;
}

long FenetrePropriete::onChgtCaseNoeuds2(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	int col = _tableNoeuds2->getCurrentColumn();
	_tableNoeuds2->setItemText(0,col,caseNoeuds2->getText());
	return 1;
}

long FenetrePropriete::onModifier(FXObject* a,FXSelector b,void* c)
{
	if(_ontChanges)
    {
		int i,j;
		if(_pObjet3D->getClassName() == FXString("SurfaceBezier") 
			|| _pObjet3D->getClassName() == FXString("SurfaceBSpline") 
			||  _pObjet3D->getClassName() == FXString("SurfaceNURBS") 
			|| _pObjet3D->getClassName() == FXString("SurfaceBezierRat"))
		{
		/*on ajoute ou on supprime des lignes ou des colonnes de la matrice
			de contrôle si les dimensions ont changé*/
			if(_pSurfaceNURBS->fournirNbreLignesCtl() != _tableCtl->getNumRows())
			{
				int tmp =_pSurfaceNURBS->fournirNbreLignesCtl(); 
				for(i=tmp;i < _tableCtl->getNumRows(); i++)
					_pSurfaceNURBS->insererLigneCtl(0,ListePoints(_pSurfaceNURBS->fournirNbreColonnesCtl()));
				
				for(i=_tableCtl->getNumRows();i < tmp; i++)
					_pSurfaceNURBS->supprimerLigneCtl(0);
				
			}
			if(_pSurfaceNURBS->fournirNbreColonnesCtl() != _tableCtl->getNumCols())
			{
				int tmp = _pSurfaceNURBS->fournirNbreColonnesCtl(); 
				for(i=tmp;i < _tableCtl->getNumCols(); i++)
					_pSurfaceNURBS->insererColonneCtl(0,ListePoints(_pSurfaceNURBS->fournirNbreLignesCtl()));
				
				for(i=_tableCtl->getNumCols();i < tmp; i++)
					_pSurfaceNURBS->supprimerColonneCtl(0);
				
			}
			/*on actualise ensuite la matrice de contrôle*/
			
			for(i = 0;i< _pSurfaceNURBS->fournirNbreLignesCtl();i++)
			{
				for(j=0;j<_pSurfaceNURBS->fournirNbreColonnesCtl();j++)
				{
					Point3D tmp;
					int prem = _tableCtl->getItemText(i,j).findf(",");
					int snd = _tableCtl->getItemText(i,j).findf(",",prem+1);
					int trois = _tableCtl->getItemText(i,j).findf(",",snd+1); 
					int fin = _tableCtl->getItemText(i,j).size() - 1;
					tmp.x = FXFloatVal(_tableCtl->getItemText(i,j).left(prem));
					tmp.y = FXFloatVal(_tableCtl->getItemText(i,j).mid(prem+1,snd-prem-1));
					tmp.z = FXFloatVal(_tableCtl->getItemText(i,j).mid(snd+1,trois-snd-1));
					tmp.w = FXFloatVal(_tableCtl->getItemText(i,j).right(fin - trois -1));
					_pSurfaceNURBS->modifierPointCtl(i,j,tmp);
				}
			}
			if(_pSurfaceNURBS->getClassName() == FXString("SurfaceNURBS") || _pSurfaceNURBS->getClassName() == FXString("SurfaceBSpline"))
			{
				/*on fait les mêmes opérations pour les tableaux de noeuds*/
				if(_pSurfaceNURBS->fournirNbreNoeuds_s() != _tableNoeuds1->getNumCols())
				{
					int tmp = _pSurfaceNURBS->fournirNbreNoeuds_s(); 
					for(i=tmp;i < _tableNoeuds1->getNumCols(); i++)
						_pSurfaceNURBS->ajouterNoeud_s(_pSurfaceNURBS->fournirNoeud_s(_pSurfaceNURBS->fournirNbreNoeuds_s()-1));
					
					for(i=_tableNoeuds1->getNumCols();i < tmp; i++)
						_pSurfaceNURBS->supprimerNoeud_s(0);
					
				}
				if(_pSurfaceNURBS->fournirNbreNoeuds_t() != _tableNoeuds2->getNumCols())
				{
					int tmp = _pSurfaceNURBS->fournirNbreNoeuds_t(); 
					for(i=tmp;i < _tableNoeuds2->getNumCols(); i++)
						_pSurfaceNURBS->ajouterNoeud_t(_pSurfaceNURBS->fournirNoeud_t(_pSurfaceNURBS->fournirNbreNoeuds_t()-1));
					
					for(i=_tableNoeuds2->getNumCols();i < tmp; i++)
						_pSurfaceNURBS->supprimerNoeud_t(0);
					
				}
				
				for(j=0;j<_pSurfaceNURBS->fournirNbreNoeuds_s();j++)
					_pSurfaceNURBS->modifierNoeud_s(j,FXFloatVal(_tableNoeuds1->getItemText(0,j)));
				
				for(j=0;j<_pSurfaceNURBS->fournirNbreNoeuds_t();j++)
					_pSurfaceNURBS->modifierNoeud_t(j,FXFloatVal(_tableNoeuds2->getItemText(0,j)));
			}
			int tmp=0;
			if(chkFilDeFer->getCheck() == 1)
				tmp = (tmp | FIL_DE_FER);
			if(chkDessinerSurfCtl->getCheck() == 1)
				tmp = (tmp | DESSINER_SURFACE_POLYEDRIQUE);
			_pSurfaceNURBS->options(tmp);
			_pSurfaceNURBS->modifierTolEch(FXFloatVal(caseTolerance->getText()));
			_pSurfaceNURBS->calculerBoiteEnglobante();
		}
		if(_pObjet3D->getClassName() == FXString("CourbeBezier") 
			|| _pObjet3D->getClassName() == FXString("CourbeBSpline") 
			||  _pObjet3D->getClassName() == FXString("CourbeNURBS") 
			|| _pObjet3D->getClassName() == FXString("CourbeBezierRat"))
		{
		/*on ajoute ou on supprime des cases de la liste de points
			de contrôle si la longueur a changé*/
			if(_pCNurbs->fournirNbrePointsCtl() != _tableCtl->getNumCols())
			{
				int tmp =_pCNurbs->fournirNbrePointsCtl(); 
				for(i=tmp;i < _tableCtl->getNumCols(); i++)
					_pCNurbs->insererPointCtl(0,Point3D());
				
				for(i=_tableCtl->getNumCols();i < tmp; i++)
					_pCNurbs->supprimerPointCtl(0);
				
			}
			
			/*on actualise ensuite la liste de points de contrôle*/
			
			for(j=0;j<_pCNurbs->fournirNbrePointsCtl();j++)
			{
			  
				Point3D tmp;
				int prem = _tableCtl->getItemText(0,j).findf(",");
				int snd = _tableCtl->getItemText(0,j).findf(",",prem+1);
				int trois = _tableCtl->getItemText(0,j).findf(",",snd+1); 
				int fin = _tableCtl->getItemText(0,j).size() - 1;
				tmp.x = FXFloatVal(_tableCtl->getItemText(0,j).left(prem));
				tmp.y = FXFloatVal(_tableCtl->getItemText(0,j).mid(prem+1,snd-prem-1));
				tmp.z = FXFloatVal(_tableCtl->getItemText(0,j).mid(snd+1,trois-snd-1));
				tmp.w = FXFloatVal(_tableCtl->getItemText(0,j).right(fin - trois -1));
				_pCNurbs->modifierPointCtl(j,tmp);
			
}
			if(_pCNurbs->getClassName() == FXString("CourbeNURBS") || _pCNurbs->getClassName() == FXString("CourbeBSpline"))
			{
				/*on fait les mêmes opérations pour les tableaux de noeuds*/
			  if(_pCNurbs->fournirNbreNoeuds() != _tableNoeuds1->getNumCols())
				{
					int tmp = _pCNurbs->fournirNbreNoeuds(); 
					for(i=tmp;i < _tableNoeuds1->getNumCols(); i++)
						_pCNurbs->ajouterNoeud(_pCNurbs->fournirNoeud(_pCNurbs->fournirNbreNoeuds()-1));
					
					for(i=_tableNoeuds1->getNumCols();i < tmp; i++)
						_pCNurbs->supprimerNoeud(0);
					
				}
				
				for(j=0;j<_pCNurbs->fournirNbreNoeuds();j++)
					_pCNurbs->modifierNoeud(j,FXFloatVal(_tableNoeuds1->getItemText(0,j)));
			}
			int tmp=0;
			if(chkDessinerSurfCtl->getCheck() == 1)
				tmp = (tmp | DESSINER_LIGNE_POLYGONALE);
			_pCNurbs->options(tmp);
			_pCNurbs->modifierTolEch(FXFloatVal(caseTolerance->getText()));
			_pCNurbs->calculerBoiteEnglobante();
		}
		else if (_pObjet3D->getClassName() == FXString("LignePolygonale") 
            || _pObjet3D->getClassName() == FXString("Segment")
            || _pObjet3D->getClassName() == FXString("Polygone")) 
        {
		/*on ajoute ou on supprime des cases de liste
			si la longueur a changé*/
			
			if(_pLPoints->longueur() != _tableCtl->getNumCols())
			{
				int tmp = _pLPoints->longueur(); 
				for(i=tmp;i < _tableCtl->getNumCols(); i++)
					_pLPoints->inserer(0,Point3D());
				
				for(i=_tableCtl->getNumCols();i < tmp; i++)
					_pLPoints->supprimer(0);
				
			}
			/*on actualise ensuite la liste*/
			
			for(i = 0;i< _pLPoints->longueur();i++)
			{
				
				Point3D tmp;
				int prem = _tableCtl->getItemText(0,i).findf(",");
				int snd = _tableCtl->getItemText(0,i).findf(",",prem+1);
				int trois = _tableCtl->getItemText(0,i).findf(",",snd+1); 
				int fin = _tableCtl->getItemText(0,i).size() - 1;
				tmp.x = FXFloatVal(_tableCtl->getItemText(0,i).left(prem));
				tmp.y = FXFloatVal(_tableCtl->getItemText(0,i).mid(prem+1,snd-prem-1));
				tmp.z = FXFloatVal(_tableCtl->getItemText(0,i).mid(snd+1,trois-snd-1));
				tmp.w = FXFloatVal(_tableCtl->getItemText(0,i).right(fin - trois -1));
				_pLPoints->modifierPoint(i,tmp);
			}	
		}
		else if (_pObjet3D->getClassName() == FXString("SurfacePolyedrique")) 
		{
			/*on ajoute ou on supprime des lignes ou des colonnes de la matrice
		    si les dimensions ont changé*/
			if(_pSurfPoly->fournirNb_lignes() != _tableCtl->getNumRows())
			{
				int tmp =_pSurfPoly->fournirNb_lignes(); 
				for(i=tmp;i < _tableCtl->getNumRows(); i++)
					_pSurfPoly->insererLigne(0,ListePoints(_pSurfPoly->fournirNb_colonnes()));
				
				for(i=_tableCtl->getNumRows();i < tmp; i++)
					_pSurfPoly->supprimerLigne(0);
				
			}
			if(_pSurfPoly->fournirNb_colonnes() != _tableCtl->getNumCols())
			{
				int tmp = _pSurfPoly->fournirNb_colonnes(); 
				for(i=tmp;i < _tableCtl->getNumCols(); i++)
					_pSurfPoly->insererColonne(0,ListePoints(_pSurfPoly->fournirNb_lignes()));
				
				for(i=_tableCtl->getNumCols();i < tmp; i++)
					_pSurfPoly->supprimerColonne(0);
				
			}
			/*on actualise ensuite la matrice de contrôle*/
			
			for(i = 0;i< _pSurfPoly->fournirNb_lignes();i++)
			{
				for(j=0;j<_pSurfPoly->fournirNb_colonnes();j++)
				{
					Point3D tmp;
					int prem = _tableCtl->getItemText(i,j).findf(",");
					int snd = _tableCtl->getItemText(i,j).findf(",",prem+1);
					int trois = _tableCtl->getItemText(i,j).findf(",",snd+1); 
					int fin = _tableCtl->getItemText(i,j).size() - 1;
					tmp.x = FXFloatVal(_tableCtl->getItemText(i,j).left(prem));
					tmp.y = FXFloatVal(_tableCtl->getItemText(i,j).mid(prem+1,snd-prem-1));
					tmp.z = FXFloatVal(_tableCtl->getItemText(i,j).mid(snd+1,trois-snd-1));
					tmp.w = FXFloatVal(_tableCtl->getItemText(i,j).right(fin - trois -1));
					_pSurfPoly->modifierPoint(i,j,tmp);
				}
			}
		}
		
    }
	
	FXRange boite_englobante;
	_owner->scene->bounds(boite_englobante); 
	_owner->viewer->setBounds(boite_englobante);
	_owner->viewer->setScene(_owner->scene);
	onCmdAccept(a,b,c);
	return 1;
}

long FenetrePropriete::onChgtChkFilDeFer(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	return 1;
}

long FenetrePropriete::onChgtchkDessinerSurfCtl(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	return 1;
}

long FenetrePropriete::onChgtCaseTolerance(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	return 1;
}

long FenetrePropriete::onSupprimerColonneCtl(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableCtl->onCmdDeleteColumn(a,b,c);
	return 1;
}

long FenetrePropriete::onSupprimerLigneCtl(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableCtl->onCmdDeleteRow(a,b,c);
	return 1;
}

long FenetrePropriete::onInsererColonneCtl(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableCtl->onCmdInsertColumn(a,b,c);
	//on remplit ensuite cette colonne avec une valeur par défaut
	for(int i=0; i < _tableCtl->getNumRows();i++)
		_tableCtl->setItemText(i,_tableCtl->getCurrentColumn()-1,"0,0,0,1");
	return 1;
}

long FenetrePropriete::onInsererLigneCtl(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableCtl->onCmdInsertRow(a,b,c);
	//on remplit ensuite cette colonne avec une valeur par défaut
	for(int i=0; i < _tableCtl->getNumCols();i++)
		_tableCtl->setItemText(_tableCtl->getCurrentRow()-1,i,"0,0,0,1");
	
	return 1;
}

long FenetrePropriete::onInsererCaseNoeud1(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableNoeuds1->onCmdInsertColumn(a,b,c);
	return 1;
}

long FenetrePropriete::onSupprimerCaseNoeud1(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableNoeuds1->onCmdDeleteColumn(a,b,c);
	return 1;
}

long FenetrePropriete::onInsererCaseNoeud2(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableNoeuds2->onCmdInsertColumn(a,b,c);
	return 1;
}

long FenetrePropriete::onSupprimerCaseNoeud2(FXObject* a,FXSelector b,void* c)
{
	_ontChanges = true;
	_tableNoeuds2->onCmdDeleteColumn(a,b,c);
	return 1;
}

FenetrePropriete::~FenetrePropriete()
{
	
}
