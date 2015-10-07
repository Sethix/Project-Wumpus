/*************************************************
Hunt the Wumpus

This is a re-make of a game by Gregory Yob created
back in 1972 called Hunt the Wumpus.

The objective of the game is to shoot the wumpus
before you die or run out of ammo.

This is a text based adventure game with
hide and seek like rules.

Created for the purpose of an assessment given to me
by Esmeralda Salamone.

Using the SFML library for rendering graphics.
http://www.sfml-dev.org/

Justin Hamm, Justin.T.Hamm@gmail.com, 10/6/2015
***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML\Graphics.hpp>
#include "gameObjects.h"
#include "gameState.h"

int main()
{
	srand(time(NULL));

	bool playingGame = true;
	GameState game;
	
	while (playingGame)
	{
		game.CallCurrentState();

		if (game.GetExit() == true) playingGame = false;
	}

	return 0;
}