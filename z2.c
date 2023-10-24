#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define FILE_ERROR -1
#define EXIT_SUCCESS 0

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godina;
	Pozicija Next;
}osoba;

int UnosPodataka(Pozicija);
int UnosNaPocetak(Pozicija);
int UnosNaKraj(Pozicija);
int IspisListe(Pozicija);
void OslobodiMemoriju(Pozicija);



int main()
{
	int a = 0, b = 0, c = 0, i = 0;
	char prez[MAX] = { 0 };
	Pozicija Head = NULL;

	Head = (Pozicija)malloc(sizeof(osoba));
	
	if (Head == NULL)
	{
		printf("Alokacija memorije nije uspjesna.\n");
		return FILE_ERROR;
	}
	Head->Next = NULL;

	printf("Za unos na pocetak liste upisite 1\nZa unos na kraj liste upisite 2\n");
	scanf("%d", &a);
	if (a == 1)
	{
		printf("Odabrali ste unos na pocetak liste. Mozete poceti s unosom podataka\n");
		UnosNaPocetak(Head);

		printf("Zelite li unijeti jos jednu osobu na pocetak liste? \nUkoliko zelite unesite 1.\n");
		scanf("%d", &b);
		if (b == 1)
		{
			printf("Koliko osoba zelite unijeti?\n");
			scanf("%d", &c);
			for (i = 0; i < c; i++)
				UnosNaPocetak(Head);
		}
	}

	else if (a == 2)
	{
		printf("Odabrali ste unos na kraj liste. Mozete poceti s unosom podataka\n");
		UnosNaKraj(Head);

		printf("Zelite li unijeti jos jednu osobu na kraj liste? \nUkoliko zelite unesite 1.\n");
		scanf("%d", &b);
		if (b == 1)
		{
			printf("Koliko osoba zelite unijeti?\n");
			scanf("%d", &c);
			for (i = 0; i < c; i++)
				UnosNaKraj(Head);
		}
	}
	else
		printf("Krivi unos");

	printf("\nVasa lista:\n");
	IspisListe(Head->Next);
	OslobodiMemoriju(Head);

	return EXIT_SUCCESS;
}


int UnosNaPocetak(Pozicija P)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(osoba));

	if (Q == NULL)
	{
		printf("Greska u alociranju memorije!");
		return FILE_ERROR;
	}
	UnosPodataka(Q);

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int UnosNaKraj(Pozicija P)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(osoba));

	if (Q == NULL)
	{
		printf("Greska u alociranju memorije!");
		return FILE_ERROR;
	}
	UnosPodataka(Q);

	while (P->Next != NULL)
		P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}


int UnosPodataka(Pozicija Q)
{
	printf("Unesite ime korisnika:\n");
	scanf(" %s", Q->ime);
	printf("Unesite prezime korisnika:\n");
	scanf(" %s", Q->prezime);
	printf("Unesite godinu rodenja korisnika:\n");
	scanf("%d", &Q->godina);

	return EXIT_SUCCESS;
}


int IspisListe(Pozicija P)
{
	if (P == NULL)
	{
		printf("Lista je prazna!\n");
		return FILE_ERROR;
	}

	while (P != NULL)
	{
		printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n", P->ime, P->prezime, P->godina);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

void OslobodiMemoriju(Pozicija P)
{
	while (P->Next != NULL)
	{
		Pozicija temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}

	free(P); 
}


