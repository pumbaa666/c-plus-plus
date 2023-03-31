#include <math.h>

float rad(float vAngle)
{
   return(vAngle*3.14/180);
}

void Ennemi::Init(int vColor, int vSens, int vType)
{
   couleur = vColor;
   vNbTir = 0;
   premier = NULL;
   dernier = NULL;
 	couleur = vColor;
   type = vType; sens = vSens;
   switch(type)
   {
   	case 0 : vie = 1; freq_tir = 10; tailleX = tailleY = 0; break;
   	case 1 : vie = 1; freq_tir = 15; tailleX = 2*TAILLE; tailleY = 2.5*TAILLE; break;
      case 2 : vie = 2; freq_tir = 20; tailleX = 5*TAILLE; tailleY = 2.5*TAILLE; break;
      case 3 : vie = 2; freq_tir = 25; tailleX = tailleY = 2*TAILLE; break;
      case 4 : vie = 4; freq_tir = 30; tailleX = 4*TAILLE; tailleY = 2*TAILLE; break;
      case 5 : vie = 4; freq_tir = 40; tailleX = tailleY = 6*TAILLE; break;
      case 6 : vie = 4; freq_tir = 50; tailleX = 4*TAILLE; tailleY = 4.5*TAILLE; break;
      case 7 : vie = 6; freq_tir = 60; tailleX = 6*TAILLE; tailleY = 6*TAILLE; break;
      case 20 : vie = 50; freq_tir = 100; tailleX = 10*TAILLE; tailleY = 7*TAILLE; break;
      case 21 : vie = 60; freq_tir = 150; tailleX = 10*TAILLE; tailleY = 7*TAILLE; break;
      case 22 : vie = 75; freq_tir = 200; tailleX = 10*TAILLE; tailleY = 7*TAILLE; break;
   }
}

void Ennemi::Deplacer(int vSensVague, int DX, int DY)
{
	y += DY;
   x += DX*vSensVague*sens;
}

void Ennemi::Positionner(int vX, int vY)
{
	x = vX;
   y = vY;
   temps_expl = 40;
}

int Ennemi::Exploser()
{
	if(temps_expl == 40)
      for(int i = 0; i < 20; i++)
   		tab_explose[i].Init(x,y,1,couleur);
   else
	   for(int i = 0; i < 20; i++)
		   tab_explose[i].Augmenter(temps_expl,couleur);
   return(--temps_expl);
}

