void Initialisation(int *vLargeur, int *vLongueur, int *vNbSimu, char *vAff0, char *vSphere, char *vSuivante)
{
     int vCount, vCount2,
         vChoix, x, y,
         vTemp;

     cout << "Bienvenue dans le jeu de la vie";

     do
     {
         cout << "\n\nEntrez les dimensions du tableau [X Y] : ";
         cin >> *vLongueur;
         cin >> *vLargeur;
     }
     while(*vLargeur < 1 || *vLongueur < 1);
//     while(*vLargeur < 3 || *vLargeur > 79 || *vLongueur < 3 || *vLongueur > 79);

     for(vCount = 0; vCount < *vLargeur; vCount++)
         for(vCount2 = 0; vCount2 < *vLongueur; vCount2++)
             sMain.tTab[vCount][vCount2] = 0;

     do
     {
         cout << "\nChoisissez le nombre de tour a simuler (0 pour infini) : ";
         cin >> *vNbSimu;
     }
     while(*vNbSimu < 0);

     do
     {
         cout << "\nVoir le tableau comme une sphere ? [o/n] ? ";
         cin >> *vSphere;
     }
     while(*vSphere != 'n' && *vSphere != 'o');

     do
     {
         cout << "\nPresser Enter pour passer a l'etape suivante ? [o/n] ? ";
         cin >> *vSuivante;
     }
     while(*vSuivante != 'n' && *vSuivante != 'o');

     cout << "\n1 Pour generer un tableau aleatoire";
     cout << "\n2 Pour inserer les valeurs au clavier";
     cout << "\n3 Pour passer les valeurs par fichier";
     cout << "\n4 Pour utiliser les tableaux pre-enregistres";
     do
     {
         cout << "\n\nVotre choix : ";
         cin >> vChoix;
     }
     while(vChoix < 1 || vChoix > 4);

     if(vChoix == 1) // Aléatoire
     {
         srand(1);
         for(vCount = 0; vCount < *vLargeur; vCount++)
             for(vCount2 = 0; vCount2 < *vLongueur; vCount2++)
                 if(rand() % 10 < 3)
                     sMain.tTab[vCount][vCount2] = 1;
     }
     else if(vChoix == 2) // Clavier
     {
         cout << "\n\nEntrez les coordonnees X et Y (-1 -1 pour quitter)\n";
         vCount = 1;
         do
         {
             cout << vCount << " [X Y] : ";
             cin >> x;
             cin >> y;
             if(x < *vLargeur && y < *vLongueur && x >= 0 && y >= 0)
             {
                 sMain.tTab[x][y] = 1;
                 vCount++;
             }
             else if(x != -1)
                 cout << "\nErreur!\n";
         }
         while(x != -1);
     }
     else if(vChoix == 3) // Fichier
     {
     /* Lire un fichier */
     }
     else if(vChoix == 4) // Tableaux pré-enregistrés
     {
         cout << "\n1 Bords\n";
         cout << "2 Coins\n";
         cout << "3 Neuf au centre\n";
         cout << "4 Une diagonale\n";
         cout << "5 Les deux diagonales\n";

         do
         {
             cout << "\n\nVotre choix : ";
             cin >> vChoix;
         }
         while(vChoix < 1 || vChoix > 5);

         if(vChoix == 1)
         {
             for(vCount = 0; vCount < *vLongueur; vCount++)
                 sMain.tTab[0][vCount] = sMain.tTab[*vLargeur-1][vCount] = 1;
             for(vCount = 0; vCount < *vLargeur; vCount++)
                 sMain.tTab[vCount][0] = sMain.tTab[vCount][*vLongueur-1] = 1;
         }
         else if(vChoix == 2)
         {
             sMain.tTab[0][0] = 1;
             sMain.tTab[0][*vLongueur-1] = 1;
             sMain.tTab[*vLargeur-1][0] = 1;
             sMain.tTab[*vLargeur-1][*vLongueur-1] = 1;
         }
         else if(vChoix == 3)
         {
             for(vCount = *vLargeur/2-1; vCount <= *vLargeur/2+1; vCount++)
                 for(vCount2 = *vLongueur/2-1; vCount2 <= *vLongueur/2+1; vCount2++)
                     sMain.tTab[vCount][vCount2] = 1;
         }
         else if(vChoix == 4)
         {
             for(vCount = 0; vCount <*vLargeur && vCount < *vLongueur;vCount++)
                 sMain.tTab[vCount][vCount] = 1;
         }
         else if(vChoix == 5)
         {
             if(*vLongueur < *vLargeur)
                 vTemp = *vLongueur;
             else
                 vTemp = *vLargeur;
             for(vCount = 0; vCount <*vLargeur && vCount < *vLongueur;vCount++)
             {
                 sMain.tTab[vCount][vCount] = 1;
                 sMain.tTab[vTemp-vCount-1][vCount] = 1;
             }
         }
     }

     do
     {
         cout << "\nAfficher les 0 [o/n] ? ";
         cin >> *vAff0;
     }
     while(*vAff0 != 'n' && *vAff0 != 'o');

     cout << "Etape n 1\n";
     AffichageTableau(vLargeur, vLongueur, vAff0);
}

