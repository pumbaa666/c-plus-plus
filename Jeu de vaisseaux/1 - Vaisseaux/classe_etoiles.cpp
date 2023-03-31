void Etoiles::Init(int vX, int vY, int vCouleur, int vVitesse)
{
  if(vX != -1)
  {
     x = vX;
     y = vY;
     couleur = vCouleur;
     vitesse = vVitesse;
  }
  else if(vitesse != 1)
     vitesse = 1;
  else
     vitesse = random(5)+2;
}

void Etoiles::Afficher()
{
	setcolor(couleur);
  if(vitesse == 1)
     line(x,y-20,x,y);
  else
     putpixel(x,y,couleur);
}

void Etoiles::Effacer()
{
  setcolor(BLACK);
  if(vitesse == 1)
     line(x,y-20,x,y);
  else
     putpixel(x,y,BLACK);
}

void Etoiles::Deplacer(int vModulo)
{
  if(vModulo%vitesse == 0)
  {
    if(vitesse == 1)
      y += 10;
    else
       y++;
    if(y > 768)
    {
      y = 0;
      x = random(800);
      couleur = COLOR(255,255,random(255));
      if(vitesse == 1)
         vitesse = 1;
      else
         vitesse = random(5)+2;
    }
  }
}
