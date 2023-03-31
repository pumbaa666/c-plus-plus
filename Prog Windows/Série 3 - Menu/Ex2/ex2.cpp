#include <owl\pch.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Ex2.rh"

int vN = 0;
TColor vOui = RGB(0,255,0);
TColor vNon = RGB(255,0,0);
char vOuiStr[6] = "vert";
char vNonStr[6] = "rouge";
char vQuestion[10] = "paire";

class TMaFenetre : public TWindow
{
	protected:
		void EvLButtonDown(uint, TPoint&);
		void EvMButtonDown(uint, TPoint&);
		void EvRButtonDown(uint, TPoint&);

   	void CmOuiRouge();
   	void CmOuiVert();
   	void CmOuiBleu();
   	void CmOuiJaune();

   	void CmNonRouge();
   	void CmNonVert();
   	void CmNonBleu();
   	void CmNonJaune();

   	void CmQuestionPaire();
   	void CmQuestionImpaire();
   	void CmQuestionPremier();
   	void CmQuestionCarre();
   	void CmQuestionParfait();

   DECLARE_RESPONSE_TABLE(TMaFenetre);

   public:
   	TMaFenetre(char* title);
      void Actualiser();
};

DEFINE_RESPONSE_TABLE1(TMaFenetre, TWindow)
	EV_WM_LBUTTONDOWN,
	EV_WM_MBUTTONDOWN,
	EV_WM_RBUTTONDOWN,

	EV_COMMAND(CM_OUI_ROUGE, CmOuiRouge),
	EV_COMMAND(CM_OUI_BLEU, CmOuiBleu),
	EV_COMMAND(CM_OUI_VERT, CmOuiVert),
	EV_COMMAND(CM_OUI_JAUNE, CmOuiJaune),

	EV_COMMAND(CM_NON_ROUGE, CmNonRouge),
	EV_COMMAND(CM_NON_BLEU, CmNonBleu),
	EV_COMMAND(CM_NON_VERT, CmNonVert),
	EV_COMMAND(CM_NON_JAUNE, CmNonJaune),

	EV_COMMAND(CM_QUESTION_PAIRE, CmQuestionPaire),
	EV_COMMAND(CM_QUESTION_IMPAIRE, CmQuestionImpaire),
	EV_COMMAND(CM_QUESTION_PREMIER, CmQuestionPremier),
	EV_COMMAND(CM_QUESTION_CARRE, CmQuestionCarre),
	EV_COMMAND(CM_QUESTION_PARFAIT, CmQuestionParfait),
END_RESPONSE_TABLE;

TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{}

void TMaFenetre::Actualiser()
{
   if(strcmp(vQuestion,"paire") == 0)
   {
      if(vN % 2 == 0)
         SetBkgndColor(vOui);
      else
         SetBkgndColor(vNon);
   }
   else if(strcmp(vQuestion,"impaire") == 0)
   {
      if(vN % 2 != 0)
         SetBkgndColor(vOui);
      else
         SetBkgndColor(vNon);
   }
   else if(strcmp(vQuestion,"premier") == 0)
   {
   	if(vN < 2)
	      SetBkgndColor(vNon);
      else
      {
	      SetBkgndColor(vOui);
   		for(int i = vN-2; i > 1; i--)
      		if(vN % i == 0)
            {
	         	SetBkgndColor(vNon);
               break;
            }
      }
   }
   else if(strcmp(vQuestion,"carre") == 0)
   {
   	if(vN == 0)
  	      SetBkgndColor(vOui);
   	else if(vN > 0)
      {
  	   	if(vN/sqrt(vN) == sqrt(vN))
   	      SetBkgndColor(vOui);
        	else
         	SetBkgndColor(vNon);
      }
     	else
        	SetBkgndColor(vNon);
   }
   else if(strcmp(vQuestion,"parfait") == 0)
   {
   	if(vN > 1)
      {
	   	int vTemp = 0;
   	   for(int i = 1; i < vN; i++)
      		if(vN % i == 0)
         		vTemp += i;
	      if(vN == vTemp)
   	      SetBkgndColor(vOui);
      	else
         	SetBkgndColor(vNon);
      }
      else
         	SetBkgndColor(vNon);
   }

   char tTitre[80] = "";
   char tN[] = "";
	itoa(vN,tN,10);

	strcat(tTitre, "N = ");
   strcat(tTitre, tN);
   strcat(tTitre, "     Oui = ");
   strcat(tTitre, vOuiStr);
   strcat(tTitre, "     Non = ");
   strcat(tTitre, vNonStr);
   strcat(tTitre, "     Question = ");
   strcat(tTitre, vQuestion);
   GetApplication()->GetMainWindow()->SetCaption(tTitre);
   Invalidate();
}

void TMaFenetre::EvLButtonDown(uint modKeys, TPoint& p)
{
	vN++;
   Actualiser();
}

void TMaFenetre::EvRButtonDown(uint modKeys, TPoint& p)
{
	vN--;
   Actualiser();
}

void TMaFenetre::EvMButtonDown(uint modKeys, TPoint& p)
{
	vN = 0;
   Actualiser();
}

void TMaFenetre::CmOuiRouge()
{
	vOui = RGB(255,0,0);
   strcpy(vOuiStr,"Rouge");
   Actualiser();
}

void TMaFenetre::CmOuiBleu()
{
	vOui = RGB(0,0,255);
   strcpy(vOuiStr,"Bleu");
   Actualiser();
}

void TMaFenetre::CmOuiJaune()
{
	vOui = RGB(0,255,255);
   strcpy(vOuiStr,"Jaune");
   Actualiser();
}

void TMaFenetre::CmOuiVert()
{
	vOui = RGB(0,255,0);
   strcpy(vOuiStr,"Vert");
   Actualiser();
}

void TMaFenetre::CmNonRouge()
{
	vNon = RGB(255,0,0);
   strcpy(vNonStr,"Rouge");
   Actualiser();
}

void TMaFenetre::CmNonBleu()
{
	vNon = RGB(0,0,255);
   strcpy(vNonStr,"Bleu");
   Actualiser();
}

void TMaFenetre::CmNonJaune()
{
	vNon = RGB(0,255,255);
   strcpy(vNonStr,"Jaune");
   Actualiser();
}

void TMaFenetre::CmNonVert()
{
	vNon = RGB(0,255,0);
   strcpy(vNonStr,"Vert");
   Actualiser();
}

void TMaFenetre::CmQuestionPaire()
{
	strcpy(vQuestion, "paire");
   Actualiser();
}

void TMaFenetre::CmQuestionImpaire()
{
	strcpy(vQuestion, "impaire");
   Actualiser();
}

void TMaFenetre::CmQuestionPremier()
{
	strcpy(vQuestion, "premier");
   Actualiser();
}

void TMaFenetre::CmQuestionCarre()
{
	strcpy(vQuestion, "carre");
   Actualiser();
}

void TMaFenetre::CmQuestionParfait()
{
	strcpy(vQuestion, "parfait");
   Actualiser();
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
	SetMainWindow(new TFrameWindow(NULL, "Série 3 - Ex2", new TMaFenetre("Série 3 - Ex2")));
   GetMainWindow()->AssignMenu(IDM_MENU1);
}

int OwlMain(int, char**)
{
	TMonAppli App;
   return App.Run();
}