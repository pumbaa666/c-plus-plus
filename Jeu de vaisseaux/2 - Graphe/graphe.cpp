#include <owl\pch.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <io.h>

#include <owl\opensave.h>
#include <owl\chooseco.h>
//#include <owl\inputdia.h>

#include "graphe.rh"

#include "classe.h"
#include "classe_tmafenetre.cpp"
#include "classe_tmonappli.cpp"
#include "classe_point.cpp"

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_COMMAND(CM_FICHIER_OUVRIR, CmFichierOuvrir),
	EV_COMMAND(CM_FICHIER_ACTUALISER, CmFichierActualiser),
	EV_COMMAND(CM_OPTIONS_POINTS, CmOptionsPoints),
	EV_COMMAND(CM_OPTIONS_RELIER, CmOptionsRelier),
	EV_COMMAND(CM_OPTIONS_COULEUR, CmOptionsCouleur),
	EV_COMMAND(CM_FICHIER_QUITTER, CmFichierQuitter),
   EV_WM_SIZE,
END_RESPONSE_TABLE;

int OwlMain(int, char**)
{
	TMaFenetre Fenetre("Projet 2 : Graphe");
   TMonAppli App;
   return App.Run();
}