// DIBSectionTestView.h : interface of the CDIBSectionTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBSECTIONTESTVIEW_H__6A610640_0C08_11D3_A9FD_54F6CD000000__INCLUDED_)
#define AFX_DIBSECTIONTESTVIEW_H__6A610640_0C08_11D3_A9FD_54F6CD000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDIBSectionTestView : public CView
{
protected: // create from serialization only
	CDIBSectionTestView();
	DECLARE_DYNCREATE(CDIBSectionTestView)

// Attributes
public:
	CDIBSectionTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBSectionTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIBSectionTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    BOOL    m_bStretch;
    UINT    m_nBitmapID;
    CString m_strFilename;

// Generated message map functions
protected:
	//{{AFX_MSG(CDIBSectionTestView)
	afx_msg void OnViewStretch();
	afx_msg void OnUpdateViewStretch(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileOpen();
    afx_msg void OnFileSave();
    afx_msg void OnFileSaveAs();
	afx_msg void OnOptions(UINT nID);
	afx_msg void OnUpdateOptions(CCmdUI* pCmdUI);
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDither();
	afx_msg void OnUpdateOptionsDither(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DIBSectionTestView.cpp
inline CDIBSectionTestDoc* CDIBSectionTestView::GetDocument()
   { return (CDIBSectionTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBSECTIONTESTVIEW_H__6A610640_0C08_11D3_A9FD_54F6CD000000__INCLUDED_)
