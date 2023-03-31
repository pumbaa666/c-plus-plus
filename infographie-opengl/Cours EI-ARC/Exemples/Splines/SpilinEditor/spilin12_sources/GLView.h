// GLView.h : header file
//
enum LightPosition {NW_LPOS,N_LPOS,NE_LPOS,W_LPOS,E_LPOS,SW_LPOS,S_LPOS,SE_LPOS};

/////////////////////////////////////////////////////////////////////////////
// CGLView view
class CGLView : public CView
{
private://data members
	float AspectRatio;
	float BackClipPlane;
	float FrontClipPlane;
	float distance;
	float ObjAngleY;
	float ObjAngleX;
	float ObjAngleZ;
	CPalette    *pOldPalette;
	CRect		ClientRect;
	CPalette    cPalette;
	CPoint MouseDownPoint;
	int GridDispList;

private:// helper functions
	HGLRC hrc;
	void SaveSettings();
	void RetrieveSettings();
	void SetCamera();
	void SetMaterials();
	void SetLights();

protected:
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void CreateRGBPalette();
	BOOLEAN bSetupPixelFormat();
	CGLView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGLView)

// Attributes
public:
	CSpilinEditorDoc* GetDocument();
	BOOL smoothshade;
	BOOL ShowGridPlane;
	COLORREF colpreview;
	COLORREF colfrontlight;
	COLORREF colbacklight;
	BOOL backcull;
	CSpilinEditorDoc::primitiva objtype;
	LightPosition FrontLightPos;
	LightPosition BackLightPos;

// Operations
public:
	void MakeCurrent();
	COLORREF bgcolor;
	COLORREF gpcolor;
	void ConstructGridPlane();
	void UpdateColors();
	void CGLView::ToggleSmoothShading() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUpdateSmoothShade(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpilinEditorView.cpp
inline CSpilinEditorDoc* CGLView::GetDocument()
   { return (CSpilinEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
