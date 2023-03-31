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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SpilinEditor.h"

#include "Persist.h"
#include "SplitWndEx.h"
#include "MainFrm.h"
#include "undo.h"
#include "SpilinEditorDoc.h"
#include "SpilinEditorView.h"
#include "GLView.h"
#include "KeyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CPersistentFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CPersistentFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_COMMAND(IDD_KEY_HELP, OnKeyHelp)
	ON_COMMAND(ID_VIEW_PREVIEWBAR, OnViewPreviewbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIEWBAR, OnUpdateViewPreviewbar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_POLYGONS,	// polygons indicator
	ID_INDICATOR_NODI,		// nodes number indicator
	ID_INDICATOR_STEPS		// spline steps indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndPreviewBar.Create(this) ||
		!m_wndPreviewBar.LoadToolBar(IDR_PREVIEWBAR))
	{
		TRACE0("Failed to create previewbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// make status bar indicators embossed	
	m_wndStatusBar.SetPaneStyle(1,m_wndStatusBar.GetPaneStyle(1) | CBRS_BORDER_RIGHT);
	m_wndStatusBar.SetPaneStyle(2,m_wndStatusBar.GetPaneStyle(2) | CBRS_BORDER_RIGHT);
	m_wndStatusBar.SetPaneStyle(3,m_wndStatusBar.GetPaneStyle(3) | CBRS_BORDER_RIGHT);

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndPreviewBar.SetBarStyle(m_wndPreviewBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	// Set toolbars titles
	m_wndToolBar.SetWindowText(_T("EditBar") );
	m_wndPreviewBar.SetWindowText(_T("PreviewBar") );

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	m_wndPreviewBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP);
	DockControlBarLeftOf(&m_wndPreviewBar,&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_wndSplitter.SetProportions(100,70);
	if(m_wndSplitter.CreateStatic( this,1, 2 ))
	{
		m_wndSplitter.CreateView(0,0,pContext->m_pNewViewClass,pContext);
		m_wndSplitter.CreateView(0,1,RUNTIME_CLASS( CGLView ),pContext);
		SetActiveView((CView *)m_wndSplitter.GetPane(0,1));
		CSpilinEditorDoc* pDoc=STATIC_DOWNCAST(CSpilinEditorDoc,GetActiveDocument());
		pDoc->pEditView=STATIC_DOWNCAST(CSpilinEditorView,m_wndSplitter.GetPane(0,0));
		pDoc->pGLView=STATIC_DOWNCAST(CGLView,m_wndSplitter.GetPane(0,1));
		m_wndSplitter.ShowWindow(SW_SHOWNORMAL);
		m_wndSplitter.UpdateWindow();
		return TRUE;
	}
	return FALSE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::DockControlBarLeftOf(CToolBar * Bar, CToolBar * LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	DockControlBar(Bar,n,&rect);
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CPersistentFrame::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this) OnQueryNewPalette();
	
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	WORD   i;
	CPalette   *pOldPal;
	CSpilinEditorView *pView = (CSpilinEditorView *)GetActiveView();
	CClientDC   dc(pView);

	pOldPal = dc.SelectPalette(&pView->m_cPalette, FALSE);
	i = dc.RealizePalette();
	dc.SelectPalette(pOldPal, FALSE);

	if (i > 0) InvalidateRect(NULL);

	return CPersistentFrame::OnQueryNewPalette();
}

void CMainFrame::OnKeyHelp() 
{
	CKeyDialog kd;
	kd.DoModal();
}

void CMainFrame::OnViewPreviewbar()  
{
	if(m_wndPreviewBar.IsWindowVisible())
		ShowControlBar(&m_wndPreviewBar,FALSE,FALSE);
	else
		ShowControlBar(&m_wndPreviewBar,TRUE,FALSE);
}

void CMainFrame::OnUpdateViewPreviewbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndPreviewBar.IsWindowVisible());
}
