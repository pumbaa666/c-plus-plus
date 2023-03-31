#include <owl\pch.h>
#include "exemple.h"

char BarreDeTitre[] = "Menu standard";

class TMaFenetre : public TWindow
{
	protected:
   	void CmFileNew();
      void CmFileOpen();
      void CmEditUndo();
      void CmEditRedo();
   DECLARE_RESPONSE_TABLE(TMaFenetre);
   public:
   	TMaFenetre(char* title);
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_COMMAND(CM_FILE_NEW, CmFileNew),
	EV_COMMAND(CM_FILE_OPEN, CmFileOpen),
	EV_COMMAND(CM_EDIT_UNDO, CmEditUndo),
	EV_COMMAND(CM_EDIT_REDO, CmEditRedo),
END_RESPONSE_TABLE;

TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{}

void TMaFenetre::CmFileNew()
{
	MessageBox("Fichier.Nouveau sélectionné", Title);
}

void TMaFenetre::CmFileOpen()
{
	MessageBox("Fichier.Ouvrir sélectionné", Title);
}

void TMaFenetre::CmEditUndo()
{
	MessageBox("Editer.Annuler sélectionné", Title);
}

void TMaFenetre::CmEditRedo()
{
	MessageBox("Editer.Refaire sélectionné", Title);
}

class TMonAppli : public TApplication
{
	public :
   	TMonAppli();
      void InitMainWindow();
};

TMonAppli::TMonAppli() : TApplication()
{}

void TMonAppli::InitMainWindow()
{
	SetMainWindow(new TFrameWindow(NULL, BarreDeTitre, new TMaFenetre(BarreDeTitre)));
   GetMainWindow()->AssignMenu(IDM_MENU1);
   nCmdShow = SW_SHOWMAXIMIZED;
}

int OwlMain(int, char**)
{
	TMonAppli App;
   return App.Run();
}

