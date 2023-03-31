#include <owl\pch.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>          
#include "Ex1.rh"

int vEpaisseur = 1,
	 vType = PS_SOLID;
char tForme[20] = "line",
     tTypeStr[20] = "Solide",
     tCouleurStr[20] = "Noir";
TColor vCouleur = RGB(0,0,0);

class TMaFenetre : public TWindow
{
	protected:
		void CmFormeLine();
		void CmFormeRect();
		void CmFormeRectRound();
		void CmFormeEllipse();
		void CmFormeArc();
		void CmFormeCorde();
		void CmFormeCamembert();
		void CmFormePolyline();
		void CmFormePolygone();

		void CmCouleurNoir();
		void CmCouleurRouge();
		void CmCouleurBleu();
		void CmCouleurVert();
		void CmCouleurJaune();

  		void CmEpais1();
  		void CmEpais2();
  		void CmEpais4();
  		void CmEpais8();
  		void CmEpais16();

  		void CmTypePlein();
  		void CmTypeTirets();
  		void CmTypePointilles();
  		void CmTypeTraitPoint();
  		void CmTypeTraitPointPoint();

      void Paint(TDC&, bool, TRect&);

   	DECLARE_RESPONSE_TABLE(TMaFenetre);

   public:
   	TMaFenetre(char* title);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_COMMAND(CM_FORME_LINE, CmFormeLine),
	EV_COMMAND(CM_FORME_RECT, CmFormeRect),
	EV_COMMAND(CM_FORME_RECT_ROUND, CmFormeRectRound),
	EV_COMMAND(CM_FORME_ELLIPSE, CmFormeEllipse),
	EV_COMMAND(CM_FORME_ARC, CmFormeArc),
	EV_COMMAND(CM_FORME_CORDE, CmFormeCorde),
	EV_COMMAND(CM_FORME_CAMEMBERT, CmFormeCamembert),
	EV_COMMAND(CM_FORME_POLYLINE, CmFormePolyline),
	EV_COMMAND(CM_FORME_POLYGONE, CmFormePolygone),

	EV_COMMAND(CM_COULEUR_NOIR, CmCouleurNoir),
	EV_COMMAND(CM_COULEUR_ROUGE, CmCouleurRouge),
	EV_COMMAND(CM_COULEUR_BLEU, CmCouleurBleu),
	EV_COMMAND(CM_COULEUR_VERT, CmCouleurVert),
	EV_COMMAND(CM_COULEUR_JAUNE, CmCouleurJaune),

	EV_COMMAND(CM_EPAIS_1, CmEpais1),
	EV_COMMAND(CM_EPAIS_2, CmEpais2),
	EV_COMMAND(CM_EPAIS_4, CmEpais4),
	EV_COMMAND(CM_EPAIS_8, CmEpais8),
	EV_COMMAND(CM_EPAIS_16, CmEpais16),

