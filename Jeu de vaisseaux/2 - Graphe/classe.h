class Point
{
	private:
   	int vX, vY, tDonnees[4]; // 0 : Heure, 1 : Minute, 2 : Secondes, 3 : Temp�rature

   public:
   	/* Constructeurs */
   	Point();

      /* M�thodes d'acc�s */
      int GetX();
      int GetY();
      int GetDonnees(int);
      void SetDonnees(int,int);

      /* Autres */
      void Init(int,int);
      void Dessiner(TDC&, TColor);
};

class TMaFenetre : public TWindow
{
	private:
   	bool vRelier, vAfficherPoints;
   	int vMax, vNbPersonne;
      char tFichier[80],    // Lecture du fichier
		     vFileName[80];   // Nom du fichier � lire

		ifstream vDataFile;
      Point tTab[1000];
      TColor vCouleur;

   public:
   	/* Constructeurs */
   	TMaFenetre(char* title);

   	/* Menus */
		void CmFichierQuitter();
		void CmFichierActualiser();
      void CmFichierOuvrir();
      void CmOptionsPoints();
      void CmOptionsRelier();
      void CmOptionsCouleur();

      /* Ev�nements */
      void Paint(TDC&, bool, TRect&);
      bool SelectFichier(char*);
      void EvSize(uint sizeType, TSize& size);  // Redimensionnement

		/* Tables de r�ponses */
   	DECLARE_RESPONSE_TABLE(TMaFenetre);

      /* Autre */
      void LireFichier();
};

class TMonAppli : public TApplication
{
	public:
   	TMonAppli();
      void InitMainWindow();
};
