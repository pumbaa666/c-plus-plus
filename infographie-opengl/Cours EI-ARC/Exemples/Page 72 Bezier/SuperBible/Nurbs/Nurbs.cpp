// Nurbs.c
// OpenGL SuperBible, Chapter 13
// Demonstrates 3D NURBS
// Program by Richard S. Wright Jr.

//#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// Remarque concernant #include <iostream.h> et <iostream> :
//
// Utiliser l'option -Wno-deprecated
// pour �viter le warning suivant :
// #warning This file includes at least one deprecated or antiquated header.
// Please consider using one of the 32 headers found in section 17.4.1.2
// of the C++ standard. Examples include substituting the <X> header
// for the <X.h> header for C++ includes, or <iostream> instead of
// the deprecated header <iostream.h>.
// To disable this warning use -Wno-deprecated.

// Si on �crit : #include <iostream> (sans le .h), alors on doit �crire :

//    std::cout << "blabla" << std::endl;

#include <iostream.h>
// NURBS object pointer
GLUnurbsObj *pNurb = NULL;

// The number of control points for this curve
GLint nNumPoints = 4; // 4 X 4

// Mesh extends four units -6 to +6 along x and y axis
// Lies in Z plane
//                 u  v  (x,y,z)	
GLfloat ctrlPoints[4][4][3]= {{{  -6.0f, -6.0f, 0.0f},	// u = 0,	v = 0
						      {	  -6.0f, -2.0f, 0.0f},	//			v = 1
							  {   -6.0f,  2.0f, 0.0f},	//			v = 2	
							  {   -6.0f,  6.0f, 0.0f}}, //			v = 3
							 
							  {{  -2.0f, -6.0f, 0.0f},	// u = 1	v = 0
						      {   -2.0f, -2.0f, 8.0f},	//			v = 1
							  {   -2.0f,  2.0f, 8.0f},	//			v = 2
//						      {   -2.0f, -2.0f, 0.0f},	//			v = 1
//							  {   -2.0f,  2.0f, 0.0f},	//			v = 2
							  {   -2.0f,  6.0f, 0.0f}},	//			v = 3
							  
							  {{   2.0f, -6.0f, 0.0f }, // u =2		v = 0
							  {    2.0f, -2.0f, 8.0f }, //			v = 1
							  {    2.0f,  2.0f, 8.0f },	//			v = 2
//							  {    2.0f, -2.0f, 0.0f }, //			v = 1
//							  {    2.0f,  2.0f, 0.0f },	//			v = 2
							  {    2.0f,  6.0f, 0.0f }},//			v = 3

							  {{   6.0f, -6.0f, 0.0f},	// u = 3	v = 0
							  {    6.0f, -2.0f, 0.0f},	//			v = 1
							  {    6.0f,  2.0f, 0.0f},	//			v = 2
							  {    6.0f,  6.0f, 0.0f}}};//			v = 3

// Knot sequence for the NURB
GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};



// Called to draw the control points in Red over the NURB
void DrawPoints(void)
	{
	int i,j;

	// Large Red Points
	glPointSize(5.0f);
	glColor3ub(255,0,0);

	// Draw all the points in the array
	glBegin(GL_POINTS);
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				glVertex3fv(ctrlPoints[i][j]);	
	glEnd();
	}

// NURBS callback error handler

void CALLBACK NurbsErrorHandler(GLenum nErrorCode)
	{
	char cMessage[64];

	// Extract a text message of the error
	strcpy(cMessage,"NURBS error occured: ");
	strcat(cMessage, (char *)gluErrorString(nErrorCode));

	// Display the message to the user
	MessageBox(NULL,cMessage,NULL,MB_OK | MB_ICONEXCLAMATION);
	}



// Called to draw scene
void RenderScene(void)
	{
	// Draw in Blue
	glColor3ub(0,0,220);

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the modelview matrix stack
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Rotate the mesh around to make it easier to see
	glRotatef(330.0f, 1.0f,0.0f,0.0f);
	
	// Render the NURB
	// Begin the NURB definition
    gluBeginSurface(pNurb);
	
	// Evaluate the surface
    gluNurbsSurface(pNurb,	// pointer to NURBS renderer
        8, Knots,			// No. of knots and knot array u direction	
        8, Knots,			// No. of knots and knot array v direction
        4 * 3,				// Distance between control points in u dir.
        3,					// Distance between control points in v dir.
        &ctrlPoints[0][0][0], // Control points
        4, 4,					// u and v order of surface
        GL_MAP2_VERTEX_3);		// Type of surface
		
	// Done with surface
	gluEndSurface(pNurb);
	
	// Show the control points
	DrawPoints();

	// Restore the modelview matrix
	glPopMatrix();


	// Dispalay the image
	glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
	{
	// Light values and coordinates
	GLfloat  whiteLight[] = {0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat  shine[] = { 100.0f };

	// Clear Window to white
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	
	// Automatically generate normals for evaluated surfaces
	glEnable(GL_AUTO_NORMAL);


	// Setup the Nurbs object
    pNurb = gluNewNurbsRenderer();

	// Install error handler to notify user of NURBS errors
	gluNurbsCallback(pNurb, GLU_ERROR,
                 reinterpret_cast<GLvoid (CALLBACK *)()>(&NurbsErrorHandler));

    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.0f);
	// Uncomment the next line and comment the one following to produce a
	// wire frame mesh.
    //gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
	gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
	}


void ChangeSize(int w, int h)
	{
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective view
	gluPerspective (45.0f, (GLdouble)w/(GLdouble)h, 1.0, 40.0f);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Viewing transformation, position for better view
    glTranslatef (0.0f, 0.0f, -20.0f);
	}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("NURBS Surface");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
  const GLubyte * s;
  s = glGetString(GL_VENDOR);
  cout << "GL_VENDOR :" << endl;
  cout << s << endl;
  s = glGetString(GL_RENDERER);
  cout << "GL_RENDERER :" << endl;
  cout << s << endl;
  s = glGetString(GL_VERSION);
  cout << "GL_VERSION :" << endl;
  cout << s << endl;
  s = glGetString(GL_EXTENSIONS);
  cout << "GL_EXTENSIONS :" << endl;
  cout << s << endl << endl;
  cout << "Pour GLU :" << endl;
  #ifndef GLU_VERSION_1_3
  cout << "Pas version 1.3" << endl;
  #endif
  #ifndef GLU_VERSION_1_2
  cout << "Pas version 1.2" << endl;
  #endif
  #ifndef GLU_VERSION_1_1
  cout << "Pas version 1.1" << endl;
  #endif

  s = gluGetString(GLU_VERSION);
  cout << s << endl;
  s = gluGetString(GLU_EXTENSIONS);
  cout << s << endl;

	glutMainLoop();
	return 0;

}
