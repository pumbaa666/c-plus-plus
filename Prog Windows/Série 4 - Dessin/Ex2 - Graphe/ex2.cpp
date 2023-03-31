#include <owl\pch.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include "Ex2.rh"

int vEpaisseur = 1,
	 vNbValeur = 0;
TColor vCouleur = RGB(0,0,0);

int tTab[1000][4], vMax;

class TMaFenetre : public TWindow
{
	protected:
		void CmFichierQuitter();
		void CmCouleurNoir();
		void CmCouleurRouge();
		void CmCouleurBleu();
		void CmCouleurVert();
		void CmCouleurJaune();

  		void CmEpais1();
  		void CmEpais2();
  		void CmEpais3();
  		void CmEpais4();

      void Paint(TDC&, bool, TRect&);

   	DECLARE_RESPONSE_TABLE(TMaFenetre);

   public:
		void CmFichierRelire();
   	TMaFenetre(char* title);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_COMMAND(CM_FICHIER_RELIRE, CmFichierRelire),
	EV_COMMAND(CM_FICHIER_QUITTER, CmFichierQuitter),

  	EV_COMMAND(CM_COULEUR_NOIR, CmCouleurNoir),
	EV_COMMAND(CM_COULEUR_ROUGE, CmCouleurRouge),
	EV_COMMAND(CM_COULEUR_BLEU, CmCouleurBleu),
	EV_COMMAND(CM_COULEUR_VERT, CmCouleurVert),
	EV_COMMAND(CM_COULEUR_JAUNE, CmCouleurJaune),

