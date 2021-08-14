#include "Func.h"
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Налаштування
void startAndSetup(S_Game*& game, int& start)
{
	do
	{
		system("cls");
		cout << "\n ВІТАЄМО У ГРІ \"ПАМ\'ЯТЬ\" (ЗМАГАЛЬНИЙ РЕЖИМ)\n--------------------------------------------\n\n";
		cout << "\n\tНАЛАШТУВАННЯ ТА ДІЇ:\n";
		cout << "\t-----------------------\n";
		cout << "\t Рівень складності:\n";
		(game->Level == 0) ? cout << "\t • 1: простий\n" : cout << "\t   1: простий\n";
		(game->Level == 1) ? cout << "\t • 2: середній\n" : cout << "\t   2: середній\n";
		(game->Level == 2) ? cout << "\t • 3: складний\n\n" : cout << "\t   3: складний\n\n";
		cout << "\t Розмір матриці:\n";
		(game->Matrix == 0) ? cout << "\t • 4: 4 x 3\n" : cout << "\t   4: 4 x 3\n";
		(game->Matrix == 1) ? cout << "\t • 5: 4 x 4\n" : cout << "\t   5: 4 x 4\n";
		(game->Matrix == 2) ? cout << "\t • 6: 5 x 4\n" : cout << "\t   6: 5 x 4\n";
		(game->Matrix == 3) ? cout << "\t • 7: 6 x 3\n" : cout << "\t   7: 6 x 3\n";
		(game->Matrix == 4) ? cout << "\t • 8: 6 x 4\n\n" : cout << "\t   8: 6 x 4\n\n";
		cout << "\t Звукові сигнали:\n";
		(game->PlSound) ? cout << "\t • 9:  увімкнено\n" : cout << "\t   9:  увімкнено\n";
		(!game->PlSound) ? cout << "\t • 10: вимкнено\n\n" : cout << "\t   10: вимкнено\n\n";
		cout << "\t Час затримки показу:\n";
		(game->Delay == 1) ? cout << "\t • 11: 1 сек\n" : cout << "\t   11: 1 сек\n";
		(game->Delay == 2) ? cout << "\t • 12: 2 сек\n" : cout << "\t   12: 2 сек\n";
		(game->Delay == 3) ? cout << "\t • 13: 3 сек\n" : cout << "\t   13: 3 сек\n";
		(game->Delay == 4) ? cout << "\t • 14: 4 сек\n" : cout << "\t   14: 4 сек\n";
		(game->Delay == 5) ? cout << "\t • 15: 5 сек\n\n" : cout << "\t   15: 5 сек\n\n";
		cout << "\t 16: Скинути на типові\n\n";
		//cout << "\t---\n";
		cout << "\t 17: Вийти з програми\n";
		cout << "\t 0:  Розпочати гру\n";
		cout << "\t-----------------------\n";

		int sel{ menuSelect(17, true) };

		switch (sel)
		{
		case 0:
			start = 1;		// запуск гри з поточними налаштуваннями
			return;
		case 1:
			game->Level = 0;
			break;
		case 2:
			game->Level = 1;
			break;
		case 3:
			game->Level = 2;
			break;
		case 4:
			game->Matrix = 0;
			game->Col = game->MatrixArr[game->Matrix][0];
			game->Row = game->MatrixArr[game->Matrix][1];
			game->Q_Card = game->Col * game->Row;
			break;
		case 5:
			game->Matrix = 1;
			game->Col = game->MatrixArr[game->Matrix][0];
			game->Row = game->MatrixArr[game->Matrix][1];
			game->Q_Card = game->Col * game->Row;
			break;
		case 6:
			game->Matrix = 2;
			game->Col = game->MatrixArr[game->Matrix][0];
			game->Row = game->MatrixArr[game->Matrix][1];
			game->Q_Card = game->Col * game->Row;
			break;
		case 7:
			game->Matrix = 3;
			game->Col = game->MatrixArr[game->Matrix][0];
			game->Row = game->MatrixArr[game->Matrix][1];
			game->Q_Card = game->Col * game->Row;
			break;
		case 8:
			game->Matrix = 4;
			game->Col = game->MatrixArr[game->Matrix][0];
			game->Row = game->MatrixArr[game->Matrix][1];
			game->Q_Card = game->Col * game->Row;
			break;
		case 9:
			game->PlSound = true;
			break;
		case 10:
			game->PlSound = false;
			break;
		case 11:
			game->Delay = 1;
			break;
		case 12:
			game->Delay = 2;
			break;
		case 13:
			game->Delay = 3;
			break;
		case 14:
			game->Delay = 4;
			break;
		case 15:
			game->Delay = 5;
			break;
		case 16:
			setByDefault(game);
			break;
		case 17:
			start = 0;			// вихід з програми
			return;
		}
	} while (true);
}

