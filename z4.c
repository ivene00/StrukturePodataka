#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define MAX_LINE 256
#define FILE_ERROR -1
#define EXIT_SUCCESS 0

struct _polinom;
typedef struct _polinom* Pozicija;
typedef struct _polinom
{
	int koef;
	int exp;
	Pozicija Next;
}Polinom;

int BrisiSve(Pozicija);
int IspisListe(Pozicija);
int UnosNaPocetak(Pozicija);
int UnesiSortirano(Pozicija, Pozicija);
int PostaviPokazivace(Pozicija, Pozicija);
int CitajIzDatoteke(char*, Pozicija);
int ZbrojiPolinome(Pozicija, Pozicija, Pozicija);
int PomnoziPolinome(Pozicija, Pozicija, Pozicija);

Pozicija Alokacija();
Pozicija NoviUnos(int, int);

int main()
{
	Pozicija Head1 = NULL;
	Pozicija Head2 = NULL;
	Pozicija Head3 = NULL;
	Pozicija Head4 = NULL;
	char file[MAX_LINE] = { 0 };
	Head1 = Alokacija();
	Head2 = Alokacija();
	Head3 = Alokacija();
	Head4 = Alokacija();
	printf("Unesite ime datoteke:\n");
	scanf(" %s", file);
	CitajIzDatoteke(file, Head1);
	ZbrojiPolinome(Head1->Next, Head2->Next, Head3->Next);
	printf("Zbrojeni polinomi:\n");
	IspisListe(Head3->Next);
	printf("Pomnozeni polinomi:\n");
	PomnoziPolinome(Head1->Next, Head2->Next, Head4->Next);
	IspisListe(Head4->Next);
	BrisiSve(Head1);
	BrisiSve(Head2);
	BrisiSve(Head3);
	BrisiSve(Head4);
	return EXIT_SUCCESS;
}

int PostaviPokazivace(Pozicija P, Pozicija Q)
{
	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

Pozicija Alokacija()
{
	Pozicija P = NULL;
	P = (Pozicija)malloc(sizeof(Polinom));
	if (P == NULL)
	{
		printf("Neuspjesno alociranje memorije!\n");
		return NULL;
	}
	return P;
}

int CitajIzDatoteke(char* imeDat, Pozicija P1)
{
	int koef = 0, exp = 0, pom = 0, brojac = 0;
	char buffer[MAX_LINE] = { 0 };
	char* pok_buffer = buffer;

	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return FILE_ERROR;
	}

	fgets(pok_buffer, MAX_LINE, fp);

	while (strlen(pok_buffer) != 0) {
		pom = sscanf(pok_buffer, " %d %d %n", &koef, &exp, &brojac);
		if (pom == 2) {
			Pozicija ClanListe = NULL;
			ClanListe = (Pozicija)malloc(sizeof(Polinom));
			ClanListe->koef = koef;
			ClanListe->exp = exp;
			ClanListe->Next = NULL;
			UnesiSortirano(P1, ClanListe);
			printf("%d %d\n", ClanListe->koef, ClanListe->exp);
		}
		else {
			printf("Greska u datoteci!");
		}

		pok_buffer += brojac;
	}


	return EXIT_SUCCESS;
}

int UnesiSortirano(Pozicija P, Pozicija Q)
{
	Pozicija tmp = NULL;
	tmp = (Pozicija)malloc(sizeof(Polinom));
	if (tmp == NULL)
	{
		printf("Greska u alociranju memorije!");
		return FILE_ERROR;
	}

	tmp->Next = NULL;
	if (P->koef == 0 || (P->koef + Q->koef == 0))
	{
		printf("Koeficijent je 0.");
		return EXIT_SUCCESS;
	}

	while (P->Next != NULL && P->Next->exp > Q->exp)
	{
		P = P->Next;
	}

	if (P->Next != NULL && P->Next->exp == Q->Next->exp)
	{
		P->Next->koef += Q->Next->koef;
	}

	else
	{
		NoviUnos(tmp->koef, tmp->exp);
		PostaviPokazivace(P, Q);
	}
	return EXIT_SUCCESS;
}


int ZbrojiPolinome(Pozicija P1, Pozicija P2, Pozicija P3)
{
	Pozicija tmp = NULL;
	tmp = (Pozicija)malloc(sizeof(Polinom));
	if (P1 == NULL || P2 == NULL)
	{
		printf("Polinom je jednak nuli!\n");
		return FILE_ERROR;
	}
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->exp > P2->exp)
		{
			Pozicija Pnovi = NULL;
			Pnovi = NoviUnos(P1->koef, P1->exp);
			UnesiSortirano(P3, Pnovi);
			P1 = P1->Next;
		}
		else if (P1->exp < P2->exp)
		{
			Pozicija Pnovi = NULL;
			Pnovi = NoviUnos(P2->koef, P2->exp);
			UnesiSortirano(P3, Pnovi);
			P2 = P2->Next;
		}
		else if (P1->exp == P2->exp)
		{
			Pozicija Pnovi = NULL;
			Pnovi = NoviUnos(P1->koef + P2->koef, P1->exp);
			UnesiSortirano(P3, Pnovi);
			P1 = P1->Next;
			P2 = P2->Next;
		}
	}

	tmp = Alokacija();
	if (P2 == NULL) {
		tmp = P1;
	}
	else if (P1 == NULL) {
		tmp = P2;
	}

	while (tmp != NULL) {
		Pozicija Nova = NoviUnos(tmp->koef, tmp->exp);
		UnesiSortirano(P3, Nova);
		tmp = tmp->Next;
	}


	return EXIT_SUCCESS;
}

int PomnoziPolinome(Pozicija P1, Pozicija P2, Pozicija P)
{
	Pozicija poz1 = P1;
	Pozicija poz2 = P2;
	Pozicija p3 = NULL;
	p3 = (Pozicija)malloc(sizeof(Polinom));
	while (poz1 != NULL)
	{
		poz2 = P2;
		while (poz2 != NULL)
		{
			p3 = NoviUnos(poz1->koef * poz2->koef, poz1->exp + poz2->exp);
			UnesiSortirano(P, poz1);
			poz2 = poz2->Next;
		}
		poz1 = poz1->Next;
	}
	free(p3);

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
		printf("%d x^%d +", P->koef, P->exp);
		P = P->Next;
	}
	printf("\n");

	return EXIT_SUCCESS;
}

Pozicija NoviUnos(int k, int e)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(Polinom));

	if (Q == NULL)
	{
		printf("Greska u alociranju!");
		return NULL;
	}
	Q->koef = k;
	Q->exp = e;
	return Q;
}

int BrisiSve(Pozicija P)
{
	Pozicija temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}
