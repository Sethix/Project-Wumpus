#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <SFML\Graphics.hpp>
#include "string.h"
#include "gameOptions.h"
#include "gameState.h"

GameState::GameState()
{
	exit = false;

	if (!splash.loadFromFile("Splash.png"))
		exit = true;

	if (!cave.loadFromFile("Background.png"))
		exit = true;

	if (!wumpusLoss.loadFromFile("Wumpus_Death.png"))
		exit = true;

	if (!pitLoss.loadFromFile("Pit_Death.png"))
		exit = true;

	if (!victory.loadFromFile("Victory.png"))
		exit = true;

	currentTexture = splash;

	window.create(sf::VideoMode(400, 400), "Hunt the Wumpus");

	sprite.setTexture(currentTexture);

	resume = false;
	state = Splash;
}

void GameState::CallCurrentState()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	switch (state)
	{
	case Splash:		currentState = &GameState::SplashScreen;
		break;
	case MainMenu:		currentState = &GameState::MainMenuScreen;
		break;
	case StartGame:		currentState = &GameState::StartGameScreen;
		break;
	case LoadGame:		currentState = &GameState::LoadGameScreen;
		break;
	case SaveGame:		currentState = &GameState::SaveGameScreen;
		break;
	case PlayGame:		currentState = &GameState::GameScreen;
		break;
	case Victory:		currentState = &GameState::WinGameScreen;
		break;
	case Loss:			currentState = &GameState::LoseGameScreen;
		break;
	case Paused:		currentState = &GameState::PauseScreen;
		break;
	case Credits:		currentState = &GameState::CreditsScreen;
		break;
	case Instructions:	currentState = &GameState::InstructionsScreen;
		break;
	case Exit:			currentState = &GameState::SetExitTrue;
		break;
	}

	sprite.setTexture(currentTexture);
	window.draw(sprite);
	window.display();
	(this->*currentState)();
}

sf::Texture GameState::GetCurrentTexture()
{
	return currentTexture;
}

void GameState::SplashScreen()
{
	currentTexture = splash;
	
	system("Pause");
	system("cls");

	state = MainMenu;
}

void GameState::MainMenuScreen()
{
	sfw::string inputString = sfw::string(80);
	bool tempBool = true;

	std::cout << "Would you like to Play, Load, Exit, View the Instructions or view the Credits?" << std::endl;

	while (tempBool)
	{
		std::cin >> inputString;

		if (inputString == "Play"				|| inputString == "play" ||
			inputString == "P"					|| inputString == "p")
		{
			state = StartGame;
			tempBool = false;
			system("cls");
		}

		else if (inputString == "Load"			|| inputString == "load" ||
				 inputString == "L"				|| inputString == "l")
		{
			state = LoadGame;
			tempBool = false;
			system("cls");
		}

		else if (inputString == "Exit"			|| inputString == "exit" ||
				 inputString == "E"				|| inputString == "e")
		{
			state = Exit;
			tempBool = false;
		}

		else if (inputString == "Instructions"	|| inputString == "instructions" ||
				 inputString == "I"				|| inputString == "i")
		{
			state = Instructions;
			tempBool = false;
		}

		else if (inputString == "Credits"		|| inputString == "credits" ||
				 inputString == "C"				|| inputString == "c")
		{
			state = Credits;
			tempBool = false;
			system("cls");
		}

		else std::cout << "Error - Please try again." << std::endl;
	}
}

void GameState::StartGameScreen()
{
	Hazard temp;
	turn = 0;

	player.GiveArrows();
	player.SetLoc(PLAYER_STARTING_ROOM);
	wumpus.SetLoc(WUMPUS_STARTING_ROOM);

	for (int i = 0; i < 20; ++i)
	{
		temp = None;

		if (i + 1 == PIT_TRAP_ROOM_ONE ||
			i + 1 == PIT_TRAP_ROOM_TWO ||
			i + 1 == PIT_TRAP_ROOM_THREE)
			temp = PitHazard;

		if (i + 1 == SUPER_BAT_ROOM_ONE ||  
			i + 1 == SUPER_BAT_ROOM_TWO)
			temp = BatHazard;

		if (i + 1 == WUMPUS_STARTING_ROOM)
			temp = WumpusHazard;

		rooms[i] = Room(i, temp);
	}

	currentTexture = cave;
	state = PlayGame;
}

void GameState::LoadGameScreen()
{
	saveData file;

	std::ifstream fin("data.dat", std::ios_base::in | std::ios_base::binary);

	if (fin.good())
		while (!fin.eof() && fin.peek() != EOF)
			fin.read((char*)&file, sizeof(file));

	else state = StartGame;

	fin.close();

	player.SetArrows(file.arrowCount);
	player.SetLoc(file.playerLoc);
	wumpus.SetLoc(file.wumpusLoc);
	turn = file.turn;

	resume = true;

	currentTexture = cave;
	state = PlayGame;
}

