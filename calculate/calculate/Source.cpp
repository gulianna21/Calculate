#include "calculate.h"
#include <iostream>

using namespace std;

void main()
{
	Calculate cl;
	setlocale(NULL,"RUSSIAN");
	cout << "Введите строку:";

	string str;
	string npl;

	cin >> str;

	npl = cl.getNPL(str);
	cout <<"Итоговая ОПЗ:"<< npl<<endl;
	cout << "Результат вычисления:" << cl.Counting(npl);
	cin.get();

	cin.get();


}