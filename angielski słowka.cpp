﻿// angielski słowka.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <consoleapi.h>
#include <time.h>

using namespace std;


int ile_slowek_w_pliku()
{
	fstream plik;
	plik.open("Slowka.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje" << endl;
	}

	string linia;
	int numer_lini = 1;
	int ile = 0;

	while (getline(plik, linia))
	{
		switch (numer_lini)
		{
		case 1:
		{
			ile += 1;
			break;
		}
		default: break;
		}
		numer_lini++;
		if (numer_lini == 3) numer_lini = 1;
	}
	plik.close();
	plik.clear();

	return ile;
}
void wczytaj_slowka(string *T_ang, string *T_pol)
{
	fstream plik;
	plik.open("Slowka.txt", ios::in | ios::app);

	if (plik.good() == false)
	{
		cout << "Plik nie istnieje";
		return;
	}

	string linia;
	int numer_lini = 1, numer_slowka = 0;
	
	while (getline(plik, linia))
	{
		switch (numer_lini)
		{
		case 1: 
		{
			T_ang[numer_slowka] = linia;
			break;
		}
		case 2:
		{
			T_pol[numer_slowka] = linia;
		}
		default: break;
		}
		numer_lini++;
		if (numer_lini == 3)
		{
			numer_lini = 1;
			numer_slowka++;
		}
	}

	plik.clear();
	plik.close();
}
void odstep(int ile) // pomocnicza funkcja ktora ustawia odpowiedni odstep (zeby slowa byly rowno od siebie)
{
	for (int i = 0; i < 15 + ile; i++)
		cout << " ";
}
void wypisz(string *T_ang, string *T_pol, int ile)
{
	void odstep(int);
	int dlugosc_max = 0;
	for (int i = 0; i < ile; i++)
	{
		if (T_pol[i].length() > dlugosc_max)
		{
			dlugosc_max = T_pol[i].length();
		}
	}
	// sprawdza jakie jest najdluzsze slowko

	int j = 5;
	for (int i = 0; i < ile; i++)
	{
		int temp = T_pol[i].length();
		temp = dlugosc_max - temp; // oblicza ile spacji musi dodac
		cout << T_pol[i];
		odstep(temp); // dodaje ilosc brakujacych spacji
		cout << T_ang[i] << endl;
	}
}

void odpytaj(string *T_ang, string *T_pol, int ile)
{
	string odpowiedz,pytanie;
	int  numer_pytania;
	int punkty = 0, czy_dobrze = 0, byly[21] = {-1};

	for(int i=0;i<20;i++)
	{
		numer_pytania = rand() % ile;
		czy_dobrze = 0;
		int j = 0;
		do
		{
			if (numer_pytania == byly[j])
			{
				numer_pytania = rand() % ile;
				j = -1;
			}
			j++;
		} while(j<21);

		pytanie = T_pol[numer_pytania];
		cout << pytanie << endl;
		getline(cin, odpowiedz);

		for (int i = 0; i < ile; i++)
		{
			if (odpowiedz == T_ang[i])
			{
				czy_dobrze++;
			}
		}

			if (czy_dobrze == 1)
			{
				cout << "DOOOOOBRZE";
				Sleep(2000);
				system("cls");
				punkty++;
			}
			else
			{
				cout << "ZLA ODPOWIEDZ !!!!" << endl;
				cout << "MIALO BYC :  " << T_ang[numer_pytania];
				Sleep(2000);
				system("cls");
			}
			byly[i] = numer_pytania;
	};

	cout << "UDALO CI SIE UZBIERAC : " << punkty << " na 20 mozliwych punktow" << endl;
}

int main()
{
	srand(time(NULL));
	int ile, wybor;
	ile = ile_slowek_w_pliku();


	if (ile == 0)
	{
		cout << "Plik jest pustty :/ wpisz jakies slowka" << endl;
		exit(0);
	}

	string *T_ang;
	T_ang = new string[ile];
	string *T_pol;
	T_pol = new string[ile];

	wczytaj_slowka(T_ang,T_pol);


	for(;;)
	{
		cout << endl;
		cout << "Aby rozpoczac wcisnij [1]" << endl;
		cout << "Aby wypisac liste slowek z tlumaczeniem wcisnij [2]" << endl;
		cout << "Aby wyjsc wcisnij [3]" << endl;
		cin >> wybor;

		cin.ignore();
		switch (wybor)
		{
		case 1:
		{
			odpytaj(T_ang, T_pol, ile);
			break;
		}
		case 2:
		{
			system("cls");
			wypisz(T_ang, T_pol, ile);
			break;
		}
		case 3:
		{
			exit(0);
		}
		default: break;
		}
		
	};

	delete[] T_ang;
	delete[] T_pol;
    return 0;
}