void GameState::SaveGameScreen()
{
	saveData file;

	file.turn = turn;
	file.playerLoc = player.GetLoc();
	file.wumpusLoc = wumpus.GetLoc();
	file.arrowCount = player.GetArrows();

	std::ofstream fout("data.dat", std::ios_base::out | std::ios_base::binary);

	if (fout.good())
		fout.write((char*)&file, sizeof(file));

	fout.close();

	currentTexture = cave;
	state = PlayGame;
}

void GameState::GameScreen()
{
	if (!LossCheck())
	{
		if (!resume)
		{
			MoveWumpus();
			++turn;
		}

		resume = false;


		if (turn == 1)
			std::cout << std::endl << "Welcome to Hunt the Wumpus!" << std::endl;

		if (player.GetLoc() == SUPER_BAT_ROOM_ONE ||
			player.GetLoc() == SUPER_BAT_ROOM_TWO)
		{
			player.SetLoc(1);
			std::cout << "You were brought back to the start by a bat!" << std::endl;
		}

		std::cout << std::endl << "Turn: "				<< turn					<< std::endl <<
								  "Arrows: "			<< player.GetArrows()	<< std::endl <<
					              "Current location: "	<< player.GetLoc()		<< std::endl;

		if (DangerCheck() == true)
			std::cout << "You sense danger nearby!" << std::endl;

		GetPlayerAction();

	}
	else state = Loss;
}

void GameState::PauseScreen()
{
	sfw::string inputString = sfw::string(80);
	bool tempBool = true;

	std::cout << std::endl <<	"Game is paused."								<< std::endl
			  <<				"Would you like to continue, save or exit?"		<< std::endl;

	while (tempBool)
	{
		std::cin >> inputString;

		if (inputString == "continue"	|| inputString == "Continue" ||
			inputString == "c"			|| inputString == "C")
		{
			state = PlayGame;
			resume = true;
			tempBool = false;
			system("cls");
		}

		else if (inputString == "Save"	|| inputString == "save" ||
				 inputString == "S"		|| inputString == "s")
		{
			state = SaveGame;
			resume = true;
			tempBool = false;
			system("cls");
		}

		else if (inputString == "Exit"	|| inputString == "exit" ||
				 inputString == "E"		|| inputString == "e")
		{
			state = Exit;
			tempBool = false;
		}

		else std::cout << "Error - Please try again." << std::endl;
	}

}

void GameState::LoseGameScreen()
{
	sfw::string inputString = sfw::string(80);
	bool tempBool = true;

	std::cout << "You lose. Would you like to play again? Y/N" << std::endl;

	while (tempBool)
	{
		std::cin >> inputString;

		if (inputString == "yes"		|| inputString == "Yes" ||
			inputString == "y"			|| inputString == "Y")
		{
			state = StartGame;
			tempBool = false;
			currentTexture = cave;
			system("cls");
		}

		else if (inputString == "No"	|| inputString == "no" ||
				 inputString == "N"		|| inputString == "n")
		{
			state = Exit;
			tempBool = false;
		}

		else std::cout << "Error - Please try again." << std::endl;
	}
}

void GameState::WinGameScreen()
{
	sfw::string inputString = sfw::string(80);
	bool tempBool = true;

	std::cout << "You win! Would you like to play again? Y/N" << std::endl;

	while (tempBool)
	{
		std::cin >> inputString;

		if (inputString == "yes"		|| inputString == "Yes" ||
			inputString == "y"			|| inputString == "Y")
		{
			state = StartGame;
			currentTexture = pitLoss;
			tempBool = false;
		}

		else if (inputString == "No"	|| inputString == "no" ||
				 inputString == "N"		|| inputString == "n")
		{
			state = Exit;
			tempBool = false;
		}

		else std::cout << "Error - Please try again." << std::endl;
	}

}

void GameState::GetPlayerAction()
{
	sfw::string inputString = sfw::string(80);
	bool tempBool = true;

	std::cout << std::endl << "Would you like to move, shoot or pause?" << std::endl;

	while (tempBool)
	{
		std::cin >> inputString;

		if (inputString == "move"			|| inputString == "Move" ||
			inputString == "m"				|| inputString == "M")
		{
			MovePlayer();
			tempBool = false;
		}

		else if (inputString == "Shoot"		|| inputString == "shoot" ||
				 inputString == "S"			|| inputString == "s")
		{
			Shoot();
			tempBool = false;
		}

		else if (inputString == "Pause"		|| inputString == "pause" ||
				 inputString == "P"			|| inputString == "p")
		{
			system("cls");
			state = Paused;
			tempBool = false;
		}

		else std::cout << "Error - Please try again." << std::endl;
	}
}

void GameState::MovePlayer()
{
	int temp = 0;

	std::cout << "Please enter a number between 1 and 3." << std::endl;

	while (temp < 1 || temp > 3)
	{
		std::cin >> temp;

		if (temp < 1 && temp > 3)
			std::cout << "Error - Please try again." << std::endl;

		std::cin.clear();
		std::cin.ignore();
	}

	system("cls");

	switch (temp)
	{
	case 1: player.SetLoc(rooms[player.GetLoc() - 1].GetConnectionOne());
		break;
	case 2: player.SetLoc(rooms[player.GetLoc() - 1].GetConnectionTwo());
		break;
	case 3: player.SetLoc(rooms[player.GetLoc() - 1].GetConnectionThree());
		break;
	}
}

