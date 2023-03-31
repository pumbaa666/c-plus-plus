void Particules::Init(int vX, int vY, int vFacteur)
{
   x = vX+random(20)-10;
   y = vY+random(20)-10;
   dx = random(10*vFacteur)-5*vFacteur;
   dy = random(10*vFacteur)-5*vFacteur;
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

bool Particules::AugmenterIntro()
{
	setcolor(BLACK);
   line(x,y,x+2*dx,y+2*dy);

   x += dx;
   y += dy;
   if(x < 0 || x > 1024)
   	return(false);
      
	setcolor(COLOR(255,255,random(150)+100));
   line(x,y,x+2*dx,y+2*dy);
	return(true);
}
