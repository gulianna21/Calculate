#include "calculate.h"
#include <iostream>

using namespace std;

void main()
{
	Calculate cl;
	setlocale(NULL,"RUSSIAN");
	cout << "������� ������:";

	string str;
	string npl;

	cin >> str;

	npl = cl.getNPL(str);
	cout <<"�������� ���:"<< npl<<endl;
	cout << "��������� ����������:" << cl.Counting(npl);
	cin.get();

	cin.get();


}