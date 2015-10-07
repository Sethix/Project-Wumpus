#include "gameOptions.h"
#include "gameObjects.h"

Player::Player()
{
	loc = PLAYER_STARTING_ROOM;
	arrows = NUMBER_OF_ARROWS;
}

int Player::GetLoc() const
{
	return loc;
}

void Player::SetLoc(int i)
{
	loc = i;
}

void Player::GiveArrows()
{
	arrows = NUMBER_OF_ARROWS;
}

int Player::GetArrows()
{
	return arrows;
}

void Player::SetArrows(int i)
{
	arrows = i;
}

void Player::UseArrow()
{
	arrows--;
}

bool Player::HasArrows() const
{
	if(arrows < 1) return false;
	else return true;
}

Wumpus::Wumpus()
{
	loc = WUMPUS_STARTING_ROOM;
}

int Wumpus::GetLoc() const
{
	return loc;
}

void Wumpus::SetLoc(int i)
{
	loc = i;
}

Room::Room()
{
	roomNum = 0;
	hazard = None;
	connectingRoomOne = 0;
	connectingRoomTwo = 0;
	connectingRoomThree = 0;
}

Room::Room(int rNum, Hazard h)
{
	roomNum = rNum + 1;
	hazard = h;

	switch (roomNum)
	{
	case 1:
		connectingRoomOne = 2;
		connectingRoomTwo = 5;
		connectingRoomThree = 18;
		break;
	case 2:
		connectingRoomOne = 1;
		connectingRoomTwo = 3;
		connectingRoomThree = 11;
		break;
	case 3:
		connectingRoomOne = 2;
		connectingRoomTwo = 4;
		connectingRoomThree = 6;
		break;
	case 4:
		connectingRoomOne = 3;
		connectingRoomTwo = 5;
		connectingRoomThree = 8;
		break;
	case 5:
		connectingRoomOne = 1;
		connectingRoomTwo = 4;
		connectingRoomThree = 10;
		break;
	case 6:
		connectingRoomOne = 3;
		connectingRoomTwo = 7;
		connectingRoomThree = 12;
		break;
	case 7:
		connectingRoomOne = 6;
		connectingRoomTwo = 8;
		connectingRoomThree = 14;
		break;
	case 8:
		connectingRoomOne = 4;
		connectingRoomTwo = 7;
		connectingRoomThree = 9;
		break;
	case 9:
		connectingRoomOne = 8;
		connectingRoomTwo = 10;
		connectingRoomThree = 15;
		break;
	case 10:
		connectingRoomOne = 5;
		connectingRoomTwo = 9;
		connectingRoomThree = 17;
		break;
	case 11:
		connectingRoomOne = 2;
		connectingRoomTwo = 12;
		connectingRoomThree = 20;
		break;
	case 12:
		connectingRoomOne = 6;
		connectingRoomTwo = 11;
		connectingRoomThree = 13;
		break;
	case 13:
		connectingRoomOne = 12;
		connectingRoomTwo = 14;
		connectingRoomThree = 19;
		break;
	case 14:
		connectingRoomOne = 7;
		connectingRoomTwo = 13;
		connectingRoomThree = 15;
		break;
	case 15:
		connectingRoomOne = 9;
		connectingRoomTwo = 14;
		connectingRoomThree = 16;
		break;
	case 16:
		connectingRoomOne = 14;
		connectingRoomTwo = 17;
		connectingRoomThree = 19;
		break;
	case 17:
		connectingRoomOne = 10;
		connectingRoomTwo = 16;
		connectingRoomThree = 18;
		break;
	case 18:
		connectingRoomOne = 1;
		connectingRoomTwo = 17;
		connectingRoomThree = 20;
		break;
	case 19:
		connectingRoomOne = 13;
		connectingRoomTwo = 16;
		connectingRoomThree = 20;
		break;
	case 20:
		connectingRoomOne = 11;
		connectingRoomTwo = 18;
		connectingRoomThree = 19;
		break;
	}
}

Hazard Room::GetHazard() const
{
	return hazard;
}

void Room::SetHazard(Hazard h)
{
	hazard = h;
}

int Room::GetRoomNum() const
{
	return roomNum;
}

int Room::GetConnectionOne() const
{
	return connectingRoomOne;
}

int Room::GetConnectionTwo() const
{
	return connectingRoomTwo;
}

int Room::GetConnectionThree() const
{
	return connectingRoomThree;
}
