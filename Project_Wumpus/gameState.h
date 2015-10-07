#pragma once
/*************************************************
gameState.h

This is a header file containing the class for the
GameState.

Our GameState calls the appropriate function
according to the current state.

It also contains a saveData struct for the purpose
of saving and loading the game.

Justin Hamm, Justin.T.Hamm@gmail.com, 10/6/2015
***************************************************/
#include <SFML\Graphics.hpp>
#include "gameObjects.h"

enum STATE
{
	Splash = 0,
	MainMenu = 1,
	StartGame = 2,
	LoadGame = 3,
	SaveGame = 4,
	PlayGame = 5,
	Victory = 6,
	Loss = 7,
	Paused = 8,
	Credits = 9,
	Instructions = 10,
	Exit = 11
};

struct saveData
{
	int turn;
	int playerLoc;
	int wumpusLoc;
	int arrowCount;
};

class GameState
{
public:
	void(GameState::*currentState)() = nullptr;		//This function pointer changes depending
													//on the current state of the game.

	GameState();									//In our constructor we assign some default
													//values and set the default state.

	void CallCurrentState();						//This function is called every frame and
													//assigns the function pointer depending on state

	sf::Texture GetCurrentTexture();				//Gets the current image to display

	void SplashScreen();							//The splash screen is our start-up screen.
													//It's the first thing players see.

	void MainMenuScreen();							//The main menu should come immediately after
													//the splash screen and allow player to either start
													//playing, exit or view instructions.

	void StartGameScreen();							//This state should initialize the game,
													//putting it into a playable state.

	void LoadGameScreen();							//This state should load your last save file.
													//If there's no file, start a new file.

	void SaveGameScreen();							//This state should save the status of the game
													//to be loaded at a later date.

	void GameScreen();								//This is the game state, where we play the game.
													
	void PauseScreen();								//This state should stop the game temporarily.

	void LoseGameScreen();							//This state should end the game and allow the player
													//to either exit or retry.

	void WinGameScreen();							//Same as the Lose state but with a victory message!

	void GetPlayerAction();							//This function gets the players next action.

	void MovePlayer();								//This function lets our player move to
													//any connected rooms.

	void MoveWumpus();								//This function randomly moves the wumpus to
													//a safe location nearby.

	void Shoot();									//This function allows the player to shoot
													//to a nearby location and takes an arrow.

	void CreditsScreen();							//This state shows the creator of this game and
													//the original wumpus.

	void InstructionsScreen();						//This state shows the rules of the game.

	void SetExitTrue();								//This sets the Exit bool so that we may
													//exit the game loop and close the application.

	bool GetExit();									//Returns the value of the Exit bool.

	bool LossCheck();								//This functions checks if the player should lose.

	bool DangerCheck();								//This function checks if there are nearby dangers.

private:
	STATE state;
	Room rooms[20];
	Player player;
	Wumpus wumpus;
	int turn;
	bool exit;
	bool resume;
	sf::Texture currentTexture;
	sf::Texture cave;
	sf::Texture splash;
	sf::Texture pitLoss;
	sf::Texture wumpusLoss;
	sf::Texture victory;
	sf::Sprite sprite;
	sf::RenderWindow window;
};