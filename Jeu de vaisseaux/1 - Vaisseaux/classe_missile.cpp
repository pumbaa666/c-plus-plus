void Missile::Init(int vX, int vY, VaisseauJoueur* c)
{
	numero = c->vNbTir;

   x = vX;
   y = vY;
}

void Missile::Afficher()
{
   setcolor(RED);
   setfillstyle(SOLID_FILL,RED);
   fillellipse(x,y,2,2);
}

void Missile::Effacer()
{
   setcolor(BLACK);
   setfillstyle(SOLID_FILL,BLACK);
   fillellipse(x,y,2,2);
}

void Missile::Deplacer(VaisseauJoueur* m, Vague *v, int vCountMain, bool *vArrive)
{
	y -= 3;   // Déplacement
   for(int i = 0; i < 11; i++) // Collision
   	for(int j = 0; j < 5; j++)
      	if(y <= v->formation[i][j].y + v->formation[i][j].tailleY  &&  y >= v->formation[i][j].y - v->formation[i][j].tailleY  &&
      	   x <= v->formation[i][j].x + v->formation[i][j].tailleX  &&  x >= v->formation[i][j].x - v->formation[i][j].tailleX)
         {
         	if(v->formation[i][j].type != 0 && v->formation[i][j].type != 100)
            {
	         	v->formation[i][j].vie--;
			      m->DetruireMissile(numero);
	         	v->formation[i][j].Effacer(vCountMain+1);
   	         if(v->formation[i][j].vie <= 0)
	            {
	   	      	v->formation[i][j].type = 100;
            	 	v->formation[i][j].Exploser();
         	      v->nb_ennemi--;
      	         if(v->nb_ennemi == 0)
   	               *vArrive = false;
	            }
            }
         }
   if(y < 0)
      m->DetruireMissile(numero);
}
