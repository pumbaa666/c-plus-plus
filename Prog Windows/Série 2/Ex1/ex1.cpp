#include <owl\pch.h>

char BarreDeTitre[] = "Série 2 - Ex1";

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
	SetBkgndColor(TColor::LtBlue);
   Invalidate();
}

void TMaFenetre::EvMButtonDown(uint modKeys, TPoint& p)
{
	SetBkgndColor(TColor::LtRed);
   Invalidate();
}

void TMaFenetre::EvRButtonDown(uint modKeys, TPoint& p)
{
	SetBkgndColor(TColor::LtGreen);
   Invalidate();
}

void TMonAppli::InitMainWindow()
{
	SetMainWindow(new TFrameWindow(NULL, BarreDeTitre, new TMaFenetre));
   nCmdShow = SW_SHOWMAXIMIZED;
}

int OwlMain(int, char * [])
{
	TMonAppli MonAppli;
   return MonAppli.Run();
}
