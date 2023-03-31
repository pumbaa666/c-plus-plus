#include <gl/glut.h>
#include <stdio.h>

////////////////////////////////////////////////////////

// Angle de rotation autour de Oy
double	a=0;
//Fonction d'initialisation
void	SetupRC();
//Fonction de redimensionnement
void	Reshape(int w,int h);
//Fonction de dessin
void	Draw();

//Texture :
  GLubyte Texture[16] =      //Image (2x2) 4 octets par pixel : RGBA
  {                          //  s, t
  	0,0,0,0,                 // (0, 0)  noir
    0xFF,0xFF,0xFF,0xFF,     // (1, 0)  blanc
  	0xFF,0xFF,0xFF,0xFF,     // (0, 1)  blanc
    0,0,0,0                  // (1, 1)  noir
  };

  GLuint Nom;

////////////////////////////
void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(.5,.5,.5,0);				//Change la couleur du fond
	glEnable(GL_DEPTH_TEST);				//Active le depth test

	glEnable(GL_TEXTURE_2D);				//Active le texturing
	glGenTextures(1,&Nom);					//Génère un n° de texture
	glBindTexture(GL_TEXTURE_2D,Nom);		//Sélectionne ce n°
	glTexImage2D (
							GL_TEXTURE_2D,		//Type : texture 2D
							0,					//Mipmap : aucun
							4,					//Couleurs : 4
							2,					//Largeur : 2
							2,					//Hauteur : 2
							0,					//Largeur du bord : 0
							GL_RGBA,			//Format : RGBA
							GL_UNSIGNED_BYTE,	//Type des couleurs
							Texture 			//Addresse de l'image
							);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	//glHint est activé si on active le filtering
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

}

////////////////////////////
void	Reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.,float(w)/float(h),1,100);
}

////////////////////////////
void	Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2,2,4,0,0,0,0,1,0);
	glRotated(a,0,1,0);

  // Cube
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);glVertex3i(-1,-1,-1);
		glTexCoord2i(1,0);glVertex3i(+1,-1,-1);
		glTexCoord2i(1,1);glVertex3i(+1,+1,-1);
		glTexCoord2i(0,1);glVertex3i(-1,+1,-1);

		glTexCoord2i(0,0);glVertex3i(-1,-1,+1);
		glTexCoord2i(1,0);glVertex3i(+1,-1,+1);
		glTexCoord2i(1,1);glVertex3i(+1,+1,+1);
		glTexCoord2i(0,1);glVertex3i(-1,+1,+1);

		glTexCoord2i(0,0);glVertex3i(+1,-1,-1);
		glTexCoord2i(1,0);glVertex3i(+1,-1,+1);
		glTexCoord2i(1,1);glVertex3i(+1,+1,+1);
		glTexCoord2i(0,1);glVertex3i(+1,+1,-1);

		glTexCoord2i(0,0);glVertex3i(-1,-1,-1);
		glTexCoord2i(1,0);glVertex3i(-1,-1,+1);
		glTexCoord2i(1,1);glVertex3i(-1,+1,+1);
		glTexCoord2i(0,1);glVertex3i(-1,+1,-1);

		glTexCoord2i(0,0);glVertex3i(-1,+1,-1);
		glTexCoord2i(1,0);glVertex3i(+1,+1,-1);
		glTexCoord2i(1,1);glVertex3i(+1,+1,+1);
		glTexCoord2i(0,1);glVertex3i(-1,+1,+1);

		glTexCoord2i(0,0);glVertex3i(-1,-1,+1);
		glTexCoord2i(1,0);glVertex3i(+1,-1,+1);
		glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
		glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glEnd();

//	a+=1;
	glutSwapBuffers();
//	glutPostRedisplay();
}

////////////////////////////////////////////////////////
int main( int argc, char *argv[ ])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Démo Texture");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	SetupRC();
	glutMainLoop();
	return 0;
}

