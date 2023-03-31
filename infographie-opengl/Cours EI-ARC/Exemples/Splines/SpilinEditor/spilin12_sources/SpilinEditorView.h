// SpilinEditorView.h : interface of the CSpilinEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPILINEDITORVIEW_H__6976DBCE_A493_11D1_80B1_977233DC2865__INCLUDED_)
#define AFX_SPILINEDITORVIEW_H__6976DBCE_A493_11D1_80B1_977233DC2865__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

struct SelElement{
		CPoint prevpun;
		CPoint actualpun;
		nodo* handle;
};

//#define _DUMP

class CSpilinEditorView : public CScrollView
{
private:
//	CSize DragOffset;
	CSpilinEditorDoc* pDoc;
	void Snapping(CPoint &point);
	CClientDC* cliDC;
	CRect SelectionRect;
	void segmento(nodo* [],CDC*);

protected: // create from serialization only
	BOOL snap;
	CSpilinEditorView(); //constructor
	DECLARE_DYNCREATE(CSpilinEditorView)

// Attributes
public:
	CPoint CenterOfSelection();
	void RotateSelVect(CPoint center,CSize offset);
	void FixSelVect();
	void TranslateSelVect(CSize offset);
	void DeleteSelVect();
	void CreateSelVect();
	int snapSize;
	int DimPenna;
	enum modalita {NIENTE,CREA,MODIFICA,INSERISCI,SELEZIONA,RUOTA,SCALA};
	CPalette m_cPalette;
	void creavpunt();
	void disegnasegm(const CPoint vpunt[],char numseg,BOOLEAN cancella);
	modalita stato;
	CPoint vpunt[5];
	int posdimodifica;
	CStatusBar* pStatus;
	CMainFrame* pFrame;
	CSpilinEditorDoc* GetDocument();

// Operations
public:
	void disegnacompleta(CDC* pDC);
	void disegnaspostnodo(CPoint mpoint);
	void Griglia(CDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpilinEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void MirrorSelVect(BOOL xdir);
	void SaveSettings();
	void RetrieveSettings();
	void disegnachiusa(CDC *pDC);
	BOOL IsMode(modalita modo) {return(stato==modo);};
	int SelVectorLenght;
	SelElement* SelVector;
	void DrawSelVect();
	BOOL drawnodespolygon;
	COLORREF gridcolor;
	COLORREF pencolor;
	COLORREF bgcolor;
	void SetMode(modalita modo) {stato=modo;};
	void ToggleGrid();
	virtual ~CSpilinEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
#ifdef _DUMP
	void DumpSelVect();
#endif

protected:

// Generated message map functions
protected:
	void ScaleSelVect(CPoint center,CSize offset);
	//{{AFX_MSG(CSpilinEditorView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnForceRedraw();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnUpdateSnap(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpilinEditorView.cpp
inline CSpilinEditorDoc* CSpilinEditorView::GetDocument()
   { return (CSpilinEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPILINEDITORVIEW_H__6976DBCE_A493_11D1_80B1_977233DC2865__INCLUDED_)
