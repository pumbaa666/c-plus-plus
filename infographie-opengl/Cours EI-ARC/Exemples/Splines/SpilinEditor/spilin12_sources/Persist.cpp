/*****************************************************
Copyright Notice

Copyright � Alessandro Falappa

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
#include "stdafx.h"
#include "persist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////
// CPersistentFrame

const CRect CPersistentFrame::s_rectDefault(10, 10,610, 410);  // static
const char CPersistentFrame::s_profileHeading[] = "WindowPos";
const char CPersistentFrame::s_profileRect[] = "Rect";
const char CPersistentFrame::s_profileIcon[] = "iconized";
const char CPersistentFrame::s_profileMax[] = "maximized";
const char CPersistentFrame::s_profileTool[] = "tool";
const char CPersistentFrame::s_profileStatus[] = "status";
IMPLEMENT_DYNAMIC(CPersistentFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CPersistentFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CPersistentFrame)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////
CPersistentFrame::CPersistentFrame()
{
    m_bFirstTime = TRUE;
}

///////////////////////////////////////////////////////////////
CPersistentFrame::~CPersistentFrame()
{
}

///////////////////////////////////////////////////////////////
void CPersistentFrame::OnDestroy()
{
    CString strText;
    BOOL bIconic, bMaximized;

    WINDOWPLACEMENT wndpl;
    wndpl.length = sizeof(WINDOWPLACEMENT);
    // gets current window position and
    //  iconized/maximized status
    BOOL bRet = GetWindowPlacement(&wndpl);
    if (wndpl.showCmd == SW_SHOWNORMAL) {
      bIconic = FALSE;
      bMaximized = FALSE;
    }
    else if (wndpl.showCmd == SW_SHOWMAXIMIZED) {
      bIconic = FALSE;
      bMaximized = TRUE;
    } 
    else if (wndpl.showCmd == SW_SHOWMINIMIZED) {
      bIconic = TRUE;
      if (wndpl.flags) {
        bMaximized = TRUE;
      }
      else {
        bMaximized = FALSE;
      }
    }
    strText.Format("%04d %04d %04d %04d",
                   wndpl.rcNormalPosition.left,
                   wndpl.rcNormalPosition.top,
                   wndpl.rcNormalPosition.right,
                   wndpl.rcNormalPosition.bottom);
    AfxGetApp()->WriteProfileString(s_profileHeading,
                                    s_profileRect, strText);
    AfxGetApp()->WriteProfileInt(s_profileHeading,
                                 s_profileIcon, bIconic);
    AfxGetApp()->WriteProfileInt(s_profileHeading,
                                 s_profileMax, bMaximized);
// restoring toolbars seems not to function very well
//    SaveBarState(AfxGetApp()->m_pszProfileName);
    CFrameWnd::OnDestroy();
}

///////////////////////////////////////////////////////////////
void CPersistentFrame::ActivateFrame(int nCmdShow)
{
    CString strText;
    BOOL bIconic, bMaximized;
    UINT flags;
    WINDOWPLACEMENT wndpl;
    CRect rect;
 
    if (m_bFirstTime) {
      m_bFirstTime = FALSE;
      strText = AfxGetApp()->GetProfileString(s_profileHeading,
                                              s_profileRect);
        if (!strText.IsEmpty()) {
          rect.left = atoi((const char*) strText);
          rect.top = atoi((const char*) strText + 5);
          rect.right = atoi((const char*) strText + 10);
          rect.bottom = atoi((const char*) strText + 15);
        }
        else {
          rect = s_rectDefault;
        }
    
        bIconic = AfxGetApp()->GetProfileInt(s_profileHeading,
                                             s_profileIcon, 0);
        bMaximized = AfxGetApp()->GetProfileInt(s_profileHeading,
                                                s_profileMax, 0);
        TRACE("CPersistentFrame::ActivateFrame   bIconic = %d, bMaximized = %d\n", bIconic, bMaximized);
    
        if (bIconic) {
          nCmdShow = SW_SHOWMINNOACTIVE;
          if (bMaximized) {
            flags = WPF_RESTORETOMAXIMIZED;
          }
          else {
            flags = WPF_SETMINPOSITION;
          }
        }
        else {
          if (bMaximized) {
            nCmdShow = SW_SHOWMAXIMIZED;
            flags = WPF_RESTORETOMAXIMIZED;
          }
          else {
            nCmdShow = SW_NORMAL;
            flags = WPF_SETMINPOSITION;
          }
        }
        wndpl.length = sizeof(WINDOWPLACEMENT);
        wndpl.showCmd = nCmdShow;
        wndpl.flags = flags;
        wndpl.ptMinPosition = CPoint(0, 0);
        wndpl.ptMaxPosition =
            CPoint(-::GetSystemMetrics(SM_CXBORDER),
                   -::GetSystemMetrics(SM_CYBORDER));
        wndpl.rcNormalPosition = rect;
// restoring toolbars seems not to function very well
//		LoadBarState(AfxGetApp()->m_pszProfileName);
        // sets window's position and iconized/maximized status
        BOOL bRet = SetWindowPlacement(&wndpl);
    }
    CFrameWnd::ActivateFrame(nCmdShow);
}

BOOL CPersistentFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
    // TODO: Add your specialized code here
    //  and/or call the base class
//    cs.dwExStyle |= WS_EX_TOPMOST; // window always on top!
    return CFrameWnd::PreCreateWindow(cs);
}

