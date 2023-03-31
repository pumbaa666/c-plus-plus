#include <owl\pch.h>

char BarreDeTitre[] = "Série 2 - Ex3";

class TMaFenetre : public TWindow
{
	void EvLButtonDown(uint, TPoint&);
	void EvMButtonDown(uint, TPoint&);
	void EvRButtonDown(uint, TPoint&);

   public:
   	TMaFenetre():TWindow(NULL, NULL, NULL){}
      DECLARE_RESPONSE_TABLE(TMaFenetre);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_WM_LBUTTONDOWN,
	EV_WM_MBUTTONDOWN,
	EV_WM_RBUTTONDOWN,
END_RESPONSE_TABLE;

class TMonAppli : public TApplication
{
	void InitMainWindow();
   public:
   	TMonAppli() : TApplication(){}
};

void TMaFenetre::EvLButtonDown(uint modKeys, TPoint& p)
{
	if(GetApplication()->GetMainWindow()->Attr.X < GetSystemMetrics(SM_CXSCREEN)-410)
	   GetApplication()->GetMainWindow()->MoveWindow(GetApplication()->GetMainWindow()->Attr.X+10,GetApplication()->GetMainWindow()->Attr.Y,400,400,1);
   Invalidate();
}

void TMaFenetre::EvMButtonDown(uint modKeys, TPoint& p)
{
   SetBkgndColor(TColor::TColor(RGB(random(255),random(255),random(255))));
   Invalidate();
}

void TMaFenetre::EvRButtonDown(uint modKeys, TPoint& p)
{
	if(GetApplication()->GetMainWindow()->Attr.X > 10)
	   GetApplication()->GetMainWindow()->MoveWindow(GetApplication()->GetMainWindow()->Attr.X-10,GetApplication()->GetMainWindow()->Attr.Y,400,400,1);
   Invalidate();
}

void TMonAppli::InitMainWindow()
{
	TFrameWindow * ad_cadre;
   TWindow * ad_fenetre;
   ad_fenetre = new TMaFenetre();
   ad_cadre = new TFrameWindow(NULL, BarreDeTitre, ad_fenetre);
   SetMainWindow(ad_cadre);
   GetMainWindow()->Attr.X = 10;
   GetMainWindow()->Attr.Y = 10;
   GetMainWindow()->Attr.W = 400;
   GetMainWindow()->Attr.H = 400;
   GetMainWindow()->Attr.Style |= WS_VSCROLL;
   GetMainWindow()->Attr.Style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
}

int OwlMain(int, char * [])
{
	TMonAppli MonAppli;
   return MonAppli.Run();
}