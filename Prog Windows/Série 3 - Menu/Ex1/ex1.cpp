#include <owl\pch.h>
#include "Ex1.rh"

class TMaFenetre : public TWindow
{
	protected:
   	void CmFondRouge();
   	void CmFondVert();
   	void CmFondJaune();
   	void CmFondBleu();
      void CmTaille100();
      void CmTaille200();
      void CmTaille400();
      void CmTaille800();
   DECLARE_RESPONSE_TABLE(TMaFenetre);
   public:
   	TMaFenetre(char* title);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_COMMAND(CM_FOND_ROUGE, CmFondRouge),
	EV_COMMAND(CM_FOND_BLEU, CmFondBleu),
	EV_COMMAND(CM_FOND_JAUNE, CmFondJaune),
	EV_COMMAND(CM_FOND_VERT, CmFondVert),
	EV_COMMAND(CM_TAILLE_100, CmTaille100),
	EV_COMMAND(CM_TAILLE_200, CmTaille200),
	EV_COMMAND(CM_TAILLE_400, CmTaille400),
	EV_COMMAND(CM_TAILLE_800, CmTaille800),
END_RESPONSE_TABLE;

TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{}

void TMaFenetre::CmFondRouge()
{
   SetBkgndColor(TColor::TColor(RGB(255,0,0)));
   Invalidate();
}

void TMaFenetre::CmFondBleu()
{
   SetBkgndColor(TColor::TColor(RGB(0,0,255)));
   Invalidate();
}

void TMaFenetre::CmFondVert()
{
   SetBkgndColor(TColor::TColor(RGB(0,255,0)));
   Invalidate();
}

void TMaFenetre::CmFondJaune()
{
   SetBkgndColor(TColor::TColor(RGB(255,255,0)));
   Invalidate();
}

void TMaFenetre::CmTaille100()
{
   GetApplication()->GetMainWindow()->MoveWindow(GetApplication()->GetMainWindow()->Attr.X,GetApplication()->GetMainWindow()->Attr.Y,100,100,1);
   Invalidate();
}

void TMaFenetre::CmTaille200()
{
   GetApplication()->GetMainWindow()->MoveWindow(GetApplication()->GetMainWindow()->Attr.X,GetApplication()->GetMainWindow()->Attr.Y,200,200,1);
   Invalidate();
}

void TMaFenetre::CmTaille400()
{
   GetApplication()->GetMainWindow()->MoveWindow(GetApplication()->GetMainWindow()->Attr.X,GetApplication()->GetMainWindow()->Attr.Y,400,400,1);
   Invalidate();
}

void TMaFenetre::CmTaille800()
{
   GetApplication()->GetMainWindow()->MoveWindow(GetApplication()->GetMainWindow()->Attr.X,GetApplication()->GetMainWindow()->Attr.Y,800,600,1);
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
	SetMainWindow(new TFrameWindow(NULL, "Série 3 - Ex1", new TMaFenetre("Série 3 - Ex1")));
   GetMainWindow()->AssignMenu(IDM_MENU1);
}

int OwlMain(int, char**)
{
	TMonAppli App;
   return App.Run();
}
