// SettingPages.h : header file
//

#ifndef __SETTINGPAGES_H__
#define __SETTINGPAGES_H__

void RinfColore(CWnd* pWind,COLORREF colore);

/////////////////////////////////////////////////////////////////////////////
// CEditorSettingPage dialog

class CEditorSettingPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditorSettingPage)
// Construction
public:
	COLORREF m_pencolor,m_gridcolor,m_bgcolor;
	CEditorSettingPage();
	~CEditorSettingPage();

// Dialog Data
	//{{AFX_DATA(CEditorSettingPage)
	enum { IDD = IDD_PROPPAGE1 };
	CStatic	m_pencolorswatch;
	CStatic	m_bgcolorswatch;
	CStatic	m_gridcolorswatch;
	CSpinButtonCtrl	m_pensizespin;
	CSpinButtonCtrl	m_gridsizespin;
	CSpinButtonCtrl	m_curvestepspin;
	int		m_curvesteps;
	BOOL	m_drawpolyg;
	int		m_gridsize;
	int		m_pensize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditorSettingPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditorSettingPage)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CObjectPage dialog

class CObjectPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CObjectPage)

// Construction
public:
	COLORREF m_objcolor;
	CObjectPage();
	~CObjectPage();

// Dialog Data
	//{{AFX_DATA(CObjectPage)
	enum { IDD = IDD_PROPPAGE2 };
	CStatic	m_objcolorswatch;
	CSpinButtonCtrl	m_sectionsspin;
	CSpinButtonCtrl	m_extrusionspin;
	CSpinButtonCtrl	m_3dstepsspin;
	int		m_3dsteps;
	int		m_sections;
	float	m_extrusion;
	BOOL	m_objbackcull;
	BOOL	m_objsmooth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CObjectPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CObjectPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CPreviewPage dialog

class CPreviewPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPreviewPage)

// Construction
public:
	COLORREF m_3dbgcolor;
	COLORREF m_gpcolor;
	COLORREF m_blcolor;
	COLORREF m_flcolor;
	CPreviewPage();
	~CPreviewPage();

// Dialog Data
	//{{AFX_DATA(CPreviewPage)
	enum { IDD = IDD_PROPPAGE3 };
	CStatic	m_gpcolorswatch;
	CStatic	m_flcolorswatch;
	CStatic	m_blcolorswatch;
	CStatic	m_3dbgcolorswatch;
	int		m_blpos;
	int		m_flpos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPreviewPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPreviewPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CPovExpPage dialog

class CPovExpPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPovExpPage)

// Construction
public:
	CPovExpPage();
	~CPovExpPage();

// Dialog Data
	//{{AFX_DATA(CPovExpPage)
	enum { IDD = IDD_PROPPAGE4 };
	CSpinButtonCtrl	m_proportionalspin;
	CSpinButtonCtrl	m_altezspin;
	BOOL	m_open;
	CString	m_objname;
	BOOL	m_conic;
	float	m_altez;
	BOOL	m_sturm;
	int		m_propfactor;
	int		m_proportional;
	int		m_ptype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPovExpPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPovExpPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnProportionalRadio();
	afx_msg void OnNormalizeRadio();
	afx_msg void OnSelendokPtypeCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void abilita(int cid);
	void disabilita(int cid);
};



#endif // __SETTINGPAGES_H__
