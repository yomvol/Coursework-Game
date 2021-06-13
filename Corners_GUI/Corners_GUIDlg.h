
// Corners_GUIDlg.h : header file
//

#pragma once
#include "pch.h"

class CCornersBoard;
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
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CCornersBoard Board;
	CornersBoardModel* BoardModel;
	bool GameInProgress;
	CornersPlayer* player1;
	CornersPlayer* player2;
	CornersPlayer* currentPlayer;
	unsigned int NumWhiteTurns = 0, NumBlackTurns = 0;
	void CleanUp();
	void UpdateName();
	CListBox GameLog;
public:
	afx_msg void OnBnClickedButton1();
	void CreatePlayer(CString PlayerName, int PlayerType, Tile t);
	void CreateBoard();
	CornersBoardModel* GetBoardMod() { return this->BoardModel; };
	CornersPlayer* GetCurPlayer() { return this->currentPlayer; };
	afx_msg void OnDestroy();
	bool GetGameInProgress() { return GameInProgress; };
	CListBox* GetLog() { return &GameLog; };
	void Judge();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
