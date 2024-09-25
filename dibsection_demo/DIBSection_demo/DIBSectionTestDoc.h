// DIBSectionTestDoc.h : interface of the CDIBSectionTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBSECTIONTESTDOC_H__6A61063E_0C08_11D3_A9FD_54F6CD000000__INCLUDED_)
#define AFX_DIBSECTIONTESTDOC_H__6A61063E_0C08_11D3_A9FD_54F6CD000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DIBSectionLite.h"

class CDIBSectionTestDoc : public CDocument
{
protected: // create from serialization only
	CDIBSectionTestDoc();
	DECLARE_DYNCREATE(CDIBSectionTestDoc)

// Attributes
public:
    CDIBSectionLite m_DIBSection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBSectionTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIBSectionTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIBSectionTestDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBSECTIONTESTDOC_H__6A61063E_0C08_11D3_A9FD_54F6CD000000__INCLUDED_)
