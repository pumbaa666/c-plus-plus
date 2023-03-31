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
// SplitWndEx.cpp : implementation file
//

#include "stdafx.h"
#include "SpilinEditor.h"
#include "SplitWndEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitWndEx

CSplitWndEx::CSplitWndEx():
	m_WidthPercentage(50), m_HeightPercentage(50)
{
}

CSplitWndEx::~CSplitWndEx()
{
}


BEGIN_MESSAGE_MAP(CSplitWndEx, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitWndEx)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitWndEx message handlers

void CSplitWndEx::OnSize(UINT nType, int cx, int cy) 
{
	if(cx!=0 && cy!=0)
	{
		int firstRowHeight,firstColumnWidth,firstRowMinHeight,firstColumnMinWidth,temp,PrevHeight,PrevWidth;
		GetRowInfo(0,firstRowHeight,temp);
		GetColumnInfo(0,firstColumnWidth,temp);
		if(firstRowHeight>0 && firstColumnWidth>0)
		{
			int nRow=GetRowCount();
			int nColumn=GetColumnCount();
			if(nRow==2) GetRowInfo(1,firstRowMinHeight,temp);
			else firstRowMinHeight=0;
			if(nColumn==2) GetColumnInfo(1,firstColumnMinWidth,temp);
			else firstColumnMinWidth=0;
			PrevHeight=firstRowHeight+firstRowMinHeight;
			PrevWidth=firstColumnWidth+firstColumnMinWidth;
			temp=int(float(100.f*firstRowHeight/PrevHeight));
			m_HeightPercentage=temp>0?temp:int(float(100.f*firstRowMinHeight/PrevHeight));
			temp=int(float(100.f*firstColumnWidth/PrevWidth));
			m_WidthPercentage=temp>0?temp:int(float(100.f*firstColumnMinWidth/PrevWidth));
			CSplitterWnd::OnSize(nType, cx, cy);
			if(nColumn==2)
			{
				int width1=(cx-GetSplitterWidth())*m_WidthPercentage/100;
				int width2=(cx-GetSplitterWidth())*(100-m_WidthPercentage)/100;
				SetColumnInfo(0,width1,20);
				SetColumnInfo(1,width2,20);
			};
			if(nRow==2)
			{
				int height1=(cy-GetSplitterWidth())*m_HeightPercentage/100;
				int height2=(cy-GetSplitterWidth())*(100-m_HeightPercentage)/100;
				SetRowInfo(0,height1,10);
				SetRowInfo(1,height2,10);
			};
			RecalcLayout();
			GetRowInfo(0,firstRowHeight,firstRowMinHeight);
			GetColumnInfo(0,firstColumnWidth,firstColumnMinWidth);
		}
		else	CSplitterWnd::OnSize(nType, cx, cy);
	};
}

void CSplitWndEx::SetProportions(int height, int width)
{
	ASSERT(height>=0 && height<=100);
	ASSERT(width>=0 && width<=100);
	m_HeightPercentage=height;
	m_WidthPercentage=width;
}

BOOL CSplitWndEx::CreateView(int row, int col, CRuntimeClass * pViewClass, CCreateContext * pContext)
{
	ASSERT(row <=2 && col<=2);
	SIZE	size;
	CRect	rect;
	GetParent()->GetClientRect(&rect);
	if(col==0) size.cx=(rect.Width()-GetSplitterWidth())*m_WidthPercentage/100;
	else size.cx=(rect.Width()-GetSplitterWidth())*(100-m_WidthPercentage)/100;
	if(row==0) size.cy=(rect.Height()-GetSplitterWidth())*m_HeightPercentage/100;
	else size.cy=(rect.Height()-GetSplitterWidth())*(100-m_HeightPercentage)/100;
	if(GetRowCount()==1)	size.cy = rect.Height();
	if(GetColumnCount()==1)	size.cx=rect.Width();
	return CSplitterWnd::CreateView(row,col,pViewClass,size,pContext);
}
