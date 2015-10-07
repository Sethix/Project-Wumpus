#pragma once
/*************************************************
gameObjects.h

This is a header file containing the objects for
our Wumpus game.

It contains a player with a location and arrows,

A wumpus with a location,

And a room object that contains a room ID, 
a hazard and the connected rooms.

Justin Hamm, Justin.T.Hamm@gmail.com, 10/6/2015
***************************************************/

enum Hazard
{
	None,
	WumpusHazard,
	PitHazard,
	BatHazard
};

class Player
{
public:
	Player();							//The constructor for our player should
										//set the starting room and arrow count.

	int GetLoc() const;					//Gets the players current location.

	void SetLoc(int i);					//Sets the players location.

	void GiveArrows();					//This function gives the default arrow count.

	int GetArrows();					//This function gets the amount of arrows
										//the player has.

	void SetArrows(int i);				//This function allows us to set a specific
										//amount of arrows.

	void UseArrow();					//Decrement arrow count by 1.

	bool HasArrows() const;				//Returns true if arrows > 0

private:
	int loc;
	int arrows;
};

class Wumpus
{
public:
	Wumpus();							//The constructor simply sets a start location.

	int GetLoc() const;					//Get the wumpus's location

	void SetLoc(int i);					//Set the wumpus's location

private:
	int loc;
};

class Room
{
public:
	Room();								//The default constructor sets all values to 0.

	Room(int rNum, Hazard h);			//This constructor for rooms sets the room number,
										//Hazard and connecting rooms using a switch.

	Hazard GetHazard() const;			//Returns the hazard in the room.

	void SetHazard(Hazard h);			//Sets the rooms hazard.

	int GetRoomNum() const;				//Gets the room number.

	int GetConnectionOne() const;		//These three functions return the connecting rooms.
	int GetConnectionTwo() const;
	int GetConnectionThree() const;

private:
	int roomNum;
	Hazard hazard;
	int connectingRoomOne;
	int connectingRoomTwo;
	int connectingRoomThree;
};
