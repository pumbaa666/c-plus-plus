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
// SettingPages.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SettingPages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEditorSettingPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CObjectPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CPreviewPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CPovExpPage, CPropertyPage)

void RinfColore(CWnd* pWind,COLORREF colore)
{
	CRect r;
	CBrush b(colore);
	CDC* pControlDC=pWind->GetDC();
	pWind->Invalidate();
	pWind->UpdateWindow();
	pWind->GetClientRect(r);
	CBrush* pOld=pControlDC->SelectObject(&b);
	pControlDC->Rectangle(r);
	pControlDC->SelectObject(pOld);
	pWind->ReleaseDC(pControlDC);
}


/////////////////////////////////////////////////////////////////////////////
// CEditorSettingPage property page

CEditorSettingPage::CEditorSettingPage() : CPropertyPage(CEditorSettingPage::IDD)
{
	//{{AFX_DATA_INIT(CEditorSettingPage)
	m_curvesteps = 0;
	m_drawpolyg = FALSE;
	m_gridsize = 0;
	m_pensize = 0;
	//}}AFX_DATA_INIT
}

CEditorSettingPage::~CEditorSettingPage()
{
}

void CEditorSettingPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorSettingPage)
	DDX_Control(pDX, IDC_PENCOLOR_SWATCH, m_pencolorswatch);
	DDX_Control(pDX, IDC_BGCOLOR_SWATCH, m_bgcolorswatch);
	DDX_Control(pDX, IDC_GRIDCOLOR_SWATCH, m_gridcolorswatch);
	DDX_Control(pDX, IDC_PENSIZE_SPIN, m_pensizespin);
	DDX_Control(pDX, IDC_GRIDSIZE_SPIN, m_gridsizespin);
	DDX_Control(pDX, IDC_CURVESTEP_SPIN, m_curvestepspin);
	DDX_Text(pDX, IDC_CURVESTEPS_EDIT, m_curvesteps);
	DDV_MinMaxInt(pDX, m_curvesteps, 1, 20);
	DDX_Check(pDX, IDC_DRAWPOLYG_CHECK, m_drawpolyg);
	DDX_Text(pDX, IDC_GRIDSIZE_EDIT, m_gridsize);
	DDV_MinMaxInt(pDX, m_gridsize, 3, 500);
	DDX_Text(pDX, IDC_PENSIZE_EDIT, m_pensize);
	DDV_MinMaxInt(pDX, m_pensize, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorSettingPage, CPropertyPage)
	//{{AFX_MSG_MAP(CEditorSettingPage)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CObjectPage property page

CObjectPage::CObjectPage() : CPropertyPage(CObjectPage::IDD)
{
	//{{AFX_DATA_INIT(CObjectPage)
	m_3dsteps = 0;
	m_sections = 0;
	m_extrusion = 0.0f;
	m_objbackcull = FALSE;
	m_objsmooth = FALSE;
	//}}AFX_DATA_INIT
}

CObjectPage::~CObjectPage()
{
}

void CObjectPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectPage)
	DDX_Control(pDX, IDC_OBJCOLOR_SWATCH, m_objcolorswatch);
	DDX_Control(pDX, IDC_SECTIONS_SPIN, m_sectionsspin);
	DDX_Control(pDX, IDC_EXTRUSION_SPIN, m_extrusionspin);
	DDX_Control(pDX, IDC_3DSTEPS_SPIN, m_3dstepsspin);
	DDX_Text(pDX, IDC_3DSTEPS_EDIT, m_3dsteps);
	DDV_MinMaxInt(pDX, m_3dsteps, 1, 40);
	DDX_Text(pDX, IDC_SECTIONS_EDIT, m_sections);
	DDV_MinMaxInt(pDX, m_sections, 3, 200);
	DDX_Text(pDX, IDC_EXTRUSION_EDIT, m_extrusion);
	DDV_MinMaxFloat(pDX, m_extrusion, 1.e-003f, 20.f);
	DDX_Check(pDX, IDC_OBJ_BACKCULL, m_objbackcull);
	DDX_Check(pDX, IDC_OBJ_SMOOTH, m_objsmooth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjectPage, CPropertyPage)
	//{{AFX_MSG_MAP(CObjectPage)
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPreviewPage property page

CPreviewPage::CPreviewPage() : CPropertyPage(CPreviewPage::IDD)
{
	//{{AFX_DATA_INIT(CPreviewPage)
	m_blpos = -1;
	m_flpos = -1;
	//}}AFX_DATA_INIT
}

