#include "pch.h"
#include "CornersManager.h"

CornersManager::CornersManager()
{

	this->board = new CornersBoard();
}

CornersManager::~CornersManager()
{
	delete board;
}

void CornersManager::ShowBoard()
{
	this->board->Show();
}