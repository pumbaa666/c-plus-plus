// Fichier Global.h

#ifndef GLOBAL_H
#define GLOBAL_H

#define ID_TIMER 1

extern GLfloat angle;
extern bool animationOn;
extern GLfloat xRot;
extern GLfloat yRot;
extern GLfloat Theta;
extern GLfloat xPos;
extern GLfloat yPos;
extern GLfloat zPos;

extern int Mode;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
extern const int bCull;
extern const int bDepth;
extern const int bOutline;
extern const int bShadeModel;

// Light values and coordinates
extern GLfloat  DistanceLumiere;
extern GLfloat lightPos[];
extern GLfloat ambientLight[];
extern GLfloat diffuseLight[];
extern GLfloat specularLight[];
extern GLfloat RotationLumiere;

extern GLuint texture1;
extern bool Stencil;
extern GLint cube;
extern GLint cubeOmbre;
extern GLfloat vfloor[4][3];

#endif

