#include <owl\pch.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include "Ex3.rh"

bool vOptionPie = true;
char tNomVille[20] = "";
int tTaille[50], vMax, vNbValeur;

class TMaFenetre : public TWindow
{
	protected:
		void CmFichierQuitter();
		void CmFichierActualiser();
		void CmOptionPie();
		void CmOptionBarre();

      void Paint(TDC&, bool, TRect&);

   	DECLARE_RESPONSE_TABLE(TMaFenetre);

   public:
   	TMaFenetre(char* title);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_COMMAND(CM_FICHIER_ACTUALISER, CmFichierActualiser),
	EV_COMMAND(CM_FICHIER_QUITTER, CmFichierQuitter),
	EV_COMMAND(CM_OPTION_PIE, CmOptionPie),
	EV_COMMAND(CM_OPTION_BARRE, CmOptionBarre),
END_RESPONSE_TABLE;

TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{
}

void TMaFenetre::Paint(TDC& dc, bool , TRect& )
{
	if(vOptionPie == false)
   {
		if(vNbValeur != 0)
   	{
			TPen StyloEchelle(RGB(0,0,0),1,0);
		   dc.SelectObject(StyloEchelle);
   	   dc.SetTextAlign(TA_CENTER);

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
	   	int vScaleX = Parent->Attr.W / 50;
		   int vScaleY = Parent->Attr.H / 12;

      	/* Axe des X */
         int vPas = 5;
   		for(int i = 0; i < 50; i += vPas)
	 	   {
    	   	dc.MoveTo(vAxeYX+i*vScaleX,vAxeXY-10);
    	  		dc.LineTo(vAxeYX+i*vScaleX,vAxeXY+10);
         	itoa(i*5,tText,10);
         	dc.TextOut(vAxeYX+i*vScaleX,vAxeXY+10,tText);
      	}

      	/* Axe des Y */
   		for(int i = 1; i < 10; i++)
	   	{
      		dc.MoveTo(vAxeYX-10,vAxeXY-i*vScaleY);
      		dc.LineTo(vAxeYX+10,vAxeXY-i*vScaleY);
         	itoa(i*(vMax/10),tText,10);
         	dc.TextOut(vAxeYX-30,vAxeXY-i*vScaleY-10,tText);
      	}

     	 	/* Graphe */
      	for(int i = 1; i < 50; i++)
      		dc.Rectangle(vAxeYX+i*vScaleX,vAxeXY+1,vAxeYX+i*vScaleX+10,vAxeXY-tTaille[i]*vScaleY/vPas);
		}
   }
   else
   {
   	int vRayon;
      float rad(int);
	   TPoint pDebut, pFin;
      TRect pRectangle;

      /* Centrage et taille des Pie */
    	if(Parent->Attr.W > Parent->Attr.H)
      {
      	vRayon = Parent->Attr.H/2-100;
	      pRectangle.left = Parent->Attr.W/2-vRayon;
   	   pRectangle.top = 100;
      	pRectangle.right = Parent->Attr.W/2+vRayon;
	      pRectangle.bottom = Parent->Attr.H-100;
      }
      else
      {
      	vRayon = Parent->Attr.W/2-100;
	      pRectangle.left = 100;
   	   pRectangle.top = Parent->Attr.H/2-vRayon;
      	pRectangle.right = Parent->Attr.W-100;
	      pRectangle.bottom = Parent->Attr.H/2+vRayon;
      }

      /* 1ère part de tarte */
      pDebut.x = 2*vRayon-100;
      pDebut.y = vRayon;

     	if(vMax == 0)
        	vMax = 1;

      pFin.x = sin(rad(tTaille[0]/vMax*360))*vRayon;
      pFin.y = cos(rad(tTaille[0]/vMax*360))*vRayon;

   	dc.Pie(pRectangle,pDebut,pFin);

      /* Toutes les autres */
      for(int i = 1; i < 50; i++)
      {
      	if(vMax == 0)
         	vMax = 1;
	      pDebut.x = pFin.x;
      	pDebut.y = pFin.y;

   	   pFin.x = sin(rad(tTaille[i]/vMax*360))*vRayon;
	      pFin.y = cos(rad(tTaille[i]/vMax*360))*vRayon;

	   	dc.Pie(pRectangle,pDebut,pFin);
      }
   }

  	/* Titre */
  	dc.TextOut(Parent->Attr.W/2,10,tNomVille);
}

float rad(int vAngle)
{
	return(vAngle*3.14/180);
}

void TMaFenetre::CmFichierQuitter()
{
	exit(0);
}

void TMaFenetre::CmFichierActualiser()
{
   /* Remise à Zéro */
   char tTemp[2] = "";
   char tCat[20] = "";
   vMax = vNbValeur = 0;
   for(int i = 0; i < 50; i++)
   	tTaille[i] = 0;

   /* Lecture du fichier */
   FILE *f;
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
     	while(strcmp(tTemp,"\n") && !feof(f));

      /* Affectation */
      if(vNbValeur == 0)
      	strcpy(tNomVille, tCat);
      else
      {
      	tTaille[atoi(tCat)/5]++;
         if(tTaille[atoi(tCat)/5] > vMax)
         	vMax = tTaille[atoi(tCat)/5]++;
      }
      vNbValeur++;
   }
   fclose(f);
   Invalidate();
}

void TMaFenetre::CmOptionPie()
{
	vOptionPie = true;
   Invalidate();
}

void TMaFenetre::CmOptionBarre()
{
	vOptionPie = false;
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
	SetMainWindow(new TFrameWindow(NULL, "Série 4 - Ex3", new TMaFenetre("Série 4 - Ex3")));
   GetMainWindow()->AssignMenu(IDM_MENU1);
}

int OwlMain(int, char**)
{
	TMaFenetre Fenetre("Série 4 - Ex3");
   TMonAppli App;
   return App.Run();
}