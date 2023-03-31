// Fichier Geometrie.cpp

#include <GL\glut.h>
#include "axes.h"
#include "points.h"
#include "lines.h"
#include "line_strip.h"
#include "line_loop.h"
#include "polygone.h"
#include "quads.h"
#include "quad_strip.h"
#include "triangles.h"
#include "triangle_strip.h"
#include "triangle_fan.h"
#include "global.h"
#include "geometrie.h"

void DessinerLaScene()
{
  switch(Figure)
  {
    case 1 : DessinerLesAxes();
             DessinerLesPoints();
             glutSetWindowTitle("Primitives : GL_POINTS");
             break;
    case 2 : DessinerLesAxes();
             DessinerLesLignes();
             glutSetWindowTitle("Primitives : GL_LINES");
             break;

    case 3 : DessinerLesAxes();
             DessinerLesLine_strip();
             glutSetWindowTitle("Primitives : GL_LINE_STRIP");
             break;
    case 4 : DessinerLesAxes();
             DessinerLesLine_loop();
             glutSetWindowTitle("Primitives : GL_LINE_LOOP");
             break;

    case 5 : DessinerLesAxes();
             DessinerLePolygone(GL_SMOOTH);
             glutSetWindowTitle("Primitives : GL_POLYGON (SMOOTH)");
             break;
    case 6 : DessinerLesAxes();
             DessinerLePolygone(GL_FLAT);
             glutSetWindowTitle("Primitives : GL_POLYGONE (FLAT)");
             break;

    case 7 : DessinerLesAxes();
             DessinerLesQuads(GL_FLAT);
             glutSetWindowTitle("Primitives : GL_QUADS");
             break;
    case 8 : DessinerLesAxes();
             DessinerLesQuad_strip(GL_SMOOTH);
             glutSetWindowTitle("Primitives : GL_QUAD_STRIP");
             break;

    case 9 : DessinerLesAxes();
             DessinerLesTriangles(GL_FLAT);
             glutSetWindowTitle("Primitives : GL_TRIANGLES");
             break;
    case 10 : DessinerLesAxes();
              DessinerLesTriangle_strip(GL_FLAT);
              glutSetWindowTitle("Primitives : GL_TRIANGLE_STRIP");
              break;
    case 11 : DessinerLesAxes();
              DessinerLesTriangle_fan(GL_SMOOTH);
              glutSetWindowTitle("Primitives : GL_TRIANGLE_FAN");
              break;
  }
}