	EV_COMMAND(CM_EPAIS_1, CmEpais1),
	EV_COMMAND(CM_EPAIS_2, CmEpais2),
	EV_COMMAND(CM_EPAIS_3, CmEpais3),
	EV_COMMAND(CM_EPAIS_4, CmEpais4),
END_RESPONSE_TABLE;

TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{
}

void TMaFenetre::Paint(TDC& dc, bool , TRect& )
{
	if(vNbValeur != 0)
   {
		TPen StyloEchelle(RGB(0,0,0),1,0);
	   dc.SelectObject(StyloEchelle);

   	/* Cadre */
      int vAxeYX = 50;
      int vAxeYY1 = 20;
      int vAxeYY2 = Parent->Attr.H-40;

      int vAxeXX1 = 0;
      int vAxeXX2 = Parent->Attr.W-20;
      int vAxeXY = Parent->Attr.H-100;

  	   dc.MoveTo(vAxeXX1,vAxeXY);
   	dc.LineTo(vAxeXX2,vAxeXY);
	   dc.MoveTo(vAxeYX,vAxeYY1);
   	dc.LineTo(vAxeYX,vAxeYY2);

	   /* Echelle */
      char tText[3] = "";
   	int vScaleX = Parent->Attr.W / (vNbValeur+2);
	   int vScaleY = Parent->Attr.H / (vMax/7);

      /* Axe des X */
      int vPas = vNbValeur/12;
      if(vPas == 0)
      	vPas = 1;
      char tHeure[9] = "";
      void AjoutZero(char[], char[]);
   	for(int i = 1; i < vNbValeur; i += vPas)
	   {
      	dc.MoveTo(vAxeYX+i*vScaleX,vAxeXY-10);
      	dc.LineTo(vAxeYX+i*vScaleX,vAxeXY+10);

         itoa(tTab[i][0],tText,10);
         AjoutZero(tText,tHeure);
         strcpy(tHeure,tText);
         strcat(tHeure,":");

         itoa(tTab[i][1],tText,10);
         AjoutZero(tText,tHeure);
         strcat(tHeure,tText);
         strcat(tHeure,":");

         itoa(tTab[i][2],tText,10);
         AjoutZero(tText,tHeure);
         strcat(tHeure,tText);

         dc.TextOut(vAxeYX+i*vScaleX-25,vAxeXY+10+(15*(i%3)),tHeure);
      }

      /* Axe des Y */
      vPas = vMax/100;
      if(vPas == 0)
      	vPas = 1;
   	for(int i = 1; i < (vMax/10); i+=vPas)
	   {
      	dc.MoveTo(vAxeYX-10,vAxeXY-i*vScaleY);
      	dc.LineTo(vAxeYX+10,vAxeXY-i*vScaleY);
         itoa(i*10,tText,10);
         dc.TextOut(vAxeYX-30,vAxeXY-i*vScaleY-5,tText);
      }

      /* Sélection du stylo */
		TPen StyloGraphe(vCouleur,vEpaisseur,0);
   	dc.SetTextAlign(TA_CENTER);
	   dc.SelectObject(StyloGraphe);

      /* Affichage du nombre de valeurs */
		char tTitre[20] = "";
      strcpy(tTitre,"Nb valeurs: ");
      itoa(vNbValeur,tText,10);
      strcat(tTitre,tText);
      dc.TextOut(130,10,tTitre);

   	/* Graphe */
	   dc.MoveTo(vAxeYX,vAxeXY-tTab[0][3]*vScaleY/10);
    	for(int i = 1; i < vNbValeur; i++)
			dc.LineTo(vAxeYX+i*vScaleX,vAxeXY-tTab[i][3]*vScaleY/10);
   }
}

void AjoutZero(char tText[3], char tHeure[9])
{
   char tTemp[3];
   if(strlen(tText) == 1)
   {
    	strcpy(tTemp,tText);
      strcpy(tText,"0");
      strcat(tText,tTemp);
   }
}

void TMaFenetre::CmFichierRelire()
{
   FILE *f;
   char tTemp[2] = "";
   char tCat[4] = "";
   int vType = 0;
   vMax = vNbValeur = 0;

   f = fopen("data.txt","r");
   while(!feof(f))
   {
   	tTemp[0] = '\0';
   	tCat[0] = '\0';
   	do
      {
			strcat(tCat,tTemp);
		  	fread(tTemp,sizeof(char),1,f);
      }
     	while(strcmp(tTemp,":") && strcmp(tTemp,"\n") && !feof(f));

     	tTab[vNbValeur][vType] = atoi(tCat);
      if(tTab[vNbValeur][vType] > vMax)
      	vMax = tTab[vNbValeur][vType];
      vType++;
      if(vNbValeur == 7)
      	vNbValeur = 7;
      if(vType == 4)
      {
      	vType = 0;
	      vNbValeur++;
      }
   }
   fclose(f);

   Invalidate();
}

void TMaFenetre::CmFichierQuitter()
{
	exit(0);
}

void TMaFenetre::CmCouleurNoir()
{
	vCouleur = RGB(0,0,0);
   Invalidate();
}

void TMaFenetre::CmCouleurVert()
{
	vCouleur = RGB(0,255,0);
   Invalidate();
}

void TMaFenetre::CmCouleurRouge()
{
	vCouleur = RGB(255,0,0);
   Invalidate();
}

void TMaFenetre::CmCouleurBleu()
{
	vCouleur = RGB(0,0,255);
   Invalidate();
}

void TMaFenetre::CmCouleurJaune()
{
	vCouleur = RGB(255,255,0);
   Invalidate();
}

void TMaFenetre::CmEpais1()
{
	vEpaisseur = 1;
   Invalidate();
}

void TMaFenetre::CmEpais2()
{
	vEpaisseur = 2;
   Invalidate();
}

void TMaFenetre::CmEpais3()
{
	vEpaisseur = 3;
   Invalidate();
}

void TMaFenetre::CmEpais4()
{
	vEpaisseur = 4;
   Invalidate();
}

class TMonAppli : public TApplication
{
	public:
   	TMonAppli();
      void InitMainWindow();
};

TMonAppli::TMonAppli() : TApplication()
{}

void TMonAppli::InitMainWindow()
{
	SetMainWindow(new TFrameWindow(NULL, "Série 4 - Ex2", new TMaFenetre("Série 4 - Ex2")));
   GetMainWindow()->AssignMenu(IDM_MENU1);
}

int OwlMain(int, char**)
{
	TMaFenetre Fenetre("Série 4 - Ex2");
   Fenetre.CmFichierRelire();
   TMonAppli App;
   return App.Run();
}
