// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ENTER 13
#define KEY_ESC 27
#define ATTR1 232
#define ATTR2 015
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPos;

int ar1; // интеджер для первого аргумента в функциях
double arguments[9];
string menu1[3] = { "Sinus", "Polynom", "[0] Exit\n"}; // первое меню
string menu2[4] = { "Left", "Right", "Trap", "< go back\n" }; // второе меню


BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

void drawmenu(HANDLE h, COORD c, int k, int n, int len, string menu[])
{
	SetConsoleTextAttribute(h, ATTR1); COORD cc = c;
	for (int i = 0; i < n; i++)
	{
		cc.X = c.X + i * len;
		SetConsoleCursorPosition(h, cc);
		cout << menu[i];
	}
	cc.X = c.X + k * len;
	SetConsoleTextAttribute(h, ATTR2);
	SetConsoleCursorPosition(h, cc);
	cout << menu[k];
	SetConsoleTextAttribute(h, ATTR1);
}

int cycle(int z, int len, string menu[])
{
	int k = 0, iKey = 67;
	drawmenu(hStdOut, CursorPos, k, z, len, menu);
	while (iKey != KEY_ENTER)
	{
		if (_kbhit())
		{
			iKey = _getch();
			switch (iKey)
			{
			case KEY_ARROW_RIGHT: k++; if (k == z) k = 0;
				drawmenu(hStdOut, CursorPos, k, z, len, menu);
				break;
			case KEY_ARROW_LEFT: k--; if (k == -1) k = z - 1;
				drawmenu(hStdOut, CursorPos, k, z, len, menu);
				break;
			}
		}
	}
	return k;
}

double fSin(double x, double k, double p, double g)
{
	double res = pow(k*(sin(p*x)), g);
	return res;
}
double fPol(double x, double a1, double a2, double a3)
{
	double res = a1 * x + a2 * x + a3 * x;
	return res;
}
double leftSin(int n, double a, double b, double k, double p, double g)
{
	double sum = 0;
	double h = (b - a) / n;
	for (double i = a; i < b; i = i + h) {
		sum += fSin(i, k, p, g);
	}
	double r = sum * h;
	if (r < 0) { r = r - 2 * r; };
	return r;
}
double rightSin(int n, double a, double b, double k, double p, double g)
{
	double sum = 0;
	double h = (b - a) / n;
	for (double i = b; i > a; i = i - h) {
		sum += fSin(i, k, p, g);
	}
	double r = sum * h;
	if (r < 0) { r = r - 2 * r; };
	return r;
}
double leftPol(int n, double a, double b, double a1, double a2, double a3)
{
	double sum = 0;
	double h = (b - a) / n;
	for (double i = a; i < b; i = i + h) {
		sum += fPol(i, a1, a2, a3);
	}
	double r = sum * h;
	if (r < 0) { r = r - 2 * r; };
	return r;
}
double rightPol(int n, double a, double b, double a1, double a2, double a3, double b1, double b2, double b3)
{
	double sum = 0;
	double h = (b - a) / n;
	for (double i = b; i > a; i = i - h) {
		sum += fPol(i, a1, a2, a3);
	}
	double r = sum * h;
	if (r < 0) { r = r - 2 * r; };
	return r;
}
double trapSin(int n, double a, double b, double k, double p, double g)
{
	double sum = 0;
	double h = (b - a) / n;
	for (double i = a; i < b; i = i + h) {
		sum += fSin(i, k, p, g) + fSin(i + h, k, p, g);
	}
	double r = sum * h / 2;
	if (r < 0) { r = r - 2 * r; };
	return r;
}
double trapPol(int n, double a, double b, double a1, double a2, double a3)
{
	double sum = 0;
	double h = (b - a) / n;
	for (double i = a; i < b; i = i + h) {
		sum += fPol(i, a1, a2, a3) + fPol(i + h, a1, a2, a3);
	}
	double r = sum * h / 2;
	if (r < 0) { r = r - 2 * r; };
	return r;
}

void enterArgs(int n) { // метод для ввода аргументов
	system("cls"); // очищаем консоль
	cout << "Please, enter " << n << " arguments.\n";
	for (int i = 0; i < n; i++)
	{
		cin >> arguments[i]; // записываем в массив
		
	}
	cout << "Your args: "; // оповещаем о успешной записи
	for (int idx = 0; idx < n; idx++)
	{
		cout << " " << arguments[idx]; // оповещаем о успешной записи
	}
	cout << ".\n";
	ar1 = (int)arguments[0]; // переводим первый элемент в инт
}

int main() {
	bool isSin = NULL; // переменная хранит решение о выборе функции
	bool secondMenu = true;  // переменная хранит решение о выборе метода
	bool exit = true;  // выйти или не выйти :D
	COORD Begin = { 0, 0 };
	SetConsoleTitle(L"GRAPH (Console Menu)"); // имя окна
	COORD crd = { 120, 40 };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(hStdOut, true, &src);
	SetConsoleScreenBufferSize(hStdOut, crd);
	SetConsoleTextAttribute(hStdOut, 232);
	// start while
	while (isSin == NULL && exit) {
		system("cls"); // очищаем
		ShowConsoleCursor(FALSE);
		SetConsoleCursorPosition(hStdOut, Begin);
		cout << "Choose a function\n";
		CursorPos = { 0, 1 };
		int k = cycle(3, 11, menu1);
		switch (k)
		{
			case 0: // синус
				isSin = TRUE;
				break;
			case 1: // полином
				isSin = FALSE;
				break;
			case 2: // выйти
				exit = false;
				break;

		}
		if (exit) {
			while (secondMenu) {
				system("cls");
				CursorPos = { 0, 1 };
				cout << "Choose a method\n";
				int das = cycle(4, 11, menu2);

				switch (das)
				{
				case 0:
					// left
					if (isSin) { // синус
						enterArgs(6);
						cout << "Result: " << leftSin(ar1, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]) << "\n";
					}
					else { // полином
						enterArgs(6);
						cout << "Result: " << leftPol(ar1, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]) << "\n";
					}
					break;
				case 1:
					// right
					if (isSin) { // синус
						enterArgs(6);
						cout << "Result: " << rightSin(ar1, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]) << "\n";
					}
					else { // полином
						enterArgs(8);
						cout << "Result: " << rightPol(ar1, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], arguments[6], arguments[7], arguments[8]) << "\n";
					}
					break;
				case 2:
					// trap
					if (isSin) { // синус
						enterArgs(6);
						cout << "Result: " << trapSin(ar1, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]) << "\n";
					}
					else { // полином
						enterArgs(6);
						cout << "Result: " << trapPol(ar1, arguments[1], arguments[2], arguments[3], arguments[4], arguments[5]) << "\n";
					}
					break;
				case 3: // выйти
					isSin = NULL;
					secondMenu = false;
					break;
				}
				isSin = NULL;
				// этот if убирает паузу при выходе из второго меню
				if(secondMenu)
					system("pause");

				system("cls"); // очищаем
			}
			secondMenu = true; // остаёмся во втором меню
		}
	}
	// end while
	SetConsoleCursorPosition(hStdOut, Begin);
	CursorPos = { 50, 19 };
	SetConsoleCursorPosition(hStdOut, CursorPos);
	cout << "GAME OVER";
	return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