void GameState::MoveWumpus()
{
	int temp = rand();

	int c1 = rooms[wumpus.GetLoc() - 1].GetConnectionOne();
	int c2 = rooms[wumpus.GetLoc() - 1].GetConnectionTwo();
	int c3 = rooms[wumpus.GetLoc() - 1].GetConnectionThree();

	bool c1Safe = false;
	bool c2Safe = false;
	bool c3Safe = false;


	if (rooms[c1 - 1].GetHazard() == None)
		c1Safe = true;

	if (rooms[c2 - 1].GetHazard() == None)
		c2Safe = true;

	if (rooms[c3 - 1].GetHazard() == None)
		c3Safe = true;

	if (temp % 3 == 0 && c1Safe)
	{
		rooms[wumpus.GetLoc() - 1].SetHazard(None);
		wumpus.SetLoc(c1);
		rooms[c1 - 1].SetHazard(WumpusHazard);
	}

	if (temp % 3 == 1 && c2Safe)
	{
		rooms[wumpus.GetLoc() - 1].SetHazard(None);
		wumpus.SetLoc(c2);
		rooms[c2 - 1].SetHazard(WumpusHazard);
	}

	if (temp % 3 == 2 && c3Safe)
	{
		rooms[wumpus.GetLoc() - 1].SetHazard(None);
		wumpus.SetLoc(c3);
		rooms[c3 - 1].SetHazard(WumpusHazard);
	}
}

void GameState::Shoot()
{
	int temp = 0;

	std::cout << "Please input a number between 1 - 3." << std::endl;

	while (temp < 1 || temp > 3)
	{
		std::cin >> temp;

		if (temp < 1 && temp > 3)
			std::cout << "Error - Please try again." << std::endl;

		std::cin.clear();
		std::cin.ignore();
	}

	system("cls");

	switch (temp)
	{
	case 1: if (wumpus.GetLoc() == rooms[player.GetLoc() - 1].GetConnectionOne())
		state = Victory;
		break;
	case 2: if (wumpus.GetLoc() == rooms[player.GetLoc() - 1].GetConnectionTwo())
		state = Victory;
		break;
	case 3: if (wumpus.GetLoc() == rooms[player.GetLoc() - 1].GetConnectionThree())
		state = Victory;
		break;
	}

	if (state != Victory) std::cout << std::endl << "You missed!" << std::endl;
	else currentTexture = victory;

	player.UseArrow();
}

void GameState::CreditsScreen()
{
	std::cout << "Original hunt the wumpus by Gregory Yob"		<< std::endl
		<<		 "This application was created by Justin Hamm"	<< std::endl;

	system("Pause");
	system("cls");

	state = MainMenu;
}

void GameState::InstructionsScreen()
{
	system("cls");
	std::cout << "Your objective is to shoot the wumpus before you either..." << std::endl
		<< "Run out of arrows" << std::endl
		<< "Fall in a pit" << std::endl
		<< "Get attacked by the wumpus" << std::endl << std::endl
		<< "Every turn you may move or shoot." << std::endl
		<< "When you move or shoot, you pick a room using a number between 1 and 3." << std::endl
		<< "If you pick 1 you will travel to the lowest numbered room and vice versa for 3." << std::endl
		<< "If you move into a room with a super bat you will be brought to the start." << std::endl
		<< "Beware! The wumpus moves occasionally." << std::endl << std::endl;

	system("Pause");
	system("cls");

	state = MainMenu;
}

void GameState::SetExitTrue()
{
	exit = true;
}

bool GameState::GetExit()
{
	return exit;
}

bool GameState::LossCheck()
{
	if (rooms[player.GetLoc() - 1].GetHazard() == None &&
		player.HasArrows() == true ||
		rooms[player.GetLoc() - 1].GetHazard() == BatHazard &&
		player.HasArrows() == true) 

		 return false;

	else
	{
		if (rooms[player.GetLoc() - 1].GetHazard() == WumpusHazard) currentTexture = wumpusLoss;
		if (rooms[player.GetLoc() - 1].GetHazard() == PitHazard) currentTexture = pitLoss;
		return true;
	}
}

bool GameState::DangerCheck()
{
	int c1, c2, c3;

	c1 = rooms[player.GetLoc() - 1].GetConnectionOne();
	c2 = rooms[player.GetLoc() - 1].GetConnectionTwo();
	c3 = rooms[player.GetLoc() - 1].GetConnectionThree();

	if (rooms[c1 - 1].GetHazard() == None &&
		rooms[c2 - 1].GetHazard() == None &&
		rooms[c3 - 1].GetHazard() == None) return false;
	else return true;
}
