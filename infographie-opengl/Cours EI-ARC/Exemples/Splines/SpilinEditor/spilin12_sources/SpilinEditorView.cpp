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
// SpilinEditorView.cpp : implementation of the CSpilinEditorView class
//

#include "stdafx.h"
#include "SpilinEditor.h"
#include "math.h"

#include "Persist.h"
#include "SplitWndEx.h"
#include "MainFrm.h"
#include "undo.h"
#include "SpilinEditorDoc.h"
#include "SpilinEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpilinEditorView

IMPLEMENT_DYNCREATE(CSpilinEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CSpilinEditorView, CScrollView)
	//{{AFX_MSG_MAP(CSpilinEditorView)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_VISUAL_REDRAW, OnForceRedraw)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_UPDATE_COMMAND_UI(ID_SNAP, OnUpdateSnap)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpilinEditorView construction/destruction

CSpilinEditorView::CSpilinEditorView():
SelectionRect(0,0,0,0), snapSize(10),
drawnodespolygon(TRUE), snap(FALSE),
DimPenna(2), stato(CREA),
bgcolor(RGB(255,255,255)),pencolor(RGB(0,0,0)),gridcolor(RGB(127,127,127)),
SelVector(NULL), SelVectorLenght(0)
{
	for (int i=0;i<=4;i++) vpunt[i]=CPoint(0,0);
}

CSpilinEditorView::~CSpilinEditorView()
{
	DeleteSelVect();
}

BOOL CSpilinEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// retrieve registry saved settings
	RetrieveSettings();
	// setting of the default cursor  and background to null
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC , NULL, NULL, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSpilinEditorView drawing

void CSpilinEditorView::OnDraw(CDC* pDC)
{
	if (snap) Griglia(pDC);
	if (pDoc->echiusa()) disegnachiusa(pDC);
	else disegnacompleta(pDC);
}

void CSpilinEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	CSize TotalDim(1000,1000);
	CSize DimPag(TotalDim.cx/4,TotalDim.cy/4);
	CSize DimLine(TotalDim.cx/10,TotalDim.cy/10);
	SetScrollSizes(MM_TEXT,TotalDim,DimPag,DimLine);
	pDoc=GetDocument();
	pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	pStatus = &pFrame->m_wndStatusBar;
	posdimodifica=0;
}

/////////////////////////////////////////////////////////////////////////////
// CSpilinEditorView diagnostics

#ifdef _DEBUG
void CSpilinEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSpilinEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSpilinEditorDoc* CSpilinEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpilinEditorDoc)));
	return (CSpilinEditorDoc*)m_pDocument;
}
#endif //_DEBUG

#ifdef _DUMP
void CSpilinEditorView::DumpSelVect()
{
	if(SelVector != NULL && SelVectorLenght!=0)
		for(int i=0;i<SelVectorLenght;i++)
		{
			ASSERT(SelVector[i].handle != NULL);
			ASSERT(SelVector[i].handle->pun.x>=0 &&SelVector[i].handle->pun.y>=0);
			afxDump<<"SelVect["<<i<<"]: prevpun="<<SelVector[i].prevpun<<" actualpun="<<SelVector[i].actualpun<<" original="<<SelVector[i].handle->pun<<"\n";
		}
	else afxDump<<"Attenzione SelVector non valido!\n";
	afxDump<<"\t----------\n";
}
#endif //_DUMP
/////////////////////////////////////////////////////////////////////////////
// CSpilinEditorView message handlers

void CSpilinEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar) {
    case VK_HOME:
      OnVScroll(SB_TOP, 0, NULL);
      OnHScroll(SB_LEFT, 0, NULL);
      break;
    case VK_END:
      OnVScroll(SB_BOTTOM, 0, NULL);
      OnHScroll(SB_RIGHT, 0, NULL);
      break;
    case VK_UP:
	  OnVScroll(SB_LINEUP, 0, NULL);
      break;
    case VK_DOWN:
      OnVScroll(SB_LINEDOWN, 0, NULL);
      break;
    case VK_PRIOR:
      OnVScroll(SB_PAGEUP, 0, NULL);
      break;
    case VK_NEXT:
      OnVScroll(SB_PAGEDOWN, 0, NULL);
      break;
    case VK_LEFT:
      OnHScroll(SB_LINELEFT, 0, NULL);
      break;
    case VK_RIGHT:
      OnHScroll(SB_LINERIGHT, 0, NULL);
      break;
	case VK_TAB:
	  pDoc->SelectNextPoint();
	  Invalidate(TRUE);
	  break;
	case VK_DELETE:
	  pDoc->CancSelNodes();
	  break;
/*	case VK_NUMPAD8:
	  pDoc->SpostaSelectNodi(1,snapSize);
	  break;
	case VK_NUMPAD2:
	  pDoc->SpostaSelectNodi(2,snapSize);
	  break;
	case VK_NUMPAD4:
	  pDoc->SpostaSelectNodi(3,snapSize);
	  break;
	case VK_NUMPAD6:
	  pDoc->SpostaSelectNodi(4,snapSize);
	  break;
*/	default:
      break;
    }
}

void CSpilinEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	cliDC->DPtoLP(&point);
	Snapping(point);
	switch(stato)
	{
	case CREA: if (!pDoc->echiusa()) pDoc->aggnodo(point);
					else pStatus->SetPaneText(0,"You can't create new isolated points. Use Insert to add points to a closed spline!");
				break;
	case MODIFICA:	if(pDoc->pickcorrel(point))
					{
						if(SelVectorLenght!=0 && pDoc->IsCurrentSelected() ) vpunt[0]=point;
						else 
						{
							pDoc->SelectCurrent(FALSE);
							creavpunt();
							#ifdef _DEBUG
							TRACE("Modify Pos: %d\n",posdimodifica);
							for (int i=0;i<=4;i++) TRACE("vpunt[%d]=%d,%d\n",i,vpunt[i].x,vpunt[i].y);
							#endif
						};
						SetCapture();
					}
					else pDoc->SelectNoPoint();
				break;
	case RUOTA:	if(SelVectorLenght!=0)
				{
					vpunt[0]=point;
					vpunt[1]=CenterOfSelection();
					SetCapture();
				}
				break;
	case SCALA: if(SelVectorLenght!=0)
				{
					vpunt[0]=point;
					vpunt[1]=CenterOfSelection();
					SetCapture();
				}
				break;
	case INSERISCI: if(pDoc->inscorrel(point)) pDoc->inserisci(point);
				break;
	case SELEZIONA: SelectionRect=CRect(point,point);
					 DeleteSelVect();
					 SetCapture();
				break;
	};
}

void CSpilinEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(GetCapture()==this)
	{
		cliDC->DPtoLP(&point);
		Snapping(point);
		switch(stato)
		{
		case SELEZIONA: SelectionRect.right=point.x;
						 SelectionRect.bottom=point.y;
						 if((SelVectorLenght=pDoc->SelectInRect(SelectionRect))>1) CreateSelVect();
						 else SelVectorLenght=0;
						break;
		case SCALA: if(SelVectorLenght!=0)
						{
						FixSelVect();
						vpunt[0]=CPoint(0,0);
						};
						break;
		case RUOTA: if(SelVectorLenght!=0)
						{
						FixSelVect();
						vpunt[0]=CPoint(0,0);
					};
						break;
		case MODIFICA: 	if(SelVectorLenght==0)
						{
							pDoc->sostnodo(point);
							posdimodifica=0;
							for (int i=0;i<=4;i++) vpunt[i]=CPoint(0,0);
						}
						else
						{
							FixSelVect();
							vpunt[0]=CPoint(0,0);
//							DragOffset=CSize(0,0);
						};
						break;
		};
		ReleaseCapture();
		pDoc->UpdateAllViews(NULL);
	};
}

void CSpilinEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	cliDC->DPtoLP(&point);
	Snapping(point);
// print mouse coordinates on status bar
	CString coords;
	coords.Format("X:%d ; Y:%d",point.x,point.y);
	pStatus->SetPaneText(0, coords);
// if mouse buttons not pressed draw snapped cursor position
	if (snap && GetCapture()!=this)
	{
		CBrush *pOldBrush=(CBrush*)cliDC->SelectStockObject(BLACK_BRUSH);	
		CPen *pOldPen=(CPen*)cliDC->SelectStockObject(BLACK_PEN);
		int prev=cliDC->SetROP2(R2_NOTXORPEN);
			int ellDelta=DimPenna+2;
			cliDC->Ellipse(vpunt[0].x-ellDelta,vpunt[0].y-ellDelta,vpunt[0].x+ellDelta,vpunt[0].y+ellDelta);
			cliDC->Ellipse(point.x-ellDelta,point.y-ellDelta,point.x+ellDelta,point.y+ellDelta);
			vpunt[0]=point;
		cliDC->SetROP2(prev);
		cliDC->SelectObject(pOldBrush);
		cliDC->SelectObject(pOldPen);
	};
	if (GetCapture()==this)
	switch(stato)
	{
		case MODIFICA: if(SelVectorLenght==0) disegnaspostnodo(point);
						else
						{
							TranslateSelVect(point-vpunt[0]);
							DrawSelVect();
							vpunt[0]=point;
						}
						break;
		case SCALA: if(SelVectorLenght!=0)
					{
						ScaleSelVect(vpunt[1],point-vpunt[0]);
						DrawSelVect();
					}
					break;
		case RUOTA: if(SelVectorLenght!=0)
					{
						RotateSelVect(vpunt[1],point-vpunt[0]);
						DrawSelVect();
					}
					break;
		case SELEZIONA:	CPen selpen;
						if( !selpen.CreatePen(PS_DOT,1,RGB(0,0,0)) ) return;
						int prev=cliDC->SetROP2(R2_NOTXORPEN);
						cliDC->SetBkColor(bgcolor);
						CPen *pOldPen=cliDC->SelectObject(&selpen);
						cliDC->SelectStockObject(NULL_BRUSH);
						cliDC->Rectangle(SelectionRect);
						SelectionRect.right=point.x;
						SelectionRect.bottom=point.y;
						cliDC->Rectangle(SelectionRect);
						cliDC->SelectObject(pOldPen);
						cliDC->SetROP2(prev);
						break;
	};
}

