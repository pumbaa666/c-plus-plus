#define TAILLE 6

VaisseauJoueur::VaisseauJoueur()
{
  vNbTir = 0;
  premier = NULL;
  dernier = NULL;
}

void VaisseauJoueur::Init(int vX, int vY, int vCouleur)
{
  x = vX;
  y = vY;
  vie = 20;
  couleur = vCouleur;
  vNbTir = 0;
  premier = NULL;
  dernier = NULL;
}

void VaisseauJoueur::Afficher()
{
	settextjustify(1,1);
   setcolor(couleur);
   outtextxy(912,50,vNom);
   setcolor(couleur);
	moveto(x,y-10*TAILLE);
   lineto(x-1.66*TAILLE,y-1.66*TAILLE);
   lineto(x-3.66*TAILLE,y-3.66*TAILLE);
   ellipse(x-4.16*TAILLE,y-3.33*TAILLE,0,180,0.83*TAILLE,2.5*TAILLE);
   ellipse(x-5*TAILLE,y+1.66*TAILLE,90,270,4.16*TAILLE,5*TAILLE);
   circle(x-6.66*TAILLE,y+1.66*TAILLE,2.5*TAILLE);
   ellipse(x-5*TAILLE,y+1.66*TAILLE,240,270,1.66*TAILLE,5*TAILLE);

   for(float vCount = 0; vCount < 1.6*3.14; vCount += 0.1)
   {
   	putpixel(x+0.83*TAILLE*(vCount), y+2.5*TAILLE+TAILLE*sin(vCount),couleur);
   	putpixel(x-0.83*TAILLE*(vCount), y+2.5*TAILLE+TAILLE*sin(vCount),couleur);
   }

	for(float vCount = 5.2; vCount < 6.28; vCount+=0.05)  //   ellipse(x+30,y+10,270,300,10,30);
      putpixel(x+5*TAILLE-1.66*TAILLE*sin(vCount),y+1.66*TAILLE+5*TAILLE*cos(vCount),couleur);
   circle(x+6.66*TAILLE,y+1.66*TAILLE,2.5*TAILLE);
   ellipse(x+5*TAILLE,y+1.66*TAILLE,270,90,4.16*TAILLE,5*TAILLE);
   ellipse(x+4.16*TAILLE,y-3.33*TAILLE,0,180,0.83*TAILLE,2.5*TAILLE);
   moveto(x+3.33*TAILLE,y-3.33*TAILLE);
   lineto(x+1.66*TAILLE,y-1.66*TAILLE);
   lineto(x,y-10*TAILLE);
}

void VaisseauJoueur::Effacer()
{
   setcolor(BLACK);
	moveto(x,y-10*TAILLE);
   lineto(x-1.66*TAILLE,y-1.66*TAILLE);
   lineto(x-3.66*TAILLE,y-3.66*TAILLE);
   ellipse(x-4.16*TAILLE,y-3.33*TAILLE,0,180,0.83*TAILLE,2.5*TAILLE);
   ellipse(x-5*TAILLE,y+1.66*TAILLE,90,270,4.16*TAILLE,5*TAILLE);
   circle(x-6.66*TAILLE,y+1.66*TAILLE,2.5*TAILLE);
   ellipse(x-5*TAILLE,y+1.66*TAILLE,240,270,1.66*TAILLE,5*TAILLE);

   for(float vCount = 0; vCount < 1.6*3.14; vCount += 0.1)
   {
   	putpixel(x+0.83*TAILLE*(vCount), y+2.5*TAILLE+TAILLE*sin(vCount),BLACK);
   	putpixel(x-0.83*TAILLE*(vCount), y+2.5*TAILLE+TAILLE*sin(vCount),BLACK);
   }

	for(float vCount = 5.2; vCount < 6.28; vCount+=0.05)  //   ellipse(x+30,y+10,270,300,10,30);
      putpixel(x+5*TAILLE-1.66*TAILLE*sin(vCount),y+1.66*TAILLE+5*TAILLE*cos(vCount),BLACK);
   circle(x+6.66*TAILLE,y+1.66*TAILLE,2.5*TAILLE);
   ellipse(x+5*TAILLE,y+1.66*TAILLE,270,90,4.16*TAILLE,5*TAILLE);
   ellipse(x+4.16*TAILLE,y-3.33*TAILLE,0,180,0.83*TAILLE,2.5*TAILLE);
   moveto(x+3.33*TAILLE,y-3.33*TAILLE);
   lineto(x+1.66*TAILLE,y-1.66*TAILLE);
   lineto(x,y-10*TAILLE);
}

void VaisseauJoueur::Deplacer(int DX, int DY)
{
  if(DX > 0 && x < 800-9*TAILLE)
      x += DX;
  if(DX < 0 && x > 9*TAILLE)
      x += DX;
  if(DY > 0 && y < 768-9*TAILLE)
      y += DY;
  if(DY < 0 && y > 550-7*TAILLE)
      y += DY;
}

void VaisseauJoueur::Tir(int vDernierTir)
{
  if(abs(dernier_tir - vDernierTir) > 20)
  {
	  dernier_tir = vDernierTir;
  	  vNbTir++;
	  Missile *courant;
	  courant = (Missile*) malloc(sizeof(Missile));
	  courant->suivant = 0;

	  if(dernier == NULL)
	  {
   	  premier = dernier = courant;
	  }
	  else
	  {
	  	  dernier->suivant = courant;
   	  dernier = courant;
	  }
	  courant->Init(x,y-65,this);
  }
}

void VaisseauJoueur::DetruireMissile(int vNum)
{
		Missile *detruit;
      Missile *temp;

		detruit = premier;
      if (vNum == 1)
      {
         if (vNbTir > 1 && detruit != NULL)
         {
      		premier = detruit->suivant;
            detruit->Effacer();
         	delete detruit;
            detruit = premier;
            for (int i = 1 ; i <vNbTir ; i++)
            {
            	detruit->numero=i;
               detruit = detruit->suivant;
            }
         }
         else if(detruit != NULL)
         {
            detruit->Effacer();
         	delete detruit;
            dernier = premier = NULL;
         }
      }
      else if (vNum < vNbTir && detruit != NULL)
      {
         while (detruit->numero < vNum)
	      	detruit = detruit->suivant;

	      temp = detruit->suivant;
         detruit->Effacer();
	      delete detruit;
	      detruit = premier;
	      for (int i=1 ; i<vNum-1 ; i++)  // pour pointer sur le missile precedant celui qui a été effacé...
	       	detruit = detruit->suivant;

	      detruit->suivant = temp;
	      detruit = temp;

	      for(int i = vNum ; i <vNbTir-1 ; i++)
	      {
	      	detruit->numero=i;
	         detruit = detruit->suivant;
	      }
      }
      else if (vNum == vNbTir && dernier != NULL)
	   {
         dernier->Effacer();
         delete dernier;
         while (detruit->numero < vNum)
      		detruit = detruit->suivant;
         dernier = detruit;
      }
      vNbTir--;
}
