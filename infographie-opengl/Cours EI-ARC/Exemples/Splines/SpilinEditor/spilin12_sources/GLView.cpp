/*****************************************************
Copyright Notice

Copyright © Alessandro Falappa

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose is hereby granted without
fee, provided that the above copyright notice, author statement
appear in all copies of this software and related documentation.

THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF
ANY KIND, EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT
LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
PARTICULAR PURPOSE.

IN NO EVENT SHALL ALESSANDRO FALAPPA BE LIABLE FOR ANY
SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
KIND, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE,
AND ON ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
******************************************************/
// GLView.cpp : implementation file
//

#include "stdafx.h"
#include "SpilinEditor.h"

#include "undo.h"
#include "SpilinEditorDoc.h"
#include "GLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////
// Constants

unsigned char _threeto8[8] = 
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char _twoto8[4] = 
{
	0, 0x55, 0xaa, 0xff
};

unsigned char _oneto8[2] = 
{
	0, 255
};

static int defaultOverride[13] = 
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] = 
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

const float VIEWANGLE=40.0f;

/////////////////////////////////////////////////////////////////////////////
// CGLView Construction/Destruction

IMPLEMENT_DYNCREATE(CGLView, CView)

CGLView::CGLView():
	smoothshade(FALSE), backcull(FALSE),ShowGridPlane(FALSE),
	objtype(CSpilinEditorDoc::LATHE),GridDispList(0),
	ObjAngleX(0.0f), ObjAngleY(0.0f), ObjAngleZ(0.0f),
	distance(4.0f), FrontClipPlane(2.8f), BackClipPlane(5.2f),
	hrc(NULL), FrontLightPos(NE_LPOS),BackLightPos(SW_LPOS)
{
}

CGLView::~CGLView()
{
#ifdef _DEBUG
	Dump(afxDump);
#endif
}


BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_SMOOTH_SHADE, OnUpdateSmoothShade)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView drawing

void CGLView::OnDraw(CDC* pDC)
{
	CSpilinEditorDoc* pDoc = GetDocument();
	static BOOL 	bBusy = FALSE;
	if(bBusy) return;
	bBusy = TRUE;
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (pDoc->Rdisplist!=0 || pDoc->Edisplist!=0)
	{
	glPushMatrix();
		glRotatef(ObjAngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(ObjAngleY, 0.0f, 1.0f, 0.0f);
		//glRotatef(ObjAngleZ, 0.0f, 0.0f, 1.0f);// In Spilin is useless
		if(ShowGridPlane)
		{
			glDisable(GL_LIGHTING);
			glColor3f(GetRValue(gpcolor)/255.0f,GetGValue(gpcolor)/255.0f,GetBValue(gpcolor)/255.0f);
			glCallList(GridDispList);
			glEnable(GL_LIGHTING);
		};
		switch (objtype)
		{
		case CSpilinEditorDoc::PRISM: glCallList(pDoc->Edisplist);
						  break;
		case CSpilinEditorDoc::LATHE: glCallList(pDoc->Rdisplist);
						  break;	
		};
	glPopMatrix();
	};
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	bBusy = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CGLView diagnostics

#ifdef _DEBUG
void CGLView::AssertValid() const
{
	CView::AssertValid();
}

void CGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
	afxDump<<"Camera Parameters\n\tAspect Ratio :"<<AspectRatio<<"\n\tClipping Planes :"<<BackClipPlane<<" : "<<FrontClipPlane;
	afxDump<<"\n\tPosition : 0.0 ; 0.0 ; "<<distance;
	afxDump<<"\nRendering Parameters\n\tBack Culling :"<<backcull<<"\n\tSmooth Shading :"<<smoothshade;
	afxDump<<"\nObject Parameters\n\tOrientation Angles :"<<ObjAngleX<<" ; "<<ObjAngleY<<" ; "<<ObjAngleZ<<"\n\tObject Type :"<<objtype;
	afxDump<<"\nView Parameters\n\tClient Rectangle :"<<ClientRect<<"\n\tMouse Down Point :"<<MouseDownPoint<<"\n";
}

CSpilinEditorDoc* CGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpilinEditorDoc)));
	return (CSpilinEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
   // styles requested by OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	//change some styles and  set to null the default cursor and background
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);
	//other way
	//cs.style |= CS_OWNDC | CS_SAVEBITS;
	
	// Call the base-class version
	return CView::PreCreateWindow(cs);
}

void CGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar) {
    case VK_UP:
	  if(distance>2.0f)
	  {	distance-=1.0f;FrontClipPlane-=1.0f;BackClipPlane-=1.0f;
		SetCamera();
		Invalidate(TRUE);};
      break;
    case VK_DOWN:
	  if(distance<12.0f)
	  {	distance+=1.0f;FrontClipPlane+=1.0f;BackClipPlane+=1.0f;
		SetCamera();
		Invalidate(TRUE);};
      break;
	}
}

void CGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	MouseDownPoint=point;
}

void CGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(GetCapture()==this)
	{
		MouseDownPoint.x=-1;MouseDownPoint.y=-1;
		ReleaseCapture();
	}
}

void CGLView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	MouseDownPoint=point;
}

void CGLView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if(GetCapture()==this)
	{
		MouseDownPoint.x=-1;MouseDownPoint.y=-1;
		ReleaseCapture();
	}
}

void CGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( GetCapture()==this)
	{
		if (nFlags==MK_LBUTTON)
		{
			ObjAngleY+=float(point.x-MouseDownPoint.x)/3.6f;
			ObjAngleX+=float(point.y-MouseDownPoint.y)/3.6f;
		};
		if (nFlags==MK_RBUTTON)
		{
			float delta=distance+float(point.y-MouseDownPoint.y)/20.0f;
			distance=delta>0.01f?delta:0.01f;
			FrontClipPlane+=float(point.y-MouseDownPoint.y)/20.0f;
			BackClipPlane+=float(point.y-MouseDownPoint.y)/20.0f;
			SetCamera();
		};
		if (nFlags == (MK_LBUTTON | MK_RBUTTON) )
		{
			TRACE("\n\tMOUSE CHORD in (%d,%d)\n\n",point.x,point.y);
		};
		MouseDownPoint=point;
		Invalidate(TRUE);
	};
}

void CGLView::OnDestroy() 
{
	// OpenGL Rendering Context releasing
	HGLRC   hrc;
	hrc = ::wglGetCurrentContext();
	if (hrc!=NULL)
	{
		::wglMakeCurrent(NULL,  NULL);

		if (hrc)
		::wglDeleteContext(hrc);
	}

	// Select our palette out of the dc
	CPalette    palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	CDC* pDC=GetDC();
	pDC->SelectPalette(&palDefault, FALSE);

	// save settings in registry
	SaveSettings();

	CView::OnDestroy();
}

void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	glViewport(0,0,cx,cy);
	if (cy > 0)
	{
		AspectRatio=float(cx)/float(cy);
		SetCamera();
		/* additional code in MFC example
		if ((ClientRect.right > cx) || (ClientRect.bottom > cy))
		  RedrawWindow();
		*/
	}
	ClientRect.right = cx;
	ClientRect.bottom = cy;
}

BOOL CGLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (pWnd==this && nHitTest==HTCLIENT)
	{
		if(WM_RBUTTONDOWN==message) ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_ZOOM));
		else ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_PREVIEW));
		return TRUE;
	};
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// retrieve registry saved settings
	RetrieveSettings();
   
	// OpenGL rendering context creation
	PIXELFORMATDESCRIPTOR pfd;
    int         n;
	//HGLRC		hrc;

    if (!bSetupPixelFormat())
        return 0;
	
	CDC* cliDC=GetDC();
    n = ::GetPixelFormat(cliDC->GetSafeHdc());
    ::DescribePixelFormat(cliDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

    CreateRGBPalette();

    hrc = wglCreateContext(cliDC->GetSafeHdc());
    wglMakeCurrent(cliDC->GetSafeHdc(), hrc);

    GetClientRect(&ClientRect);
	if (ClientRect.bottom)
		AspectRatio = (GLfloat)ClientRect.right/ClientRect.bottom;
	else	// don't divide by zero, not that we should ever run into that...
		AspectRatio = 1.0f;
	SetCamera();
	SetLights();
	SetMaterials();
	ConstructGridPlane();

	glEnable(GL_DEPTH_TEST);
	/* Nomals are normalized during generation (faster) uncomment if is not the case
	glEnable(GL_NORMALIZE);
	//*/
	glShadeModel(GL_FLAT);
	glClearDepth(1.0f);
	glClearColor(GetRValue(bgcolor)/255.0f,GetGValue(bgcolor)/255.0f,GetBValue(bgcolor)/255.0f, 1.0f );

	return 0;
}

BOOL CGLView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
/////////////////////////////////////////////////////////
// Helpers
void CGLView::SetCamera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//	gluPerspective(VIEWANGLE, AspectRatio, FrontClipPlane, BackClipPlane);
	gluPerspective(VIEWANGLE, AspectRatio, 0.1f, 200.0f);
    glTranslatef(0.0f, 0.0f, -distance);
	glMatrixMode(GL_MODELVIEW);
}

