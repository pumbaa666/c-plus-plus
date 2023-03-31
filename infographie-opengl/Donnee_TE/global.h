// Loïc Correvon
// Fichier Global.h
#ifndef GLOBAL_H
#define GLOBAL_H

#define DELTA_TIME 20

/*extern GLfloat angleX;
extern GLfloat angleY;
extern GLfloat angleZ;*/
extern GLfloat deltaAngle;
extern char AxeRotation;

extern int Mode;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
extern GLenum spinMode;
extern GLfloat xRot;
extern GLfloat yRot;
extern GLfloat xPos;
extern GLfloat yPos;
extern GLfloat zPos;
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

#endif
