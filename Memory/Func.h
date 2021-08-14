#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>		// _getch();
#include <cmath>
#pragma warning( disable : 4996)

using namespace std;

__declspec(selectany)  char tab[8]{ "\t\t\t\t\t\t\t" };
__declspec(selectany)  char tab_er[11]{ "\a\n\t\t\t\t\t\t\t\t" };

struct S_Card
{
	int Number{ 0 };
	bool ShowNow{ false };
	bool Opened{ false };
	bool Illum{ false };
	int Color{ 0 };
};

struct S_Game
{
	// Карти
	int Q_Card{ 0 };
	const int Q_Color{ 12 };
	const int ColorArr[12]{ 16,32,48,64,80,96,128,176,192,208,224,240 };
	S_Card CardsArr[24];

	// Статистика гри
	int BotCount{ 0 };
	int BotHit{ 0 };
	float BotPerc{ 0.0 };
	int UserCount{ 0 };
	int UserHit{ 0 };
	float UserPerc{ 0.0 };
	int TotalOpened{ 0 };

	// Поточні налаштування гри
	int Level;			// 0, 1, 2 - складність
	int Delay;			// затримка відкриття в секундах
	bool PlSound;		// звуковий супровід
	int Matrix;			// матриця (індекс в масиві варіантів матриць)

	// Типові налаштування гри
	const int Def_Level{ 1 };
	const int Def_Delay{ 3 };
	const bool Def_PlSound{ 1 };
	const int Def_Matrix{ 4 };			// 0: 4 x 3 *** 1: 4 x 4 *** 2: 5 x 4 *** 3: 6 x 3 *** 4: 6 x 4

	// Масив варіантів матриці
	const int MatrixArr[5][2]
	{
		{4,3},
		{4,4},
		{5,4},
		{6,3},
		{6,4}
	};

	// Для зручності друку
	int Row;
	int Col;
};

struct S_Screen
{
	const int Size_x = 14;
	const int Size_y = 9;
	const int X_pos{ Size_x / 2 - 1 };
	const int Y_pos{ Size_y / 2 };
};

// Основні
void startAndSetup(S_Game*& game, int& reStart);
void setByDefault(S_Game*& game);
void prepareGame(S_Game*& game);
void prnCards(S_Game*& game, S_Screen*& scr, int mode = 0);

// Допоміжні
void numToStr(char* str, int a);
bool strToNum(char* str, int& a, int& b);
bool inputStr(S_Game*& game, char* str, int& a, int& b);
void botAct(S_Game*& game, int& a, int& b);
void showABit(const int& delay);
int menuSelect(int a, bool tab = false);
int funcReStart();
