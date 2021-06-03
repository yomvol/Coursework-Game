#pragma once
#include "CornersBoard.h"

class CornersPlayer
{
protected:
	CornersBoard* board;
	Tile tile;
	string name;
	bool IsSurrendering = false;
	bool DidHop = false;
	bool IsPassingTurn = false;
	unsigned int prevcol, prevrow;
public:
	CornersPlayer();
	virtual ~CornersPlayer();
	void SetupPlayer(string name, Tile tile);
	void SetBoard(CornersBoard* board);
	virtual bool MakeMove() = 0;
	string GetName();
	bool GetIsSurrendering();
	bool GetDidHop(); // I really miss C# properties
	bool GetIsPassingTurn();
	void SetDidHop(bool value); // I really miss C# properties
	void SetIsPassingTurn(bool value);
};