CPreviewPage::~CPreviewPage()
{
}

void CPreviewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewPage)
	DDX_Control(pDX, IDC_GPCOLOR_SWATCH, m_gpcolorswatch);
	DDX_Control(pDX, IDC_FLCOLOR_SWATCH, m_flcolorswatch);
	DDX_Control(pDX, IDC_BLCOLOR_SWATCH, m_blcolorswatch);
	DDX_Control(pDX, IDC_3DBGCOLOR_SWATCH, m_3dbgcolorswatch);
	DDX_Radio(pDX, IDC_BL_POS, m_blpos);
	DDX_Radio(pDX, IDC_FL_POS, m_flpos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreviewPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPreviewPage)
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPovExpPage property page

CPovExpPage::CPovExpPage() : CPropertyPage(CPovExpPage::IDD)
{
	//{{AFX_DATA_INIT(CPovExpPage)
	m_open = FALSE;
	m_objname = _T("");
	m_conic = FALSE;
	m_altez = 0.0f;
	m_sturm = FALSE;
	m_propfactor = 0;
	m_proportional = -1;
	m_ptype = -1;
	//}}AFX_DATA_INIT
}

CPovExpPage::~CPovExpPage()
{
}

void CPovExpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPovExpPage)
	DDX_Control(pDX, IDC_PROPORTIONAL_SPIN, m_proportionalspin);
	DDX_Control(pDX, IDC_ALTEZ_SPIN, m_altezspin);
	DDX_Check(pDX, IDC_OPEN_CHECK, m_open);
	DDX_Text(pDX, IDC_OBJNAME_EDIT, m_objname);
	DDV_MaxChars(pDX, m_objname, 255);
	DDX_Check(pDX, IDC_CONIC_CHECK, m_conic);
	DDX_Text(pDX, IDC_ALTEZ_EDIT, m_altez);
	DDV_MinMaxFloat(pDX, m_altez, 1.e-003f, 5000.f);
	DDX_Check(pDX, IDC_STURM_CHECK, m_sturm);
	DDX_Text(pDX, IDC_PROPORTIONAL_EDIT, m_propfactor);
	DDV_MinMaxInt(pDX, m_propfactor, 1, 500);
	DDX_Radio(pDX, IDC_PROPORTIONAL_RADIO, m_proportional);
	DDX_CBIndex(pDX, IDC_PTYPE_COMBO, m_ptype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPovExpPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPovExpPage)
	ON_BN_CLICKED(IDC_PROPORTIONAL_RADIO, OnProportionalRadio)
	ON_BN_CLICKED(IDC_NORMALIZE_RADIO, OnNormalizeRadio)
	ON_CBN_SELENDOK(IDC_PTYPE_COMBO, OnSelendokPtypeCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CEditorSettingPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	RinfColore(&m_pencolorswatch,m_pencolor);
	RinfColore(&m_bgcolorswatch,m_bgcolor);
	RinfColore(&m_gridcolorswatch,m_gridcolor);
	
	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CEditorSettingPage::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ClientToScreen(&point);
	CRect penrect,bgrect,gridrect;
	m_gridcolorswatch.GetWindowRect(gridrect);
	m_pencolorswatch.GetWindowRect(penrect);
	m_bgcolorswatch.GetWindowRect(bgrect);
	if(bgrect.PtInRect(point))
	{
		CColorDialog coloreq(m_bgcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_bgcolor=coloreq.GetColor();
	};
	if(penrect.PtInRect(point))
	{
		CColorDialog coloreq(m_pencolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_pencolor=coloreq.GetColor();
	};
	if(gridrect.PtInRect(point))
	{
		CColorDialog coloreq(m_gridcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_gridcolor=coloreq.GetColor();
	};
	Invalidate(FALSE);
	CPropertyPage::OnLButtonUp(nFlags, point);
}

BOOL CEditorSettingPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_pensizespin.SetRange( 1, 10 );
	m_gridsizespin.SetRange( 3, 500 );
	m_curvestepspin.SetRange( 1, 20 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CObjectPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_3dstepsspin.SetRange( 1, 40 );
	m_extrusionspin.SetRange( 0,20 );
	m_sectionsspin.SetRange( 3,200 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CObjectPage::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ClientToScreen(&point);
	CRect objrect;
	m_objcolorswatch.GetWindowRect(objrect);
	if(objrect.PtInRect(point))
	{
		CColorDialog coloreq(m_objcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_objcolor=coloreq.GetColor();
	};
	Invalidate(FALSE);
	CPropertyPage::OnLButtonUp(nFlags, point);
}

void CObjectPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	RinfColore(&m_objcolorswatch,m_objcolor);
	
	// Do not call CPropertyPage::OnPaint() for painting messages
}

BOOL CPreviewPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreviewPage::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ClientToScreen(&point);
	CRect tredbgrect,blrect,gprect,flrect;
	m_3dbgcolorswatch.GetWindowRect(tredbgrect);
	m_blcolorswatch.GetWindowRect(blrect);
	m_flcolorswatch.GetWindowRect(flrect);
	m_gpcolorswatch.GetWindowRect(gprect);
	if(blrect.PtInRect(point))
	{
		CColorDialog coloreq(m_blcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_blcolor=coloreq.GetColor();
	};
	if(flrect.PtInRect(point))
	{
		CColorDialog coloreq(m_flcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_flcolor=coloreq.GetColor();
	};
	if(tredbgrect.PtInRect(point))
	{
		CColorDialog coloreq(m_3dbgcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_3dbgcolor=coloreq.GetColor();
	};
	if(gprect.PtInRect(point))
	{
		CColorDialog coloreq(m_gpcolor,CC_FULLOPEN);
		if (coloreq.DoModal()==IDOK) m_gpcolor=coloreq.GetColor();
	};
	Invalidate(FALSE);
	CPropertyPage::OnLButtonUp(nFlags, point);
}

void CPreviewPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	RinfColore(&m_3dbgcolorswatch,m_3dbgcolor);
	RinfColore(&m_blcolorswatch,m_blcolor);
	RinfColore(&m_flcolorswatch,m_flcolor);
	RinfColore(&m_gpcolorswatch,m_gpcolor);
	
	// Do not call CPropertyPage::OnPaint() for painting messages
}

BOOL CPovExpPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	UDACCEL* pAcc=new UDACCEL;
	pAcc->nSec=1;
	pAcc->nInc=5;
	OnSelendokPtypeCombo();
	m_proportionalspin.SetRange( 1, 1000 );
	m_proportionalspin.SetAccel( 1,pAcc );
	m_altezspin.SetRange( 1, 1000 );
	if (m_proportional==0) {
		SendDlgItemMessage(IDC_PROPORTIONAL_RADIO,BM_SETCHECK,BST_CHECKED);
		OnProportionalRadio(); }
	else {
		SendDlgItemMessage(IDC_NORMALIZE_RADIO,BM_SETCHECK,BST_CHECKED);
		OnNormalizeRadio();	};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPovExpPage::OnProportionalRadio() 
{
	abilita(IDC_PROPORTIONAL_EDIT);
	abilita(IDC_PROPORTIONAL_SPIN);
}

void CPovExpPage::OnNormalizeRadio() 
{
	disabilita(IDC_PROPORTIONAL_EDIT);
	disabilita(IDC_PROPORTIONAL_SPIN);
}

void CPovExpPage::OnSelendokPtypeCombo() 
{
	switch( (int)SendDlgItemMessage(IDC_PTYPE_COMBO, CB_GETCURSEL, 0, 0) )
	{
	case 0://Lathe
				disabilita(IDC_ALTEZ_EDIT);
				disabilita(IDC_ALTEZ_SPIN);
				disabilita(IDC_STURM_CHECK);
				disabilita(IDC_OPEN_CHECK);
				disabilita(IDC_CONIC_CHECK);
				break;
	case 1://Prism
				abilita(IDC_ALTEZ_EDIT);
				abilita(IDC_ALTEZ_SPIN);
				abilita(IDC_STURM_CHECK);
				abilita(IDC_OPEN_CHECK);
				abilita(IDC_CONIC_CHECK);
				break;
	case 2://SOR
				disabilita(IDC_ALTEZ_EDIT);
				disabilita(IDC_ALTEZ_SPIN);
				abilita(IDC_STURM_CHECK);
				abilita(IDC_OPEN_CHECK);
				disabilita(IDC_CONIC_CHECK);
				break;
	};
}

void CPovExpPage::disabilita(int cid)
{
	CWnd *pctrl=GetDlgItem(cid);
	pctrl->EnableWindow(FALSE);
}

void CPovExpPage::abilita(int cid)
{
	CWnd *pctrl=GetDlgItem(cid);
	pctrl->EnableWindow(TRUE);
}