void CSpilinEditorView::disegnacompleta(CDC* pDC)
{
	if (pDoc->nnodi() >=1)
	{
		CBrush redbru;
		if (!redbru.CreateSolidBrush(RGB(200,50,50))) return;
		CBrush greenbru;
		if (!greenbru.CreateSolidBrush(RGB(50,220,50))) return;
		CBrush gridbru;
		if (!gridbru.CreateSolidBrush(gridcolor)) return;
		CPen lightpen;
		if( !lightpen.CreatePen(PS_DOT,0,gridcolor) ) return;
		CPen thickpen;
		if( !thickpen.CreatePen(PS_SOLID,DimPenna,pencolor) ) return; 
		pDC->SetBkColor(bgcolor);
		// set the size of nodes circles
		int ellDelta=DimPenna+2;
		//draw the first node
		nodo *punt=pDoc->nprimo();
		pDC->MoveTo(punt->pun);
		CPen *pOldPen=(CPen*)pDC->SelectStockObject(BLACK_PEN);
		CBrush *pOldBrush=pDC->SelectObject(&gridbru);		
		pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
	  if (pDoc->nnodi()>=2)
	  {
		// draw the first and the last linear segments
		pDC->SelectObject(&lightpen);
		pDC->LineTo(punt->succ->pun);
		if (pDoc->nnodi()>=3)
		{
		punt=pDoc->nultimo();
		pDC->MoveTo(punt->pun);
		pDC->SelectObject(&lightpen);
		pDC->LineTo(punt->prec->pun);
		punt=punt->prec;
		pDC->SelectStockObject(BLACK_PEN);
		pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
		}
		if (pDoc->nnodi()>=4)
		{
	// draw the nodes and the nodes polygon
			punt=pDoc->nprimo()->succ;
			pDC->MoveTo(punt->pun);
			pDC->SelectStockObject(BLACK_PEN);
			do{					
				pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
				if(drawnodespolygon)
				{
					pDC->SelectObject(&lightpen);
					pDC->LineTo(punt->succ->pun);
					pDC->SelectStockObject(BLACK_PEN);
				};
				punt=punt->succ;
			}
			while (punt->succ->succ!=NULL);
	// draw the actual spline
			float ax,bx,cx,ay,by,cy,delta,x,dex,de2x,de3x,y,dey,de2y,de3y;
			nodo *vpunt[4];
			delta=float(1./pDoc->numsteps);
			vpunt[0]=pDoc->nprimo();
			vpunt[1]=vpunt[0]->succ;
			vpunt[2]=vpunt[1]->succ;
			vpunt[3]=vpunt[2]->succ;
			pDC->SelectObject(thickpen);
			while (vpunt[3]!=NULL)
			{
				ax=.5f*float((-vpunt[0]->pun.x+3*vpunt[1]->pun.x-3*vpunt[2]->pun.x+vpunt[3]->pun.x));
				bx=.5f*float((2*vpunt[0]->pun.x-5*vpunt[1]->pun.x+4*vpunt[2]->pun.x-vpunt[3]->pun.x));
				cx=.5f*float((-vpunt[0]->pun.x+vpunt[2]->pun.x));
				
				ay=.5f*float((-vpunt[0]->pun.y+3*vpunt[1]->pun.y-3*vpunt[2]->pun.y+vpunt[3]->pun.y));
				by=.5f*float((2*vpunt[0]->pun.y-5*vpunt[1]->pun.y+4*vpunt[2]->pun.y-vpunt[3]->pun.y));
				cy=.5f*float((-vpunt[0]->pun.y+vpunt[2]->pun.y));
			
				x=float(vpunt[1]->pun.x);
				dex=((ax*delta+bx)*delta+cx)*delta;
				de2x=(6*ax*delta+2*bx)*delta*delta;
				de3x=6*ax*delta*delta*delta;
				
				y=float(vpunt[1]->pun.y);
				dey=((ay*delta+by)*delta+cy)*delta;
				de2y=(6*ay*delta+2*by)*delta*delta;
				de3y=6*ay*delta*delta*delta;
				
				pDC->MoveTo(vpunt[1]->pun);
				for(int j=1;j<=pDoc->numsteps;j++)
				{
					x+=dex;
					dex+=de2x;
					de2x+=de3x;
					y+=dey;
					dey+=de2y;
					de2y+=de3y;
					pDC->LineTo(int(x),int(y));
				};
				vpunt[0]=vpunt[0]->succ;
				vpunt[1]=vpunt[1]->succ;
				vpunt[2]=vpunt[2]->succ;
				vpunt[3]=vpunt[3]->succ;
			};
		};
	};
	// disegno ultimo punto con un colore verde
	if(!pDoc->echiusa() )
	{
		punt=pDoc->nultimo();
		pDC->SelectObject(greenbru);
		pDC->SelectStockObject(BLACK_PEN);
		pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
	};
	// draw selected nodes
	punt=pDoc->nprimo();
	while (punt!=NULL)
	{
		if(punt->selected)
		{
			pDC->SelectObject(redbru);
			pDC->SelectStockObject(BLACK_PEN);
			pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
		}
		punt=punt->succ;
	};
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
  };
}

void CSpilinEditorView::Griglia(CDC* pDC)
{
	CPen gridp;
	if( !gridp.CreatePen(PS_SOLID,1,gridcolor) ) return;
	CPen *pOld=pDC->SelectObject(&gridp);
	for (int i=0;i<=1000;i+=snapSize)
		{
			pDC->MoveTo(i,0);
			pDC->LineTo(i,1000);
			pDC->MoveTo(0,i);
			pDC->LineTo(1000,i);
		};
	pDC->SelectObject(pOld);
}

void CSpilinEditorView::ToggleGrid()
{
	snap^=1;
	Invalidate(TRUE);	
}

void CSpilinEditorView::OnUpdateSnap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(snap);
}

