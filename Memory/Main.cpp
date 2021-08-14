#include "Func.h"
#include <iostream>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	// Відкриваємо консоль в максимальному розмірі вікна
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

	// Режим друку карт
	// 0 - всі закриті (дефолт)
	// 1 - фора (всі відкриті)
	// 2 - короткочасно відкриті 2 карти після чийогось ходу, всі решта закриті
	// 3 - відкриті всі вгадані карти, решта - сірі

	S_Game* game = new S_Game;
	S_Screen* scr = new S_Screen;
	char inpStr[10];
	int a{ 0 }, b{ 0 };
	bool hit{ false };
	bool theEnd{ false };
	bool abort{ false };

	// Значення змінної Start
	// -1 - перший запуск
	// 0 - завершити роботу програми
	// 1 - запустити з поточними налаштуваннями
	// 2 - запустити з типовими налаштуваннями
	// 3 - запустити зі зміною налаштувань

	// Старт гри
	int start{ -1 };
	setByDefault(game);

	do
	{
		if (start == -1 || start == 3)
			startAndSetup(game, start);

		if (!start)
			break;

		if (start == 2)
			setByDefault(game);

		a = 0, b = 0;
		hit = false;
		theEnd = false;

		// Готуємо гру (генерація карт, занулення полів і статистики)
		prepareGame(game);

		// Початок
		system("cls");
		cout << tab << '\n' << endl;
		cout << tab << "РОЗПОЧИНАЄМО!!!\n";
		cout << tab << "----------------\n\n";
		cout << tab << "Карти буде відкрито на " << game->Delay << " сек, намагайтесь запам\'ятати їх розташування!!!\n\n";
		cout << tab << "Як тільки будете готові, натисніть будь-яку клавішу...";

		cin.clear();
		_getch();

		// Запалюємо карти
		prnCards(game, scr, 1);
		showABit(game->Delay);
		prnCards(game, scr, 0);

		// Починаємо. Цикл ходів
		do
		{
			// Ходи юзера
			do
			{
				a = 0, b = 0, hit = false;

				if (!inputStr(game, inpStr, a, b))
				{
					abort = true;
					break;
				}

				// якщо вгадав
				if (game->CardsArr[a - 1].Color == game->CardsArr[b - 1].Color)
				{
					hit = true;

					game->CardsArr[a - 1].ShowNow = true;
					game->CardsArr[b - 1].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "ВИ ВГАДАЛИ!!!";
					if (game->PlSound)
					{
						Beep(1000, 300);
						Beep(1000, 300);
					}

					showABit(game->Delay);
					game->CardsArr[a - 1].ShowNow = false;
					game->CardsArr[b - 1].ShowNow = false;

					game->CardsArr[a - 1].Opened = true;
					game->CardsArr[b - 1].Opened = true;
					prnCards(game, scr, 3);

					++game->UserHit;
					game->TotalOpened += 2;
				}
				// якщо не вгадав
				else
				{
					hit = false;

					game->CardsArr[a - 1].ShowNow = true;
					game->CardsArr[b - 1].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "ВИ НЕ ВГАДАЛИ :(((";
					if (game->PlSound)
						Beep(400, 300);

					showABit(game->Delay);
					game->CardsArr[a - 1].ShowNow = false;
					game->CardsArr[b - 1].ShowNow = false;
					prnCards(game, scr, 3);

					// Ставимо мітки про запал карт
					game->CardsArr[a - 1].Illum = true;
					game->CardsArr[b - 1].Illum = true;
				}

				++game->UserCount;
				if (game->TotalOpened == game->Q_Card)
					theEnd = true;

			} while (hit && !theEnd);

			if (theEnd || abort)
				break;

			// Ходи бота
			do
			{
				a = 0, b = 0, hit = false;
				cout << tab << "(" << game->BotCount + 1 << ") " << "Хід бота! Натисніть будь-яку клавішу...";

				_getch();

				botAct(game, a, b);

				// якщо вгадав
				if (game->CardsArr[a].Color == game->CardsArr[b].Color)
				{
					hit = true;

					game->CardsArr[a].ShowNow = true;
					game->CardsArr[b].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "БОТ ВГАДАВ!!!";
					if (game->PlSound)
					{
						Beep(1000, 300);
						Beep(1000, 300);
					}

					showABit(game->Delay);
					game->CardsArr[a].ShowNow = false;
					game->CardsArr[b].ShowNow = false;

					game->CardsArr[a].Opened = true;
					game->CardsArr[b].Opened = true;
					prnCards(game, scr, 3);

					++game->BotHit;
					game->TotalOpened += 2;
				}
				// якщо не вгадав
				else
				{
					hit = false;

					game->CardsArr[a].ShowNow = true;
					game->CardsArr[b].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "БОТ НЕ ВГАДАВ :(((";
					if (game->PlSound)
						Beep(400, 300);

					showABit(game->Delay);
					game->CardsArr[a].ShowNow = false;
					game->CardsArr[b].ShowNow = false;
					prnCards(game, scr, 3);

					// Ставимо мітки про запал карт
					game->CardsArr[a].Illum = true;
					game->CardsArr[b].Illum = true;
				}

				++game->BotCount;
				if (game->TotalOpened == game->Q_Card)
					theEnd = true;

			} while (hit && !theEnd);

			if (theEnd || abort)
				break;

		} while (true);

		if (!abort)
		{
			(game->UserCount) ? game->UserPerc = ((float)game->UserHit / game->UserCount) * 100.0 : game->UserPerc = 0;
			(game->BotCount) ? game->BotPerc = ((float)game->BotHit / game->BotCount) * 100.0 : game->BotPerc = 0;

			cout << "\n\a";
			cout << tab << "Гру завершено. Статистика:\n";
			cout << tab << "-----------------------------------\n";
			cout << tab << "  Всього ходів:   " << game->UserCount + game->BotCount << "\n\n";
			cout << tab << "  ВИ:\n";
			cout << tab << "    К-сть ходів:  " << game->UserCount << ", з них:\n";
			cout << tab << "      вдалих:     " << game->UserHit << "\n";
			cout << tab << "      невдалих:   " << game->UserCount - game->UserHit << "\n";
			cout << tab << "      % вдалих:   " << game->UserPerc << "\n\n";
			cout << tab << "  БОТ:\n";
			cout << tab << "    К-сть ходів:  " << game->BotCount << ", з них:\n";
			cout << tab << "      вдалих:     " << game->BotHit << "\n";
			cout << tab << "      невдалих:   " << game->BotCount - game->BotHit << "\n";
			cout << tab << "      % вдалих:   " << game->BotPerc << "\n";
			cout << tab << "-----------------------------------\n\n";

			if (game->BotPerc > game->UserPerc)
				cout << tab << "УПС... БОТ ЗІГРАВ КРАЩЕ!\n";
			else if (game->BotPerc < game->UserPerc)
				cout << tab << "ВІТАЄМО!!! ВИ ЗІГРАЛИ КРАЩЕ!\n";
			else
				cout << tab << "ЧУДОВА ГРА!!! ВИ ЗІГРАЛИ З БОТОМ НА РІВНІ!\n";

			start = funcReStart();
			if (!start)
				break;
		}
		else
		{
			abort = false;
			start = 3;
		}

	} while (true);

	delete game;
	delete scr;

	cout << '\n' << endl;

	system("pause");
}