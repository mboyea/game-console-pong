#include <Windows.h>		//used to interact with the console
#include <string>			//used to convert an int to a wstring & make wstrings
#include <cmath>			//used to round numbers
#include <random>			//used to generate random numbers
#include <ctime>			//used to generate a seed for the random numbers

#define SCREENWIDTH		120
#define SCREENHEIGHT	30

#define CONSOLEWIDTH	(SCREENWIDTH * 8)
#define CONSOLEHEIGHT	(SCREENHEIGHT * 16)

/*FUNCTION DECLARATIONS*/

int chooseDifficulty();
void playPong(int AIdifficulty);
bool bEnemyShouldMove(int BallX, int BallY, int EnemyPaddleY, int Difficulty);
int getRandomNumber(int rangeMax);



int main() {
	int AIdifficulty = chooseDifficulty();
	playPong(AIdifficulty);
	return 0;
}



int chooseDifficulty() {

	/*INTEGER MACROS*/

	#define MENUWIDTH		80
	#define MENUHEIGHT		4
	#define CURSORWIDTH		1
	#define CURSORHEIGHT	1

	#define DifficultyVeryEasy		5
	#define DifficultyEasy			4
	#define DifficultyNormal		3
	#define DifficultyHard			2
	#define DifficultyVeryHard		1
	#define DifficultyImpossible	0

	#define DifficultyVeryEasyX		(MenuX + 3)
	#define DifficultyEasyX			(MenuX + 18)
	#define DifficultyNormalX		(MenuX + 28)
	#define DifficultyHardX			(MenuX + 41)
	#define DifficultyVeryHardX		(MenuX + 51)
	#define DifficultyImpossibleX	(MenuX + 66)

	#define MenuX					lround((SCREENWIDTH * 0.5) - (MENUWIDTH * 0.5))
	#define MenuY					lround((SCREENHEIGHT * 0.6) + (MENUHEIGHT * 0.5))
	#define CursorY					lround(MenuY - (MENUHEIGHT * 0.5))

	/*VARIABLE DEFINITIONS*/

	int CursorX = DifficultyNormalX;

	/*SPRITE CREATIONS*/

	//menu sprite
	std::wstring menuSprite;
	menuSprite += L" ______________________________________________________________________________ ";
	menuSprite += L"|                          Press [Enter] to continue.                          |";
	menuSprite += L"| ( )Very Easy   ( )Easy   ( )Normal    ( )Hard   ( )Very Hard   ( )Impossible |";
	menuSprite += L"|______________________________________________________________________________|";

	//cursor sprite
	std::wstring cursorSprite;
	cursorSprite += L"o";

	/*SCREEN CREATION*/

	//create screen buffer
	TCHAR *screen = new TCHAR[SCREENWIDTH*SCREENHEIGHT];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	//TODO: set the window width and height for the menu

	//game loop
	bool bDifficultyChosen = false;
	while (!bDifficultyChosen)
	{
		/*USER INPUT*/

		if ((GetKeyState('D') < 0) || (GetKeyState(VK_RIGHT) < 0)) {
			if (CursorX == DifficultyVeryEasyX) {
				CursorX = DifficultyEasyX;
			}
			else if (CursorX == DifficultyEasyX) {
				CursorX = DifficultyNormalX;
			}
			else if (CursorX == DifficultyNormalX) {
				CursorX = DifficultyHardX;
			}
			else if (CursorX == DifficultyHardX) {
				CursorX = DifficultyVeryHardX;
			}
			else if (CursorX == DifficultyVeryHardX) {
				CursorX = DifficultyImpossibleX;
			}
			else if (CursorX == DifficultyImpossibleX) {
				CursorX = DifficultyVeryEasyX;
			}
			Sleep(static_cast<int>(150));
		}
		if ((GetKeyState('A') < 0) || (GetKeyState(VK_LEFT) < 0)) {
			if (CursorX == DifficultyVeryEasyX) {
				CursorX = DifficultyImpossibleX;
			}
			else if (CursorX == DifficultyEasyX) {
				CursorX = DifficultyVeryEasyX;
			}
			else if (CursorX == DifficultyNormalX) {
				CursorX = DifficultyEasyX;
			}
			else if (CursorX == DifficultyHardX) {
				CursorX = DifficultyNormalX;
			}
			else if (CursorX == DifficultyVeryHardX) {
				CursorX = DifficultyHardX;
			}
			else if (CursorX == DifficultyImpossibleX) {
				CursorX = DifficultyVeryHardX;
			}
			Sleep(static_cast<int>(150));
		}
		if (GetKeyState(VK_RETURN) < 0) {
			if (CursorX == DifficultyVeryEasyX) {
				return DifficultyVeryEasy;
			}
			else if (CursorX == DifficultyEasyX) {
				return DifficultyEasy;
			}
			else if (CursorX == DifficultyNormalX) {
				return DifficultyNormal;
			}
			else if (CursorX == DifficultyHardX) {
				return DifficultyHard;
			}
			else if (CursorX == DifficultyVeryHardX) {
				return DifficultyVeryHard;
			}
			else if (CursorX == DifficultyImpossibleX) {
				return DifficultyImpossible;
			}
			Sleep(static_cast<int>(150));
		}

		/*SPRITE WRITING*/

		//writes space to each character on the screen
		for (int x = 0; x < SCREENWIDTH; x++) {
			for (int y = 0; y < SCREENHEIGHT; y++) {
				if (y <= SCREENHEIGHT)
					screen[y*SCREENWIDTH + x] = ' ';
			}
		}

		//write menu to screen
		for (int x = 0; x < MENUWIDTH; x++) {
			for (int y = 0; y < MENUHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - MenuY)) * SCREENWIDTH + x + (MenuX - 1)] = menuSprite[y * MENUWIDTH + x];
			}
		}

		//write cursor to screen
		for (int x = 0; x < CURSORWIDTH; x++) {
			for (int y = 0; y < CURSORHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - CursorY)) * SCREENWIDTH + x + (CursorX - 1)] = cursorSprite[y * CURSORWIDTH + x];
			}
		}

		/*DISPLAY SCREEN*/

		//display screen
		screen[SCREENWIDTH * SCREENHEIGHT - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, SCREENWIDTH * SCREENHEIGHT, { 0,0 }, &dwBytesWritten);

		/*GAME SPEED*/

		Sleep(static_cast<int>(25));
	}
	return DifficultyNormal;
}

