void Vague::Init()
{
	char *p;
   sens = 1; vCompteurSens = num = nb_ennemi = 0;
   premier[0] = 20;

   FILE *f = fopen("vague.txt","r");
   for(int i = 0; i < 9; i++)
   {
	   for(int j = 0; j < 5; j++)
      {
   		for(int k = 0; k < 11; k++)
         {
         	fread(p,sizeof(char),1,f);
            tVague[i][j][k] = int(*p-97);
         }
        	fread(p,sizeof(char),1,f);  // Lit un Return à chaque ligne donc passe à la ligne suivante
      }
     	fread(p,sizeof(char),1,f);  // Lit un Return à chaque tableau donc passe au tableau suivant
   }
   fclose(f);
}

void Vague::Positionner(int vY)
{
   int ecartX = 0, ecartY = 0;
   int vCouleurMilieu = random(255);

   for(int vCount = 0; vCount < 5; vCount++)
	   for(int vCount2 = 0; vCount2 < 11; vCount2++)
      {
            int vSensEn;

            if(vCount % 2 == 0)
               vSensEn = -1;
            else
               vSensEn = 1;

            if(tVague[num][vCount][vCount2] != 0)
   	         nb_ennemi++;

	   	   formation[vCount2][vCount].Init(COLOR(30*vCount+105,vCouleurMilieu,250-15*vCount2),vSensEn,tVague[num][vCount][vCount2]);

     	      if(formation[vCount2][vCount].tailleX > ecartX && formation[vCount2][vCount].type < 20)
        	      ecartX = formation[vCount2][vCount].tailleX;

           	if(formation[vCount2][vCount].tailleY > ecartY && formation[vCount2][vCount].type < 20)
              	ecartY = formation[vCount2][vCount].tailleY;
      }

   int vMilieu = 400-10*ecartX;
   for(int vCount = 0; vCount < 5; vCount++)
	   for(int vCount2 = 0; vCount2 < 11; vCount2++)
      {
            formation[vCount2][vCount].Positionner(vCount2*2*ecartX+vMilieu, vCount*2*ecartY-vY);
      	   formation[vCount2][vCount].Afficher(0);
      }
   frequence = 1.9*(formation[0][0].x - formation[0][0].tailleX);
   vCompteurSens = frequence/2;
}

bool Vague::Amener(int angle)
{
   for(int vCount = 0; vCount < 11; vCount++)
	   for(int vCount2 = 0; vCount2 < 5; vCount2++)
      {
      	if(formation[vCount][vCount2].type == 100)
         {
            if(formation[vCount][vCount2].Exploser() == 0)
            	formation[vCount][vCount2].type = 0;
         }
	      else if(formation[vCount][vCount2].type != 0)
	      {
            formation[vCount][vCount2].Effacer(angle);
            formation[vCount][vCount2].Deplacer(1,0,1);
            formation[vCount][vCount2].Afficher(angle);
   	   }
      }
   if(formation[0][0].y-formation[0][0].tailleY > 50)
   {
      deltax = 1; deltay = 0;
      return(true);
   }
   else
      return(false);
}

bool Vague::Deplacer(int angle,VaisseauJoueur* vJ)
{
	bool vExpl = false;
   for(int vCount = 0; vCount < 11; vCount++)
	   for(int vCount2 = 0; vCount2 < 5; vCount2++)
      {
      	if(formation[vCount][vCount2].type == 100)
         {
            if (formation[vCount][vCount2].premier != NULL)
            {
                formation[vCount][vCount2].Exploser();
	   		 	 MissileEnnemi *courant=NULL;
			       MissileEnnemi *temp;
			       courant = formation[vCount][vCount2].premier;
			       int NbTirTemp = formation[vCount][vCount2].vNbTir;
			       for (int i = 1 ; i<=NbTirTemp ; i++)
			       {
			       	int test = formation[vCount][vCount2].vNbTir;
			         if (i < NbTirTemp)
				       	temp = courant->suivant;

			         courant->Effacer();
			       	courant->Deplacer(&formation[vCount][vCount2],vJ);
			         if (formation[vCount][vCount2].vNbTir == test)
			         {
			         	test = formation[vCount][vCount2].vNbTir;
			         	courant->Afficher();
			         }
			         courant = temp;

			       }
            }
            else if (formation[vCount][vCount2].Exploser() <= 0)
            {
            	formation[vCount][vCount2].type = 0;
            }
            vExpl = true;
   	   }

      	else if(formation[vCount][vCount2].type != 0)
	      {
            formation[vCount][vCount2].Effacer(angle);
            formation[vCount][vCount2].Deplacer(sens,deltax,deltay);
            formation[vCount][vCount2].Afficher(angle);
            if (random(10000)<formation[vCount][vCount2].freq_tir)
	            formation[vCount][vCount2].Tir();

            if(formation[vCount][vCount2].vNbTir > 0)
			 	{
	   		 	 MissileEnnemi *courant=NULL;
			       MissileEnnemi *temp;
			       courant = formation[vCount][vCount2].premier;
			       int NbTirTemp = formation[vCount][vCount2].vNbTir;
			       for (int i = 1 ; i<=NbTirTemp ; i++)
			       {
			       	int test = formation[vCount][vCount2].vNbTir;
			         if (i < NbTirTemp)
				       	temp = courant->suivant;

			         courant->Effacer();
			       	courant->Deplacer(&formation[vCount][vCount2],vJ);
			         if (formation[vCount][vCount2].vNbTir == test)
			         {
			         	test = formation[vCount][vCount2].vNbTir;
			         	courant->Afficher();
			         }
			         courant = temp;
			       }
			    }

            vExpl = true;
   	   }

      }
      vCompteurSens++;
      if(vCompteurSens % frequence == 0)
      {
        sens *= -1;
        vCompteurSens = 0;
      }
      return(vExpl);
}
