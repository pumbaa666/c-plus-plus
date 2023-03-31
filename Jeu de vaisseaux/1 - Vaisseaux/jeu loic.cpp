#include <conio.h>
#include <stdio.h>

#include "winbgim.h"
#include "classe.h"
#include "classe_titre.cpp"
#include "classe_vaisseau_joueur.cpp"
#include "classe_vague.cpp"
#include "classe_missile.cpp"
#include "classe_missile_ennemi.cpp"
#include "classe_etoiles.cpp"
#include "classe_ennemi.cpp"
#include "classe_pave.cpp"
#include "classe_particule.cpp"

#define NBETOILES 200

void main(void)
{

  /************************* Déclaration *************************/
  VaisseauJoueur cJoueur;
  Vague cVague;
  Etoiles tFond[NBETOILES];
  Pave cPave;

  int vUser = 0, vOldUser = 0, vCountMain = 0, vCount = 0;
  bool vSens = 0, vArrive = 0, vHyperEspace = 0;

  void Menu(char[],int);
  void HyperEspace(Etoiles[], bool);

  /******************************* Initialisation *******************************/
  randomize();
  cVague.Init();
  initwindow(1024,768);
  char vNomJoueur[15];
  Menu(vNomJoueur,0);

  cleardevice();
  vUser = 0;

  setcolor(LIGHTGRAY);
  line(801,0,801,768);
  line(802,0,802,768);
  line(803,0,803,768);
  setcolor(COLOR(24,737,228));
  settextjustify(1,1);
  settextstyle(6, HORIZ_DIR, 2);
  outtextxy(912,210,"Points de vie");
  outtextxy(912,230,"20");

  for(int vCount = 0; vCount < NBETOILES; vCount++)
     tFond[vCount].Init(random(800), random(768), COLOR(255,255,random(255)), random(5)+2);

  cPave.Afficher(0);
  cVague.Positionner(200);
  cJoueur.Init(400,600,COLOR(255,200,50));
  strcpy(cJoueur.vNom,vNomJoueur);
  /******************************************************************************/

  do // Boucle principale
  {
    /****** Affichage des étoiles du background *******/
    for(vCount = 0; vCount < NBETOILES; vCount++)
    {
       tFond[vCount].Effacer();
       tFond[vCount].Deplacer(vCountMain);
       tFond[vCount].Afficher();
    }

   /***** Déplacement du vaisseau si ça s'y prête *****/
   if(vHyperEspace == false)
   {
      cJoueur.Effacer();
      switch(vUser)
      {
         case 49 : cJoueur.Effacer(); cJoueur.Deplacer(-2,2); break;
         case 50 : cJoueur.Effacer(); cJoueur.Deplacer(0,2); break;
         case 51 : cJoueur.Effacer(); cJoueur.Deplacer(2,2); break;
         case 52 : cJoueur.Effacer(); cJoueur.Deplacer(-2,0); break;
         case 54 : cJoueur.Effacer(); cJoueur.Deplacer(2,0); break;
         case 55 : cJoueur.Effacer(); cJoueur.Deplacer(-2,-2); break;
         case 56 : cJoueur.Effacer(); cJoueur.Deplacer(0,-2); break;
         case 57 : cJoueur.Effacer(); cJoueur.Deplacer(2,-2); break;

         case 72 : cJoueur.Effacer(); cJoueur.Deplacer(0,-2); vUser = 0; break;
         case 75 : cJoueur.Effacer(); cJoueur.Deplacer(-2,0); vUser = 0; break;
         case 77 : cJoueur.Effacer(); cJoueur.Deplacer(2,0); vUser = 0; break;
         case 80 : cJoueur.Effacer(); cJoueur.Deplacer(0,2); vUser = 0; break;
      }
    }
    cJoueur.Afficher();

    if(kbhit())
    {
      vOldUser = vUser;   // Pour que le vaisseau continue de bouger après avoir pressé une touche
      vUser = getch();
      printf("\n%c : %i",vUser,vUser);
      flushall();
      if(vUser != 112 && vUser != 116 && vHyperEspace == false)
  	      cPave.Afficher(vUser);

      if(vUser == 32 && vHyperEspace == false)     // Espace - Tir de missile
      {
         cJoueur.Tir(vCountMain);
         vUser = vOldUser;
      }
      if(vUser == 112) // p - Pause
      {
			int vCntColor = 11;
         vUser = 0;
      	settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
         do
         {
         	setcolor(COLOR(vCntColor,0,0));
	         if(vSens == 0)
   		      vCntColor++;
         	else
		         vCntColor--;
      	   if(vCntColor == 255 || vCntColor == 10)
         		vSens = !vSens;
            settextjustify(1,1);
	         outtextxy(912,400,"Pause");
   	      delay(10);
	         if(kbhit())
   			   vUser = getch();
      	}
	      while(vUser != 112 && vUser != 27);
         setcolor(BLACK);
         outtextxy(912,400,"Pause");
         vUser = vOldUser;
      }
    }

    /***** Arrivage et déplacement des ennemis *****/
    if(vArrive == false)
       vArrive = cVague.Amener(vCountMain);
    else
    {
    	 if(vHyperEspace == true)
       {
	       HyperEspace(tFond,false);
          vHyperEspace = false;
       }
       if(cVague.Deplacer(vCountMain, &cJoueur) == false)   // Laisse le temps au dernier ennemi d'exploser
       {
       	vArrive = false;
 	      cPave.Afficher(0);
         cVague.num++;
         cVague.Positionner(500);
         vHyperEspace = true;
         HyperEspace(tFond,true);
       }
    }

    /***** Déplacement des missiles du joueur *****/
    if(cJoueur.vNbTir > 0)
	 {
    	 Missile *courant=NULL;
       Missile *temp;
       courant = cJoueur.premier;
       int NbTirTemp = cJoueur.vNbTir;
       for (int i = 1 ; i<=NbTirTemp ; i++)
       {
       	int test = cJoueur.vNbTir;
         if (i < NbTirTemp && courant != NULL)
	       	temp = courant->suivant;

         courant->Effacer();
       	courant->Deplacer(&cJoueur, &cVague, vCountMain, &vArrive);
         if (cJoueur.vNbTir == test)
         {
         	test = cJoueur.vNbTir;
         	courant->Afficher();
         }
         courant = temp;
       }
    }
    vCountMain++;
    delay(1);
  }
  while(vUser != 27);
  closegraph();
}

