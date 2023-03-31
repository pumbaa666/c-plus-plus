#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <bios.h>
#include <fcntl.h>
#include <memory.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "images.h"
#include "winbgim.cpp"


graphique::graphique()
{

}

/// Ferme la fenêtre graphique
graphique::~graphique()
{
	closegraph();
}
/**
 * Lit les pixels de l'images
 *
 * @param	image*	img	pointeur sur l'image en mémoire
 * @param	int	ix	position en x de l'image
 * @param	int	iy	position en y de l'image
 */

void graphique::dsp_sprite(image * img,int ix, int iy, long transparentR, long transparentG, long transparentB, int offsetR, int offsetG, int offsetB)
{
	int x,y,nbpix;

	nbpix=0;
	for(y=0; y < img->height; ++y)
	{
		for(x=0; x < img->width; ++x)
		{
         // appliquer un filtre de couleur
         img->sprite[nbpix].bleu= img->sprite[nbpix].bleu+offsetB;
         img->sprite[nbpix].vert= img->sprite[nbpix].vert+offsetG;
         img->sprite[nbpix].rouge= img->sprite[nbpix].rouge+offsetR;
      	if (img->sprite[nbpix].bleu==transparentB && img->sprite[nbpix].vert==transparentG && img->sprite[nbpix].rouge==transparentR )
         {
         // on a un pixel transparent
         }
         else
         {
				putpixel(x+ix,img->height-1-y+iy,COLOR(img->sprite[nbpix].bleu,img->sprite[nbpix].vert,img->sprite[nbpix].rouge));
         }
			nbpix++;
		}
	}
}

/// Fonctions de chargement d'une image en mémoire
image * graphique::loadBMP(char file[255])
{
	FILE * bmp;
	img * image;
	unsigned short int offset,type;

	bmp=fopen(file,"rb");
	if (bmp!=NULL)
	{
		image = (img*)malloc(sizeof(img));

		if (image!=NULL)
		{
			fread(&type,sizeof(unsigned short int),1,bmp); //Vérification de la signature

			if (type==19778)
			{
				fseek(bmp,10,SEEK_SET);
				fread(&offset,sizeof(unsigned short int),1,bmp); //Adresse de l'information image
				fseek(bmp,18,SEEK_SET);
				fread(&image->width,sizeof(unsigned int),2,bmp); //Récupération des dimensions
				fseek(bmp,offset,SEEK_SET);
				image->sprite = (pixel*)malloc(image->height * image->width * sizeof(pixel));
				fread(image->sprite,image->height * image->width * sizeof(pixel),1,bmp);
			}
			else
			{
				printf("\nLe fichier %s n'est pas un fichier bitmap",file);
				image=NULL;
			}
		}
		else
		{
				printf("\nErreur d'allocation");
				getch();
		}
	}
	else
	{
		printf("\nLe fichier %s est manquant",file);
		getch();
	}
	fclose(bmp);
	return(image);
}
void graphique::afficherImage(char file[255], int x, int y, long transparentR, long transparentG, long transparentB, int offsetR, int offsetG, int offsetB)
{
	//image
	image * imageAffiche; //Définitions du sprite
	imageAffiche = loadBMP(file);
	dsp_sprite(imageAffiche,x,y,transparentR,transparentG,transparentB, offsetR,  offsetG,  offsetB);
}

void  graphique::putimage2(int x, int y, void* image, int bitblt, int width, int height)
{
    BGIimage* bi = (BGIimage*)image;
    HDC tempHDC;
    HBITMAP tempBMP;
    char *bitmapBits;
    char *actualBits;
    unsigned int localImageSize;
    bi->width=width;
    bi->height=height;
    hBitMapInfo.bmiHeader.biWidth=bi->width;
    hBitMapInfo.bmiHeader.biHeight=bi->height;
    localImageSize=(bi->width)*(bi->height)*32/8; //32 bits per pixel, 8 bits per byte
    hBitMapInfo.bmiHeader.biSizeImage=localImageSize;

    actualBits=bi->bits;

    bitmapBits=new char[localImageSize];
    tempHDC=CreateCompatibleDC(hdc[visual_page != active_page|| bgiemu_handle_redraw ? 1 : 0]);
    if (0==SetDIBitsToDevice(tempHDC,0,0,bi->width,bi->height,0,0,0,bi->height-1,&(bi->bits),&hBitMapInfo,DIB_RGB_COLORS))
	cerr << "Unable to copy image to offscreen buffer" << endl;

    tempBMP=CreateDIBSection(tempHDC,&hBitMapInfo,DIB_RGB_COLORS,(void**)&bitmapBits,0,0);

    if (!SelectObject(tempHDC,tempBMP))
	cerr << "cannot select bitmap image in offscreen window" << endl;

    memcpy(bitmapBits,actualBits,localImageSize);

    // Select the bitmaps into the compatible DC.
    if (SelectObject(hdc[0], tempBMP)) // was tempBMP))
	cerr << "Unable to synch graphics window with bitmap." << endl;

    if (!BitBlt(hdc[0],x,y,bi->width,bi->height,tempHDC,0,0,bitblt_mode_cnv[bitblt])) //bi->hdc was tempHDC
        cerr << "Unable to copy bitmap to graphics window." << endl;

    if (SelectObject(hdc[1], tempBMP)) // was tempBMP))
	cerr << "Unable to synch graphics window with bitmap." << endl;

    if (!BitBlt(hdc[1],x,y,bi->width,bi->height,tempHDC,0,0,bitblt_mode_cnv[bitblt])) //bi->hdc was tempHDC
        cerr << "Unable to copy bitmap to graphics window." << endl;

    DeleteObject(tempBMP);
    //delete bitmapBits;  // To prevent heap leak, should be in,
    // but if it is in, the program will crash.  why?
    DeleteDC(tempHDC);

}