// Прописує в поточні значення типові значення
void setByDefault(S_Game*& game)
{
	game->Level = game->Def_Level;
	game->Matrix = game->Def_Matrix;
	game->PlSound = game->Def_PlSound;
	game->Delay = game->Def_Delay;

	game->Col = game->MatrixArr[game->Matrix][0];
	game->Row = game->MatrixArr[game->Matrix][1];

	game->Q_Card = game->Col * game->Row;
}

// Генерує розкладку карт перед початком гри
void prepareGame(S_Game*& game)
{
	// Присвоюємо картам номери 
	for (int i{ 0 }; i < game->Q_Card; ++i)
		game->CardsArr[i].Number = i + 1;

	// Занулюємо в картах всі поля видимості і поле кольору
	for (int i{ 0 }; i < game->Q_Card; ++i)
	{
		game->CardsArr[i].Illum = false;
		game->CardsArr[i].ShowNow = false;
		game->CardsArr[i].Opened = false;
		game->CardsArr[i].Color = 0;
	}

	// Генеруємо і присвоюємо картам кольори
	int card_ind{ 0 }, col_ind{ 0 };
	bool col_rep{ false };

	for (int i{ 0 }; i < game->Q_Card; ++i)
	{
		col_rep = false;
		col_ind = rand() % game->Q_Color;
		if (!i)
		{
			game->CardsArr[i].Color = game->ColorArr[col_ind];
			do {
				card_ind = rand() % game->Q_Card;
			} while (!card_ind);

			game->CardsArr[card_ind].Color = game->ColorArr[col_ind];
			continue;
		}
		else if (game->CardsArr[i].Color)
			continue;
		else
		{
			for (int j{ 0 }; j < i; ++j)
				if (game->ColorArr[col_ind] == game->CardsArr[j].Color)
				{
					col_rep = true;
					break;
				}

			if (col_rep)
			{
				--i;
				continue;
			}

			game->CardsArr[i].Color = game->ColorArr[col_ind];

			do {
				card_ind = rand() % game->Q_Card;

			} while (game->CardsArr[card_ind].Color);

			game->CardsArr[card_ind].Color = game->ColorArr[col_ind];
		}
	}

	// Занулюємо статистику (це потрібно, коли гра в одному сеансі не перша)
	game->BotCount = 0;
	game->BotHit = 0;
	game->BotPerc = 0;
	game->UserCount = 0;
	game->UserHit = 0;
	game->UserPerc = 0;
	game->TotalOpened = 0;
}