void CGLView::SetLights()
{
	// main light
	GLfloat light_diffuse[] = {GetRValue(colfrontlight)/255.0f,GetGValue(colfrontlight)/255.0f,GetBValue(colfrontlight)/255.0f, 1.0f };
	GLfloat light_position[] = { 0.0f, 0.0f, 5.0f, 0.0f };
	switch(FrontLightPos)
	{
	case NW_LPOS:light_position[0]=-10.0f;light_position[1]=10.0f;break;
	case N_LPOS:light_position[1]=10.0f;break;
	case NE_LPOS:light_position[0]=10.0f;light_position[1]=10.0f;break;
	case W_LPOS:light_position[0]=-10.0f;break;
	case E_LPOS:light_position[0]=10.0f;break;
	case SW_LPOS:light_position[0]=-10.0f;light_position[1]=-10.0f;break;
	case S_LPOS:light_position[1]=-10.0f;break;
	case SE_LPOS:light_position[0]=10.0f;light_position[1]=-10.0f;break;
	};
	// back light
	GLfloat backlight_diffuse[] = { GetRValue(colbacklight)/255.0f,GetGValue(colbacklight)/255.0f,GetBValue(colbacklight)/255.0f, 1.0f };
	GLfloat backlight_position[] = { 0.0f, 0.0f,-5.0f, 0.0f };
	switch(BackLightPos)
	{
	case NW_LPOS:backlight_position[0]=-10.0f;backlight_position[1]=10.0f;break;
	case N_LPOS:backlight_position[1]=10.0f;break;
	case NE_LPOS:backlight_position[0]=10.0f;backlight_position[1]=10.0f;break;
	case W_LPOS:backlight_position[0]=-10.0f;break;
	case E_LPOS:backlight_position[0]=10.0f;break;
	case SW_LPOS:backlight_position[0]=-10.0f;backlight_position[1]=-10.0f;break;
	case S_LPOS:backlight_position[1]=-10.0f;break;
	case SE_LPOS:backlight_position[0]=10.0f;backlight_position[1]=-10.0f;break;
	};
	// global light parameters
	GLfloat lm_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, backlight_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, backlight_diffuse);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0f);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void CGLView::SetMaterials()
{
	GLfloat mat_ambient[] = { GetRValue(colpreview)/510.0f,GetGValue(colpreview)/510.0f,GetBValue(colpreview)/510.0f, 1.0f };
	GLfloat mat_diffuse[] = { GetRValue(colpreview)/255.0f,GetGValue(colpreview)/255.0f,GetBValue(colpreview)/255.0f, 1.0f };
	GLfloat mat_specular[] = { GetRValue(colfrontlight)/270.0f,GetGValue(colfrontlight)/270.0f,GetBValue(colfrontlight)/270.0f, 1.0f };
	GLfloat matb_diffuse[] = { GetRValue(colpreview)/765.0f,GetGValue(colpreview)/765.0f,GetBValue(colpreview)/510.0f, 1.0f };
//	GLfloat matb_diffuse[] = { 1.0f-GetRValue(colpreview)/255.0f,1.0f-GetGValue(colpreview)/255.0f,1.0f-GetBValue(colpreview)/765.0f, 1.0f };
	GLfloat matb_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_BACK, GL_DIFFUSE, matb_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, matb_specular);
}

