TMonAppli::TMonAppli() : TApplication()
{}

void TMonAppli::InitMainWindow()
{
	SetMainWindow(new TFrameWindow(NULL, "Projet 2 : Graphe", new TMaFenetre("Projet 2 : Graphe")));
   GetMainWindow()->AssignMenu(IDM_MENU1);
}
