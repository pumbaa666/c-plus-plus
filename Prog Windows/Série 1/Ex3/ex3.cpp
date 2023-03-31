#include <owl\applicat.h>
#include <owl\framewin.h>
#include <owl\dc.h>
#include <stdlib.h>
char BarreDeTitre[40] = "Exercice Modifié";

class TMaFenetre : public TWindow
{
	public :
   	TMaFenetre();
};

class TMonApplication : public TApplication
{
   private :
		void InitMainWindow();
   public :
   	TMonApplication(char far *);
}
;

TMaFenetre::TMaFenetre() : TWindow(NULL, NULL, NULL)
{
	SetBkgndColor(TColor::TColor(RGB(random(255),random(255),random(255))));
}

TMonApplication::TMonApplication(char far *titre) : TApplication(titre)
{}

void TMonApplication::InitMainWindow()
{
	TFrameWindow * ad_cadre;
   TWindow * ad_fenetre;
   ad_fenetre = new TMaFenetre();
   ad_cadre = new TFrameWindow(NULL, BarreDeTitre, ad_fenetre);
   SetMainWindow(ad_cadre);
   GetMainWindow()->Attr.X = GetMainWindow()->Attr.Y = 0;
   GetMainWindow()->Attr.W = random(1280);
   GetMainWindow()->Attr.H = random(1024);
   GetMainWindow()->Attr.Style |= WS_VSCROLL;
   GetMainWindow()->Attr.Style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
}

int OwlMain(int argc, char * argv[])
{
	randomize();
	if(argc >= 2)
   	strcpy(BarreDeTitre, argv[1]);

   TMonApplication MonAppli(BarreDeTitre);
   MonAppli.Run();
   return MonAppli.Status;
}
