#include "pch.h"
#include "CornersHumanPlayer.h"

CornersHumanPlayer::CornersHumanPlayer()
{}

CornersHumanPlayer::~CornersHumanPlayer()
{}

bool CornersHumanPlayer::MakeMove()
{
	unsigned int startrow, startcol, endrow, endcol;
	char input;
	cout << "����� " << name << ", ��� ���." << endl;
	if (this->DidHop)
	{
		cout << "������� P, ����� ��������� ����� �������  ";
		cin >> input;
		if (input == 'p' || input == 'P')
		{
			this->IsPassingTurn = true;
			return true;
		}
	}
	if (this->DidHop == false)
	{
		cout << "����� ������ ������?" << endl;
		cout << "������� ������: ";
		cin >> startrow;
		startrow = 8 - startrow; //EXCEPTION?
		cout << "������� ������� (��� ������� S, ����� �������): ";
		cin >> input;
		switch (input)
		{
		case 'a':
		case 'A':
			startcol = 0;
			break;
		case 'b':
		case 'B':
			startcol = 1;
			break;
		case 'c':
		case 'C':
			startcol = 2;
			break;
		case 'd':
		case 'D':
			startcol = 3;
			break;
		case 'e':
		case 'E':
			startcol = 4;
			break;
		case 'f':
		case 'F':
			startcol = 5;
			break;
		case 'g':
		case 'G':
			startcol = 6;
			break;
		case 'h':
		case 'H':
			startcol = 7;
			break;
		case 's':
		case 'S':
			IsSurrendering = true;
			return false;
		default:
			cout << "�������� ����� ������" << endl;
			return false;
		}
		if (!this->board->CheckLegalPick(startcol, startrow, this->tile))
		{
			cout << "������ ������ ������ ��������..." << endl;
			return false;
		}
	}
	else
	{
		startcol = prevcol;
		startrow = prevrow;
	}
	cout << "���� ������ ������?" << endl;
	cout << "������� ������: ";
	cin >> endrow;
	endrow = 8 - endrow; //EXCEPTION?
	cout << "������� ������� (��� ������� S, ����� �������): ";
	cin >> input;
	switch (input)
	{
	case 'a':
	case 'A':
		endcol = 0;
		break;
	case 'b':
	case 'B':
		endcol = 1;
		break;
	case 'c':
	case 'C':
		endcol = 2;
		break;
	case 'd':
	case 'D':
		endcol = 3;
		break;
	case 'e':
	case 'E':
		endcol = 4;
		break;
	case 'f':
	case 'F':
		endcol = 5;
		break;
	case 'g':
	case 'G':
		endcol = 6;
		break;
	case 'h':
	case 'H':
		endcol = 7;
		break;
	case 's':
	case 'S':
		IsSurrendering = true;
		return false;
	default:
		cout << "�������� ����� ������" << endl;
		return false;
	}
	cout << endl;

	if (this->board->CheckLegal(startcol, startrow, endcol, endrow))
	{
		unsigned int adiffx = abs(int(endcol - startcol));
		unsigned int adiffy = abs(int(endrow - startrow));
		if (DidHop == true && !(adiffy == 2 || adiffx == 2))
		{
			cout << "� ����� ������� ����� ������ �������" << endl;
			return false;
		}
		this->board->SetTile(endcol, endrow, this->tile);
		this->board->SetTile(startcol, startrow, Tile_Empty);
		if (adiffy == 2 || adiffx == 2)
		{
			prevcol = endcol;
			prevrow = endrow;
			DidHop = true;
		}
		return true;
	}

	return false;
}