void CSpilinEditorView::disegnaspostnodo(CPoint mpoint)
{
	if (GetCapture()==this)
	{
		CPen grayp;
		if( !grayp.CreatePen(PS_DOT,1,gridcolor) ) return;
		CPen gomma;
		if( !gomma.CreatePen(PS_SOLID,DimPenna,bgcolor) ) return;
		CPen boldp;
		if( !boldp.CreatePen(PS_SOLID,DimPenna,pencolor) ) return;
		cliDC->SetBkColor(bgcolor);
		CBrush *pOldBrush=cliDC->GetCurrentBrush();
		CPen *pOldPen=cliDC->GetCurrentPen();
		switch (pDoc->nnodi())
		{
		case 0: break;
		case 1: cliDC->SelectStockObject(WHITE_BRUSH);
				cliDC->SelectStockObject(WHITE_PEN);
				cliDC->Ellipse(vpunt[0].x-3,vpunt[0].y-3,vpunt[0].x+3,vpunt[0].y+3);
				cliDC->SelectStockObject(BLACK_PEN);
				cliDC->SelectStockObject(GRAY_BRUSH);
				cliDC->Ellipse(mpoint.x-3,mpoint.y-3,mpoint.x+3,mpoint.y+3);
				break;
		case 2: cliDC->SelectStockObject(GRAY_BRUSH);		
				switch (posdimodifica)
				{
				case 1:	cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[0]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(mpoint);
						break;
				case 2: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[0]);
						cliDC->LineTo(vpunt[1]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[0]);
						cliDC->LineTo(mpoint);
						break;
				default: while (AfxMessageBox("   Error in function disegnaspostnodo()!\nCase 2",MB_OK | MB_ICONEXCLAMATION) !=IDOK);
				}
		break;
		case 3: cliDC->SelectStockObject(GRAY_BRUSH);		
				switch (posdimodifica)
				{
				case 1:	cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[0]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(mpoint);
						break;
				case 3:	cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[2]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(mpoint);
						break;
				case 2: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[0]);
						cliDC->LineTo(vpunt[1]);
						cliDC->LineTo(vpunt[2]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[0]);
						cliDC->LineTo(mpoint);
						cliDC->LineTo(vpunt[2]);
						break;
				default: while (AfxMessageBox("   Error in function disegnaspostnodo()!\nCase 3",MB_OK | MB_ICONEXCLAMATION) !=IDOK);
				};
		break;
		case 4: cliDC->SelectStockObject(GRAY_BRUSH);		
				switch (posdimodifica)
				{
				case 1: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[0]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(mpoint);
						break;
				case 2: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[0]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[0]);
						cliDC->LineTo(mpoint);
						disegnasegm(vpunt,1,TRUE);
						cliDC->SelectObject(grayp);
						vpunt[1]=mpoint;
						disegnasegm(vpunt,1,FALSE);
						break;
				case 3: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[2]);
						cliDC->LineTo(vpunt[3]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[3]);
						cliDC->LineTo(mpoint);
						disegnasegm(vpunt,1,TRUE);
						cliDC->SelectObject(grayp);
						vpunt[2]=mpoint;
						disegnasegm(vpunt,1,FALSE);
						break;
				case 4:	cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[2]);
						cliDC->LineTo(vpunt[3]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[2]);
						cliDC->LineTo(mpoint);
						break;
				default: while (AfxMessageBox("   Error in function disegnaspostnodo()!\nCase 4",MB_OK | MB_ICONEXCLAMATION) !=IDOK);
				};
		break;
		default: switch (posdimodifica)
				{
				case 1: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[0]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(mpoint);
						disegnasegm(vpunt,2,TRUE);
						vpunt[posdimodifica-1]=mpoint;
						disegnasegm(vpunt,2,FALSE);
						break;
				case 2: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[1]);
						cliDC->LineTo(vpunt[0]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[0]);
						cliDC->LineTo(mpoint);
						disegnasegm(vpunt,2,TRUE);
						vpunt[posdimodifica-1]=mpoint;
						disegnasegm(vpunt,2,FALSE);
						break;
				case 4: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[3]);
						cliDC->LineTo(vpunt[4]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[4]);
						cliDC->LineTo(mpoint);
						disegnasegm(vpunt,2,TRUE);
						vpunt[posdimodifica-1]=mpoint;
						disegnasegm(vpunt,2,FALSE);
						break;
				case 5: cliDC->SelectObject(gomma);
						cliDC->MoveTo(vpunt[3]);
						cliDC->LineTo(vpunt[4]);
						cliDC->SelectObject(grayp);
						cliDC->MoveTo(vpunt[3]);
						cliDC->LineTo(mpoint);
						disegnasegm(vpunt,2,TRUE);
						vpunt[posdimodifica-1]=mpoint;
						disegnasegm(vpunt,2,FALSE);
						break;
				case 3: disegnasegm(vpunt,2,TRUE);
						vpunt[posdimodifica-1]=mpoint;
						disegnasegm(vpunt,2,FALSE);
						break;
				default: while (AfxMessageBox("   Error in function disegnaspostnodo()!\nCase 5",MB_OK | MB_ICONEXCLAMATION) !=IDOK);
				};
		};
		vpunt[posdimodifica-1]=mpoint;
		cliDC->SelectObject(pOldBrush);
		cliDC->SelectObject(pOldPen);
	};
}