	EV_COMMAND(CM_TYPE_PLEIN, CmTypePlein),
	EV_COMMAND(CM_TYPE_TIRETS, CmTypeTirets),
	EV_COMMAND(CM_TYPE_POINTILLES, CmTypePointilles),
	EV_COMMAND(CM_TYPE_TRAIT_POINT, CmTypeTraitPoint),
	EV_COMMAND(CM_TYPE_TRAIT_POINT_POINT, CmTypeTraitPointPoint),
END_RESPONSE_TABLE;

TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{}

void TMaFenetre::Paint(TDC& dc, bool , TRect& )
{
	char tTitre[80] = "";
   char tTemp[] = "";

   strcat(tTitre,"Forme : ");
   strcat(tTitre,tForme);

   strcat(tTitre," - Couleur : ");
   strcat(tTitre,tCouleurStr);

   strcat(tTitre," - Type de trait : ");
   strcat(tTitre,tTypeStr);

   strcat(tTitre," - Epaisseur : ");
   itoa(vEpaisseur,tTemp,10);
   strcat(tTitre,tTemp);

	TPen Stylo(vCouleur,vEpaisseur,vType);
   dc.SetTextAlign(TA_CENTER);
   dc.SelectObject(Stylo);

   int X1 = 50;
   int X2 = Parent->Attr.W-50;
   int Y1 = 50;
   int Y2 = Parent->Attr.H-150;

   dc.MoveTo(X1,Y1);
   if(strcmp(tForme,"line") == 0)
   	dc.LineTo(X2,Y2);
   else if(strcmp(tForme,"rectangle") == 0)
   	dc.Rectangle(X1,Y1,X2,Y2);
   else if(strcmp(tForme,"roundrect") == 0)
		dc.RoundRect(X1,Y1,X2,Y2,110,110);
   else if(strcmp(tForme,"ellipse") == 0)
		dc.Ellipse(X1,Y1,X2,Y2);
   else if(strcmp(tForme,"arc") == 0)
		dc.Arc(X1,Y1,X2,Y2,X1*2,Y1,X2,Y2);
   else if(strcmp(tForme,"corde") == 0)
		dc.Chord(X1,Y1,X2,Y2,X1*2,Y1,X2,Y2);
   else if(strcmp(tForme,"camembert") == 0)
		dc.Pie(X1,Y1,X2,Y2,X1*2,Y1,X2,Y2/2);
   else if(strcmp(tForme,"polyline") == 0)
   {
   	TPoint pt[] = {TPoint(X1,Y1),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
                     TPoint(X2,Y2)
                    };
   	dc.Polyline(pt,8);
   }
   else if(strcmp(tForme,"polygone") == 0)
   {
   	TPoint pt2[] = {TPoint(X1,Y1),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
      					TPoint(random(X2-X1),random(Y2-Y1)),
                     TPoint(X2,Y2)
                    };
   	dc.Polygon(pt2,8);
   }
   dc.TextOut(Parent->Attr.W/2,Y2+20,tTitre);
}

void TMaFenetre::CmFormeLine()
{
	strcpy(tForme,"line");
   Invalidate();
}

void TMaFenetre::CmFormeRect()
{
	strcpy(tForme,"rectangle");
   Invalidate();
}

void TMaFenetre::CmFormeRectRound()
{
	strcpy(tForme,"roundrect");
   Invalidate();
}

void TMaFenetre::CmFormeEllipse()
{
	strcpy(tForme,"ellipse");
   Invalidate();
}

void TMaFenetre::CmFormeArc()
{
	strcpy(tForme,"arc");
   Invalidate();
}

void TMaFenetre::CmFormeCorde()
{
	strcpy(tForme,"corde");
   Invalidate();
}

void TMaFenetre::CmFormeCamembert()
{
	strcpy(tForme,"camembert");
   Invalidate();
}

void TMaFenetre::CmFormePolyline()
{
	strcpy(tForme,"polyline");
   Invalidate();
}

void TMaFenetre::CmFormePolygone()
{
	strcpy(tForme,"polygone");
   Invalidate();
}

void TMaFenetre::CmCouleurNoir()
{
	vCouleur = RGB(0,0,0);
   strcpy(tCouleurStr,"Noir");
   Invalidate();
}

void TMaFenetre::CmCouleurRouge()
{
	vCouleur = RGB(255,0,0);
   strcpy(tCouleurStr,"Rouge");
   Invalidate();
}

void TMaFenetre::CmCouleurBleu()
{
	vCouleur = RGB(0,0,255);
   strcpy(tCouleurStr,"Bleu");
   Invalidate();
}

void TMaFenetre::CmCouleurVert()
{
	vCouleur = RGB(0,255,0);
   strcpy(tCouleurStr,"Vert");
   Invalidate();
}

void TMaFenetre::CmCouleurJaune()
{
	vCouleur = RGB(255,255,0);
   strcpy(tCouleurStr,"Jaune");
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

void TMaFenetre::CmEpais4()
{
	vEpaisseur = 4;
   Invalidate();
}

void TMaFenetre::CmEpais8()
{
	vEpaisseur = 8;
   Invalidate();
}

void TMaFenetre::CmEpais16()
{
	vEpaisseur = 16;
   Invalidate();
}

void TMaFenetre::CmTypePlein()
{
	vType = PS_SOLID;
   strcpy(tTypeStr,"Plein");
   Invalidate();
}

void TMaFenetre::CmTypeTirets()
{
	vType = PS_DASH;
   strcpy(tTypeStr,"Tirets");
   Invalidate();
}

void TMaFenetre::CmTypePointilles()
{
	vType = PS_DOT;
   strcpy(tTypeStr,"Pointillés");
   Invalidate();
}

void TMaFenetre::CmTypeTraitPoint()
{
	vType = PS_DASHDOT;
   strcpy(tTypeStr,"Trait-Point");
   Invalidate();
}

void TMaFenetre::CmTypeTraitPointPoint()
{
	vType = PS_DASHDOTDOT;
   strcpy(tTypeStr,"Trait-Point-Point");
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
	SetMainWindow(new TFrameWindow(NULL, "Série 4 - Ex1", new TMaFenetre("Série 4 - Ex1")));
   GetMainWindow()->AssignMenu(IDM_MENU1);
}

int OwlMain(int, char**)
{
	randomize();
	TMonAppli App;
   return App.Run();
}
