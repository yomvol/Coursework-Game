// CStartUpDlg.cpp : implementation file
//

#include "pch.h"
#include "Corners_GUI.h"
#include "CStartUpDlg.h"
#include "afxdialogex.h"


// CStartUpDlg dialog

IMPLEMENT_DYNAMIC(CStartUpDlg, CDialogEx)

CStartUpDlg::CStartUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTDIALOG, pParent)
	, Player1Name(_T(""))
	, Player2Name(_T(""))
{
	dlgParent = nullptr;
}

CStartUpDlg::~CStartUpDlg()
{
}

void CStartUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PLAYER1NAME, Player1Name);
	DDX_Text(pDX, IDC_PLAYER2NAME, Player2Name);
	DDX_Control(pDX, IDC_HUMAN1, P1HumanSwitch);
	DDX_Control(pDX, IDC_COMPUTER1, P1ComputerSwitch);
	DDX_Control(pDX, IDC_HUMAN2, P2HumanSwitch);
	DDX_Control(pDX, IDC_COMPUTER2, P2ComputerSwitch);
}


BEGIN_MESSAGE_MAP(CStartUpDlg, CDialogEx)
	ON_BN_CLICKED(IDSTARTBUTTON, &CStartUpDlg::OnBnClickedStartbutton)
END_MESSAGE_MAP()


// CStartUpDlg message handlers


BOOL CStartUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	P1HumanSwitch.SetCheck(1);
	P1ComputerSwitch.SetCheck(0);
	P2HumanSwitch.SetCheck(1);
	P2ComputerSwitch.SetCheck(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CStartUpDlg::SetDlgParent(CCornersGUIDlg* P)
{
	this->dlgParent = P;
}


void CStartUpDlg::OnBnClickedStartbutton()
{
	UpdateData(TRUE);
	if (Player1Name == "" || Player2Name == "")
	{
		AfxMessageBox(L"Enter players` names");
		return;
	}
	int P1Type, P2Type;
	if (P1HumanSwitch.GetCheck() == 1 && P1ComputerSwitch.GetCheck() == 0)
		P1Type = 1;
	else if (P1HumanSwitch.GetCheck() == 0 && P1ComputerSwitch.GetCheck() == 1)
		P1Type = 2;
	else
		throw;
	if (P2HumanSwitch.GetCheck() == 1 && P2ComputerSwitch.GetCheck() == 0)
		P2Type = 1;
	else if (P2HumanSwitch.GetCheck() == 0 && P2ComputerSwitch.GetCheck() == 1)
		P2Type = 2;
	else
		throw;

	dlgParent->CreatePlayer(Player1Name, P1Type, Tile_White);
	dlgParent->CreatePlayer(Player2Name, P2Type, Tile_Black);

	this->EndDialog(IDOK);
}
