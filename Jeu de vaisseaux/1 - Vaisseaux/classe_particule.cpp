void Particules::Init(int vX, int vY, int vCouleur)
{
   x = vX;
   y = vY;
   dx = random(3)-1;
   dy = random(6);
   couleur = vCouleur;
}

void Particules::Init(int vX, int vY, int vFacteur, int vCouleur)
{
   x = vX+random(20)-10;
   y = vY+random(20)-10;
   dx = random(10*vFacteur)-5*vFacteur;
   dy = random(10*vFacteur)-5*vFacteur;
   couleur = vCouleur;
}

void Particules::Augmenter(int temps, int couleur)
{
	if(x-3*dx < 800)
		putpixel(x-3*dx,y-3*dy,BLACK); // -3* pour faire une trace de 3 pixels
   x += dx;
   y += dy;
   if(temps > 4 && x < 800)
		putpixel(x,y,couleur);
}

bool Particules::Augmenter()
{
	setcolor(BLACK);
   line(x,y,x+2*dx,y+2*dy);

   x += dx;
   y += dy;
   if(x < 0 || x > 1024)
   	return(false);
      
	setcolor(couleur);
   line(x,y,x+2*dx,y+2*dy);
	return(true);
}
