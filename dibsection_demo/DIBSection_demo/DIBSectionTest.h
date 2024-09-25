// DIBSectionTest.h : main header file for the DIBSECTIONTEST application
//

#if !defined(AFX_DIBSECTIONTEST_H__6A610638_0C08_11D3_A9FD_54F6CD000000__INCLUDED_)
#define AFX_DIBSECTIONTEST_H__6A610638_0C08_11D3_A9FD_54F6CD000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionTestApp:
// See DIBSectionTest.cpp for the implementation of this class
//

class CDIBSectionTestApp : public CWinApp
{
public:
	CDIBSectionTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBSectionTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDIBSectionTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBSECTIONTEST_H__6A610638_0C08_11D3_A9FD_54F6CD000000__INCLUDED_)
