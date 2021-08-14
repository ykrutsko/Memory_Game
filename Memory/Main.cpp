#include "Func.h"
#include <iostream>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	// ³�������� ������� � ������������� ����� ����
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

	// ����� ����� ����
	// 0 - �� ������ (������)
	// 1 - ���� (�� ������)
	// 2 - ������������ ������ 2 ����� ���� �������� ����, �� ����� ������
	// 3 - ������ �� ������ �����, ����� - ��

	S_Game* game = new S_Game;
	S_Screen* scr = new S_Screen;
	char inpStr[10];
	int a{ 0 }, b{ 0 };
	bool hit{ false };
	bool theEnd{ false };
	bool abort{ false };

	// �������� ����� Start
	// -1 - ������ ������
	// 0 - ��������� ������ ��������
	// 1 - ��������� � ��������� ��������������
	// 2 - ��������� � �������� ��������������
	// 3 - ��������� � ����� �����������

	// ����� ���
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

		// ������ ��� (��������� ����, ��������� ���� � ����������)
		prepareGame(game);

		// �������
		system("cls");
		cout << tab << '\n' << endl;
		cout << tab << "������������!!!\n";
		cout << tab << "----------------\n\n";
		cout << tab << "����� ���� ������� �� " << game->Delay << " ���, ����������� �����\'����� �� ������������!!!\n\n";
		cout << tab << "�� ����� ������ �����, �������� ����-��� ������...";

		cin.clear();
		_getch();

		// ��������� �����
		prnCards(game, scr, 1);
		showABit(game->Delay);
		prnCards(game, scr, 0);

		// ��������. ���� ����
		do
		{
			// ���� �����
			do
			{
				a = 0, b = 0, hit = false;

				if (!inputStr(game, inpStr, a, b))
				{
					abort = true;
					break;
				}

				// ���� ������
				if (game->CardsArr[a - 1].Color == game->CardsArr[b - 1].Color)
				{
					hit = true;

					game->CardsArr[a - 1].ShowNow = true;
					game->CardsArr[b - 1].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "�� �������!!!";
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
				// ���� �� ������
				else
				{
					hit = false;

					game->CardsArr[a - 1].ShowNow = true;
					game->CardsArr[b - 1].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "�� �� ������� :(((";
					if (game->PlSound)
						Beep(400, 300);

					showABit(game->Delay);
					game->CardsArr[a - 1].ShowNow = false;
					game->CardsArr[b - 1].ShowNow = false;
					prnCards(game, scr, 3);

					// ������� ���� ��� ����� ����
					game->CardsArr[a - 1].Illum = true;
					game->CardsArr[b - 1].Illum = true;
				}

				++game->UserCount;
				if (game->TotalOpened == game->Q_Card)
					theEnd = true;

			} while (hit && !theEnd);

			if (theEnd || abort)
				break;

			// ���� ����
			do
			{
				a = 0, b = 0, hit = false;
				cout << tab << "(" << game->BotCount + 1 << ") " << "ճ� ����! �������� ����-��� ������...";

				_getch();

				botAct(game, a, b);

				// ���� ������
				if (game->CardsArr[a].Color == game->CardsArr[b].Color)
				{
					hit = true;

					game->CardsArr[a].ShowNow = true;
					game->CardsArr[b].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "��� ������!!!";
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
				// ���� �� ������
				else
				{
					hit = false;

					game->CardsArr[a].ShowNow = true;
					game->CardsArr[b].ShowNow = true;
					prnCards(game, scr, 2);

					cout << tab << "��� �� ������ :(((";
					if (game->PlSound)
						Beep(400, 300);

					showABit(game->Delay);
					game->CardsArr[a].ShowNow = false;
					game->CardsArr[b].ShowNow = false;
					prnCards(game, scr, 3);

					// ������� ���� ��� ����� ����
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
			cout << tab << "��� ���������. ����������:\n";
			cout << tab << "-----------------------------------\n";
			cout << tab << "  ������ ����:   " << game->UserCount + game->BotCount << "\n\n";
			cout << tab << "  ��:\n";
			cout << tab << "    �-��� ����:  " << game->UserCount << ", � ���:\n";
			cout << tab << "      ������:     " << game->UserHit << "\n";
			cout << tab << "      ��������:   " << game->UserCount - game->UserHit << "\n";
			cout << tab << "      % ������:   " << game->UserPerc << "\n\n";
			cout << tab << "  ���:\n";
			cout << tab << "    �-��� ����:  " << game->BotCount << ", � ���:\n";
			cout << tab << "      ������:     " << game->BotHit << "\n";
			cout << tab << "      ��������:   " << game->BotCount - game->BotHit << "\n";
			cout << tab << "      % ������:   " << game->BotPerc << "\n";
			cout << tab << "-----------------------------------\n\n";

			if (game->BotPerc > game->UserPerc)
				cout << tab << "���... ��� ǲ���� �����!\n";
			else if (game->BotPerc < game->UserPerc)
				cout << tab << "²�����!!! �� ǲ����� �����!\n";
			else
				cout << tab << "������ ���!!! �� ǲ����� � ����� �� в�Ͳ!\n";

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