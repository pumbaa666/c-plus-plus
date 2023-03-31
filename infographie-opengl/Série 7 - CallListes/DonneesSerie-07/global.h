// Fichier Global.h

#ifndef GLOBAL_H
#define GLOBAL_H

#define DELTA_TIME 20

extern int Mode;
extern GLboolean spinMode;
extern GLfloat xRot;
extern GLfloat yRot;
extern bool ButtonLeftDown;
extern bool ButtonRightDown;
extern bool FullScreen;

extern GLdouble AngleOuverture;   // en degrés
extern GLdouble RapportAspect, PlanAvant, PlanArriere;

extern GLuint cone, axes;
extern const int bCull;        // 00000001
extern const int bDepth;       // 00000010
extern const int bOutline;     // 00000100
extern const int bShadeModel;  // 00001000
#endif
