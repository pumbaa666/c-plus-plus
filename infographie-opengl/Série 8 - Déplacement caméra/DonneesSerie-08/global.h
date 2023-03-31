// Fichier Global.h
#ifndef GLOBAL_H
#define GLOBAL_H

#define DELTA_TIME 20

extern int Mode;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
extern GLboolean spinMode;
extern GLfloat xRot;
extern GLfloat yRot;
extern GLfloat zPos;
extern GLfloat xPos;
extern GLfloat Theta;
extern bool ButtonLeftDown;
extern bool ButtonRightDown;
extern bool FullScreen;

extern GLdouble AngleOuverture;   // en degrés
extern GLdouble RapportAspect, PlanAvant, PlanArriere;

extern const int bCull;
extern const int bDepth;
extern const int bOutline;
extern const int bShadeModel;

extern GLuint axes, murs, toit, maison, sol;

#endif

