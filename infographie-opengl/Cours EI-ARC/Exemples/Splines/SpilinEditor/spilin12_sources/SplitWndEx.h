#if !defined(AFX_SPLITWNDEX_H__524FC047_A3C8_11D1_80B1_8CAA5673107D__INCLUDED_)
#define AFX_SPLITWNDEX_H__524FC047_A3C8_11D1_80B1_8CAA5673107D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SplitWndEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplitWndEx window

class CSplitWndEx : public CSplitterWnd
{
//this is to prevent creation of dynamic splitter windows
private:
	BOOL Create( CWnd* pParentWnd, int nMaxRows, int nMaxCols, SIZE sizeMin, CCreateContext* pContext, DWORD dwStyle, UINT nID);
// Construction
public:
	CSplitWndEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitWndEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL CreateView( int row, int col, CRuntimeClass* pViewClass, CCreateContext* pContext );
	void SetProportions(int height,int width);
	int GetSplitterWidth() const { return m_cxSplitter; }
	virtual ~CSplitWndEx();

protected:
	int m_WidthPercentage;
	int m_HeightPercentage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitWndEx)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITWNDEX_H__524FC047_A3C8_11D1_80B1_8CAA5673107D__INCLUDED_)
