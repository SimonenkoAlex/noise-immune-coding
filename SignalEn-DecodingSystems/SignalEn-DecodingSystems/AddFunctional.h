#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

enum ConsoleColor {
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5,
	Brown = 6, LightGray = 7, DarkGray = 8, LightBlue = 9, LightGreen = 10,
	LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

// Функция записи строки текста в 16-ричном коде
string ConvertStrTo16Bit(string inputString) {
	string string16bit = "";
	for (int i = 0; i < inputString.size(); i++) {
		switch (inputString.at(i))
		{
		case 'А': string16bit += "C0"; break;
		case 'Б': string16bit += "C1"; break;
		case 'В': string16bit += "C2"; break;
		case 'Г': string16bit += "C3"; break;
		case 'Д': string16bit += "C4"; break;
		case 'Е': string16bit += "C5"; break;
		case 'Ж': string16bit += "C6"; break;
		case 'З': string16bit += "C7"; break;
		case 'И': string16bit += "C8"; break;
		case 'Й': string16bit += "C9"; break;
		case 'К': string16bit += "CA"; break;
		case 'Л': string16bit += "CB"; break;
		case 'М': string16bit += "CC"; break;
		case 'Н': string16bit += "CD"; break;
		case 'О': string16bit += "CE"; break;
		case 'П': string16bit += "CF"; break;
		case 'Р': string16bit += "D0"; break;
		case 'С': string16bit += "D1"; break;
		case 'Т': string16bit += "D2"; break;
		case 'У': string16bit += "D3"; break;
		case 'Ф': string16bit += "D4"; break;
		case 'Х': string16bit += "D5"; break;
		case 'Ц': string16bit += "D6"; break;
		case 'Ч': string16bit += "D7"; break;
		case 'Ш': string16bit += "D8"; break;
		case 'Щ': string16bit += "D9"; break;
		case 'Ъ': string16bit += "DA"; break;
		case 'Ы': string16bit += "DB"; break;
		case 'Ь': string16bit += "DC"; break;
		case 'Э': string16bit += "DD"; break;
		case 'Ю': string16bit += "DE"; break;
		case 'Я': string16bit += "DF"; break;
		case 'а': string16bit += "E0"; break;
		case 'б': string16bit += "E1"; break;
		case 'в': string16bit += "E2"; break;
		case 'г': string16bit += "E3"; break;
		case 'д': string16bit += "E4"; break;
		case 'е': string16bit += "E5"; break;
		case 'ж': string16bit += "E6"; break;
		case 'з': string16bit += "E7"; break;
		case 'и': string16bit += "E8"; break;
		case 'й': string16bit += "E9"; break;
		case 'к': string16bit += "EA"; break;
		case 'л': string16bit += "EB"; break;
		case 'м': string16bit += "EC"; break;
		case 'н': string16bit += "ED"; break;
		case 'о': string16bit += "EE"; break;
		case 'п': string16bit += "EF"; break;
		case 'р': string16bit += "F0"; break;
		case 'с': string16bit += "F1"; break;
		case 'т': string16bit += "F2"; break;
		case 'у': string16bit += "F3"; break;
		case 'ф': string16bit += "F4"; break;
		case 'х': string16bit += "F5"; break;
		case 'ц': string16bit += "F6"; break;
		case 'ч': string16bit += "F7"; break;
		case 'ш': string16bit += "F8"; break;
		case 'щ': string16bit += "F9"; break;
		case 'ъ': string16bit += "FA"; break;
		case 'ы': string16bit += "FB"; break;
		case 'ь': string16bit += "FC"; break;
		case 'э': string16bit += "FD"; break;
		case 'ю': string16bit += "FE"; break;
		case 'я': string16bit += "FF"; break;
		case ' ': string16bit += "20"; break;
		case ',': string16bit += "2C"; break;
		case '.': string16bit += "2E"; break;
		case '0': string16bit += "30"; break;
		case '1': string16bit += "31"; break;
		case '2': string16bit += "32"; break;
		case '3': string16bit += "33"; break;
		case '4': string16bit += "34"; break;
		case '5': string16bit += "35"; break;
		case '6': string16bit += "36"; break;
		case '7': string16bit += "37"; break;
		case '8': string16bit += "38"; break;
		case '9': string16bit += "39"; break;
		}
	}
	return string16bit;
}

string Convert16To2(string inputString) {
	string binaryNumber = "";
	for (int i = 0; i < inputString.size(); i++) {
		switch (inputString.at(i)) {
		case '0': binaryNumber += "0000";
		case '1': binaryNumber += "0001";
		case '2': binaryNumber += "0010";
		case '3': binaryNumber += "0011";
		case '4': binaryNumber += "0100";
		case '5': binaryNumber += "0101";
		case '6': binaryNumber += "0110";
		case '7': binaryNumber += "0111";
		case '8': binaryNumber += "1000";
		case '9': binaryNumber += "1001";
		case 'A': binaryNumber += "1010";
		case 'B': binaryNumber += "1011";
		case 'C': binaryNumber += "1100";
		case 'D': binaryNumber += "1101";
		case 'E': binaryNumber += "1110";
		case 'F': binaryNumber += "1111";
			//case '.': binaryNumber += ".";
		}
	}
	return binaryNumber;
}