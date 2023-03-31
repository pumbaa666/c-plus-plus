#include <gl\glut.h>                // Librairie GLUT
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "evenements.h"
#include "geometrie.h"
#include "global.h"
#include "main.h"

void SetupRC()
{
	glClearColor(0.5f, 0.0f, 1.0f, 1.0f );  	//l'écran sera effacé en noir
	glShadeModel(GL_SMOOTH);					//le triangle sera rempli en dégradé
//  glShadeModel(GL_FLAT);
}

int main(int argc, char **argv)
{


  char caract = 0;
  int i = 0;

  for(i = 3 ; i < 7 ; i++)
  {
        caract = i;
        printf("(%ld)\t%c\n", i , caract);
  }

  system("PAUSE");
    return 0;
}