void Ennemi::Afficher(int old_angle)
{
  int angle = old_angle;
  setcolor(couleur);
  switch(type)
  {
   case 1 :     // "Y"
   {
     	moveto(x,y+2.5*TAILLE);
  		lineto(x-0.5*TAILLE,y+2.5*TAILLE);
  		lineto(x-0.5*TAILLE,y-0.5*TAILLE);
  		lineto(x-2*TAILLE,y-2*TAILLE);
  		lineto(x-1.5*TAILLE,y-5*TAILLE+2.5*TAILLE);
  		lineto(x,y-TAILLE);
  		lineto(x+1.5*TAILLE,y-2.5*TAILLE);
 		lineto(x+2*TAILLE,y-2*TAILLE);
  		lineto(x+0.5*TAILLE,y-0.5*TAILLE);
  		lineto(x+0.5*TAILLE,y+2.5*TAILLE);
  		lineto(x,y+2.5*TAILLE);

      break;
   }

   case 2 :     // Triangle
   {
  	  	ellipse(x,y-2.5*TAILLE,180,360,5*TAILLE,1.3*TAILLE);
	  	moveto(x-5*TAILLE,y-2.5*TAILLE);
	  	lineto(x,y+2*TAILLE);
	  	lineto(x+5*TAILLE,y-2.5*TAILLE);
      break;
   }

   case 3 :
   {
  		// pentagramme
  		circle(x,y,6*TAILLE/3);
  		moveto(x+sin(rad(angle))*6*TAILLE/3,y-cos(rad(angle))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+144))*6*TAILLE/3,y-cos(rad(angle+144))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+288))*6*TAILLE/3,y-cos(rad(angle+288))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+72))*6*TAILLE/3,y-cos(rad(angle+72))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+216))*6*TAILLE/3,y-cos(rad(angle+216))*6*TAILLE/3);
  		lineto(x+sin(rad(angle))*6*TAILLE/3,y-cos(rad(angle))*6*TAILLE/3);
   	break;
   }

   case 4 :     // hache
   {
  		ellipse(x,y-2*TAILLE,180,360,4*TAILLE,4*TAILLE);
  		ellipse(x-2*TAILLE,y-2*TAILLE,180,360,2*TAILLE,2*TAILLE);
  		ellipse(x+2*TAILLE,y-2*TAILLE,180,360,2*TAILLE,2*TAILLE);
      break;
   }

   case 5 :   //Soleil
   {
	  	circle(x,y,3*TAILLE);
	  	for(float vCount = 0; vCount < 6.24; vCount+=6.28/3)
	  	{
	  	  moveto(x+3*TAILLE*sin(vCount+rad(angle)-0.3),y+3*TAILLE*cos(vCount+rad(angle)-0.3));
	  	  lineto(x+6*TAILLE*sin(vCount+rad(angle)),y+6*TAILLE*cos(vCount+rad(angle)));
	  	  lineto(x+3*TAILLE*sin(vCount+rad(angle)+0.3),y+3*TAILLE*cos(vCount+rad(angle)+0.3));
	  	}
      break;
   }

   case 6 :   // double canons
  	{
  		circle(x,y,4*TAILLE);

		/** canon gauche **/
		moveto(x-2.5*TAILLE,y+3.1*TAILLE);
  		lineto(x-2.5*TAILLE,y+5*TAILLE);
 		lineto(x-1.5*TAILLE,y+5*TAILLE);
	  	lineto(x-1.5*TAILLE,y+3.7*TAILLE);

  		/** canon droite **/
  		moveto(x+2.5*TAILLE,y+3.1*TAILLE);
 		lineto(x+2.5*TAILLE,y+5*TAILLE);
  		lineto(x+1.5*TAILLE,y+5*TAILLE);
		lineto(x+1.5*TAILLE,y+3.7*TAILLE);

     // setcolor(couleur-COLOR(angle,angle,angle));
      circle(x,y,3*TAILLE);
      break;
  	}

   case 7 :  // Tank
	{
      angle = angle/30;
  		moveto(x-6*TAILLE,y-6*TAILLE);
  		lineto(x-4.5*TAILLE,y-6*TAILLE);
  		lineto(x-4.5*TAILLE,y-4.5*TAILLE);
  		lineto(x+4.5*TAILLE,y-4.5*TAILLE);
  		lineto(x+4.5*TAILLE,y-6*TAILLE);
  		lineto(x+6*TAILLE,y-6*TAILLE);
  		lineto(x+6*TAILLE,y+4*TAILLE);
  		lineto(x+4.5*TAILLE,y+4*TAILLE);
  		lineto(x+4.5*TAILLE,y+2.5*TAILLE);
      lineto(x-4.5*TAILLE,y+2.5*TAILLE);
  		lineto(x-4.5*TAILLE,y+4*TAILLE);
  		lineto(x-6*TAILLE,y+4*TAILLE);
  		lineto(x-6*TAILLE,y-6*TAILLE);

  		// canons
 		moveto(x-6*TAILLE+5.2*TAILLE,y+2.5*TAILLE);
  		if (angle%2==0)
  		{
				lineto(x-6*TAILLE+5.2*TAILLE,y+4.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+4.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+2.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+6*TAILLE);
  				lineto(x-6*TAILLE+6.8*TAILLE,y+6*TAILLE);
      		lineto(x-6*TAILLE+6.8*TAILLE,y+2.5*TAILLE);
  		}
  		else
  		{
  				lineto(x-6*TAILLE+5.2*TAILLE,y+6*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+6*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+2.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+4.5*TAILLE);
  				lineto(x-6*TAILLE+6.8*TAILLE,y+4.5*TAILLE);
      		lineto(x-6*TAILLE+6.8*TAILLE,y+2.5*TAILLE);
  		}

   break;
   }

   case 20 :  // BOSS 1
   {
      moveto(x,y+4*TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y+TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y);
  		lineto(x-3.5*TAILLE*1.5,y);
  		ellipse(x-4.5*TAILLE*1.5,y,180,360,TAILLE*1.5,TAILLE*1.5);
  		moveto(x-5.5*TAILLE*1.5,y);
  		lineto(x-7.5*TAILLE*1.5,y);
  		lineto(x-7.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x-6*TAILLE*1.5,y-1.5*TAILLE*1.5);
      lineto(x-6*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-3*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-3*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-0.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-0.5*TAILLE*1.5,y-4.5*TAILLE*1.5);
  		lineto(x+0.5*TAILLE*1.5,y-4.5*TAILLE*1.5);

  		lineto(x+0.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+1.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+1.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+3*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+3*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+6*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+6*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+7.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+7.5*TAILLE*1.5,y);
  		lineto(x+5.5*TAILLE*1.5,y);
  		ellipse(x+4.5*TAILLE*1.5,y,180,360,TAILLE*1.5,TAILLE*1.5);
 		moveto(x+3.5*TAILLE*1.5,y);
  		lineto(x+1.5*TAILLE*1.5,y);
  		lineto(x+1.5*TAILLE*1.5,y+TAILLE*1.5);
  		lineto(x,y+4*TAILLE*1.5);
   	break;
   }

  case 21 :     // K2000
  {
  		moveto(x,y+7*TAILLE);
  		lineto(x-2*TAILLE,y+2*TAILLE);
  		lineto(x-3*TAILLE,y+4*TAILLE);
  		lineto(x-4*TAILLE,y+2*TAILLE);
  		lineto(x-5*TAILLE,y+4*TAILLE);
  		lineto(x-6*TAILLE,y+2*TAILLE);
  		lineto(x-8*TAILLE,y+7*TAILLE);
  		lineto(x-10.1*TAILLE,y+1.9*TAILLE);
  		ellipse(x-10*TAILLE,y-TAILLE,90,270,3*TAILLE,3*TAILLE);
  		moveto(x-10*TAILLE,y-4*TAILLE);
  		lineto(x-6*TAILLE,y-4*TAILLE);
  		lineto(x-7*TAILLE,y-6*TAILLE);
  		lineto(x-4*TAILLE,y-6*TAILLE);
  		lineto(x-5*TAILLE,y-4*TAILLE);
  		lineto(x+5*TAILLE,y-4*TAILLE);
  		lineto(x+4*TAILLE,y-6*TAILLE);
  		lineto(x+7*TAILLE,y-6*TAILLE);
  		lineto(x+6*TAILLE,y-4*TAILLE);
  		lineto(x+10*TAILLE,y-4*TAILLE);
  		ellipse(x+10*TAILLE,y-TAILLE,270,90,3*TAILLE,3*TAILLE);
  		moveto(x+10*TAILLE,y+2*TAILLE);
  		lineto(x+10*TAILLE,y+2*TAILLE);
  		lineto(x+8*TAILLE,y+7*TAILLE);
      lineto(x+6*TAILLE,y+2*TAILLE);
  		lineto(x+5*TAILLE,y+4*TAILLE);
  		lineto(x+4*TAILLE,y+2*TAILLE);
  		lineto(x+3*TAILLE,y+4*TAILLE);
  		lineto(x+2*TAILLE,y+2*TAILLE);
  		lineto(x,y+7*TAILLE);

  		/** K2000 **/
      angle = old_angle/10;
      angle = angle%14;
  		for(int vCount = 0; vCount < 14; vCount++)
  		{
    		rectangle(x-10.5*TAILLE+1.5*TAILLE*vCount,y-2*TAILLE,x-9*TAILLE+1.5*TAILLE*vCount,y-0.5*TAILLE);
    		if(vCount == angle)
         {
      		setfillstyle(SOLID_FILL,couleur);
      		bar(x-10.5*TAILLE+1.5*TAILLE*vCount,y-2*TAILLE,x-9*TAILLE+1.5*TAILLE*vCount,y-0.5*TAILLE);
      		setfillstyle(SOLID_FILL,BLACK);
      	}
  		}

      break;
   }

   case 22 : //BOSS 3
   {
  		int RX = 10*TAILLE, RY = 6*TAILLE;
      float angle2 = rad(old_angle*3);
  		setfillstyle(SOLID_FILL,couleur);
  		for(float vAngle = 6.367; vAngle < 12.47; vAngle+=0.01)
    		putpixel(x+sin(vAngle)*RX,y+cos(vAngle)*RY,couleur);

  		fillellipse(x+sin(angle2)*RX,y+cos(angle2)*RY,0.5*TAILLE,0.5*TAILLE);

  		for(float vAngle = 7.33; vAngle < 11.51; vAngle+=0.05)
    		putpixel(x+sin(vAngle)*TAILLE,y+cos(vAngle)*TAILLE+5.5*TAILLE,couleur);

  		setlinestyle(SOLID_LINE,1,3);
  		moveto(x-4.5*TAILLE,y);
  		lineto(x-4.5*TAILLE,y+2*TAILLE);
  		lineto(x-5.5*TAILLE,y+2*TAILLE);
  		lineto(x-5.5*TAILLE,y);

  		moveto(x+4.5*TAILLE,y);
  		lineto(x+4.5*TAILLE,y+2*TAILLE);
  		lineto(x+5.5*TAILLE,y+2*TAILLE);
  		lineto(x+5.5*TAILLE,y);
  		setlinestyle(SOLID_LINE,1,1);

      break;
   }
	}
}

