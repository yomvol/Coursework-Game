#include "pch.h"
#include "CornersPlayer.h"

CornersPlayer::CornersPlayer()
{}

CornersPlayer::~CornersPlayer()
{}

void CornersPlayer::SetupPlayer(string name, Tile tile)
{
	this->name = name;
	this->tile = tile;
}

void CornersPlayer::SetBoard(CornersBoard* board)
{
	this->board = board;
}

string CornersPlayer::GetName()
{
	return this->name;
}

bool CornersPlayer::GetIsSurrendering()
{
	return this->IsSurrendering;
}

bool CornersPlayer::GetDidHop()
{
	return this->DidHop;
}

bool CornersPlayer::GetIsPassingTurn()
{
	return this->IsPassingTurn;
}

void CornersPlayer::SetDidHop(bool value) // I really miss C# properties
{
	this->DidHop = value;
}
void CornersPlayer::SetIsPassingTurn(bool value)
{
	this->IsPassingTurn = value;
}