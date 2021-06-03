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
	delete board;
}

void CornersManager::ShowBoard()
{
	this->board->Show();
}

void CornersManager::MakeMove()
{
	ShowBoard();
	while (!currentPlayer->MakeMove())
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
	
	/*
	if (this->board->CheckEndCondition())
	{
		if (this->board->IsVictory())
			cout << "Игрок " << currentPlayer->GetName() << " победил!" << endl;
		else
			cout << "Ничья!" << endl;
		this->bGameFinished = true;
		ShowBoard();
		return;
	}
	*/
	// Check for consequential turns
	if (currentPlayer->GetDidHop() == false)
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	else if (currentPlayer->GetIsPassingTurn() == true)
	{
		currentPlayer->SetDidHop(false);
		currentPlayer->SetIsPassingTurn(false);
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
}

bool CornersManager::IsGameFinished()
{
	return GameFinished;
}