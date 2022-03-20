#include <Windows.h>
#include <locale.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "ParityCheckCode.h"
#include "HammingCode.h"
#include "BergerCode.h"

using namespace std;

int i, j;

void select(int position) {
	switch (position)
	{
	case 0: parityCheckCode16Bit(); system("cls"); break;
	case 1: parityCheckCode4Bit();  system("cls"); break;
	case 2: hammingCode(); system("cls"); break;
	case 3: bergerCode(); system("cls"); break;
	case 4: break;
	case 5: exit(0); break;
	}
}

int main() {
	setlocale(LC_CTYPE, "Russian_Russia.1251");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD active = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD noActive = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	char lines[][40] = { "Код проверки чётности (16 бит)", "Код проверки чётности (4 бита)",
		"Код Хемминга (4 бита)", "Код Бергера (4 бита)", "Комбинированный код", "Выход" };
	COORD coordinate;
	int position = 0, lastItemMenu = 6;
	char code;
	while (true) {
		system("cls");
		for (int i = 0; i < lastItemMenu; i++) {
			if (position == i)
				SetConsoleTextAttribute(handle, active);
			else
				SetConsoleTextAttribute(handle, noActive);
			coordinate.X = 25; coordinate.Y = 5 + i * 2;
			SetConsoleCursorPosition(handle, coordinate);
			cout << i + 1 << ") " << lines[i] << endl;
		}
		code = _getch();
		if (code == 72) {
			if (position == 0) position = lastItemMenu - 1;
			else position--;
		}
		if (code == 80) {
			if (position == lastItemMenu - 1) position = 0;
			else position++;
		}
		if (code == 13) select(position);
	}
	return 0;
}