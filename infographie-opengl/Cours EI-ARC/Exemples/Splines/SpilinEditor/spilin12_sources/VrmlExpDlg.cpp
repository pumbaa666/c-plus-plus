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
// VrmlExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpilinEditor.h"
#include "VrmlExpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VrmlExpDlg dialog


VrmlExpDlg::VrmlExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VrmlExpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VrmlExpDlg)
	m_sez = 0;
	m_splstep = 0;
	m_shininess = 0.0f;
	m_transparency = 0.0f;
	m_crease = 0;
	m_verso = FALSE;
	m_radius = 0;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void VrmlExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VrmlExpDlg)
	DDX_Control(pDX, IDC_SPIN5, m_radiuspin);
	DDX_Control(pDX, IDC_SPIN4, m_creasespin);
	DDX_Control(pDX, IDC_SPIN3, m_stepspin);
	DDX_Control(pDX, IDC_SPIN2, m_sezspin);
	DDX_Text(pDX, IDC_SEZIONI, m_sez);
	DDV_MinMaxInt(pDX, m_sez, 3, 500);
	DDX_Text(pDX, IDC_STEPS, m_splstep);
	DDV_MinMaxInt(pDX, m_splstep, 1, 50);
	DDX_Text(pDX, IDC_SHININESS, m_shininess);
	DDV_MinMaxFloat(pDX, m_shininess, 0.0f, 1.0f);
	DDX_Text(pDX, IDC_TRANSPARENCY, m_transparency);
	DDV_MinMaxFloat(pDX, m_transparency, 0.0f, 1.0f);
	DDX_Text(pDX, IDC_CREASE, m_crease);
	DDV_MinMaxInt(pDX, m_crease, 0, 90);
	DDX_Check(pDX, IDC_VERSO, m_verso);
	DDX_Text(pDX, IDC_RAGGIO, m_radius);
	DDV_MinMaxInt(pDX, m_radius, 0, 1000);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VrmlExpDlg, CDialog)
	//{{AFX_MSG_MAP(VrmlExpDlg)
	ON_BN_CLICKED(IDC_COLOR_DIFFUSE, OnColorDiffuse)
	ON_BN_CLICKED(IDC_COLOR_SPECULAR, OnColorSpecular)
	ON_BN_CLICKED(IDC_COLOR_EMITTED, OnColorEmitted)
	ON_WM_PAINT()
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VrmlExpDlg message handlers
BOOL VrmlExpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_sezspin.SetRange( 0, 500 );
	m_stepspin.SetRange( 0, 50 );
	m_creasespin.SetRange( 0, 90 );
	m_radiuspin.SetRange( 0, 10000 );
	diffusec=RGB(50,80,210);
	specularc=RGB(255,255,255);
	emittedc=RGB(0,0,0);
	return TRUE;
}

void VrmlExpDlg::OnColorDiffuse() 
{
	TRACE("Esecuzione di VrmlExpDlg::OnColorDiffuse\n");
	CColorDialog coloreq(diffusec,CC_FULLOPEN);
	if (coloreq.DoModal()==IDOK) diffusec=coloreq.GetColor();
	RinfColore(IDC_COLOR_DIFF,diffusec);
}

void VrmlExpDlg::OnColorSpecular() 
{
	TRACE("Esecuzione di VrmlExpDlg::OnColorSpecular\n");
	CColorDialog coloreq(specularc,CC_FULLOPEN);
	if (coloreq.DoModal()==IDOK) specularc=coloreq.GetColor();
	RinfColore(IDC_COLOR_SPEC,specularc);
}

void VrmlExpDlg::OnColorEmitted() 
{
	TRACE("Esecuzione di VrmlExpDlg::OnColorEmitted\n");
	CColorDialog coloreq(emittedc,CC_FULLOPEN);
	if (coloreq.DoModal()==IDOK) emittedc=coloreq.GetColor();
	RinfColore(IDC_COLOR_EMES,emittedc);
}

void VrmlExpDlg::RinfColore(int id,COLORREF colore)
{
	CRect r;
	CBrush b(colore);
	CWnd *pWnd=GetDlgItem(id);
	CDC* pControlDC=pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pWnd->GetClientRect(r);
	CBrush* pOld=pControlDC->SelectObject(&b);
	pControlDC->Rectangle(r);
	pControlDC->SelectObject(pOld);
	pWnd->ReleaseDC(pControlDC);
}

void VrmlExpDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RinfColore(IDC_COLOR_DIFF,diffusec);
	RinfColore(IDC_COLOR_SPEC,specularc);
	RinfColore(IDC_COLOR_EMES,emittedc);
}
