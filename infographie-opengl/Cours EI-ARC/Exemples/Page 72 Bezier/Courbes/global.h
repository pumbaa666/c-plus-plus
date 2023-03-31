// Fichier Global.h

#ifndef GLOBAL_H
#define GLOBAL_H

extern GLfloat ctrlpoints[4][3];

extern int largeur;
extern int hauteur;

extern bool Stencil;
extern GLint cube;
extern GLint cubeOmbre;
extern GLfloat vfloor[4][3];
extern GLfloat vfloor2[4][3];

// Plan de projection de l'ombre à 0.01 de hauteur à cause du Depth Buffer
//extern GLfloat vfloor2[4][3];

extern GLfloat positionProperties[];

extern bool ButtonLeftDown;
extern bool ButtonRightDown;
extern bool FullScreen;
extern GLfloat xRot;
extern GLfloat yRot;
extern GLfloat zPos;
extern GLfloat xPos;
extern GLfloat Theta;


#endif
