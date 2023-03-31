// SettingSheet.h : header file
//
// This class defines custom modal property sheet 
// CSettingSheet.
 
#ifndef __SETTINGSHEET_H__
#define __SETTINGSHEET_H__

#include "SettingPages.h"

/////////////////////////////////////////////////////////////////////////////
// CSettingSheet

class CSettingSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSettingSheet)

// Construction
public:
	CSettingSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CEditorSettingPage m_Page1;
	CObjectPage m_Page2;
	CPreviewPage m_Page3;
	CPovExpPage m_Page4;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSettingSheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CSettingSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __SETTINGSHEET_H__
