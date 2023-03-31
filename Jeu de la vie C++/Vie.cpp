#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream.h>

struct Tableau
{
    bool tTab[100][100];
}sMain;

void AffichageTableau(int*, int*, char*);
void Initialisation(int*, int*, int*, char*, char*, char*);
int NombreVoisins(int, int, int, int, char);
int Survivants(int*, int*);

void main(void)
{
     int vLargeur, vLongueur,
         vNbSimu,
         vCount, vCount2, vNumEtape, vCnt, vCnt2,
         vNbVois;
     char vAff0, vUser, vSphere, vSuivante;
     Tableau sTemp;

     Initialisation(&vLargeur, &vLongueur, &vNbSimu, &vAff0, &vSphere, &vSuivante); // Menu et initialisation
     vNumEtape = 0;
     do
     {
         for(vCount = 0; vCount < vLargeur; vCount++)
         {
             for(vCount2 = 0; vCount2 < vLongueur; vCount2++)
             {
                 /*************************** Test de la vie ***************************/
                 vNbVois = NombreVoisins(vCount,vCount2, vLongueur, vLargeur, vSphere);
                 if(sMain.tTab[vCount][vCount2] == 0 && vNbVois == 3) // Naissance
                     sTemp.tTab[vCount][vCount2] = 1;
                 else if(sMain.tTab[vCount][vCount2] == 1 && (vNbVois == 2 || vNbVois == 3)) // Survie
                     sTemp.tTab[vCount][vCount2] = 1;
                 else if(sMain.tTab[vCount][vCount2] == 1 && vNbVois >= 4) // Etouffement
                     sTemp.tTab[vCount][vCount2] = 0;
                 else if(sMain.tTab[vCount][vCount2] == 1 && (vNbVois == 0 || vNbVois == 1)) // Solitude
                     sTemp.tTab[vCount][vCount2] = 0;
                 else
                     sTemp.tTab[vCount][vCount2] = sMain.tTab[vCount][vCount2];
                 /**********************************************************************/
             }
         }

         sMain = sTemp;
         if(Survivants(&vLargeur, &vLongueur) == 0)
         {
             fflush(stdin);
             getchar();
             cout << "\nEtape n " << vNumEtape+2 << "\n";
             AffichageTableau(&vLargeur, &vLongueur, &vAff0);
             cout << "\n\nVotre systeme est mort !";
             vNumEtape = 2;
             vNbSimu = 1;
         }
         else
         {
             if(vSuivante == 'o')
             {
                 cout << "\n\n\nPressez Enter pour passer a l'etape suivante (q pour quitter) : ";
                 fflush(stdin);
                 vUser = getchar();
                 if(vUser == 'q')
                 {
                     vNumEtape = 2;
                     vNbSimu = 1;
                 }
                 else
                 {
                     cout << "Etape n " << vNumEtape+2 << "\n";
                     cout << "\n";
                     AffichageTableau(&vLargeur, &vLongueur, &vAff0);

                 }
             }
             else
             {
                 cout << "\nEtape n " << vNumEtape+2 << "\n";
                 AffichageTableau(&vLargeur, &vLongueur, &vAff0);
             }
         }
         vNumEtape++;
     }
     while(vNumEtape < vNbSimu || vNbSimu == 0);

     if(vUser != 'q')
     {
         cout << "\n\nPressez une touche pour quitter";
         fflush(stdin);
         getch();
     }
}
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

int NombreVoisins(int vX, int vY, int vXMax, int vYMax, char vSphere)
{
    int vNbVoisins = 0, vTestX, vTestY, vCnt, vCnt2;

    for(vCnt = vX-1; vCnt <= vX+1; vCnt++)
    {
        for(vCnt2 = vY-1; vCnt2 <= vY+1; vCnt2++)
        {
            if(vSphere == 'o') // Si le tableau est considéré comme une sphère
            {
                if(vCnt < 0)
                    vTestX = vYMax-1;
                else if(vCnt == vYMax)
                    vTestX = 0;
                else
                    vTestX = vCnt;

                if(vCnt2 < 0)
                    vTestY = vXMax-1;
                else if(vCnt2 == vXMax)
                    vTestY = 0;
                else
                    vTestY = vCnt2;
            }
            else
            {
                vTestX = vCnt;
                vTestY = vCnt2;
            }

            if(sMain.tTab[vTestX][vTestY] == 1)
                if(vTestX != vX || vTestY != vY)
                    vNbVoisins++;
        }
    }
    //cout << "\nvX: " << vX << ", vY: " << vY << ", Voisins: " << vNbVoisins;
    return(vNbVoisins);
}

void AffichageTableau(int *vLargeur, int *vLongueur, char *vAff0)
{
     int vCount, vCount2;

     for(vCount = 0; vCount < *vLargeur; vCount++)
     {
         for(vCount2 = 0; vCount2 < *vLongueur; vCount2++)
             if(*vAff0 == 'o')
                 cout << sMain.tTab[vCount][vCount2];// << " ";
             else
                 if(sMain.tTab[vCount][vCount2] == 0)
                     cout << " ";
                 else
                     cout << "1";
         cout << "\n";
     }
}

int Survivants(int *vLargeur, int *vLongueur)
{
    int vCount, vCount2, vSurvivants = 0;

     for(vCount = 0; vCount < *vLargeur; vCount++)
         for(vCount2 = 0; vCount2 < *vLongueur; vCount2++)
             if(sMain.tTab[vCount][vCount2] == 1)
                 vSurvivants++;
     return(vSurvivants);
}