void Menu(char vNomJoueur[50],int vIni)
{
  char vNom[50] = "";
  void Intro(char[]);
  int vUser, vMenu = vIni, vCount = 0;
  graphique *Power;
  img* imagePower = Power->loadBMP("fond.bmp");
  Power->putimage2(0,0, imagePower->sprite, COPY_PUT,1024,768);
  Titre cAccueil;
  cAccueil.Init("Last day in space",50);
  do
  {
     vUser = 0;
     cAccueil.Afficher(vCount,vMenu);
     if(kbhit())
     {
        vUser = getch();
        flushall();
     }

     if (vUser == 72)
     {
     		vMenu--;
         if (vMenu < 0)
         	vMenu = 3;
     }
     if (vUser == 80)
     {
     		vMenu++;
         if (vMenu == 4)
         	vMenu = 0;
     }

     delay(10);
     vCount++;
     if(vCount == 255)
        vCount = 0;
  }
  while(vUser != 13);

  if(vMenu == 0)  // Jouer
  {
  	  FILE *f = fopen("name.dat","r");
     if(f == NULL)
     	  vMenu = 1;
     else
     	  fread(vNom,sizeof(char),15,f);
  }
  if(vMenu == 1) // Nouveau joueur
  {
     setactivepage(1);
     settextstyle(5,HORIZ_DIR,5);
     setcolor(COLOR(200,0,200));
     outtextxy(512,250,"Entrez votre nom");
     setvisualpage(1);

     vCount = 0;
     do
     {
     	   vUser = getch();
         if(vUser == 8)
         {
         	if(vCount > 0)
	         {
			      setcolor(BLACK);
      		   outtextxy(512,300,vNom);
		         setcolor(COLOR(200,0,200));
      	   	vCount--;
   	      	vNom[vCount] = '\0';
  	      	   outtextxy(512,300,vNom);
         	}
         }
         else
         {
	   	   setcolor(BLACK);
   	      outtextxy(512,300,vNom);
	         setcolor(COLOR(200,0,200));
				vNom[vCount] = vUser;
	         outtextxy(512,300,vNom);
	     		vCount++;
         }
     }
     while(vUser != 13);
     vNom[vCount-1] = '\0';
     FILE *f = fopen("name.dat","w");
     fwrite(vNom,sizeof(vNom),1,f);
     fclose(f);
     setactivepage(0);
     setvisualpage(0);
     Intro(vNom);
  }
  if(vMenu == 2)  // Aide
  {
  	  setactivepage(3);
     setcolor(COLOR(245,180,24));
     settextstyle(3,1,3);
     settextjustify(0,0);
     outtextxy(20,150,"Le but du jeu est de supprimer tout les vaisseaux ennemis qui arrivent par vague.");
     outtextxy(20,220,"Pour vous déplacer, vous pouvez utiliser soit les touches fléchées, soit le pavé numérique.");
     outtextxy(20,270,"En utilisant les flèches, vous ne vous déplacez qu'une fois. Par contre, avec le pavé");
     outtextxy(20,320,"numérique, le vaisseau reste en mouvement.");
     outtextxy(20,390,"Utilisez la touche 5 pour vous stabiliser.");
     outtextxy(20,440,"Espace pour tirer");
     setvisualpage(3);

     settextjustify(1,1);
     settextstyle(6,0,6);
     int vCouleurAide = 0;
     bool vSens = 0;
     do
     {
        if(vSens == 0)
  		     vCouleurAide++;
        else
	        vCouleurAide--;
     	  if(vCouleurAide == 255 || vCouleurAide == 0)
           vSens = !vSens;
        setcolor(COLOR(245,180,vCouleurAide));
	  	  outtextxy(512,50,"Aide");
        delay(10);
     }
     while(!kbhit());
  	  setactivepage(0);
     setvisualpage(0);
     Menu("",2);
  }
  if(vMenu == 3) // Quitter
  	  exit(0);
  strcpy(vNomJoueur,vNom);
}

