TMaFenetre::TMaFenetre(char* title) : TWindow(NULL, title, NULL)
{
	strcpy(tFichier, "");
	strcpy(vFileName, "");
	vNbPersonne = 0;
   vMax = 0;
   vAfficherPoints = true;
   vRelier = false;
   vCouleur = RGB(0,0,0);
}

void TMaFenetre::Paint(TDC& dc, bool , TRect&)
{
	if(vNbPersonne != 0)
   {
		TPen StyloEchelle(RGB(0,0,0),1,0);
	   dc.SelectObject(StyloEchelle);

   	/* Cadre */
      int vAxeYX = 50;
      int vAxeYY1 = 20;
      int vAxeYY2 = Parent->Attr.H-40;

      int vAxeXX1 = 0;
      int vAxeXX2 = Parent->Attr.W-20;
      int vAxeXY = Parent->Attr.H-110;

  	   dc.MoveTo(vAxeXX1,vAxeXY);
   	dc.LineTo(vAxeXX2,vAxeXY);
	   dc.MoveTo(vAxeYX,vAxeYY1);
   	dc.LineTo(vAxeYX,vAxeYY2);

	   /* Echelle */
   	int vScaleX = Parent->Attr.W / (vNbPersonne+2);
      int vScaleY;

      /* Ajuste la taille si l'échelle est trop petite */
      if(vMax < 7)
		   vScaleY = Parent->Attr.H;
      else
		   vScaleY = Parent->Attr.H / (vMax/7);

      /* Axe des X */
      dc.TextOut(vAxeYX,10,"Température [K]");
      int vPas = vNbPersonne/12;
      if(vPas == 0)
      	vPas = 1;
      char tHeure[9] = "";
      char tText[3] = "";
      void AjoutZero(int, char[]);
   	for(int i = 1; i < vNbPersonne; i += vPas) // Commence à 1 pour ne pas écrire la 1ère valeur qui chevaucherai les axes
	   {
      	dc.MoveTo(vAxeYX+i*vScaleX,vAxeXY-10);
      	dc.LineTo(vAxeYX+i*vScaleX,vAxeXY+10);

         strcpy(tHeure, "");
         for(int compteur = 0; compteur < 3; compteur++)
         {
	         AjoutZero(tTab[i].GetDonnees(compteur),tText);
   	      strcat(tHeure,tText);
      	   strcat(tHeure,":");
         }
         tHeure[8] = '\0';  // Enlève les : de trop à la fin de la chaine

         dc.TextOut(vAxeYX+i*vScaleX-25,vAxeXY+10+(15*(i%3)),tHeure);
      }

      /* Axe des Y */
      dc.TextOut(vAxeXX2-50,vAxeXY-25,"Heure");
      vPas = vMax/100;
      if(vPas == 0)
      	vPas = 1;
   	for(int i = 1; i < (vMax/8); i+=vPas)
	   {
      	dc.MoveTo(vAxeYX-10,vAxeXY-i*vScaleY);
      	dc.LineTo(vAxeYX+10,vAxeXY-i*vScaleY);
         itoa(i*10,tText,10);
         dc.TextOut(vAxeYX-45,vAxeXY-i*vScaleY-5,tText);
      }

      /* Dessin du graphe lui même */
     	TPen Stylo(vCouleur,1,0);
      dc.SelectObject(Stylo);
      TBrush Pinceau(vCouleur);
      dc.SelectObject(Pinceau);

     	if(vRelier == true)
      {
         dc.MoveTo(vAxeYX,vAxeXY-tTab[0].GetDonnees(3)*vScaleY/10);
	    	for(int i = 0; i < vNbPersonne; i++)
				dc.LineTo(vAxeYX+i*vScaleX,vAxeXY-tTab[i].GetDonnees(3)*vScaleY/10);
      }
      if(vAfficherPoints == true)
	    	for(int i = 0; i < vNbPersonne; i++)
				dc.Ellipse(vAxeYX+i*vScaleX-3,vAxeXY-tTab[i].GetDonnees(3)*vScaleY/10-3,vAxeYX+i*vScaleX+3,vAxeXY-tTab[i].GetDonnees(3)*vScaleY/10+3);

      /* Etats */
      char tEtats[80] = "Afficher points : ";
      if(vAfficherPoints == true)
	      strcat(tEtats,"On");
      else
	      strcat(tEtats,"Off");
      dc.TextOut(vAxeXX2-150,10,tEtats);
      strcpy(tEtats,"Relier points : ");
      if(vRelier == true)
	      strcat(tEtats,"On");
      else
	      strcat(tEtats,"Off");
      dc.TextOut(vAxeXX2-150,30,tEtats);
   }
}

