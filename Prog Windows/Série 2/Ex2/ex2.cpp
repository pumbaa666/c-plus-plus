#include <owl\pch.h>
#include <stdio.h>
#include <string.h>

char BarreDeTitre[] = "Série 2 - Ex 3";

class TMaFenetre : public TWindow
{
	void EvLButtonDown(uint, TPoint&);
	void EvMButtonDown(uint, TPoint&);
	void EvRButtonDown(uint, TPoint&);
   //void EvMouseMove(uint, TPoint&);

   public:
   	TMaFenetre():TWindow(NULL, NULL, NULL){}
      DECLARE_RESPONSE_TABLE(TMaFenetre);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_WM_LBUTTONDOWN,
	EV_WM_MBUTTONDOWN,
	EV_WM_RBUTTONDOWN,
  //	EV_WM_MOUSEMOVE,
END_RESPONSE_TABLE;

class TMonAppli : public TApplication
{
	void InitMainWindow();
   public:
   	TMonAppli() : TApplication(){}
};

class TMaFrame : public TFrameWindow
{
	public:
		void ChangeTitre();
};

void TMaFrame::ChangeTitre()
{

}

void TMaFenetre::EvLButtonDown(uint modKeys, TPoint& p)
{
   char vCtrl[3] = "Off",
   	  vShift[3] = "Off",
        tTitre[80] = "";

	SetBkgndColor(TColor::LtBlue);
   if(modKeys & MK_CONTROL)
       strcpy(vCtrl,"On");
   if(modKeys & MK_SHIFT)
       strcpy(vShift,"On");
   strcat(tTitre, "Ctrl - ");
   strcat(tTitre, vCtrl);
   strcat(tTitre, "   _-_   Shift - ");
   strcat(tTitre, vShift);
   GetApplication()->GetMainWindow()->SetCaption(tTitre);
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

/*void TMaFenetre::EvMouseMove(uint modKeys, TPoint& p)
{
	SetBkgndColor(TColor::TColor(RGB(p.x,p.y,0)));
   Invalidate();
} */

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