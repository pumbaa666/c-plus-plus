#ifndef IMAGES_H
#define IMAGES_H
#ifndef px

// * Définition d'un pixel. Codage RVBA.

typedef struct px
{
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    // à supprimer si image 24bits
    unsigned char alpha;
}pixel;
#endif

#ifndef image
/**
 * Définition d'une image (Dimensions et pixels)
 */
typedef struct image
{
    int width;
    int height;
    px * sprite;
}img;
#endif

class graphique
{
  	public:
   	graphique();
		~graphique();

	public:
   	// image
		image * loadBMP(char*);
		void dsp_sprite(image*,int x,int y, long transparentR=-1, long transparentG=-1, long transparentB=-1, int offsetR=0, int offsetG=0, int offsetB=0);
	  	void afficherImage(char *, int x, int y,long transparentR=-1, long transparentG=-1, long transparentB=-1, int offsetR=0, int offsetG=0, int offsetB=0);
      void putimage2(int x, int y, void* image, int bitblt, int width, int height);
};
#endif