bool TMaFenetre::SelectFichier(char *fileName)
{
    OPENFILENAME OpenFile;

    memset(&OpenFile, 0, sizeof(OPENFILENAME));
    strcpy(fileName,"");

    OpenFile.lStructSize = sizeof(OPENFILENAME);
    OpenFile.hwndOwner = GetActiveWindow();
    OpenFile.lpstrFile = (LPSTR)fileName;
    OpenFile.nMaxFile = 255;
    OpenFile.lpstrFilter = "Text Files(*.txt;*.doc)\0*.txt;*.doc\0All Files (*.*)\0*.*\0";
    OpenFile.nFilterIndex = 1;
    OpenFile.lpstrTitle = "Ouvrir";
    if(strcmp(vFileName,"") != 0)
	    OpenFile.lpstrInitialDir = vFileName;
    else
	    OpenFile.lpstrInitialDir = "E:\\C++\\Projet\\2 - Graphe - c - épuré";

    if(GetOpenFileName(&OpenFile))
        return true;
    else
        return false;
}

void TMaFenetre::CmOptionsPoints()
{
   vAfficherPoints = !vAfficherPoints;
   Invalidate();
}

void TMaFenetre::CmOptionsRelier()
{
   vRelier = !vRelier;
   Invalidate();
}

void TMaFenetre::CmOptionsCouleur()
{
   static TColor custColors[16];
   TChooseColorDialog::TData choose;

   choose.Flags = CC_RGBINIT;
   choose.Color = vCouleur;
   choose.CustColors = custColors;

   if(TChooseColorDialog(this, choose).Execute() == IDOK)
		vCouleur = choose.Color;
   Invalidate();
}

void TMaFenetre::CmFichierActualiser()
{
	if(strcmp(tFichier,"") != 0)
   {
		strcpy(tFichier,"");
   	vDataFile.close();
	   vDataFile.open(vFileName, ios::in);
   	LireFichier();
   }
}

void TMaFenetre::CmFichierOuvrir()
{
   vDataFile.close();
   if(SelectFichier(vFileName) == true)
   {
	   vDataFile.open(vFileName, ios::in);
   	LireFichier();
   }
}

void TMaFenetre::LireFichier()
{
   int i = 0; // Compteur
   char vTemp[2]; // Variable temporaire qui stock un chiffre (heure, min...)
   char vBuffer[80];
   bool vQuitter = false;
   vNbPersonne = 0;
   vMax = 0;
   do
  	{
      vDataFile >> tFichier;  // Ecrit une ligne du fichier dans la mémoire
     	for(int z = 0; z < 2; z++)  // Vide vTemp (étonemment un strcpy(vTemp,"") ne suffit pas)
      	vTemp[z] = '\0';
      int j = 0;
      for(int i = 0; i < 4; i++)
      {
        	strcpy(vBuffer,"");
	      while(tFichier[j] != ':' && tFichier[j] != '\0' && tFichier[j] != '\n' && tFichier[j] != '@')
   	   {
         	vTemp[0] = tFichier[j];
         	strcat(vBuffer,vTemp);
         	j++;
	      }
	      if(tFichier[j] == '@')
         {
				vQuitter = true;
            break;
         }
         tTab[vNbPersonne].SetDonnees(i, atoi(vBuffer));  // Enregistres les données dans le tableau de points
         if(i == 3 && tTab[vNbPersonne].GetDonnees(3) > vMax)
         	vMax = tTab[vNbPersonne].GetDonnees(3);
         j++;
      }
      vNbPersonne++;
  }
  while(vQuitter == false);
  vNbPersonne--;
  Invalidate();
}

void TMaFenetre::CmFichierQuitter()
{
	exit(0);
}

void TMaFenetre::EvSize(uint sizeType, TSize& size)
{
	TWindow::EvSize(sizeType, size);
   Invalidate();
}

static void AjoutZero(int vNum, char tHeure[9])
{
   char tTemp[3];
   char tText[3];
   itoa(vNum,tText,10);
   if(strlen(tText) == 1)
   {
    	strcpy(tTemp,tText);
      strcpy(tText,"0");
      strcat(tText,tTemp);
   }
   else
   	strcpy(tHeure,tText);
}