void CSpilinEditorView::disegnasegm(const CPoint vpunt[],char numseg,BOOLEAN cancella)
{
	float ax,bx,cx,ay,by,cy,delta,x,dex,de2x,de3x,y,dey,de2y,de3y;
	delta=float(1./pDoc->numsteps);
	cliDC->MoveTo(vpunt[1]);
	CPen gomma;
	if( !gomma.CreatePen(PS_SOLID,DimPenna,bgcolor) ) return;
	CPen boldp;
	if( !boldp.CreatePen(PS_SOLID,DimPenna,pencolor) ) return; 
	CPen* pOldPen;
	if (cancella)  pOldPen=cliDC->SelectObject(&gomma);
	else pOldPen=cliDC->SelectObject(&boldp);
	cliDC->SetBkColor(bgcolor);
	for (int i=0;i<numseg;i++)
	{
	ax=float(.5*(-vpunt[i].x+3*vpunt[i+1].x-3*vpunt[i+2].x+vpunt[i+3].x));
	bx=float(.5*(2*vpunt[i].x-5*vpunt[i+1].x+4*vpunt[i+2].x-vpunt[i+3].x));
	cx=float(.5*(-vpunt[i].x+vpunt[i+2].x));

	ay=float(.5*(-vpunt[i].y+3*vpunt[i+1].y-3*vpunt[i+2].y+vpunt[i+3].y));
	by=float(.5*(2*vpunt[i].y-5*vpunt[i+1].y+4*vpunt[i+2].y-vpunt[i+3].y));
	cy=float(.5*(-vpunt[i].y+vpunt[i+2].y));

	x=float(vpunt[i+1].x);
	dex=((ax*delta+bx)*delta+cx)*delta;
	de2x=(6*ax*delta+2*bx)*delta*delta;
	de3x=6*ax*delta*delta*delta;
		
	y=float(vpunt[i+1].y);
	dey=((ay*delta+by)*delta+cy)*delta;
	de2y=(6*ay*delta+2*by)*delta*delta;
	de3y=6*ay*delta*delta*delta;
		
		cliDC->MoveTo(vpunt[i+1]);
		for(int j=1;j<=pDoc->numsteps;j++)
		{
			x+=dex;
			dex+=de2x;
			de2x+=de3x;
			y+=dey;
			dey+=de2y;
			de2y+=de3y;
			cliDC->LineTo(int(x),int(y));
		};
	};
	cliDC->SelectObject(pOldPen);
}

void CSpilinEditorView::creavpunt()
{
nodo* corr=pDoc->ncorr();
nodo* prim=pDoc->nprimo();
if(corr!=NULL)
{
switch(pDoc->nnodi())
{
case 1: vpunt[0]=corr->pun;
		posdimodifica=1;
		break;
case 2: vpunt[0]=prim->pun;
		vpunt[1]=prim->succ->pun;
		if (corr->prec==NULL) {posdimodifica=1;}
		else {posdimodifica=2;};
		break;
case 3: vpunt[0]=prim->pun;
		vpunt[1]=prim->succ->pun;
		vpunt[2]=prim->succ->succ->pun;
		if (corr->prec==NULL) {posdimodifica=1;}
		else if (corr->succ==NULL) {posdimodifica=3;}
			 else {posdimodifica=2;};
		break;
case 4: vpunt[0]=prim->pun;
		vpunt[1]=prim->succ->pun;
		vpunt[2]=prim->succ->succ->pun;
		vpunt[3]=prim->succ->succ->succ->pun;
		if(corr->succ==NULL){posdimodifica=4;}
		else if (corr->succ->succ==NULL){posdimodifica=3;}
			 else if (corr->prec==NULL){posdimodifica=1;}
				  else {posdimodifica=2;};
		break;
default: if(corr->succ==NULL)
		{
			if(pDoc->echiusa()){
			posdimodifica=3;
			vpunt[0]=corr->prec->prec->pun;
			vpunt[1]=corr->prec->pun;
			vpunt[2]=corr->pun;
			vpunt[3]=pDoc->nprimo()->pun;
			vpunt[4]=pDoc->nprimo()->succ->pun;
			}
			else{
			posdimodifica=5;
			vpunt[0]=corr->prec->prec->prec->prec->pun;
			vpunt[1]=corr->prec->prec->prec->pun;
			vpunt[2]=corr->prec->prec->pun;
			vpunt[3]=corr->prec->pun;
			vpunt[4]=corr->pun;
			}
		}
		else if (corr->succ->succ==NULL)
			{
				if(pDoc->echiusa()){
				posdimodifica=3;
				vpunt[0]=corr->prec->prec->pun;
				vpunt[1]=corr->prec->pun;
				vpunt[2]=corr->pun;
				vpunt[3]=corr->succ->pun;
				vpunt[4]=pDoc->nprimo()->pun;
				}
				else{
				posdimodifica=4;
				vpunt[0]=corr->prec->prec->prec->pun;
				vpunt[1]=corr->prec->prec->pun;
				vpunt[2]=corr->prec->pun;
				vpunt[3]=corr->pun;
				vpunt[4]=corr->succ->pun;
				}
			}
			else if (corr->prec==NULL)
				{
					if(pDoc->echiusa()){
					posdimodifica=3;
					vpunt[0]=pDoc->nultimo()->prec->pun;
					vpunt[1]=pDoc->nultimo()->pun;
					vpunt[2]=corr->pun;
					vpunt[3]=corr->succ->pun;
					vpunt[4]=corr->succ->succ->pun;
					}
					else{
					posdimodifica=1;
					vpunt[0]=corr->pun;
					vpunt[1]=corr->succ->pun;
					vpunt[2]=corr->succ->succ->pun;
					vpunt[3]=corr->succ->succ->succ->pun;
					vpunt[4]=corr->succ->succ->succ->succ->pun;
					}
				}
				else if(corr->prec->prec==NULL)
					{
						if(pDoc->echiusa()){
						posdimodifica=3;
						vpunt[0]=pDoc->nultimo()->pun;
						vpunt[1]=corr->prec->pun;
						vpunt[2]=corr->pun;
						vpunt[3]=corr->succ->pun;
						vpunt[4]=corr->succ->succ->pun;
						}
						else{
						posdimodifica=2;
						vpunt[0]=corr->prec->pun;
						vpunt[1]=corr->pun;
						vpunt[2]=corr->succ->pun;
						vpunt[3]=corr->succ->succ->pun;
						vpunt[4]=corr->succ->succ->succ->pun;
						}
					}
					else
					{
						posdimodifica=3;
						vpunt[0]=corr->prec->prec->pun;
						vpunt[1]=corr->prec->pun;
						vpunt[2]=corr->pun;
						vpunt[3]=corr->succ->pun;
						vpunt[4]=corr->succ->succ->pun;
					};
};
};
}

