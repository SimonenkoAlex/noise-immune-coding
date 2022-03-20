#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <cstdlib>		//подключение функции rand
#include <ctime>		//подключение функции TIME

using namespace std;

string Convert10to2(int inputString) {
	int ost[50], i = 0, k1, k2;
	string string2bit = "";
	do {
		ost[i] = inputString % 2;
		inputString = (int)inputString / 2;
		i++;
	} while (inputString);
	k1 = i - 1; k2 = i;
	for (i = k1; i >= 0; i--) {
		string2bit += ('0' + ost[i]);
	}
	switch (k2)
	{
	case 1: return "00" + string2bit;
	case 2: return "0" + string2bit;
	case 3: return string2bit;
	}
}

void bergerCode() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	system("cls");
	// ---------------- объявление переменных --------------------
	string saveString, addLine, string16Bit, string2Bit;
	int number, countBit = 4;
	// - исходная строка = ФИО полностью + дата рождения
	string inputString = "Симоненко Александр Евгеньевич 30.04.1999";
	SetColor(LightCyan, Black); cout << "\n Исходная строка - ";
	SetColor(White, Black); cout << inputString << endl;
	// - записать исходную строку в 16-ричном коде
	string16Bit = ConvertStrTo16Bit(inputString);
	// - перевод полученной записи в двоичный код 
	string2Bit = Convert16To2(string16Bit);
	// - Подсчёт кол-ва пакетов по 4 бита
	int countPackets = packetCounting(string2Bit, countBit);
	// - Разбиение на пакеты по 4 бита
	int k = 0, inf = 0;
	struct words w[650];
	string word = "";
	gotoxy(0, 10);
	for (int temp = 1; temp < string2Bit.size(); temp = i + 1)
	{
		// - формируем слово из 4-ёх бит
		for (j = 0, i = temp; (i % (countBit)) != 0; i++, j++)
			word += string2Bit.at(i - 1);
		// - формируем конец строки 
		word += string2Bit.at(i - 1) + '\0';
		// - копируем слово в массив
		w[k].id = k; w[k].word = word;
		cout << "<- " << w[k].word << " ->\t";
		// - очищаем строку 
		word = ""; k++; inf++;
	}
	_getch();
	gotoxy(0, 10);
	// - Вычисление контрольных бит
	int countOne = 0, error = 0;					// количество ошибок
	string ivert = ""; k = 0;
	for (j = 0; j < countPackets; j++) {
		for (i = 0; i < countBit; i++) {
			if (w[j].word.at(i) == '1') countOne++;
		}
		cout << "<- " << w[j].word;
		// Двоичная запись количества единиц
		ivert = Convert10to2(countOne);
		// Инвертированая двоичная запись
		for (i = 0; i < 3; i++) {
			if (ivert.at(i) == '1') ivert.at(i) = '0';
			else if (ivert.at(i) == '0') ivert.at(i) = '1';
		}
		w[j].word += ivert;
		SetColor(LightGreen, Black); cout << ivert;
		SetColor(White, Black); cout << " ->\t";
		countOne = 0; k += 3;
	}
	_getch();
	int randbit1, randbit2;
	string random = "", kontr = "";
	gotoxy(0, 140);
	// ------------------- Передача сообщения --------------------
	for (j = 0; j < countPackets; j++) {
		// --------- появление (или не появление) помехи ---------
		srand((unsigned int)::time(NULL) + j * 1.5);
		int Q1 = (rand() % 2);					// -- одной
		srand((unsigned int)::time(NULL));
		int Q2 = (rand() % 2);					// -- двух
		random += ('0' + Q1); random += ('0' + Q2);
		//cout << Q1 << " " << Q2 << endl;

		switch (atoi(random.c_str()))
		{
		case 00: {
			cout << "<- " << w[j].word << " ->";
			SetColor(LightGreen, Black);
			cout << " Ошибок НЕТ\n";
			SetColor(White, Black);
			break;
		}
		case 01: {
			srand((unsigned int)::time(NULL) + j);
			randbit2 = (rand() % countBit);
			cout << "<- ";
			for (int i = 0; i < (countBit + 3); i++) {
				if (i == randbit2) {
					SetColor(Red, Black);
					if (w[j].word.at(i) == '0') w[j].word.at(i) = '1';
					else if (w[j].word.at(i) == '1') w[j].word.at(i) = '0';
					cout << w[j].word.at(i);
				}
				else {
					SetColor(White, Black);
					cout << w[j].word.at(i);
				}
				SetColor(White, Black);
			}
			cout << " ->";
			for (i = 0; i < countBit; i++) {
				if (w[j].word.at(i) == '1') countOne++;
			}
			// Двоичная запись количества единиц
			ivert = Convert10to2(countOne);
			kontr = ivert;
			// Инвертированая двоичная запись
			for (i = 0; i < 3; i++) {
				if (ivert.at(i) == '1') ivert.at(i) = '0';
				else if (ivert.at(i) == '0') ivert.at(i) = '1';
			}
			if (ivert != kontr) {
				SetColor(LightRed, Black);
				cout << " ОШИБКА\n";
				error++;
			}
			else {
				SetColor(LightGreen, Black);
				cout << " Ошибок НЕТ\n";
			}
			SetColor(White, Black);
			break;
		}
		case 10: {
			srand((unsigned int)::time(NULL) + j);
			randbit1 = (rand() % countBit);
			cout << "<- ";
			for (int i = 0; i < (countBit + 3); i++) {
				if (i == randbit1) {
					SetColor(Red, Black);
					if (w[j].word.at(i) == '0') w[j].word.at(i) = '1';
					else if (w[j].word.at(i) == '1') w[j].word.at(i) = '0';
					cout << w[j].word.at(i);
				}
				else {
					SetColor(White, Black);
					cout << w[j].word.at(i);
				}
				SetColor(White, Black);
			}
			cout << " ->";
			for (i = 0; i < countBit; i++) {
				if (w[j].word.at(i) == '1') countOne++;
			}
			// Двоичная запись количества единиц
			ivert = Convert10to2(countOne);
			kontr = ivert;
			// Инвертированая двоичная запись
			for (i = 0; i < 3; i++) {
				if (ivert.at(i) == '1') ivert.at(i) = '0';
				else if (ivert.at(i) == '0') ivert.at(i) = '1';
			}
			if (ivert != kontr) {
				SetColor(LightRed, Black);
				cout << " ОШИБКА\n";
				error++;
			}
			else {
				SetColor(LightGreen, Black);
				cout << " Ошибок НЕТ\n";
			}
			SetColor(White, Black);
			break;
		}
		case 11: {
			srand((unsigned int)::time(NULL) + j);
			randbit1 = (rand() % countBit);	// -- одной
			srand((unsigned int)::time(NULL) + j * 1000);
			randbit2 = (rand() % countBit);
			cout << "<- ";
			for (int i = 0; i < (countBit + 3); i++) {
				if (i == randbit1) {
					SetColor(Red, Black);
					if (w[j].word.at(i) == '0') w[j].word.at(i) = '1';
					else if (w[j].word.at(i) == '1') w[j].word.at(i) = '0';
					cout << w[j].word.at(i);
				}
				else if (i == randbit2) {
					SetColor(Red, Black);
					if (w[j].word.at(i) == '0') w[j].word.at(i) = '1';
					else if (w[j].word.at(i) == '1') w[j].word.at(i) = '0';
					cout << w[j].word.at(i);
				}
				else {
					SetColor(White, Black);
					cout << w[j].word.at(i);
				}
				SetColor(White, Black);
			}
			cout << " ->";
			for (i = 0; i < countBit; i++) {
				if (w[j].word.at(i) == '1') countOne++;
			}
			// Двоичная запись количества единиц
			ivert = Convert10to2(countOne);
			kontr = ivert;
			// Инвертированая двоичная запись
			for (i = 0; i < 3; i++) {
				if (ivert.at(i) == '1') ivert.at(i) = '0';
				else if (ivert.at(i) == '0') ivert.at(i) = '1';
			}
			if (ivert != kontr) {
				SetColor(LightRed, Black);
				cout << " ОШИБКА\n";
				error++;
			}
			else {
				SetColor(LightGreen, Black);
				cout << " Ошибок НЕТ\n";
			}
			SetColor(White, Black);
			break;
		}
		}
		k++; countOne = 0;
		random = "";
	}

	float g = (float)k / (inf + k);
	double p = ((float)error / countPackets) * 100.;
	//position.X = 0; position.Y = 250;
	//SetConsoleCursorPosition(hstdout, position);
	SetColor(LightCyan, Black); cout << "\n Процент пакетов переданых с опознанием ошибки - ";
	SetColor(White, Black); cout << p << "%\n (Количество ошибок - " << error << ")\n";
	//SetColor(LightCyan, Black); cout << "\n Количество информационных бит - ";
	//SetColor(White, Black); cout << inf << endl;
	//SetColor(LightCyan, Black); cout << "\n Количество проверочных бит - ";
	//SetColor(White, Black); cout << k << endl;
	SetColor(LightCyan, Black); cout << "\n Избыточность кода - ";
	SetColor(White, Black); printf("%.4f", g);

	_getch();
}