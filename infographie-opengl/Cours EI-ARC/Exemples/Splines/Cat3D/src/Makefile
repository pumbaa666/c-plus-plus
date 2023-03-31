OTHER_SOURCES=
SOURCES=Polygone.cpp SurfaceBezierRat.cpp LignePolygonale.cpp Courbe.cpp CourbeAPoles.cpp CourbeBezier.cpp CourbeBezierRat.cpp CourbeBSpline.cpp CourbeNURBS.cpp Surface.cpp SurfaceNURBS.cpp ListePoints.cpp SurfaceAPoles.cpp SurfacePolyedrique.cpp MatricePoints.cpp SurfaceBSpline.cpp Transformation.cpp Objet3D.cpp SurfaceBezier.cpp FenetreVisualisation.cpp FenetrePropriete.cpp

OBJECTS=$(SOURCES:.cpp=.o) $(OTHER_SOURCES:.cpp=.o) 
HEADERS=$(SOURCES:.cpp=.h) Tableau.h ListeChainee.h
MACRO=-DHAVE_OPENGL 
EXEC=../bin/CAT3D

INCLUDE=-I/export/homes/eleves/es2i/es2i2002/trouch/FOX/include/fox 
LIBS=-L/export/homes/eleves/es2i/es2i2002/trouch/FOX/lib -lFOX
CFLAGS= -Wall -pedantic -ansi -ggdb -c 
CC=g++

.cpp.o:
	$(CC) $(MACRO) $(CFLAGS) $(INCLUDE) $*.cpp


all : $(EXEC) 

$(EXEC) : $(OBJECTS)  
	$(CC) $(OBJECTS) $(LIBS) -o $(EXEC)



clean:
	@rm -f *.o *\~ core