// Вивід на екран карт
void prnCards(S_Game*& game, S_Screen*& scr, int mode)
{
	system("cls");

	char dispNum[3]{ NULL };
	int curr_col{ 0 };

	cout << '\n' << endl;

	for (int i{ 0 }; i < game->Row; ++i)						// рядів карт
	{
		for (int j{ 0 }; j < scr->Size_y; ++j)					// рядів в карті
		{
			cout << tab;
			for (int k{ 0 }; k < game->Col; ++k)				// колонок карт
			{
				numToStr(dispNum, game->CardsArr[i * game->Col + k].Number);

				for (int z{ 0 }; z < scr->Size_x; ++z)			// колонок в карті
				{
					switch (mode)
					{
					case 0:
						curr_col = 112;
						break;
					case 1:
						curr_col = game->CardsArr[i * game->Col + k].Color;
						break;
					case 2:
						if (game->CardsArr[i * game->Col + k].ShowNow)
							curr_col = game->CardsArr[i * game->Col + k].Color;
						else
							curr_col = 112;
						break;
					case 3:
						if (game->CardsArr[i * game->Col + k].Opened)
							curr_col = game->CardsArr[i * game->Col + k].Color;
						else
							curr_col = 112;
						break;
					}
					SetConsoleTextAttribute(hConsole, curr_col);
					if (mode != 1 && mode != 2 && mode != 3 && z == scr->X_pos && j == scr->Y_pos)
					{
						cout << dispNum;
						++z;
					}
					else if (mode == 3 && z == scr->X_pos && j == scr->Y_pos)
					{
						if (game->CardsArr[i * game->Col + k].Opened)
							(curr_col == 240) ? cout << '•' : cout << ' ';
						else
						{
							cout << dispNum;
							++z;
						}
					}
					else
						(curr_col == 240) ? cout << '•' : cout << ' ';
					SetConsoleTextAttribute(hConsole, 7);
				}
				cout << "   ";

			}
			cout << '\n';
		}
		cout << '\n' << endl;
	}
}


// Допоміжні

// Перетворює номери карт в стрічку для виводу на екран
void numToStr(char* str, int num)
{
	char tmp[5];
	if (num < 10)
	{
		str[0] = '0';
		str[1] = '\0';
		strcat(str, itoa(num, tmp, 10));
	}
	else
		itoa(num, str, 10);
}

//Переводить стрічку ходу гравця у числа
bool strToNum(char* str, int& a, int& b)
{
	char sArr[]{ ".,+-*/ " };
	if (strlen(str) != 5 || !strchr(sArr, str[2]) || !isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) || !isdigit(str[4]))
		return false;

	char tmp[10];
	tmp[2] = '\0';

	tmp[0] = str[0];
	tmp[1] = str[1];
	a = atoi(tmp);

	tmp[0] = str[3];
	tmp[1] = str[4];
	b = atoi(tmp);

	return true;

}

// Функція вводу ходу гравця
bool inputStr(S_Game*& game, char* str, int& a, int& b)
{
	cout << tab << "[формат вводу NN.NN, 0 - перервати гру]" << '\n' << endl;
	do
	{
		cout << tab << "(" << game->UserCount + 1 << ") " << "Ваш хід >>> ";
		cin.getline(str, BUFSIZ);
		cin.clear();

		if (strlen(str) == 1 && str[0] == '0')
		{
			if (game->PlSound)
			{
				Beep(400, 100);
				Beep(400, 100);
				Beep(400, 100);
			}

			return false;
		}


		if (!strToNum(str, a, b) || a < 1 || b < 1 || a > game->Q_Card || b > game->Q_Card || a == b)
		{
			cout << tab_er << "Упс... Не коректний ввід!\n\n";
			continue;
		}

		if (game->CardsArr[a - 1].Opened || game->CardsArr[b - 1].Opened)
		{
			cout << tab_er << "УВАЖНІШЕ! Принаймні одна карта з Вашого ходу вже відгадана!\n\n";
			continue;
		}

		return true;

	} while (true);
}

