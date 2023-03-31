class MissileEnnemi;
class VaisseauJoueur;
class Vague;

class Missile
{
	private:
   	int x, y;

   public:
      int numero;
      Missile *suivant;
      void Init(int,int, VaisseauJoueur*);
      void Afficher();
      void Effacer();
      void Deplacer(VaisseauJoueur*,Vague*,int,bool*);
};

class VaisseauJoueur
{
  private:
    int couleur, dernier_tir;

  public:
    Missile *premier;
    Missile *dernier;
    int vNbTir,x, y, vie;
    int nbMissile;
    char vNom[15];

    VaisseauJoueur();
    void Init(int,int,int);
    void Afficher();
    void Effacer();
    void Deplacer(int,int);
    void Tir(int);
    void DetruireMissile(int);
};

class Etoiles
{
  public:
    int x, y, couleur, vitesse;

  public:
    void Afficher();
    void Effacer();
    void Deplacer(int);
    void Init(int,int,int,int);
};

class Particules
{
	private:
		int x, y, dx, dy, couleur;
   public:
   	void Init(int,int,int);
   	void Init(int,int,int,int);
   	void Augmenter(int,int);
      bool Augmenter();
};

class Ennemi
{
	private:
   	int couleur, deltaX, deltaY, temps_expl, sens;
      Particules tab_explose[20];

   public:
    	MissileEnnemi *premier;
    	MissileEnnemi *dernier;
      int vNbTir, freq_tir, x, y, tailleX, tailleY, type, vie;
      void Init(int,int,int);
      void Positionner(int,int);
      void Afficher(int);
      void Effacer(int);
      void Deplacer(int,int,int);
      int Exploser();
      void DetruireMissile(int);
      void Tir();
};

class Vague
{
	private:
   	int 	sens, vCompteurSens,
            frequence,
            deltay, deltax,
            type, premier[2];

   public:
   	int num, nb_ennemi;
      Ennemi formation[11][5];
   	void Init();
      void Positionner(int);
      bool Amener(int);
      bool Deplacer(int,VaisseauJoueur*);

      int tVague[15][5][11];
};

class Titre
{
  	private:
     	int y, largeur, hauteur, vOldMenu;
      float rapport;
      char *text;
      bool **tTab;

   public:
      void Init(char[],int);
      void Afficher(int,int);
      ~Titre();
};

class Pave
{
	   private:
      	int x, y;
         bool feu;

      public:
      	Pave();
      	void Afficher(int);
};

class MissileEnnemi
{
 	private:
   	int x,y;
      
   public:
   	int numero;
   	MissileEnnemi *suivant;
      void Init(int,int,Ennemi*);
      void Afficher();
      void Effacer();
      void Deplacer(Ennemi*,VaisseauJoueur*);

};
