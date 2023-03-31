#if !defined(AFX_VRMLEXPDLG_H__EB1A5625_642E_11D1_93A1_8EA16F1DC630__INCLUDED_)
#define AFX_VRMLEXPDLG_H__EB1A5625_642E_11D1_93A1_8EA16F1DC630__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VrmlExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VrmlExpDlg dialog

class VrmlExpDlg : public CDialog
{
// Construction
public:
	void RinfColore(int id, COLORREF colore);
	COLORREF emittedc;
	COLORREF specularc;
	COLORREF diffusec;
	BOOL OnInitDialog();
	VrmlExpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(VrmlExpDlg)
	enum { IDD = IDD_VRML_OPTIONS };
	CSpinButtonCtrl	m_radiuspin;
	CSpinButtonCtrl	m_creasespin;
	CSpinButtonCtrl	m_stepspin;
	CSpinButtonCtrl	m_sezspin;
	int		m_sez;
	int		m_splstep;
	float	m_shininess;
	float	m_transparency;
	int		m_crease;
	BOOL	m_verso;
	int		m_radius;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VrmlExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VrmlExpDlg)
	afx_msg void OnColorDiffuse();
	afx_msg void OnColorSpecular();
	afx_msg void OnColorEmitted();
	afx_msg void OnPaint();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VRMLEXPDLG_H__EB1A5625_642E_11D1_93A1_8EA16F1DC630__INCLUDED_)