void CSpilinEditorView::OnForceRedraw() 
{
	Invalidate(TRUE);	
}

int CSpilinEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// contesto grafico
	cliDC = new CClientDC(this);
	ASSERT(cliDC != NULL);
	return 0;
}

void CSpilinEditorView::OnDestroy() 
{
	// deletes Client Device Context pointer
    if (cliDC) delete cliDC;
	// store settings in registry
	SaveSettings();

	CScrollView::OnDestroy();
}

void CSpilinEditorView::segmento(nodo* vpunt[],CDC* pDC)
{
	float ax,bx,cx,ay,by,cy,x,dex,de2x,de3x,y,dey,de2y,de3y;
	float delta=float(1./pDoc->numsteps);
	ax=float(.5*(-vpunt[0]->pun.x+3*vpunt[1]->pun.x-3*vpunt[2]->pun.x+vpunt[3]->pun.x));
	bx=float(.5*(2*vpunt[0]->pun.x-5*vpunt[1]->pun.x+4*vpunt[2]->pun.x-vpunt[3]->pun.x));
	cx=float(.5*(-vpunt[0]->pun.x+vpunt[2]->pun.x));
	
	ay=float(.5*(-vpunt[0]->pun.y+3*vpunt[1]->pun.y-3*vpunt[2]->pun.y+vpunt[3]->pun.y));
	by=float(.5*(2*vpunt[0]->pun.y-5*vpunt[1]->pun.y+4*vpunt[2]->pun.y-vpunt[3]->pun.y));
	cy=float(.5*(-vpunt[0]->pun.y+vpunt[2]->pun.y));

	x=float(vpunt[1]->pun.x);
	dex=ax*delta*delta*delta+bx*delta*delta+cx*delta;
	de2x=6*ax*delta*delta*delta+2*bx*delta*delta;
	de3x=6*ax*delta*delta*delta;
	
	y=float(vpunt[1]->pun.y);
	dey=ay*delta*delta*delta+by*delta*delta+cy*delta;
	de2y=6*ay*delta*delta*delta+2*by*delta*delta;
	de3y=6*ay*delta*delta*delta;
	
	pDC->MoveTo(vpunt[1]->pun);
	for(int j=1;j<=pDoc->numsteps;j++)
	{
		x+=dex;
		dex+=de2x;
		de2x+=de3x;
		y+=dey;
		dey+=de2y;
		de2y+=de3y;
		pDC->LineTo(int(x),int(y));
	};
}

void CSpilinEditorView::Snapping(CPoint &point)
{
	if (snap)
	{
		if ( point.x%snapSize > (snapSize/2) ) point.x+=snapSize-point.x%snapSize;
		else point.x-=point.x%snapSize;
		if ( point.y%snapSize > (snapSize/2) ) point.y+=snapSize-point.y%snapSize;
		else point.y-=point.y%snapSize;
	};
}

BOOL CSpilinEditorView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	OnPrepareDC(cliDC);
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}

BOOL CSpilinEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (pWnd==this && nHitTest==HTCLIENT)
	switch (stato)
	{
	case CREA: ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_CREA));
				return TRUE;
				break;
	case MODIFICA: ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_MODIF));
				return TRUE;
				break;
	case INSERISCI: ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_INSER));
				return TRUE;
				break;
	case SELEZIONA: ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
				return TRUE;
	case RUOTA: ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_ROTATE));
				return TRUE;
	case SCALA: ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_SCALE));
				return TRUE;
				break;
	};
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CSpilinEditorView::OnEraseBkgnd(CDC* pDC) 
{
	CBrush backbru;
	if(backbru.CreateSolidBrush(bgcolor))
	{
		CBrush* pOldBrush=pDC->SelectObject(&backbru);
		pDC->Rectangle(0,0,1000,1000);
		pDC->SelectObject(pOldBrush);
	};
	return TRUE;
}

void CSpilinEditorView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_SPILIN_EDITOR_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CSpilinEditorView::CreateSelVect()
{
	if(SelVectorLenght!=0 && SelVector==NULL)
	{
		SelVector=new SelElement[SelVectorLenght];
		nodo* pnod=pDoc->nprimo();
		int i=0;
		while (pnod!=NULL)
		{
			if( pnod->selected)
			{
				SelVector[i].prevpun=CPoint(-5,-5);
				SelVector[i].actualpun=pnod->pun;
				SelVector[i++].handle=pnod;
			};
			pnod=pnod->succ;
		};
#ifdef _DUMP
	afxDump<<"Create:\n";
	DumpSelVect();
#endif
	}
}

void CSpilinEditorView::DeleteSelVect()
{
	if(SelVectorLenght!=0 && SelVector != NULL)
	{
		#ifdef _DUMP
			afxDump<<"Delete:\n";
			DumpSelVect();
		#endif
		delete[] SelVector;
		SelVector=NULL;
		SelVectorLenght=0;
	}
}

void CSpilinEditorView::TranslateSelVect(CSize offset)
{
	ASSERT(SelVector != NULL && SelVectorLenght!=0);
	for(int i=0;i<SelVectorLenght;i++)
	{
		SelVector[i].actualpun=(SelVector[i].prevpun=SelVector[i].actualpun)+offset;
	};
}