// Функція прорахунку ходу бота
void botAct(S_Game*& game, int& a, int& b)
{
	int ind_a{ 0 }, ind_b{ 0 };
	bool flag{ false };

	// Поточний фрагмент коду тільки для 1-го і 2-го рівнів складності
	if (game->Level != 0)
	{
		// Перевіряємо в масиві запалені карти, а саме: чи є серед них пари по кольору, якщо так, відкриваємо саме їх
		for (int i{ 0 }; i < game->Q_Card - 1; ++i)
		{
			// якщо карта не запалена або відкрита пропускаємо
			if (!game->CardsArr[i].Illum || game->CardsArr[i].Opened)
				continue;

			for (int j{ i + 1 }; j < game->Q_Card; ++j)
			{
				// якщо наступна в порівнянні карта не запалена або відкрита пропускаємо
				if (!game->CardsArr[j].Illum || game->CardsArr[j].Opened)
					continue;

				if (game->CardsArr[i].Color == game->CardsArr[j].Color)
				{
					a = i;
					b = j;
					return;
				}
			}
		}
	}

	// Вибір першої карти. Всі рівні складності (випадково з невідкритих)
	do {

		ind_a = rand() % game->Q_Card;

		// Якщо випадково знайдена карта вже відкрита на повтор циклу
		if (game->CardsArr[ind_a].Opened)
			continue;

		break;

	} while (true);


	// Вибір 2-ї карти тільки для 2-го (найвищого) рівня складності гри
	if (game->Level == 2)
	{
		// Перевіряємо колір вибраної в алгоритмі вище першої карти на співпадіння по запалених, але ще не відгаданих
		// Якщо знаходимо, то другою відкриваємо її
		for (int i{ 0 }; i < game->Q_Card; ++i)
		{
			// Якщо не запалена або відкрита або це та сама карта пропускаємо
			if (!game->CardsArr[i].Illum || game->CardsArr[i].Opened || ind_a == i)
				continue;

			if (game->CardsArr[ind_a].Color == game->CardsArr[i].Color)
			{
				a = ind_a;
				b = i;
				return;
			}
		}
	}

	// Якщо в алгоримах вище 2-ї карти не згенерували, то друга - випадкова
	do {
		// Вона має бути:
		// - не така сама як перша 
		// - не відкрита

		ind_b = rand() % game->Q_Card;

		if (ind_b == ind_a)
			continue;

		if (game->CardsArr[ind_b].Opened)
			continue;

		break;

	} while (true);

	a = ind_a;
	b = ind_b;
}

// Бігова доріжка під картами на момент відкриття
void showABit(const int& delay)
{
	cout << '\n' << endl;
	for (int i{ 0 }; i < delay; ++i)
	{
		if (!i) {
			cout << tab << "ВІДКРИТО НА " << delay << " СЕКУНД";
			(delay == 1) ? cout << "У (0 " : (delay > 1 && delay < 5) ? cout << "И (0 " : cout << " (0 ";
		}
		if (i) cout << ' ' << i << ' ';
		for (int j{ 0 }; j < 8; ++j) {
			cout << char(149);
			Sleep(125);
		}
		if (i == (delay - 1)) cout << ' ' << delay << ") ЗАКРИВАЮ!";
	}
	Sleep(500);
}

// Функція коректності вибору опції з меню
int menuSelect(int a, bool tab)
{
	int inputValue{ 0 };
	while (1) {
		(!tab) ? cout << ">>> " : cout << "\t>>> ";
		cin >> inputValue;
		if (cin.fail() || inputValue < 0 || inputValue > a) {
			cin.clear();
			cin.ignore(32767, '\n');
			(!tab) ? cout << "\n\t\a" : cout << "\n\t\t\a";
			cout << "Упс... Не коректний ввід!\n\n";
		}
		else
		{
			cin.ignore(32767, '\n');
			return inputValue;
		}
	}
}

// Функція запиту на перезапуск гри
int funcReStart()
{
	int inputValue{ 0 };
	cout << '\n' << endl;
	cout << tab << "Зіграємо ще раз?\n";
	cout << tab << "--------------------------------\n";
	cout << tab << " 1 - з поточними налаштуваннями\n";
	cout << tab << " 2 - з типовими налаштуваннями\n";
	cout << tab << " 3 - зі зміною налаштувань\n";
	cout << tab << " 0 - ні, дякую, іншим разом :(\n";
	cout << tab << "--------------------------------\n";

	while (1) {
		cout << tab << ">>> ";
		cin >> inputValue;
		if (cin.fail() || inputValue < 0 || inputValue > 3) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << tab_er << "\n\t\aУпс... Не коректний ввід!\n";
			continue;
		}
		else
		{
			cin.ignore(32767, '\n');
			return inputValue;
		}
	}
}