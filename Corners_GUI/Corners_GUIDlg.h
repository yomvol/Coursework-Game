
// Corners_GUIDlg.h : header file
//

#pragma once
#include "CCornersBoard.h"

// CCornersGUIDlg dialog
class CCornersGUIDlg : public CDialogEx
{
// Construction
public:
	CCornersGUIDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CORNERS_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CCornersBoard Board;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
