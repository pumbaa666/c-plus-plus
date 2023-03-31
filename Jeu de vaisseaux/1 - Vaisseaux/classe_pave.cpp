Pave::Pave()
{
	x = 912;
   y = 550;
   feu = true;
}

void Pave::Afficher(int vNum)
{
	int vCentre, vDec = 0;

   if(vNum != 32)
		for(float i = rad(180); i <= rad(495); i+=rad(45), vDec++)
   	{
   		if(vDec % 2 == 0)
      		vCentre = 60;
	      else
   	   	vCentre = 100;

	      if((vDec == 0 && vNum == 56) || (vDec == 1 && vNum == 55) || (vDec == 2 && vNum == 52) ||
   	   	(vDec == 3 && vNum == 49) || (vDec == 4 && vNum == 50) || (vDec == 5 && vNum == 51) ||
      	   (vDec == 6 && vNum == 54) || (vDec == 7 && vNum == 57))

        		setcolor(RED);
	      else
   	   	setcolor(WHITE);
			moveto(x+sin(i)*20 + sin(i)*vCentre,y+cos(i)*20 + cos(i)*vCentre);
	   	lineto(x+sin(i+rad(110))*30 + sin(i)*vCentre,y+cos(i+rad(110))*30 + cos(i)*vCentre);
		   lineto(x+sin(i+rad(120))*20 + sin(i)*vCentre,y+cos(i+rad(120))*20 + cos(i)*vCentre);
     		lineto(x+sin(i+rad(170))*40 + sin(i)*vCentre,y+cos(i+rad(170))*40 + cos(i)*vCentre);

	     	lineto(x+sin(i+rad(-170))*40 + sin(i)*vCentre,y+cos(i+rad(-170))*40 + cos(i)*vCentre);
		   lineto(x+sin(i+rad(-120))*20 + sin(i)*vCentre,y+cos(i+rad(-120))*20 + cos(i)*vCentre);
   		lineto(x+sin(i+rad(-110))*30 + sin(i)*vCentre,y+cos(i+rad(-110))*30 + cos(i)*vCentre);
			lineto(x+sin(i)*20 + sin(i)*vCentre,y+cos(i)*20 + cos(i)*vCentre);

//	      setfillstyle(SOLID_FILL,RED);
//   	   floodfill(x + sin(i)*vCentre, y + cos(i)*vCentre, WHITE);
	   }

   if(feu == false)
   {
		if(vNum == 32)
	   {
   		feu = true;
      	for(int i=824; i <= 1024; i++)
	         for(int j=0; j < 384; j+=7)
   	         putpixel(x-100+i-824,y+100+(384-j)/7,COLOR(255*i/1024,255*j/384,0));
	   }
   }
   else if(vNum != 32)
   {
   	setfillstyle(SOLID_FILL,BLACK);
	   bar(x-100,y+100,x+100,y+155);
	 	setcolor(WHITE);
      rectangle(x-100,y+100,x+100,y+154);
      settextjustify(1,1);
      outtextxy(x,y+135,"FEU");
      feu = false;
   }
}