void CSpilinEditorView::FixSelVect()
{
	ASSERT(SelVector != NULL && SelVectorLenght!=0);
	#ifdef _DUMP
		afxDump<<"Fix & Clamp:\n";
		DumpSelVect();
	#endif
	for(int i=0;i<SelVectorLenght;i++)
	{
		ASSERT(SelVector[i].handle != NULL);
		SelVector[i].handle->pun.x=SelVector[i].actualpun.x>0?SelVector[i].actualpun.x:0;
		SelVector[i].handle->pun.y=SelVector[i].actualpun.y>0?SelVector[i].actualpun.y:0;
	};
	pDoc->FixSelDocVect();
}

void CSpilinEditorView::ScaleSelVect(CPoint center, CSize offset)
{
	ASSERT(SelVector != NULL && SelVectorLenght!=0);
	float factor=1.0f+offset.cx/50.0f;
	for(int i=0;i<SelVectorLenght;i++)
	{
		ASSERT(SelVector[i].handle != NULL);
		SelVector[i].prevpun=SelVector[i].actualpun;
		SelVector[i].actualpun.x=center.x+long( float(SelVector[i].handle->pun.x-center.x)*factor) ;
		SelVector[i].actualpun.y=center.y+long( float(SelVector[i].handle->pun.y-center.y)*factor );
	};
}

void CSpilinEditorView::RotateSelVect(CPoint center,CSize offset)
{
	ASSERT(SelVector != NULL && SelVectorLenght!=0);
	double cosine=cos(offset.cx*3.14159265359/200);
	double sine=sin(offset.cx*3.14159265359/200);
	for(int i=0;i<SelVectorLenght;i++)
	{
		ASSERT(SelVector[i].handle != NULL);
		SelVector[i].prevpun=SelVector[i].actualpun;
		SelVector[i].actualpun.x=center.x+long(sine*(center.y-SelVector[i].handle->pun.y)+cosine*(SelVector[i].handle->pun.x-center.x));
		SelVector[i].actualpun.y=center.y+long(sine*(SelVector[i].handle->pun.x-center.x)+cosine*(SelVector[i].handle->pun.y-center.y));
	};
}

CPoint CSpilinEditorView::CenterOfSelection()
{
	CPoint centro(0,0);
	ASSERT(SelVector != NULL && SelVectorLenght!=0);
	for(int i=0;i<SelVectorLenght;i++)
	{
		ASSERT(SelVector[i].handle != NULL);
		centro+=SelVector[i].actualpun;
	};
	centro.x/=SelVectorLenght;
	centro.y/=SelVectorLenght;
	return centro;
//	else TRACE("CenterOfSelection: No valid selection to operate on\n");
//	return CPoint(-5,-5);
}

void CSpilinEditorView::DrawSelVect()
{
	if(SelVector != NULL && SelVectorLenght!=0)
	{
		CBrush gomma;
		int ellDelta=DimPenna+2;
		if( !gomma.CreateSolidBrush(bgcolor) ) return;
		CBrush *pOldBrush=(CBrush*)cliDC->GetCurrentBrush();
		CPen *pOldPen=(CPen*)cliDC->SelectStockObject(NULL_PEN);
		int prev=cliDC->SetROP2(R2_NOT);
		for(int i=0;i<SelVectorLenght;i++)
		{
			cliDC->SelectObject(gomma);
			cliDC->Ellipse(SelVector[i].prevpun.x-ellDelta,SelVector[i].prevpun.y-ellDelta,SelVector[i].prevpun.x+ellDelta,SelVector[i].prevpun.y+ellDelta);
			cliDC->SelectStockObject(BLACK_BRUSH);
			cliDC->Ellipse(SelVector[i].actualpun.x-ellDelta,SelVector[i].actualpun.y-ellDelta,SelVector[i].actualpun.x+ellDelta,SelVector[i].actualpun.y+ellDelta);
		};
		cliDC->SelectObject(pOldPen);
		cliDC->SelectObject(pOldBrush);
		cliDC->SetROP2(prev);
	}
}

