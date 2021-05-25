// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ENTER 13
#define KEY_ESC 27
#define ATTR1 232
#define ATTR2 015
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPos, Matrix = { 75, 0 };

int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n12 = 0, n13 = 0, n14 = 0, n15 = 0, n16 = 0, n23 = 0, n24 = 0, n25 = 0, n26 = 0, n34 = 0, n35 = 0, n36 = 0, n45 = 0, n46 = 0, n56 = 0;

int color2, color3, color4, color5;

string menu1[3] = { "four", "five", "six" };
string menu2[2] = { "yes", "no" };
string menu3[4] = { "painting", "connectivity", "the shortest way", "exit" };
string menu4[6] = { "1","2","3","4","5","6" };
string menupainting[3] = { "connectivity", "the shortest way", "exit" };
string menuconnectivity[3] = { "painting", "the shortest way", "exit" };
string menudouble[2] = { "the shortest way", "exit" };

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

void drawline()
{
	CursorPos.X = 70;
	for (int zikkurat = 0; zikkurat < 40; zikkurat++)
	{
		CursorPos.Y = zikkurat;
		SetConsoleCursorPosition(hStdOut, CursorPos);
		cout << "|";
	}
}

void vangog(int n, int k)
{
	int z = n + 2;
	COORD Painting;
	Painting = { 77, 0 };
	Painting.Y = z;
	SetConsoleCursorPosition(hStdOut, Painting);
	SetConsoleTextAttribute(hStdOut, 16 * k);
	cout << n;
	int x = 77 + n * 4;
	Painting = { 0, 2 };
	Painting.X = x;
	SetConsoleCursorPosition(hStdOut, Painting);
	cout << n;
	if (n == 2) color2 = k;
	if (n == 3) color3 = k;
	if (n == 4) color4 = k;
	if (n == 5) color5 = k;
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
int main() {
	// functions to use

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
