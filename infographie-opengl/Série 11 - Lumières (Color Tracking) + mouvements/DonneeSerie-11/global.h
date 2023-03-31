// Fichier Global.h
#ifndef GLOBAL_H
#define GLOBAL_H

extern int Mode;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
extern GLenum spinMode;

extern GLfloat xRot;
extern GLfloat yRot;
extern GLfloat zPos;
extern GLfloat xPos;
extern GLfloat Theta;

extern GLfloat rotationSphere;
extern GLfloat xSphere1;
extern GLfloat zSphere2;
extern GLdouble fRadius;
extern int sphere1;
extern int sphere2;
extern int nbSommetSphere;

extern bool ButtonLeftDown;
extern bool ButtonRightDown;
extern bool FullScreen;

extern GLdouble AngleOuverture;   // en degrés
extern GLdouble RapportAspect, PlanAvant, PlanArriere;

extern const int bCull;        // 00000001
extern const int bDepth;       // 00000010
extern const int bOutline;     // 00000100
extern const int bShadeModel;  // 00001000

#endif
