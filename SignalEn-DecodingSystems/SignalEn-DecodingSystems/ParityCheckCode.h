#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <locale.h>
#include <cstdlib>		//подключение функции rand
#include <ctime>		//подключение функции TIME
#include "AddFunctional.h"

using namespace std;

extern int i, j;

struct words {
	unsigned int id;
	string word;
};

int noiseGeneration(words w[400], int countPackets, int countBit) {
	int randbit1, randbit2, number = 0;
	int error = 0;		// кол-во ошибок
	string random = "";
	countBit++;
	if (countBit == 5)
		gotoxy(0, 10);
	else if (countBit == 17)
		gotoxy(0, 250);

	for (j = 0; j < countPackets; j++) {
		// - появление (или не появление) помехи
		srand((unsigned int)::time(NULL));
		int Q1 = (rand() % 2);	// -- одной
		srand((unsigned int)::time(NULL));
		int Q2 = (rand() % 2);	// -- двух
		random += ('0' + Q1); random += ('0' + Q2);
		if (countBit == 17)
			gotoxy(50, 5 + (j * 1.5));

		//cout << Q1 << " " << Q2 << endl;
		switch (atoi(random.c_str()))
		{
		case 00: {
			cout << w[j].word;
			number = (w[j].word.at(0) - '0');
			for (i = 1; i < countBit; i++) {
				number ^= (w[j].word.at(i) - '0');
			}
			SetColor(Green, Black);
			if (countBit == 17)
				cout << number;
			else if (countBit == 5)
				cout << number << "\t";
			SetColor(White, Black);
			break;
		}
		case 01: {
			srand((unsigned int)::time(NULL) + j);
			randbit2 = (rand() % countBit);
			//cout << randbit2 << endl;
			for (int i = 0; i < countBit; i++) {
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
			number = (w[j].word.at(0) - '0');
			for (i = 1; i < countBit; i++) {
				number ^= (w[j].word.at(i) - '0');
			}
			if (number == 1) error++;
			SetColor(Green, Black);
			if (countBit == 17)
				cout << number;
			else if (countBit == 5)
				cout << number << "\t";
			SetColor(White, Black);
			break;
		}
		case 10: {
			srand((unsigned int)::time(NULL) + j);
			randbit1 = (rand() % countBit);
			//cout << randbit1 << endl;
			for (int i = 0; i < countBit; i++) {
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
			number = (w[j].word.at(0) - '0');
			for (i = 1; i < countBit; i++) {
				number ^= (w[j].word.at(i) - '0');
			}
			if (number == 1) error++;
			SetColor(Green, Black);
			if (countBit == 17)
				cout << number;
			else if (countBit == 5)
				cout << number << "\t";
			SetColor(White, Black);
			break;
		}
		case 11: {
			srand((unsigned int)::time(NULL) + j);
			randbit1 = (rand() % countBit);	// -- одной
			srand((unsigned int)::time(NULL) + j * 1000);
			randbit2 = (rand() % countBit);
			for (int i = 0; i < countBit; i++) {
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
			//cout << randbit1 << " " << randbit2 << endl;
			number = (w[j].word.at(0) - '0');
			for (i = 1; i < countBit; i++) {
				number ^= (w[j].word.at(i) - '0');
			}
			if (number == 1) error++;
			SetColor(Green, Black);
			if (countBit == 17)
				cout << number;
			else if (countBit == 5)
				cout << number << "\t";
			SetColor(White, Black);
			break;
		}
		}
		if (countBit == 17)
			gotoxy(0, 0);
		random = "";
	}
	return error;
}

int packetCounting(string string2Bit, int countBit) {
	int countPackets, remainder, addCountZero;
	if ((string2Bit.size() % countBit) == 0) {
		countPackets = string2Bit.size() / countBit;
		SetColor(Yellow, Black); cout << "\n Кол-во пакетов - ";
		SetColor(White, Black); cout << countPackets << endl;
	}
	else {
		remainder = string2Bit.size() % countBit;
		addCountZero = countBit - remainder;
		countPackets = (string2Bit.size() + addCountZero) / countBit;
		for (i = 0; i < addCountZero; i++) {
			string2Bit += '0';
		}
		SetColor(Yellow, Black); cout << "\n Кол-во пакетов - ";
		SetColor(White, Black); cout << countPackets << endl;
	}
	return countPackets;
}

void parityCheckCode16Bit() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	system("cls");

	string saveString, addLine, string16Bit, string2Bit;
	int number, countBit = 16;
	// - исходная строка = ФИО полностью + дата рождения
	string inputString = "Симоненко Александр Евгеньевич 30.04.1999";
	SetColor(LightCyan, Black); cout << "\n Исходная строка - ";
	SetColor(White, Black); cout << inputString << endl;
	// - записать исходную строку в 16-ричном коде
	string16Bit = ConvertStrTo16Bit(inputString);
	// - перевод полученной записи в двоичный код 
	string2Bit = Convert16To2(string16Bit);
	// - Подсчёт кол-ва пакетов по 16 бит
	int countPackets = packetCounting(string2Bit, countBit);
	// - Разбиение на пакеты по 16 бит
	int k = 0, inf = 0;
	struct words w[400];
	string word = "";
	for (int temp = 1; temp < string2Bit.size(); temp = i + 1)
	{
		gotoxy(2, 5 + (k * 1.5));
		// - формируем слово из 16-и бит
		for (j = 0, i = temp; (i % (countBit)) != 0; i++, j++)
			word += string2Bit.at(i - 1);
		// - формируем конец строки 
		word += string2Bit.at(i - 1) + '\0';
		// - копируем слово в массив
		w[k].id = k; w[k].word = word;
		cout << w[k].id << " - " << w[k].word << endl;
		// - очищаем строку 
		word = ""; k++; inf++;
		gotoxy(0, 0);
	}
	_getch();

	k = 0;				// кол-во проверочных (k) бит
	for (j = 0; j < countPackets; j++) {
		position.X = 27; position.Y = 5 + (j * 1.5);
		SetConsoleCursorPosition(hstdout, position);
		number = (w[j].word.at(0) - '0');
		for (i = 1; i < countBit; i++) {
			number ^= (w[j].word.at(i) - '0');
			cout << w[j].word.at(i);
		}
		k++;
		SetColor(Green, Black);
		cout << number << endl;
		SetColor(White, Black);
		addLine = '0' + number;
		w[j].word += addLine;
		position.X = 0; position.Y = 0;
		SetConsoleCursorPosition(hstdout, position);
	}
	_getch();

	int countError = noiseGeneration(w, countPackets, countBit);
	float g = (float)k / (inf + k);
	float p = ((float)countError / countPackets) * 100.;
	position.X = 0; position.Y = 240;
	SetConsoleCursorPosition(hstdout, position);
	SetColor(LightCyan, Black); cout << "\n Количесво найденных ощибок - ";
	SetColor(White, Black); cout << countError << " (ошибки одиночные)" << endl;
	SetColor(LightCyan, Black); cout << "\n Процент найденных ощибок - ";
	SetColor(White, Black); cout << p << "% \n" << endl;
	SetColor(LightCyan, Black); cout << "\n Избыточность кода - ";
	SetColor(White, Black); printf("%.4f", g);

	_getch();
}

void parityCheckCode4Bit() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	system("cls");

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
		// - формируем слово из 8-и бит
		for (j = 0, i = temp; (i % (countBit)) != 0; i++, j++)
			word += string2Bit.at(i - 1);
		// - формируем конец строки 
		word += string2Bit.at(i - 1) + '\0';
		// - копируем слово в массив
		w[k].id = k; w[k].word = word;
		cout << w[k].word << "\t";
		// - очищаем строку 
		word = ""; k++; inf++;
	}
	_getch();
	gotoxy(0, 10);
	k = 0;		// кол-во проверочных (k) бит
	for (j = 0; j < countPackets; j++) {
		number = (w[j].word.at(0) - '0');
		cout << w[j].word.at(0);
		for (i = 1; i < countBit; i++) {
			number ^= (w[j].word.at(i) - '0');
			cout << w[j].word.at(i);
		}
		k++;
		SetColor(Green, Black);
		cout << number << "\t";
		SetColor(White, Black);
		addLine = '0' + number;
		w[j].word += addLine;
	}
	_getch();

	int countError = noiseGeneration(w, countPackets, countBit);
	float g = (float)k / (inf + k);
	float p = ((float)countError / countPackets) * 100.;
	gotoxy(0, 75);
	SetColor(LightCyan, Black); cout << "\n Количесво найденных ощибок - ";
	SetColor(White, Black); cout << countError << " (ошибки одиночные)" << endl;
	SetColor(LightCyan, Black); cout << "\n Процент найденных ощибок - ";
	SetColor(White, Black); cout << p << "% \n" << endl;
	SetColor(LightCyan, Black); cout << "\n Избыточность кода - ";
	SetColor(White, Black); printf("%.4f", g);

	_getch();
}