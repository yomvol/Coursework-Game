#include "pch.h"
#include "CornersManager.h"
#include "CornersHumanPlayer.h"
#include "CornersComputerPlayer.h"

CornersManager::CornersManager()
{
	this->board = new CornersBoard();
	string PlayerName;
	int playertype;
	cout << "Введите тип игрока, играющего за белых (@) (1 - Человек, любое другое число - Компьютер): ";
	cin >> playertype;
	if (playertype == 1)
		this->player1 = new CornersHumanPlayer();
	else
		this->player1 = new CornersComputerPlayer();
	cout << "Введите тип игрока, играющего за чёрных (*) (1 - Человек, любое другое число - Компьютер): ";
	cin >> playertype;
	if (playertype == 1)
		this->player2 = new CornersHumanPlayer();
	else
		this->player2 = new CornersComputerPlayer();

	cin.ignore();
	cout << "Введите имя игрока, играющего за белых (@): ";
	getline(cin, PlayerName);
	player1->SetupPlayer(PlayerName, Tile_White);
	cout << "Введите имя игрока, играющего за чёрных (*): ";
	getline(cin, PlayerName);
	player2->SetupPlayer(PlayerName, Tile_Black);
	player1->SetBoard(this->board);
	player2->SetBoard(this->board);
	currentPlayer = player1;
}

CornersManager::~CornersManager()
{
	delete this->board;
	delete this->player1;
	delete this->player2;
}

void CornersManager::ShowBoard()
{
	cout << "Ходов белых сделано: " << NumWhiteTurns << " Ходов чёрных сделано: " << NumBlackTurns << endl;
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
				cout << "Игрок " << player2->GetName() << " победил из-за задержки оппонента в доме" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			unsigned int BlackFault = this->board->BlacksOnBlackBase();
			if (BlackFault > 0)
			{
				cout << "Игрок " << player1->GetName() << " победил из-за задержки оппонента в доме" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
		}
		if (NumBlackTurns == 80)
		{
			if (WhiteProgress > BlackProgress)
			{
				cout << "Игрок " << player1->GetName() << " победил!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			else if (WhiteProgress == BlackProgress)
			{
				cout << "Ничья!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			else
			{
				cout << "Игрок " << player2->GetName() << " победил!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
		}
		else
		{
			if (WhiteProgress == 9)
			{
				cout << "Игрок " << player1->GetName() << " победил!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
			if (BlackProgress == 9)
			{
				cout << "Игрок " << player2->GetName() << " победил!" << endl;
				this->GameFinished = true;
				ShowBoard();
				return;
			}
		}
	}

	ShowBoard();
	while (!currentPlayer->MakeMove(NumWhiteTurns, NumBlackTurns))
	{
		if (currentPlayer->GetIsSurrendering())
		{
			cout << "Игрок " << currentPlayer->GetName() << " сдаётся!" << endl << endl;
			this->GameFinished = true;
			ShowBoard();
			return;
		}
		cout << "Недопустимый ход, попробуйте ещё раз" << endl << endl;
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