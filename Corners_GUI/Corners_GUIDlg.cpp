// Corners_GUIDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Corners_GUI.h"
#include "Corners_GUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CStartUpDlg.h"
#include "CornersHumanPlayer.h"
#include "CornersComputerPlayer.h"

#define MYTIMER_ID 222
// CCornersGUIDlg dialog



CCornersGUIDlg::CCornersGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CORNERS_GUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	BoardModel = nullptr;
	player1 = nullptr;
	player2 = nullptr;
	currentPlayer = nullptr;
	GameInProgress = false;
}

void CCornersGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CORNERSBOARD, Board);
	DDX_Control(pDX, IDC_LOG, GameLog);
}

BEGIN_MESSAGE_MAP(CCornersGUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCornersGUIDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCornersGUIDlg message handlers

BOOL CCornersGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	Board.SetGameManager(this);

	return TRUE;  // return TRUE  unless you set the focus to a control I DO SET FOCUS TO THE BOARD CONTROL
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCornersGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCornersGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCornersGUIDlg::CreatePlayer(CString PlayerName, int PlayerType, Tile t)
{
	if (t == Tile_White)
	{
		if (PlayerType == 1)
		{
			player1 = new CornersHumanPlayer();
			player1->SetupPlayer(PlayerName, Tile_White);
		}
		else if (PlayerType == 2)
		{
			player1 = new CornersComputerPlayer();
			player1->SetupPlayer(PlayerName, Tile_White);
		}
	}
	else if (t == Tile_Black)
	{
		if (PlayerType == 1)
		{
			player2 = new CornersHumanPlayer();
			player2->SetupPlayer(PlayerName, Tile_Black);
		}
		else if (PlayerType == 2)
		{
			player2 = new CornersComputerPlayer();
			player2->SetupPlayer(PlayerName, Tile_Black);
		}
	}
}

void CCornersGUIDlg::CreateBoard()
{
	this->BoardModel = new CornersBoardModel();
}

void CCornersGUIDlg::OnBnClickedButton1()
{
	CleanUp();
	if (GameInProgress)
	{
		GameInProgress = false;
		KillTimer(MYTIMER_ID);
		Invalidate();
	}
	CStartUpDlg StartUpDlg;
	StartUpDlg.SetDlgParent(this);
	int Result = StartUpDlg.DoModal();
	if (Result == IDOK)
	{
		GotoDlgCtrl(GetDlgItem(IDC_CORNERSBOARD));
		if (BoardModel == nullptr)
			CreateBoard();
		player1->SetBoard(BoardModel);
		player2->SetBoard(BoardModel);
		currentPlayer = player1;
		UpdateName();
		PlaySound(TEXT("watching-the-waves.wav"), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME | SND_NODEFAULT);
		SetTimer(MYTIMER_ID, 1000, NULL);
		GameInProgress = true;
		Invalidate();
	}
}

void CCornersGUIDlg::CleanUp()
{
	PlaySound(NULL, 0, 0);
	if (BoardModel != nullptr)
	{
		delete BoardModel;
		BoardModel = nullptr;
	}
	if (player1 != nullptr)
	{
		delete player1;
		player1 = nullptr;
	}
	if (player2 != nullptr)
	{
		delete player2;
		player2 = nullptr;
	}
	currentPlayer = nullptr;
}

void CCornersGUIDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	CleanUp();
}

void CCornersGUIDlg::UpdateName()
{
	CString str, color;
	if (currentPlayer->GetPColor() == Tile_White)
		color = L"White";
	else
		color = L"Black";
	str.Format(L"It`s %s`s (%s) turn now.", currentPlayer->GetName(), color);
	GameLog.AddString(str);
}

void CCornersGUIDlg::Judge()
{
	CString str;
	if (NumBlackTurns > 15 && NumBlackTurns == NumWhiteTurns)
	{
		unsigned int WhiteProgress = this->BoardModel->WhitesOnBlackBase();
		unsigned int BlackProgress = this->BoardModel->BlacksOnWhiteBase();
		if (NumBlackTurns == 40)
		{
			unsigned int WhiteFault = this->BoardModel->WhitesOnWhiteBase();
			if (WhiteFault > 0)
			{
				str.Format(L"Player %s won because of his opponent`s impediment at its base.", player2->GetName());
				GameLog.AddString(str);
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
			unsigned int BlackFault = this->BoardModel->BlacksOnBlackBase();
			if (BlackFault > 0)
			{
				str.Format(L"Player %s won because of his opponent`s impediment at its base.", player1->GetName());
				GameLog.AddString(str);
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
		}
		if (NumBlackTurns == 80)
		{
			if (WhiteProgress > BlackProgress)
			{
				str.Format(L"Player %s won!", player1->GetName());
				GameLog.AddString(str);
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
			else if (WhiteProgress == BlackProgress)
			{
				GameLog.AddString(L"Draw!");
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
			else
			{
				str.Format(L"Player %s won!", player2->GetName());
				GameLog.AddString(str);
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
		}
		else
		{
			if (WhiteProgress == 9)
			{
				str.Format(L"Player %s won!", player1->GetName());
				GameLog.AddString(str);
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
			if (BlackProgress == 9)
			{
				str.Format(L"Player %s won!", player2->GetName());
				GameLog.AddString(str);
				PlaySound(NULL, 0, 0);
				KillTimer(MYTIMER_ID);
				this->GameInProgress = false;
				return;
			}
		}
	}

	if (currentPlayer->GetIsSurrendering())
	{
		str.Format(L"Player %s gives up.", currentPlayer->GetName());
		GameLog.AddString(str);
		PlaySound(NULL, 0, 0);
		KillTimer(MYTIMER_ID);
		this->GameInProgress = false;
		return;
	}

	// Check for consequential turns
	if (currentPlayer->GetDidHop() == false)
	{
		if (currentPlayer == player1)
			NumWhiteTurns++;
		else
			NumBlackTurns++;
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
		str.Format(L"White turns: %u :: Black turns: %u", NumWhiteTurns, NumBlackTurns);
		GameLog.AddString(str);
		UpdateName();
	}
	else if (currentPlayer->GetIsPassingTurn() == true)
	{
		if (currentPlayer == player1)
			NumWhiteTurns++;
		else
			NumBlackTurns++;
		currentPlayer->SetDidHop(false);
		currentPlayer->SetIsPassingTurn(false);
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
		str.Format(L"White turns: %u :: Black turns: %u", NumWhiteTurns, NumBlackTurns);
		GameLog.AddString(str);
		UpdateName();
	}
}

void CCornersGUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (GameInProgress == false || currentPlayer->IsHuman() == true)
	{
		CDialogEx::OnTimer(nIDEvent);
		return;
	}

	currentPlayer->MakeMove(10, 10, 10, 10, NumWhiteTurns, NumBlackTurns);
	this->Invalidate();
	Judge();

	CDialogEx::OnTimer(nIDEvent);
}
