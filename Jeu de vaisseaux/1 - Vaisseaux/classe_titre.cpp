#include "images.cpp"

void Titre::Init(char txt[], int vY)
{
	vOldMenu = 666;
   settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
   text = new char(strlen(txt));
   text = txt;
   y = vY;
   largeur = textwidth(txt);
   hauteur = textheight(txt);
   tTab = new bool*[largeur];
   rapport = float(largeur)/255;

   setactivepage(2);
   outtextxy(0,y,text);
   for(int i = 0; i < largeur; i++)
      tTab[i] = new bool[hauteur];
   for(int i = 0; i < largeur; i++)
      for(int j = 0; j < hauteur; j++)
    	  tTab[i][j] = getpixel(i,j+y);
   setactivepage(0);

   settextstyle(4, HORIZ_DIR, 2);
   settextjustify(1,1);
   setcolor(WHITE);
	outtextxy(512,400,"Jouer");
	outtextxy(512,460,"Nouveau joueur");
	outtextxy(512,520,"Aide");
	outtextxy(512,580,"Quitter");
}

void Titre::Afficher(int vEnCours, int vMenu)
{
   int vCouleur;
	char tTitre[4][15] = {"Jouer","Nouveau Joueur", "Aide", "Quitter"};

   for(int i = 0; i < largeur; i++)
      for(int j = 0; j < hauteur; j++)
         if(tTab[i][j] != 0)
         {
            vCouleur = vEnCours - i/rapport;
            putpixel(512+i-largeur/2,j+y,COLOR(vCouleur,0,255-vCouleur));
         }
   if(vMenu != vOldMenu)
   {
   	vOldMenu = vMenu;
	   for(int i = 0; i < 4; i++)
   	{
   		if(i == vMenu)
	      	setcolor(CYAN);
	      else
		      setcolor(WHITE);
			outtextxy(512,400+60*i,tTitre[i]);
	   }
   }
}

Titre::~Titre()
{
  for(int i = 0; i < largeur; i++)
  		delete tTab[i];
  delete tTab;
}
