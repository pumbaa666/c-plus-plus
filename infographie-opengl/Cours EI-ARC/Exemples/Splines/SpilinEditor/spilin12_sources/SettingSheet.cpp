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
// SettingSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SettingSheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingSheet

IMPLEMENT_DYNAMIC(CSettingSheet, CPropertySheet)

CSettingSheet::CSettingSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	//remove Apply and Help buttons
/*	m_Page1.m_psp.dwFlags&=(~PSP_HASHELP);
	m_Page2.m_psp.dwFlags&=(~PSP_HASHELP);
	m_Page3.m_psp.dwFlags&=(~PSP_HASHELP);
	m_Page4.m_psp.dwFlags&=(~PSP_HASHELP);*/
	m_psh.dwFlags|=PSH_NOAPPLYNOW;
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().
	
	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);
}

CSettingSheet::~CSettingSheet()
{
}


BEGIN_MESSAGE_MAP(CSettingSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSettingSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSettingSheet message handlers


