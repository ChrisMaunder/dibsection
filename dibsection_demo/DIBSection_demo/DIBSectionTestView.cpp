// DIBSectionTestView.cpp : implementation of the CDIBSectionTestView class
//

#include "stdafx.h"
#include "DIBSectionTest.h"

#include "DIBSectionTestDoc.h"
#include "DIBSectionTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestView

IMPLEMENT_DYNCREATE(CDIBSectionTestView, CView)

BEGIN_MESSAGE_MAP(CDIBSectionTestView, CView)
	//{{AFX_MSG_MAP(CDIBSectionTestView)
	ON_COMMAND(ID_VIEW_STRETCH, OnViewStretch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STRETCH, OnUpdateViewStretch)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND_RANGE(ID_OPTIONS_1, ID_OPTIONS_32, OnOptions)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_1, ID_OPTIONS_32, OnUpdateOptions)
	ON_COMMAND(ID_VIEW_PROPS, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPS, OnUpdateViewProperties)
	ON_COMMAND(ID_OPTIONS_DITHER, OnOptionsDither)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DITHER, OnUpdateOptionsDither)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestView construction/destruction

CDIBSectionTestView::CDIBSectionTestView()
{
    m_bStretch = FALSE;
    m_nBitmapID = -1;
}

CDIBSectionTestView::~CDIBSectionTestView()
{
}

BOOL CDIBSectionTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestView drawing

void CDIBSectionTestView::OnDraw(CDC* pDC)
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if (pDoc->m_DIBSection.GetSafeHandle())
    {
        if (m_bStretch)
        {
            CRect rect;
            GetClientRect(rect);
            pDoc->m_DIBSection.Stretch(pDC, CPoint(0,0), rect.Size());
        }
        else
            pDoc->m_DIBSection.Draw(pDC, CPoint(0,0));
    }
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestView diagnostics

#ifdef _DEBUG
void CDIBSectionTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDIBSectionTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIBSectionTestDoc* CDIBSectionTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIBSectionTestDoc)));
	return (CDIBSectionTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestView message handlers

void CDIBSectionTestView::OnViewStretch() 
{
    m_bStretch = !m_bStretch;
    Invalidate();
}

void CDIBSectionTestView::OnUpdateViewStretch(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_bStretch);
}

BOOL CDIBSectionTestView::OnEraseBkgnd(CDC* pDC) 
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if (!pDoc->m_DIBSection.GetSafeHandle())
	    return CView::OnEraseBkgnd(pDC);

    if (m_bStretch)
        return TRUE;

    CRect ClientRect, ImageRect;
    GetClientRect(ClientRect);
    ImageRect.SetRect(0,0, pDoc->m_DIBSection.GetWidth(), pDoc->m_DIBSection.GetHeight());

#ifdef _WIN32_WCE
    HBRUSH hBrush = ::CreateSolidBrush(RGB(255,255,255));
#else
    HBRUSH hBrush =  (HBRUSH) GetClassLong(m_hWnd, GCL_HBRBACKGROUND);
#endif

    ::FillRect(pDC->GetSafeHdc(), 
               CRect(ImageRect.right,0, ClientRect.right, ImageRect.bottom), hBrush);
    ::FillRect(pDC->GetSafeHdc(), 
               CRect(0, ImageRect.bottom, ClientRect.right, ClientRect.bottom), hBrush);

#ifdef _WIN32_WCE
    ::DeleteObject(hBrush);
#endif

    return TRUE;
}

void CDIBSectionTestView::OnFileOpen() 
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString strFilter = "Bitmap Files (*.bmp)|*.bmp|All Files (*.*) |*.*||";

	CFileDialog	dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 
	if (dlg.DoModal() == IDOK) 
    {
        if (pDoc->m_DIBSection.Load(dlg.GetPathName()))
            pDoc->SetTitle(dlg.GetFileTitle());
        else
            AfxMessageBox(_T("Unable to open bitmap file"));

        m_nBitmapID = -1;
        Invalidate();
    }
}

void CDIBSectionTestView::OnFileSave() 
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if (!m_strFilename.IsEmpty())
        pDoc->m_DIBSection.Save(m_strFilename);
    else
        OnFileSaveAs();
}

void CDIBSectionTestView::OnFileSaveAs() 
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CString strFilter = "Bitmap Files (*.bmp)|*.bmp|All Files (*.*) |*.*||";

	CFileDialog	dlg(FALSE, NULL, m_strFilename, OFN_HIDEREADONLY|OFN_EXPLORER, strFilter, NULL); 
	if (dlg.DoModal() == IDOK) 
    {
        m_strFilename = dlg.GetPathName();
        pDoc->m_DIBSection.Save(m_strFilename);
        pDoc->SetTitle(dlg.GetFileTitle());
    }
}