void Ennemi::Effacer(int old_angle)
{
  setcolor(BLACK);
  int angle;
  angle = old_angle-1;

  switch(type)
  {
   case 1 :     // EFFACAGE "Y"
   {
     	moveto(x,y+2.5*TAILLE);
  		lineto(x-0.5*TAILLE,y+2.5*TAILLE);
  		lineto(x-0.5*TAILLE,y-0.5*TAILLE);
  		lineto(x-2*TAILLE,y-2*TAILLE);
  		lineto(x-1.5*TAILLE,y-5*TAILLE+2.5*TAILLE);
  		lineto(x,y-TAILLE);
  		lineto(x+1.5*TAILLE,y-2.5*TAILLE);
 		lineto(x+2*TAILLE,y-2*TAILLE);
  		lineto(x+0.5*TAILLE,y-0.5*TAILLE);
  		lineto(x+0.5*TAILLE,y+2.5*TAILLE);
  		lineto(x,y+2.5*TAILLE);

      break;
   }

   case 2 :     // EFFACAGE Triangle
   {
  	  	ellipse(x,y-2.5*TAILLE,180,360,5*TAILLE,1.3*TAILLE);
	  	moveto(x-5*TAILLE,y-2.5*TAILLE);
	  	lineto(x,y+2*TAILLE);
	  	lineto(x+5*TAILLE,y-2.5*TAILLE);
      break;
   }

   case 3 :     // EFFACAGE pentagramme
   {
  		circle(x,y,6*TAILLE/3);
  		moveto(x+sin(rad(angle))*6*TAILLE/3,y-cos(rad(angle))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+144))*6*TAILLE/3,y-cos(rad(angle+144))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+288))*6*TAILLE/3,y-cos(rad(angle+288))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+72))*6*TAILLE/3,y-cos(rad(angle+72))*6*TAILLE/3);
  		lineto(x+sin(rad(angle+216))*6*TAILLE/3,y-cos(rad(angle+216))*6*TAILLE/3);
  		lineto(x+sin(rad(angle))*6*TAILLE/3,y-cos(rad(angle))*6*TAILLE/3);
   	break;
   }

   case 4 :     // EFFACAGE hache
   {
  		ellipse(x,y-2*TAILLE,180,360,4*TAILLE,4*TAILLE);
  		ellipse(x-2*TAILLE,y-2*TAILLE,180,360,2*TAILLE,2*TAILLE);
  		ellipse(x+2*TAILLE,y-2*TAILLE,180,360,2*TAILLE,2*TAILLE);
      break;
   }

   case 5 :   // EFFACAGE Soleil
   {
	  	circle(x,y,3*TAILLE);
	  	for(float vCount = 0; vCount < 6.24; vCount+=6.28/3)
	  	{
	  	  moveto(x+3*TAILLE*sin(vCount+rad(angle)-0.3),y+3*TAILLE*cos(vCount+rad(angle)-0.3));
	  	  lineto(x+6*TAILLE*sin(vCount+rad(angle)),y+6*TAILLE*cos(vCount+rad(angle)));
	  	  lineto(x+3*TAILLE*sin(vCount+rad(angle)+0.3),y+3*TAILLE*cos(vCount+rad(angle)+0.3));
	  	}
      break;
   }

   case 6 :   // EFFACAGE Double canons
  	{
      angle = angle/20;
      setfillstyle(SOLID_FILL,BLACK);
  		fillellipse(x,y,4*TAILLE,4*TAILLE);
		/** canon gauche **/
		moveto(x-2.5*TAILLE,y+3.1*TAILLE);
  		lineto(x-2.5*TAILLE,y+5*TAILLE);
 		lineto(x-1.5*TAILLE,y+5*TAILLE);
	  	lineto(x-1.5*TAILLE,y+3.7*TAILLE);

  		/** canon droite **/
  		moveto(x+2.5*TAILLE,y+3.1*TAILLE);
 		lineto(x+2.5*TAILLE,y+5*TAILLE);
  		lineto(x+1.5*TAILLE,y+5*TAILLE);
		lineto(x+1.5*TAILLE,y+3.7*TAILLE);
      break;
  	}

   case 7 :  // EFFACAGE Tank
	{
      angle = angle/30;
  		moveto(x-6*TAILLE,y-6*TAILLE);
  		lineto(x-4.5*TAILLE,y-6*TAILLE);
  		lineto(x-4.5*TAILLE,y-4.5*TAILLE);
  		lineto(x+4.5*TAILLE,y-4.5*TAILLE);
  		lineto(x+4.5*TAILLE,y-6*TAILLE);
  		lineto(x+6*TAILLE,y-6*TAILLE);
  		lineto(x+6*TAILLE,y+4*TAILLE);
  		lineto(x+4.5*TAILLE,y+4*TAILLE);
  		lineto(x+4.5*TAILLE,y+2.5*TAILLE);
      lineto(x-4.5*TAILLE,y+2.5*TAILLE);
  		lineto(x-4.5*TAILLE,y+4*TAILLE);
  		lineto(x-6*TAILLE,y+4*TAILLE);
  		lineto(x-6*TAILLE,y-6*TAILLE);

  		// canons
 		moveto(x-6*TAILLE+5.2*TAILLE,y+2.5*TAILLE);
  		if (angle%2==0)
  		{
				lineto(x-6*TAILLE+5.2*TAILLE,y+4.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+4.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+2.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+6*TAILLE);
  				lineto(x-6*TAILLE+6.8*TAILLE,y+6*TAILLE);
      		lineto(x-6*TAILLE+6.8*TAILLE,y+2.5*TAILLE);
  		}
  		else
  		{
  				lineto(x-6*TAILLE+5.2*TAILLE,y+6*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+6*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+2.5*TAILLE);
  				lineto(x-6*TAILLE+6*TAILLE,y+4.5*TAILLE);
  				lineto(x-6*TAILLE+6.8*TAILLE,y+4.5*TAILLE);
      		lineto(x-6*TAILLE+6.8*TAILLE,y+2.5*TAILLE);
  		}
   break;
   }

   case 20 :     // EFFACAGE BOSS 1
   {
      moveto(x,y+4*TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y+TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y);
  		lineto(x-3.5*TAILLE*1.5,y);
  		ellipse(x-4.5*TAILLE*1.5,y,180,360,TAILLE*1.5,TAILLE*1.5);
  		moveto(x-5.5*TAILLE*1.5,y);
  		lineto(x-7.5*TAILLE*1.5,y);
  		lineto(x-7.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x-6*TAILLE*1.5,y-1.5*TAILLE*1.5);
      lineto(x-6*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-3*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-3*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x-1.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-0.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x-0.5*TAILLE*1.5,y-4.5*TAILLE*1.5);
  		lineto(x+0.5*TAILLE*1.5,y-4.5*TAILLE*1.5);

  		lineto(x+0.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+1.5*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+1.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+3*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+3*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+6*TAILLE*1.5,y-3*TAILLE*1.5);
  		lineto(x+6*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+7.5*TAILLE*1.5,y-1.5*TAILLE*1.5);
  		lineto(x+7.5*TAILLE*1.5,y);
  		lineto(x+5.5*TAILLE*1.5,y);
  		ellipse(x+4.5*TAILLE*1.5,y,180,360,TAILLE*1.5,TAILLE*1.5);
 		moveto(x+3.5*TAILLE*1.5,y);
  		lineto(x+1.5*TAILLE*1.5,y);
  		lineto(x+1.5*TAILLE*1.5,y+TAILLE*1.5);
  		lineto(x,y+4*TAILLE*1.5);
   	break;
   }


	case 21 :      // EFFACAGE K2000
   {
  		moveto(x,y+7*TAILLE);
  		lineto(x-2*TAILLE,y+2*TAILLE);
  		lineto(x-3*TAILLE,y+4*TAILLE);
  		lineto(x-4*TAILLE,y+2*TAILLE);
  		lineto(x-5*TAILLE,y+4*TAILLE);
  		lineto(x-6*TAILLE,y+2*TAILLE);
  		lineto(x-8*TAILLE,y+7*TAILLE);
  		lineto(x-10.1*TAILLE,y+1.9*TAILLE);
  		ellipse(x-10*TAILLE,y-TAILLE,90,270,3*TAILLE,3*TAILLE);
  		moveto(x-10*TAILLE,y-4*TAILLE);
  		lineto(x-6*TAILLE,y-4*TAILLE);
  		lineto(x-7*TAILLE,y-6*TAILLE);
  		lineto(x-4*TAILLE,y-6*TAILLE);
  		lineto(x-5*TAILLE,y-4*TAILLE);
  		lineto(x+5*TAILLE,y-4*TAILLE);
  		lineto(x+4*TAILLE,y-6*TAILLE);
  		lineto(x+7*TAILLE,y-6*TAILLE);
  		lineto(x+6*TAILLE,y-4*TAILLE);
  		lineto(x+10*TAILLE,y-4*TAILLE);
  		ellipse(x+10*TAILLE,y-TAILLE,270,90,3*TAILLE,3*TAILLE);
  		moveto(x+10*TAILLE,y+2*TAILLE);
  		lineto(x+10*TAILLE,y+2*TAILLE);
  		lineto(x+8*TAILLE,y+7*TAILLE);
      lineto(x+6*TAILLE,y+2*TAILLE);
  		lineto(x+5*TAILLE,y+4*TAILLE);
  		lineto(x+4*TAILLE,y+2*TAILLE);
  		lineto(x+3*TAILLE,y+4*TAILLE);
  		lineto(x+2*TAILLE,y+2*TAILLE);
  		lineto(x,y+7*TAILLE);

  		/** K2000 **/
  		setfillstyle(SOLID_FILL,BLACK);
      bar(x-11*TAILLE,y-2*TAILLE,x+11*TAILLE,y-0.2*TAILLE);
      break;
   }

   case 22 : // EFFACAGE BOSS 3
   {
  		int RX = 10*TAILLE, RY = 6*TAILLE;

  		setfillstyle(SOLID_FILL,BLACK);
  		for(float vAngle = 6.367; vAngle < 12.47; vAngle+=0.01)
    		putpixel(x+sin(vAngle)*RX,y+cos(vAngle)*RY,BLACK);

      float angle2 = rad((old_angle-1)*3);
  	  	fillellipse(x+sin(angle2)*RX,y+cos(angle2)*RY,0.5*TAILLE,0.5*TAILLE);

  		for(float vAngle = 7.33; vAngle < 11.51; vAngle+=0.01)
    		putpixel(x+sin(vAngle)*TAILLE,y+cos(vAngle)*TAILLE+5.5*TAILLE,BLACK);

  		setlinestyle(SOLID_LINE,1,3);
  		moveto(x-4.5*TAILLE,y);
  		lineto(x-4.5*TAILLE,y+2*TAILLE);
  		lineto(x-5.5*TAILLE,y+2*TAILLE);
  		lineto(x-5.5*TAILLE,y);

  		moveto(x+4.5*TAILLE,y);
  		lineto(x+4.5*TAILLE,y+2*TAILLE);
  		lineto(x+5.5*TAILLE,y+2*TAILLE);
  		lineto(x+5.5*TAILLE,y);
  		setlinestyle(SOLID_LINE,1,1);

      break;
   }

   }

}

void Ennemi::Tir()
{

  	  vNbTir++;
	  MissileEnnemi *courant;
	  courant = (MissileEnnemi*) malloc(sizeof(MissileEnnemi));
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
	  courant->Init(x,y,this);
}

void Ennemi::DetruireMissile(int vNum)
{
		MissileEnnemi *detruit;
      MissileEnnemi *temp;

		detruit = premier;
      if (vNum == 1)
      {
         if (vNbTir > 1)
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
         else
         {
            detruit->Effacer();
         	delete detruit;
            dernier = premier = NULL;
         }
      }
      else if (vNum < vNbTir)
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
      else if (vNum == vNbTir)
	   {
         dernier->Effacer();
         delete dernier;
         while (detruit->numero < vNum)
      		detruit = detruit->suivant;
         dernier = detruit;
      }
      vNbTir--;
}


