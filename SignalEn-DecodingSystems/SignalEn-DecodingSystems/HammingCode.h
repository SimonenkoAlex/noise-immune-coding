#include <Windows.h>
#include <iostream>

using namespace std;

void hammingCode() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	system("cls");
	// ---------------- ���������� ���������� --------------------
	string saveString, addLine, string16Bit, string2Bit;
	int number, countBit = 4;
	// - �������� ������ = ��� ��������� + ���� ��������
	string inputString = "��������� ��������� ���������� 30.04.1999";
	SetColor(LightCyan, Black); cout << "\n �������� ������ - ";
	SetColor(White, Black); cout << inputString << endl;
	// - �������� �������� ������ � 16-������ ����
	string16Bit = ConvertStrTo16Bit(inputString);
	// - ������� ���������� ������ � �������� ��� 
	string2Bit = Convert16To2(string16Bit);
	// - ������� ���-�� ������� �� 4 ����
	int countPackets = packetCounting(string2Bit, countBit);
	// - ��������� �� ������ �� 4 ����
	int k = 0, inf = 0;
	struct words w[650];
	string word = "";
	gotoxy(0, 10);
	for (int temp = 1; temp < string2Bit.size(); temp = i + 1)
	{
		// - ��������� ����� �� 4-�� ���
		for (j = 0, i = temp; (i % (countBit)) != 0; i++, j++)
			word += string2Bit.at(i - 1);
		// - ��������� ����� ������ 
		word += string2Bit.at(i - 1) + '\0';
		// - �������� ����� � ������
		w[k].id = k; w[k].word = word;
		cout << "<- " << w[k].word << " ->\t";
		// - ������� ������ 
		word = ""; k++; inf++;
	}
	_getch();
	gotoxy(0, 10);
	// - ���������� ����������� ���
	k = 0;
	int data[10], error = 0; // ���������� ������
	for (j = 0; j < countPackets; j++) {
		data[0] = (w[j].word.at(0) - '0');
		data[1] = (w[j].word.at(1) - '0');
		data[2] = (w[j].word.at(2) - '0');
		data[4] = (w[j].word.at(3) - '0');

		data[6] = data[0] ^ data[2] ^ data[4];
		data[5] = data[0] ^ data[1] ^ data[4];
		data[3] = data[0] ^ data[1] ^ data[2];

		w[j].word = '0' + data[0];
		cout << "<- " << data[0];
		for (i = 1; i < (countBit + 3); i++) {
			addLine = '0' + data[i];
			w[j].word += addLine;
			switch (i)
			{
			case 1: case 2: case 4: {
				SetColor(White, Black);
				cout << data[i];
				break;
			}
			case 3: case 5: case 6: {
				SetColor(Green, Black);
				cout << data[i];
				SetColor(White, Black);
				break;
			}
			}
		}
		k += 3;
		cout << " ->\t";
	}
	_getch();
	gotoxy(0, 140);
	int c, c1, c2, c3; // ��� ���������� ������� ��������� ������
	int randbit1, randbit2, dataatrec[10];
	// ------------------- �������� ��������� --------------------
	for (j = 0; j < countPackets; j++) {
		// --------- ��������� (��� �� ���������) ������ ---------
		srand((unsigned int)::time(NULL) + j * 1.5);
		int Q1 = (rand() % 2);					// -- �����
	//	srand((unsigned int)::time(NULL));
	//	int Q2 = (rand() % 2);					// -- ����
	//	random += ('0' + Q1); random += ('0' + Q2);
		//cout << Q1 << " " << Q2 << endl;

		if (Q1 == 1) {
			srand((unsigned int)::time(NULL) + j);
			randbit1 = (rand() % (countBit + 3));
			//cout << randbit2 << endl;
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
			cout << " ->\t";
		}
		else if (Q1 == 0) {
			SetColor(White, Black);
			cout << "<- " << w[j].word << " ->\t";
		}
		for (i = 0; i < (countBit + 3); i++) {
			dataatrec[i] = (w[j].word.at(i) - '0');
		}
		c1 = dataatrec[6] ^ dataatrec[4] ^ dataatrec[2] ^ dataatrec[0];
		c2 = dataatrec[5] ^ dataatrec[4] ^ dataatrec[1] ^ dataatrec[0];
		c3 = dataatrec[3] ^ dataatrec[2] ^ dataatrec[1] ^ dataatrec[0];
		c = c3 * 4 + c2 * 2 + c1;

		if (c == 0) {
			/*position.X = 0; position.Y = 250;
			SetConsoleCursorPosition(hstdout, position);*/
			SetColor(LightGreen, Black);
			cout << "��� ������ �������� ������\n";
			SetColor(White, Black);
			//_getch();
		}
		else {
			/*position.X = 0; position.Y = 250;
			SetConsoleCursorPosition(hstdout, position);*/
			SetColor(LightRed, Black);
			cout << "������ �� ������� " << c;
			SetColor(White, Black);
			error++;
			//_getch();

			//if errorneous bit is 0 we complement it else vice versa
			if (w[j].word.at(7 - c) == '0')
				w[j].word.at(7 - c) = '1';
			else w[j].word.at(7 - c) = '0';
			cout << " <- " << w[j].word << " ->\n";
		}
	}

	float g = (float)k / (inf + k);
	double p = ((float)error / countPackets) * 100.;
	//position.X = 0; position.Y = 250;
	//SetConsoleCursorPosition(hstdout, position);
	SetColor(LightCyan, Black); cout << "\n ������� ������� ��������� � ���������� ������ - ";
	SetColor(White, Black); cout << p << "%\n (���������� ������ - " << error << ")\n";
	//SetColor(LightCyan, Black); cout << "\n ���������� �������������� ��� - ";
	//SetColor(White, Black); cout << inf << endl;
	//SetColor(LightCyan, Black); cout << "\n ���������� ����������� ��� - ";
	//SetColor(White, Black); cout << k << endl;
	SetColor(LightCyan, Black); cout << "\n ������������ ���� - ";
	SetColor(White, Black); printf("%.4f", g);

	_getch();
}