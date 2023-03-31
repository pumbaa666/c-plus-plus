// SpilinEditor.h : main header file for the SPILINEDITOR application
//

#if !defined(AFX_SPILINEDITOR_H__6976DBC6_A493_11D1_80B1_977233DC2865__INCLUDED_)
#define AFX_SPILINEDITOR_H__6976DBC6_A493_11D1_80B1_977233DC2865__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpilinEditorApp:
// See SpilinEditor.cpp for the implementation of this class
//

class CSpilinEditorApp : public CWinApp
{
public:
	CSpilinEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpilinEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpilinEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPILINEDITOR_H__6976DBC6_A493_11D1_80B1_977233DC2865__INCLUDED_)
