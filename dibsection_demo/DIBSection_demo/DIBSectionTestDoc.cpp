// DIBSectionTestDoc.cpp : implementation of the CDIBSectionTestDoc class
//

#include "stdafx.h"
#include "DIBSectionTest.h"

#include "DIBSectionTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestDoc

IMPLEMENT_DYNCREATE(CDIBSectionTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIBSectionTestDoc, CDocument)
	//{{AFX_MSG_MAP(CDIBSectionTestDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestDoc construction/destruction

CDIBSectionTestDoc::CDIBSectionTestDoc()
{
	// TODO: add one-time construction code here

}

CDIBSectionTestDoc::~CDIBSectionTestDoc()
{
}

BOOL CDIBSectionTestDoc::OnNewDocument()
{
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestDoc serialization

void CDIBSectionTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestDoc diagnostics

#ifdef _DEBUG
void CDIBSectionTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIBSectionTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestDoc commands

BOOL CDIBSectionTestDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    return TRUE;
}
