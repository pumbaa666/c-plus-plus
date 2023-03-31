// Fichier Global.h
#ifndef GLOBAL_H
#define GLOBAL_H

#define LARGEUR_TERRAIN 200

extern int Mode;  // GL_SMOOTH, GL_LINE, DEPTH, CULL
extern GLenum spinMode;
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

extern const int bCull;        // 00000001
extern const int bDepth;       // 00000010
extern const int bOutline;     // 00000100
extern const int bShadeModel;  // 00001000

extern GLuint axes, murs, toit, maison, sol, cone;
extern GLfloat altitudeNeige;
extern GLfloat altitudeMer;
extern int nbDeCollines;
extern int rayonDesCollines;

#endif
