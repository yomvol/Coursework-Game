#pragma once
#include "CornersPlayer.h"

class CornersHumanPlayer : public CornersPlayer
{
public:
	CornersHumanPlayer();
	virtual ~CornersHumanPlayer();
	virtual bool MakeMove();

};

