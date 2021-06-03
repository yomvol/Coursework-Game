#include "pch.h"
#include "CornersManager.h"
#include "CornersHumanPlayer.h"

CornersManager::CornersManager()
{
	this->board = new CornersBoard();
	//int playertype;
	string PlayerName;
	this->player1 = new CornersHumanPlayer();
	this->player2 = new CornersHumanPlayer();

	//cin.ignore(); Without it everything works fine
	cout << "������� ��� ������, ��������� �� ����� (@): ";
	getline(cin, PlayerName);
	player1->SetupPlayer(PlayerName, Tile_White);
	cout << "������� ��� ������, ��������� �� ������ (*): ";
	getline(cin, PlayerName);
	player2->SetupPlayer(PlayerName, Tile_Black);
	player1->SetBoard(this->board);
	player2->SetBoard(this->board);
	currentPlayer = player1;
}

CornersManager::~CornersManager()
{
	delete board;
}

void CornersManager::ShowBoard()
{
	cout << "����� ����� �������: " << NumWhiteTurns << " ����� ������ �������: " << NumBlackTurns << endl;
	this->board->Show();
}

void CornersManager::MakeMove()
{
	if (NumBlackTurns > 10 && NumBlackTurns == NumWhiteTurns)
	{
		unsigned int WhiteProgress = this->board->WhitesOnBlackBase();
		unsigned int BlackProgress = this->board->BlacksOnWhiteBase();
		if (NumBlackTurns == 40)
		{
			unsigned int WhiteFault = this->board->WhitesOnWhiteBase();
			if (WhiteFault > 0)
			{
				cout << "����� " << player2->GetName() << " ������� ��-�� �������� ��������� � ����" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			unsigned int BlackFault = this->board->BlacksOnBlackBase();
			if (BlackFault > 0)
			{
				cout << "����� " << player1->GetName() << " ������� ��-�� �������� ��������� � ����" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
		}
		if (NumBlackTurns == 80)
		{
			if (WhiteProgress > BlackProgress)
			{
				cout << "����� " << player1->GetName() << " �������!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			else if (WhiteProgress == BlackProgress)
			{
				cout << "�����!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			else
			{
				cout << "����� " << player2->GetName() << " �������!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
		}
		else
		{
			if (WhiteProgress == 9)
			{
				cout << "����� " << player1->GetName() << " �������!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			if (BlackProgress == 9)
			{
				cout << "����� " << player2->GetName() << " �������!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
		}
	}

	ShowBoard();
	while (!currentPlayer->MakeMove())
	{
		if (currentPlayer->GetIsSurrendering())
		{
			cout << "����� " << currentPlayer->GetName() << " ������!" << endl << endl;
			this->GameFinished = true;
			ShowBoard();
			return;
		}
		cout << "������������ ���, ���������� ��� ���" << endl << endl;
		ShowBoard();
	}
	
	
	// Check for consequential turns
	if (currentPlayer->GetDidHop() == false)
	{
		if (currentPlayer == player1)
			NumWhiteTurns++;
		else
			NumBlackTurns++;
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
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
	}
}

bool CornersManager::IsGameFinished()
{
	return GameFinished;
}