void CSpilinEditorView::disegnachiusa(CDC * pDC)
{
	ASSERT(pDoc->nnodi() >=3);
	CBrush redbru;
	if (!redbru.CreateSolidBrush(RGB(200,50,50))) return;
	CBrush greenbru;
	if (!greenbru.CreateSolidBrush(RGB(50,220,50))) return;
	CBrush gridbru;
	if (!gridbru.CreateSolidBrush(gridcolor)) return;
	CPen lightpen;
	if( !lightpen.CreatePen(PS_DOT,0,gridcolor) ) return;
	CPen thickpen;
	if( !thickpen.CreatePen(PS_SOLID,DimPenna,pencolor) ) return; 
	pDC->SetBkColor(bgcolor);
	// set the size of nodes circles
	int ellDelta=DimPenna+2;
	//draw the nodes and the linear segments
	nodo *punt=pDoc->nprimo();
	pDC->MoveTo(punt->pun);
	CPen *pOldPen=(CPen*)pDC->SelectStockObject(BLACK_PEN);
	CBrush *pOldBrush=pDC->SelectObject(&gridbru);		
	do{					
		pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
		if(drawnodespolygon)
		{
			pDC->SelectObject(&lightpen);
			pDC->LineTo(punt->succ->pun);
			pDC->SelectStockObject(BLACK_PEN);
		};
		punt=punt->succ;
	}
	while (punt->succ!=NULL);
// draw the last node and the closing linear segment
	punt=pDoc->nultimo();
	pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
	pDC->SelectObject(&lightpen);
	pDC->LineTo(pDoc->nprimo()->pun);
// draw the actual spline
	float ax,bx,cx,ay,by,cy,delta,x,dex,de2x,de3x,y,dey,de2y,de3y;
	nodo *vpunt[4];
	delta=float(1./pDoc->numsteps);
	if (pDoc->nnodi()==3){
		vpunt[0]=pDoc->nprimo();
		vpunt[1]=vpunt[0]->succ;
		vpunt[2]=vpunt[1]->succ;
		vpunt[3]=vpunt[0];
	}
	else{
		vpunt[0]=pDoc->nprimo();
		vpunt[1]=vpunt[0]->succ;
		vpunt[2]=vpunt[1]->succ;
		vpunt[3]=vpunt[2]->succ;
	};
	pDC->SelectObject(thickpen);
	do{
		ax=.5f*float((-vpunt[0]->pun.x+3*vpunt[1]->pun.x-3*vpunt[2]->pun.x+vpunt[3]->pun.x));
		bx=.5f*float((2*vpunt[0]->pun.x-5*vpunt[1]->pun.x+4*vpunt[2]->pun.x-vpunt[3]->pun.x));
		cx=.5f*float((-vpunt[0]->pun.x+vpunt[2]->pun.x));
		
		ay=.5f*float((-vpunt[0]->pun.y+3*vpunt[1]->pun.y-3*vpunt[2]->pun.y+vpunt[3]->pun.y));
		by=.5f*float((2*vpunt[0]->pun.y-5*vpunt[1]->pun.y+4*vpunt[2]->pun.y-vpunt[3]->pun.y));
		cy=.5f*float((-vpunt[0]->pun.y+vpunt[2]->pun.y));
	
		x=float(vpunt[1]->pun.x);
		dex=((ax*delta+bx)*delta+cx)*delta;
		de2x=(6*ax*delta+2*bx)*delta*delta;
		de3x=6*ax*delta*delta*delta;
		
		y=float(vpunt[1]->pun.y);
		dey=((ay*delta+by)*delta+cy)*delta;
		de2y=(6*ay*delta+2*by)*delta*delta;
		de3y=6*ay*delta*delta*delta;
		
		pDC->MoveTo(vpunt[1]->pun);
		for(int j=1;j<=pDoc->numsteps;j++)
		{
			x+=dex;
			dex+=de2x;
			de2x+=de3x;
			y+=dey;
			dey+=de2y;
			de2y+=de3y;
			pDC->LineTo(int(x),int(y));
		};
		vpunt[0]=vpunt[0]->succ!=NULL ? vpunt[0]->succ : pDoc->nprimo();
		vpunt[1]=vpunt[1]->succ!=NULL ? vpunt[1]->succ : pDoc->nprimo();
		vpunt[2]=vpunt[2]->succ!=NULL ? vpunt[2]->succ : pDoc->nprimo();
		vpunt[3]=vpunt[3]->succ!=NULL ? vpunt[3]->succ : pDoc->nprimo();
	}
	while (vpunt[0]!=pDoc->nprimo());
	// draw selected nodes
	punt=pDoc->nprimo();
	while (punt!=NULL)
	{
		if(punt->selected)
		{
			pDC->SelectObject(redbru);
			pDC->SelectStockObject(BLACK_PEN);
			pDC->Ellipse(punt->pun.x-ellDelta,punt->pun.y-ellDelta,punt->pun.x+ellDelta,punt->pun.y+ellDelta);
		}
		punt=punt->succ;
	};
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CSpilinEditorView::RetrieveSettings()
{
	CWinApp* pApp=AfxGetApp();
	bgcolor=pApp->GetProfileInt("Settings", "BGcolor",0x00FFFFFF);
	pencolor=pApp->GetProfileInt("Settings", "PENcolor",0x00000000);
	gridcolor=pApp->GetProfileInt("Settings", "GRIDcolor",0x00777777);
	drawnodespolygon=pApp->GetProfileInt("Settings", "DrawPolygon",1);
	DimPenna=pApp->GetProfileInt("Settings", "PenSize",2);
	snapSize=pApp->GetProfileInt("Settings", "GridSize",10);
}

void CSpilinEditorView::SaveSettings()
{
	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileInt("Settings", "BGcolor",bgcolor);
	pApp->WriteProfileInt("Settings", "PENcolor",pencolor);
	pApp->WriteProfileInt("Settings", "GRIDcolor",gridcolor);
	pApp->WriteProfileInt("Settings", "DrawPolygon",drawnodespolygon);
	pApp->WriteProfileInt("Settings", "PenSize",DimPenna);
	pApp->WriteProfileInt("Settings", "GridSize",snapSize);
}

void CSpilinEditorView::MirrorSelVect(BOOL xdir)
{
	ASSERT(SelVectorLenght!=0 && SelVector!=NULL);
	CPoint centro=CenterOfSelection();
	if (centro.x>0)
	{
		if(xdir) // Mirror X
		{
			for(int i=0;i<SelVectorLenght;i++)
			{
				ASSERT(SelVector[i].handle != NULL);
				SelVector[i].actualpun.x=2*centro.x-SelVector[i].handle->pun.x;
			};
		}
		else {//Mirror Y
			for(int i=0;i<SelVectorLenght;i++)
			{
				ASSERT(SelVector[i].handle != NULL);
				SelVector[i].actualpun.y=2*centro.y-SelVector[i].handle->pun.y;
			};
		};
		FixSelVect();
		pDoc->CheckPoint();
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	};
}