void playPong(int AIdifficulty) {

	/*INTEGER MACROS*/

#define BALLWIDTH			1
#define BALLHEIGHT			1
#define PADDLEWIDTH			1
#define PADDLEHEIGHT		4
#define SCOREBOARDWIDTH		20
#define SCOREBOARDHEIGHT	4
#define POINTSWIDTH			2
#define POINTSHEIGHT		1

#define PlayerPaddleX		(SCREENWIDTH - 10)
#define EnemyPaddleX		11

#define PlayerScoreboardX	(PlayerPaddleX - 40)
#define PlayerScoreboardY	(SCREENHEIGHT - 2)
#define EnemyScoreboardX	(EnemyPaddleX + 20)
#define EnemyScoreboardY	(SCREENHEIGHT - 2)
#define PlayerPointsX		(PlayerScoreboardX + 16)
#define PlayerPointsY		(PlayerScoreboardY - 2)
#define EnemyPointsX		(EnemyScoreboardX + 16)
#define EnemyPointsY		(EnemyScoreboardY - 2)

	/*VARIABLE DEFINITIONS*/

	int BallX = lround(SCREENWIDTH * 0.5);		//ball position x
	int BallY = lround(SCREENHEIGHT * 0.5);		//ball position y
	int BallVX = -1;							//ball velocity x
	int BallVY = 1;								//ball velocity y
	int PlayerPaddleY = lround((SCREENHEIGHT * 0.5) + (PADDLEHEIGHT * 0.5));	//player paddle position y
	int EnemyPaddleY = lround((SCREENHEIGHT * 0.5) + (PADDLEHEIGHT * 0.5));		//enemy paddle position y
	int PlayerPoints = 0;
	int EnemyPoints = 0;

	/*SPRITE CREATIONS*/

	//ball sprite
	std::wstring ballSprite;
	ballSprite += L"o";

	//paddle sprite
	std::wstring paddleSprite;
	paddleSprite += L"|";
	paddleSprite += L"|";
	paddleSprite += L"|";
	paddleSprite += L"|";

	//player scoreboard sprite
	std::wstring scoreboardPlayerSprite;
	scoreboardPlayerSprite += L" __________________ ";
	scoreboardPlayerSprite += L"|                  |";
	scoreboardPlayerSprite += L"| Player Score:    |";
	scoreboardPlayerSprite += L"|__________________|";

	//enemy scoreboard sprite
	std::wstring scoreboardEnemySprite;
	scoreboardEnemySprite += L" __________________ ";
	scoreboardEnemySprite += L"|                  |";
	scoreboardEnemySprite += L"|  Enemy Score:    |";
	scoreboardEnemySprite += L"|__________________|";

	std::wstring playerPointsSprite;
	playerPointsSprite = L"0 ";

	std::wstring enemyPointsSprite;
	enemyPointsSprite = L"0 ";

	/*SCREEN CREATION*/

	//create screen buffer
	TCHAR *screen = new TCHAR[SCREENWIDTH*SCREENHEIGHT];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	//TODO: set the window width and height for the screen

	//game loop
	while (true)
	{
		/*MOVEMENT & PHYSICS*/

		//do player paddle movement
		if ((GetKeyState('W') < 0) || (GetKeyState(VK_UP) < 0)) {
			PlayerPaddleY++;
		}
		else if ((GetKeyState('S') < 0) || (GetKeyState(VK_DOWN) < 0)) {
			PlayerPaddleY--;
		}

		//do enemy paddle movement
		if (bEnemyShouldMove(BallX, BallY, EnemyPaddleY, AIdifficulty)) {
			if (BallY > (EnemyPaddleY - lround(PADDLEHEIGHT * 0.5))) {
				EnemyPaddleY++;
			}
			if (BallY < (EnemyPaddleY - lround(PADDLEHEIGHT * 0.5))) {
				EnemyPaddleY--;
			}
		}

		//do paddle wall collision
		if (PlayerPaddleY > SCREENHEIGHT) {
			PlayerPaddleY = SCREENHEIGHT;
		}
		else if ((PlayerPaddleY - PADDLEHEIGHT) < 1) {
			PlayerPaddleY = PADDLEHEIGHT;
		}
		if (EnemyPaddleY > SCREENHEIGHT) {
			EnemyPaddleY = SCREENHEIGHT;
		}
		else if ((EnemyPaddleY - PADDLEHEIGHT) < 1) {
			EnemyPaddleY = PADDLEHEIGHT;
		}

		//do ball movement
		BallX += BallVX;
		BallY += BallVY;

		//do ball wall collision
		if (BallX > SCREENWIDTH) {
			BallX = SCREENWIDTH;
			BallVX = -1;
			EnemyPoints++;
			//update enemy points sprite
			enemyPointsSprite = std::to_wstring(EnemyPoints);
		}
		if (BallX < 1) {
			BallX = 1;
			BallVX = 1;
			PlayerPoints++;
			playerPointsSprite = std::to_wstring(PlayerPoints);

		}
		if (BallY > SCREENHEIGHT) {
			BallY = SCREENHEIGHT;
			BallVY = -1;
		}
		if (BallY < 1) {
			BallY = 1;
			BallVY = 1;
		}

		//do paddle ball collision
		if (BallX == PlayerPaddleX) {
			if ((BallY == PlayerPaddleY) || (BallY == PlayerPaddleY - 1) || (BallY == PlayerPaddleY - 2) || (BallY == PlayerPaddleY - 3)) {
				BallVX = -1;
			}
		}
		else if (BallX == EnemyPaddleX) {
			if ((BallY == EnemyPaddleY) || (BallY == EnemyPaddleY - 1) || (BallY == EnemyPaddleY - 2) || (BallY == EnemyPaddleY - 3)) {
				BallVX = 1;
			}
		}

		/*SPRITE WRITING*/
		
		//writes space to each character on the screen
		for (int x = 0; x < SCREENWIDTH; x++) {
			for (int y = 0; y < SCREENHEIGHT; y++) {
				if (y <= SCREENHEIGHT)
					screen[y*SCREENWIDTH + x] = ' ';
			}
		}
		
		//write player scoreboard to the screen
		for (int x = 0; x < SCOREBOARDWIDTH; x++) {
			for (int y = 0; y < SCOREBOARDHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - PlayerScoreboardY)) * SCREENWIDTH + x + (PlayerScoreboardX - 1)] = scoreboardPlayerSprite[y * SCOREBOARDWIDTH + x];
			}
		}

		//write player points to the screen
		for (int x = 0; x < POINTSWIDTH; x++) {
			for (int y = 0; y < POINTSHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - PlayerPointsY)) * SCREENWIDTH + x + (PlayerPointsX - 1)] = playerPointsSprite[y * POINTSWIDTH + x];
			}
		}

		//write enemy scoreboard to the screen
		for (int x = 0; x < SCOREBOARDWIDTH; x++) {
			for (int y = 0; y < SCOREBOARDHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - EnemyScoreboardY)) * SCREENWIDTH + x + (EnemyScoreboardX - 1)] = scoreboardEnemySprite[y * SCOREBOARDWIDTH + x];
			}
		}

		//write enemy points to the screen
		for (int x = 0; x < POINTSWIDTH; x++) {
			for (int y = 0; y < POINTSHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - EnemyPointsY)) * SCREENWIDTH + x + (EnemyPointsX - 1)] = enemyPointsSprite[y * POINTSWIDTH + x];
			}
		}

		//write ball to screen
		for (int x = 0; x < BALLWIDTH; x++) {
			for (int y = 0; y < BALLHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - BallY)) * SCREENWIDTH + x + (BallX - 1)] = ballSprite[y * BALLWIDTH + x];
			}
		}

		//write player paddle to screen
		for (int x = 0; x < PADDLEWIDTH; x++) {
			for (int y = 0; y < PADDLEHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - PlayerPaddleY)) * SCREENWIDTH + x + (PlayerPaddleX - 1)] = paddleSprite[y * PADDLEWIDTH + x];
			}
		}

		//write enemy paddle to screen
		for (int x = 0; x < PADDLEWIDTH; x++) {
			for (int y = 0; y < PADDLEHEIGHT; y++) {
				screen[(y + (SCREENHEIGHT - EnemyPaddleY)) * SCREENWIDTH + x + (EnemyPaddleX - 1)] = paddleSprite[y * PADDLEWIDTH + x];
			}
		}

		/*DISPLAY SCREEN*/

		//display screen
		screen[SCREENWIDTH * SCREENHEIGHT - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, SCREENWIDTH * SCREENHEIGHT, { 0,0 }, &dwBytesWritten);

		/*GAME SPEED*/

		//wait 40 miliseconds (25 FPS)
		Sleep(static_cast<int>(40));
	}
	return;
}

//enemy AI (the closer difficluty is to 1, the harder the AI is to beat)
bool bEnemyShouldMove(int BallX, int BallY, int EnemyPaddleY, int Difficulty) {
	if (getRandomNumber(10 - Difficulty) == 1) {
		return false;
	}
	if (BallX < (EnemyPaddleX + lround(SCREENWIDTH * 0.5) + getRandomNumber(50))) {
		if (BallY > (EnemyPaddleY + Difficulty)) {
			return true;
		}
		else if (BallY < ((EnemyPaddleY + PADDLEHEIGHT - 1) - Difficulty)) {
			return true;
		}
		else return false;
	}
	return false;
}

//random number generator
int getRandomNumber(int rangeMax) {
	std::mt19937 randNumb((unsigned int)time(NULL));
	std::uniform_int_distribution<int> dist(1, rangeMax);
	return dist(randNumb);
}
