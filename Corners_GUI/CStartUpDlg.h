#pragma once
#include "Corners_GUIDlg.h"

// CStartUpDlg dialog

class CStartUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartUpDlg)

public:
	CStartUpDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CStartUpDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString Player1Name;
	CString Player2Name;
	CButton P1HumanSwitch;
	CButton P1ComputerSwitch;
	CButton P2HumanSwitch;
	CButton P2ComputerSwitch;

	CCornersGUIDlg* dlgParent;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStartbutton();
	void SetDlgParent(CCornersGUIDlg* P);
};
