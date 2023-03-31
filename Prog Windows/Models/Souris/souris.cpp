#include <owl\pch.h>

char BarreDeTitre[] = "Les messages souris";

class TMaFenetre : public TWindow
{
	void EvLButtonDown(uint, TPoint&);
	void EvMButtonDown(uint, TPoint&);
	void EvRButtonDown(uint, TPoint&);
	void EvLButtonUp(uint, TPoint&);
	void EvMButtonUp(uint, TPoint&);
	void EvRButtonUp(uint, TPoint&);
   void EvMouseMove(uint, TPoint&);
   void EvLButtonDblClk(uint, TPoint&);
   void EvMButtonDblClk(uint, TPoint&);
   void EvRButtonDblClk(uint, TPoint&);

   public:
   	TMaFenetre():TWindow(NULL, NULL, NULL){}
      DECLARE_RESPONSE_TABLE(TMaFenetre);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_WM_LBUTTONDOWN,
	EV_WM_MBUTTONDOWN,
	EV_WM_RBUTTONDOWN,
	EV_WM_LBUTTONUP,
	EV_WM_MBUTTONUP,
	EV_WM_RBUTTONUP,
	EV_WM_MOUSEMOVE,
	EV_WM_LBUTTONDBLCLK,
	EV_WM_MBUTTONDBLCLK,
	EV_WM_RBUTTONDBLCLK,
END_RESPONSE_TABLE;

class TMonAppli : public TApplication
{
	void InitMainWindow();
   public:
   	TMonAppli() : TApplication(){}
};

void TMaFenetre::EvLButtonDown(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvMButtonDown(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvRButtonDown(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvLButtonUp(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvMButtonUp(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvRButtonUp(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvMouseMove(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvLButtonDblClk(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvMButtonDblClk(uint modKeys, TPoint& p)
{
}

void TMaFenetre::EvRButtonDblClk(uint modKeys, TPoint& p)
{
}

void TMonAppli::InitMainWindow()
{
	SetMainWindow(new TFrameWindow (NULL, BarreDeTitre, new TMaFenetre));
   nCmdShow = SW_SHOWMAXIMIZED;
}

int OwlMain(int, char *[])
{
	TMonAppli MonAppli;
   return MonAppli.Run();
}