void Intro(char vNom[])
{
	void AfficherText(char[],int*,int*);
   void Text();
   void Curseur(int, int);
   void Voyage();

   char vText[2000] = "";
   int vUser = 0, vX = 100, vY = 100;

	cleardevice();
   strcpy(vText,"Bienvenue ");
   strcat(vText,vNom);
   strcat(vText,"@");
   strcat(vText,"La galaxie à besoin de vous : des flottes entières de vaisseaux extraterrestres veulent tout détruire.@Sautez dans votre spaceship et nettoyez-moi tout ça!@!!! OVER !!!"); // @ pour sauter à la ligne
   AfficherText(vText,&vX,&vY);

	Curseur(vX, vY);
   Voyage();
}

void AfficherText(char vText[], int *vX, int *vY)
{
	setcolor(COLOR(25,220,50));
	settextstyle(3,1,3);

	char vTemp[2] = "";
   int vUser = 0;

	for(int i = 0; i < strlen(vText); i++)
   {
      vTemp[0] = vText[i];
      if(*vX >= 850 && vTemp[0] == ' ' || vTemp[0] == '@')
      {
		   setfillstyle(SOLID_FILL,BLACK);
         bar(*vX-7,*vY+5,*vX+7,*vY+10);
      	*vX = 100;
         *vY += 40;
      }
      else
      {
	      *vX += 15;
		   setfillstyle(SOLID_FILL,BLACK);
         bar(*vX-22,*vY+5,*vX-8,*vY+10);
	   	outtextxy(*vX,*vY,vTemp);
		   setfillstyle(SOLID_FILL,COLOR(25,220,50));
         bar(*vX-7,*vY+5,*vX+7,*vY+10);
      }
      if(kbhit())
      	if(vUser = getch() == 27)
         	break;
      delay(100);
   }
   *vX += 15;
}

void Curseur(int vX, int vY)
{
   int vUser = 0;
   bool vFlip = true;
   do
   {
   	if(vFlip == true)
      {
		   setfillstyle(SOLID_FILL,BLACK);
         bar(vX-22,vY+5,vX-8,vY+10);
      }
      else
      {
		   setfillstyle(SOLID_FILL,COLOR(25,220,50));
         bar(vX-22,vY+5,vX-8,vY+10);
      }
      vFlip = !vFlip;
      if(kbhit())
      	vUser = getch();
      delay(250);
   }
	while(vUser == 0);
}

void Voyage()
{
   #define NBPART 500
	int vUser = 0;
	cleardevice();
   Particules tTab[NBPART];
   for(int i = 0; i < NBPART; i++)
   	tTab[i].Init(512,384,5,COLOR(255,255,random(150)+100));
   for(int i = 0; i < 250; i++)
   {
      if(kbhit())
      	if(vUser = getch() == 27)
         	break;
	   for(int j = 0; j < NBPART; j++)
   		if(tTab[j].Augmenter() == false)
         	tTab[j].Init(random(12)+500,random(14)+370,5,COLOR(255,255,random(150)+100));
   	delay(50);
   }
}

void HyperEspace(Etoiles tFond[NBETOILES], bool vHE)
{
   if(vHE == true)   // Entrée de l'HyperEspace
   {
  	 	for(int i = 0; i < NBETOILES; i++)
     		tFond[i].Effacer();

      for(int j = 0; j < 20; j++)
   	{
  	 		for(int i = 0; i < NBETOILES; i++)
     		{
  	  			tFond[i].Deplacer(2*3*4*5);
     			tFond[i].Afficher();
   		}
  			delay(25);
     	}
   	for(int i = 0; i < NBETOILES; i++)
  	   	tFond[i].Init(-1, 0, 0, 0);
     	setfillstyle(SOLID_FILL,BLACK);
      bar(0,740,799,768);
   }
   else  // Sortie de l'HyperEspace
  	{
     	for(int i = 0; i < NBETOILES; i++)
   	{
   		tFond[i].Init(-1, 0, 0, 0);
  	 		tFond[i].y -= 20;
    	}
   }
}
