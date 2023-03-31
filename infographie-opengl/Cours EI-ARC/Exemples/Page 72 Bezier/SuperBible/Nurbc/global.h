// Fichier Global.h
#ifndef GLOBAL_H
#define GLOBAL_H

// NURBS object pointer
extern GLUnurbsObj *pNurb;
// The number of control points for this curve
extern GLint nNumPoints;

extern GLfloat ctrlPoints[4][3];

// Knot sequence for the NURB
extern GLfloat Knots[];


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

extern const int bCull;
extern const int bDepth;
extern const int bOutline;
extern const int bShadeModel;


// Light values and coordinates
extern GLfloat lightPos[];
extern GLfloat spotDir[];

// cutOff entre 0 et 90 (angle d'ouverture)
// 180 --> lumière uniforme
extern GLfloat spotCutOff;

// spotExponent entre 0 et 128, 0 --> lumière uniforme
extern GLfloat spotExponent;

extern GLfloat ambientLight[];
extern GLfloat diffuseLight[];
extern GLfloat specularLight[];
extern GLfloat RotationLumiere;

#endif
