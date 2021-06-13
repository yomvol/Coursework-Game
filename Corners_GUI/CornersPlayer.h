#pragma once
#include "CornersBoardModel.h"

class CornersPlayer
{
protected:
	CornersBoardModel* board;
	Tile tile;
	CString name;
	bool IsSurrendering = false;
	bool DidHop = false;
	bool IsPassingTurn = false;
	unsigned int prevcol, prevrow;
public:
	CornersPlayer();
	virtual ~CornersPlayer();
	void SetupPlayer(CString name, Tile tile);
	virtual void SetBoard(CornersBoardModel* board);
	virtual bool MakeMove(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int) = 0;
	CString GetName();
	bool GetIsSurrendering();
	bool GetDidHop(); // I really miss C# properties
	bool GetIsPassingTurn();
	void SetDidHop(bool value); // I really miss C# properties
	void SetIsPassingTurn(bool value);
	void SetIsSurrendering(bool value) { IsSurrendering = value; };
	virtual bool IsHuman() = 0;
	Tile GetPColor() { return tile; };
};