void CDIBSectionTestView::OnOptions(UINT nID) 
{
    int nOldID = m_nBitmapID;
    switch (nID)
    {
        case ID_OPTIONS_1:  m_nBitmapID = IDB_GRADIENT_1; break;
#ifndef _WIN32_WCE
        case ID_OPTIONS_2:  m_nBitmapID = IDB_GRADIENT_2;  break;
#endif
        case ID_OPTIONS_4:  m_nBitmapID = IDB_GRADIENT_4;  break;
        case ID_OPTIONS_8:  m_nBitmapID = IDB_GRADIENT_8;  break;
        case ID_OPTIONS_16: m_nBitmapID = IDB_GRADIENT_16; break;
        case ID_OPTIONS_24: m_nBitmapID = IDB_GRADIENT_24; break;
        case ID_OPTIONS_32: m_nBitmapID = IDB_GRADIENT_32; break;
    }

	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if (!pDoc->m_DIBSection.SetBitmap(m_nBitmapID))
    {
        AfxMessageBox(_T("Unable to load bitmap file"));
        m_nBitmapID = nOldID;
    } 
    else
    {
        m_strFilename.Empty();
        GetDocument()->SetTitle(_T("Untitled"));
    }

    Invalidate();
}

void CDIBSectionTestView::OnUpdateOptions(CCmdUI* pCmdUI) 
{
    switch (pCmdUI->m_nID)
    {
        case ID_OPTIONS_1: 
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_1);      
            break;

        case ID_OPTIONS_2:
#if defined(_WIN32_WCE) && !defined(_WIN32_WCE_EMULATION)
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_2);      
#else
            pCmdUI->SetCheck(FALSE);
            pCmdUI->Enable(FALSE);
#endif
            break;

        case ID_OPTIONS_4:
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_4);      
            break;

        case ID_OPTIONS_8:
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_8);      
            break;

        case ID_OPTIONS_16:
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_16);      
            break;

        case ID_OPTIONS_24:
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_24);      
            break;

        case ID_OPTIONS_32:
            pCmdUI->SetCheck(m_nBitmapID == IDB_GRADIENT_32);      
            break;
    }
}

void CDIBSectionTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

    OnOptions(ID_OPTIONS_32);
}

void CDIBSectionTestView::OnViewProperties() 
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CString str;
#ifdef _WIN32_WCE
    str.Format(_T("Display Image Properties:\n")
               _T("Dim:\t%d x %d\n")
               _T("Depth:\t%d bit%s\n")
               _T("Size:\t%d Kb"),
#else
        str.Format(_T("Display Image Properties:\n")
               _T("Dimension:\t%d x %d pixels\n")
               _T("Color Depth:\t%d bit%s per pixel\n")
               _T("Image Size:\t%d Kb"),
#endif
               pDoc->m_DIBSection.GetWidth(), 
               pDoc->m_DIBSection.GetHeight(),
               pDoc->m_DIBSection.GetBitCount(), 
               (pDoc->m_DIBSection.GetBitCount() == 1)? _T("") : _T("s"),
               pDoc->m_DIBSection.GetImageSize() / 1024);

    MessageBox(str, _T("Properties"), MB_ICONINFORMATION);
}

void CDIBSectionTestView::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    pCmdUI->Enable(pDoc->m_DIBSection.GetSafeHandle() != NULL);
}

void CDIBSectionTestView::OnOptionsDither() 
{
#ifndef _WIN32_WCE
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    pDoc->m_DIBSection.SetDither(!pDoc->m_DIBSection.GetDither());
#endif
}

void CDIBSectionTestView::OnUpdateOptionsDither(CCmdUI* pCmdUI) 
{
#ifdef _WIN32_WCE
    pCmdUI->Enable(FALSE);
    pCmdUI->SetCheck(FALSE);
#else
	CDIBSectionTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if (!pDoc->m_DIBSection.GetSafeHandle() || pDoc->m_DIBSection.GetBitCount() <= 8)
    {
        pCmdUI->Enable(FALSE);
        pCmdUI->SetCheck(FALSE);
    }
    else
    {
        pCmdUI->Enable(TRUE);
        pCmdUI->SetCheck(pDoc->m_DIBSection.GetDither());
    }
#endif
}