BOOLEAN CGLView::bSetupPixelFormat()
{
	// define desired pixel format
	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,												   // version number
        PFD_DRAW_TO_WINDOW |             // support window
        PFD_SUPPORT_OPENGL |			    // support OpenGL
        PFD_DOUBLEBUFFER,				      // double buffered
        PFD_TYPE_RGBA,                           // RGBA type
        24,                                               // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;

    if ( (pixelformat = ChoosePixelFormat(GetDC()->GetSafeHdc(), &pfd)) == 0 )
    {
        AfxMessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

    if (SetPixelFormat(GetDC()->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        pixelformat = 1;	
		if (DescribePixelFormat(this->GetDC()->GetSafeHdc(), pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)==0)
		{
			AfxMessageBox("SetPixelFormat failed (no OpenGL compatible video mode)");
			return FALSE;
		}
    }

    return TRUE;
}

void CGLView::CreateRGBPalette()
{
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE *pPal;
    int n, i;
	CDC* cliDC=GetDC();

    n = ::GetPixelFormat(cliDC->GetSafeHdc());
    ::DescribePixelFormat(cliDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE)
    {
        n = 1 << pfd.cColorBits;
        pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

        ASSERT(pPal != NULL);

        pPal->palVersion = 0x300;
        pPal->palNumEntries = n;
        for (i=0; i<n; i++)
        {
            pPal->palPalEntry[i].peRed =
                    ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen =
                    ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue =
                    ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags = 0;
        }

        /* fix up the palette to include the default GDI palette */
        if ((pfd.cColorBits == 8)                           &&
            (pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
            (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
            (pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
           )
        {
			for (i = 1 ; i <= 12 ; i++)
                pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
        }

        cPalette.CreatePalette(pPal);
        delete pPal;

        pOldPalette = cliDC->SelectPalette(&cPalette, FALSE);
        cliDC->RealizePalette();
    }
}

unsigned char CGLView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val;

    val = (unsigned char) (i >> shift);
    switch (nbits) 
	{

    case 1:
        val &= 0x1;
        return _oneto8[val];
    case 2:
        val &= 0x3;
        return _twoto8[val];
    case 3:
        val &= 0x7;
        return _threeto8[val];

    default:
        return 0;
    }
}
///////////////////////////////////////////////////
// PopUp Menu handlers

/*void CGLView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu popmenu;
	if (popmenu.LoadMenu(IDR_GLPOPUP))
	{
		popmenu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,point.x, point.y,this );// route commands through this window
		popmenu.DestroyMenu();
	}
}*/

void CGLView::ToggleSmoothShading() 
{
	smoothshade^=1;
	if(smoothshade) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);
	Invalidate(TRUE);
}

/*void CGLView::OnFlipN() 
{
	CSpilinEditorDoc* pDoc = GetDocument();
	pDoc->pviewnormflip^=1;
	if(objtype)	pDoc->generaExtrusion();
	else pDoc->generaSolido();
	Invalidate(TRUE);
}*/

void CGLView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
		CSpilinEditorDoc* pDoc = GetDocument();
		pDoc->GeometryUpdate(backcull);
		if (backcull) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
		Invalidate(TRUE);
}

void CGLView::UpdateColors()
{
	glClearColor(GetRValue(bgcolor)/255.0f,GetGValue(bgcolor)/255.0f,GetBValue(bgcolor)/255.0f, 1.0f );
	SetLights();
	SetMaterials();
}

void CGLView::OnUpdateSmoothShade(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(smoothshade==1);
}

void CGLView::ConstructGridPlane()
{
	if(GridDispList==0) GridDispList=glGenLists(1);
	glNewList(GridDispList,GL_COMPILE);
	glBegin(GL_LINES);
		//glColor3f(GetRValue(gpcolor)/255.0f,GetGValue(gpcolor)/255.0f,GetBValue(gpcolor)/255.0f);
		glNormal3f(0.0f,0.0f,1.0f);
#define LATO 1.2f
		for(float cont=-LATO;cont<=LATO;cont+=0.2f)
		{
				glVertex3f(cont,-LATO,0.0f);
				glVertex3f(cont,LATO,0.0f);
				glVertex3f(-LATO,cont,0.0f);
				glVertex3f(LATO,cont,0.0f);
		};
	glEnd();
	glEndList();
}

void CGLView::RetrieveSettings()
{
	CWinApp* pApp=AfxGetApp();
	bgcolor=pApp->GetProfileInt("Settings", "PreviewBGcolor",0x00000000);
	gpcolor=pApp->GetProfileInt("Settings", "PreviewGRIDcolor",0x00777777);
	colpreview=pApp->GetProfileInt("Settings", "PreviewOBJECTcolor",0x00F3BF0C);
	colfrontlight=pApp->GetProfileInt("Settings", "PreviewFRONTLIGHTcolor",0x00FFFFFF);
	colbacklight=pApp->GetProfileInt("Settings", "PreviewBACKLIGHTcolor",0x00888888);
}

void CGLView::SaveSettings()
{
	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileInt("Settings", "PreviewBGcolor",bgcolor);
	pApp->WriteProfileInt("Settings", "PreviewGRIDcolor",gpcolor);
	pApp->WriteProfileInt("Settings", "PreviewOBJECTcolor",colpreview);
	pApp->WriteProfileInt("Settings", "PreviewFRONTLIGHTcolor",colfrontlight);
	pApp->WriteProfileInt("Settings", "PreviewBACKLIGHTcolor",colbacklight);
}

void CGLView::MakeCurrent()
{
		wglMakeCurrent(GetDC()->GetSafeHdc(), hrc);
}
