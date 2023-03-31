// Fichier Global.h

#ifndef GLOBAL_H
#define GLOBAL_H

extern int Mode;
extern GLenum spinMode;
extern GLfloat xRot;
extern GLfloat yRot;
extern GLfloat zPos;
extern GLfloat xPos;
extern GLfloat Theta;
extern bool ButtonLeftDown;
extern bool ButtonRightDown;
extern bool FullScreen;

extern GLdouble AngleOuverture;   // en degr�s
extern GLdouble RapportAspect, PlanAvant, PlanArriere;

// Light values and coordinates
extern GLfloat	 lightPos[];
extern GLfloat  spotDir[];

// cutOff entre 0 et 90 (angle d'ouverture)
// 180 --> lumi�re uniforme
extern GLfloat spotCutOff;

// spotExponent entre 0 et 128, 0 --> lumi�re uniforme
extern GLfloat spotExponent;

extern GLfloat  ambientLight[];
extern GLfloat  diffuseLight[];
extern GLfloat  specularLight[];

#endif
