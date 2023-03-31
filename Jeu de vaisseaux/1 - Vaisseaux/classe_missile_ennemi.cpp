void MissileEnnemi::Init(int vX, int vY, Ennemi* c)
{
	numero = c->vNbTir;
   x = vX;
   y = vY;
}

void MissileEnnemi::Afficher()
{
   setcolor(RED);
   setfillstyle(SOLID_FILL,RED);
   fillellipse(x,y,2,2);
}

void MissileEnnemi::Effacer()
{
   setcolor(BLACK);
   setfillstyle(SOLID_FILL,BLACK);
   fillellipse(x,y,2,2);
}

void MissileEnnemi::Deplacer(Ennemi* vMissileEn, VaisseauJoueur* vJ)
{
	void GameOver();
	y += 3;   // Déplacement
   if(y>=vJ->y-9*TAILLE && y<=vJ->y+7 && x>=vJ->x-TAILLE*2 && x<=vJ->x+TAILLE*2 ||
   y>vJ->y-5*TAILLE && y<vJ->y+7 && x>vJ->x-TAILLE*9 && x<vJ->x-TAILLE*2 ||
   y>vJ->y-5*TAILLE && y<vJ->y+7 && x>vJ->x+TAILLE*2 && x<vJ->x+TAILLE*9)
   {
      if (vMissileEn != NULL)
	  		vMissileEn->DetruireMissile(numero);
      vJ->vie--;
      if(vJ->vie < 0)
        	GameOver();

  		/******* Affichage de "Point de vie" *******/
    	if (vJ->vie > 10)
  			setcolor(COLOR(24,177,228));
    	else if (vJ->vie > 5 )
			setcolor(COLOR(255,100,50));
    	else
  	 		setcolor(COLOR(223,0,5));
    	settextjustify(1,1);
		settextstyle(6, HORIZ_DIR, 2);
   	outtextxy(912,210,"Points de vie");

   	char vie_char[4];
	   itoa(vJ->vie,vie_char,10);   // converti le int en char pour pouvoir l'afficher!!
	   setfillstyle(SOLID_FILL,BLACK);
	   bar(870,210,950,230);
	   outtextxy(912,230,vie_char);
	}
  	else if(y > 768)
      if (vMissileEn != NULL)
	      vMissileEn->DetruireMissile(numero);
}

void GameOver()
{
 	setfillstyle(SOLID_FILL,BLACK);
   bar(0,0,1024,768);
   settextstyle(6,0,9);
   settextjustify(1,1);
   setcolor(WHITE);
   char tText[] = "Game Over";
   outtextxy(512,400,tText);

   /***** Création du tableau *****/
   int x = textwidth(tText);
   int y = textheight(tText);
   Particules **tTab;
   tTab = new Particules*[x];
   for(int i = 0; i < x; i++)
      tTab[i] = new Particules[y];
   for(int i = 0; i < x; i++)
	   for(int j = 0; j < y; j++)
      	tTab[i][j].Init(i+512-x/2,j+384-y/2,getpixel(i+512-x/2,j+384-y/2));

   /***** Animation *****/
   do
		for(int j = 0; j < y; j++)
		   for(int i = 0; i < x; i++)
      		tTab[i][j].Augmenter();
   while(!kbhit());

   getch();
   exit(0);
}
