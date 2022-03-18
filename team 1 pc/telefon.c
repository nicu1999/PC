#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct
{ // structura pentru dictionar
	char *gresit;
	char *corect;
} dictionar;
// task 1
int numar(int litera, int li, int k)
{
	int i = 0;
	int aux = 0;
	for (i = litera; i > li - 1; i--)
	{
		aux = aux * 10 + k;
	}
	return aux;
}

void inlocuire(int litera, int *tasta)
{
	if (litera <= 90 && litera >= 65)
	{ // verifica daca este majuscula
		printf("1");
		fflush(stdin);
		litera = litera + 32; // micsoreaza litera
		*tasta = 1;			  // inregistreaza ultima tasta (aici 1)
	}
	if (litera >= 97 && litera <= 99)
	{
		if (*tasta == 2)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 97, 2));
		*tasta = 2;
	}
	if (litera >= 100 && litera <= 102)
	{
		if (*tasta == 3)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 100, 3));
		*tasta = 3;
	}
	if (litera >= 103 && litera <= 105)
	{
		if (*tasta == 4)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 103, 4));
		*tasta = 4;
	}
	if (litera >= 106 && litera <= 108)
	{
		if (*tasta == 5)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 106, 5));
		*tasta = 5;
	}
	if (litera >= 109 && litera <= 111)
	{
		if (*tasta == 6)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 109, 6));
		*tasta = 6;
	}
	if (litera >= 112 && litera <= 115)
	{
		if (*tasta == 7)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 112, 7));
		*tasta = 7;
	}
	if (litera >= 116 && litera <= 118)
	{
		if (*tasta == 8)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 116, 8));
		*tasta = 8;
	}
	if (litera >= 119 && litera <= 122)
	{
		if (*tasta == 9)
		{
			printf("#");
			fflush(stdin);
		};
		printf("%d", numar(litera, 119, 9));
		*tasta = 9;
	}
	if (litera == 32)
	{
		printf("0");
		*tasta = 0;
	};
	fflush(stdin);
}

void codificare(char frz_litera[])
{
	int i = 0;
	int tasta = 99; // sa nu se faca confuzii in program
	for (i = 0; i < strlen(frz_litera) - 1; i++)
	{
		inlocuire(frz_litera[i], &tasta);
	}
}
// task 2
void printarecaracter(char maj, char nr, int k)
{
	char c = 0;
	if (nr == '1')
	{
		return;
	}
	if (nr == '#')
	{ // ignora diezul
		return;
	}
	if (nr == '0')
	{
		c = 32 + k;
	}
	if (nr == '2')
	{
		c = 97 + k; // k numara de cate ori a fost folosita tasta
	}				// numai o data => a, de doua ori =>b etc.
	if (nr == '3')
	{
		c = 100 + k;
	}
	if (nr == '4')
	{
		c = 103 + k;
	}
	if (nr == '5')
	{
		c = 106 + k;
	}
	if (nr == '6')
	{
		c = 109 + k;
	}
	if (nr == '7')
	{
		c = 112 + k;
	}
	if (nr == '8')
	{
		c = 116 + k;
	}
	if (nr == '9')
	{
		c = 119 + k;
	}
	if (maj == '1')
	{ // micsoreaza daca este majuscula
		c = c - 32;
	}
	printf("%c", c); // printeaza caracterul
	fflush(stdin);
}

void decodificare(char cod[])
{
	int k = 0;
	int i = 0;
	while (cod[i] != '\n')
	{
		if (cod[i] == cod[i + 1])
		{ // numara de cate ori exista caractere succesive
			k++;
		}
		else
		{
			printarecaracter(cod[i - k - 1], cod[i], k); // printeaza caracterele
			k = 0;										 // reseteaza contorul
		}
		i++;
	}
}
// task3
void autocorect(dictionar **vector, char *sintagma, int n)
{
	int i;
	int ok;
	char output[100];
	output[0] = '\n';
	char *aux = 0;				 // literele, luate pe rand de strtok
	aux = strtok(sintagma, " "); // prima chemare strtok
	while (aux != NULL)
	{
		ok = 0;
		for (i = 0; i < n; i++)
		{
			if (strcmp(aux, (*vector)[i].gresit) == 0)
			{
				strcat(output, (*vector)[i].corect);
				strcat(output, " ");
				ok = 1;
			}
		}
		if (ok == 0)
		{
			strcat(output, aux); // daca nu e nimic de corectat se concateneaza
			strcat(output, " "); // un spatiu si litera
		}
		aux = strtok(NULL, " \n"); // pentru chemarile succesive
	}
	codificare(output);
	printf("\n");
}
// task4
int nrcomponente(char mesaj[])
{		   // de fapt numara spatiile
	int i; // nr componentelor fiind nr spatii+1
	int k = 1;
	for (i = 0; i < strlen(mesaj) - 1; i++)
	{
		if (mesaj[i] == 32)
		{
			k++;
		}
	}
	return k;
}
void transfer(char mesaj[], long long int **componente, int n)
{
	int i = 0;
	int j = 0;
	int aux;
	*componente = calloc(n, sizeof(long long int));
	do
	{
		for (j = 0; j < strlen(mesaj); j++)
		{ // prelucreaza fiecare
			if (mesaj[j] == 32)
			{		 // litera in parte, verifica daca e
				i++; // spatiu, daca da, sare peste
			}		 // daca litera e majuscula, se noteaza 1
			if (mesaj[j] <= 90 && mesaj[j] >= 65)
			{ // si se micsoreaza litera
				(*componente)[i] = (*componente)[i] * 10 + 1;
				mesaj[j] = mesaj[j] + 32;
			}
			if (mesaj[j] >= 97 && mesaj[j] <= 99)
			{
				aux = numar(mesaj[j], 97, 2);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 100 && mesaj[j] <= 102)
			{
				aux = numar(mesaj[j], 100, 3);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 103 && mesaj[j] <= 105)
			{
				aux = numar(mesaj[j], 103, 4);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 106 && mesaj[j] <= 108)
			{
				aux = numar(mesaj[j], 106, 5);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 109 && mesaj[j] <= 111)
			{
				aux = numar(mesaj[j], 109, 6);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 112 && mesaj[j] <= 115)
			{
				aux = numar(mesaj[j], 112, 7);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 116 && mesaj[j] <= 118)
			{
				aux = numar(mesaj[j], 116, 8);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
			if (mesaj[j] >= 119 && mesaj[j] <= 122)
			{
				aux = numar(mesaj[j], 119, 9);
				while (aux != 0)
				{
					(*componente)[i] = (*componente)[i] * 10 + aux % 10;
					aux = aux / 10;
				}
			}
		}
	} while (i != n - 1);
}

void printarecomponente(long long int **componente, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%lld ", (*componente)[i]);
		fflush(stdin);
	}
}
void cmmcmppoz(long long int **componente, int n)
{ // aflarea maximultui
	int i = 1;
	long long int maxim = (*componente)[0]; // maximul
	int maximnr = 1;						// pozitia
	for (i = 1; i < n; i++)
	{
		if ((*componente)[i] > maxim)
		{
			maxim = (*componente)[i];
			maximnr = i + 1;
		}
	}
	printf("%lld %d\n", maxim, maximnr);
}
int prim(long long int **componente, int n)
{ // se foloseste cmmdc
	int i = 0;
	int j = 0;
	long long int aux1 = 0;
	long long int aux2 = 0;
	for (i = 0; i < n - 2; i++)
	{
		for (j = i + 1; j < n - 1; j++)
		{
			aux1 = (*componente)[i];
			aux2 = (*componente)[j];
			while (aux1 != aux2)
			{
				if (aux1 > aux2)
					aux1 = aux1 - aux2;
				else
					aux2 = aux2 - aux1;
			}
			if (aux1 != 1)
			{
				return 0;
			}
		}
	}
	return 1;
}

int magic(long long int **componente, int n)
{ //(∩｀-´)⊃━☆ﾟ.*･｡ﾟ
	int aux = 0;
	int i = 0;
	int magic = 0;
	for (i = 0; i < n; i++)
	{
		aux = (*componente)[i];
		while (aux != 0)
		{
			magic = magic + aux % 10;
			aux = aux / 10;
		}
	}
	return magic % 9;
}

int main()
{
	// task1
	char fraza[255];
	char cod[255];
	fgets(fraza, 255, stdin); // citeste fraza
	fflush(stdin);			  // folosit in combinatie cu fgets pt a goli bufferul
	codificare(fraza);		  // codifica fraza
	printf("\n");
	// task2
	fgets(cod, 255, stdin);
	fflush(stdin);
	decodificare(cod); // decodifica fraza
	printf("\n");
	// task3
	int n;
	int i;
	char aux[100];
	char *s1; // folosite mai mult sau mai
	char *s2; // putin sa nu crape strtok
	char sintagma[100];
	fgets(sintagma, 100, stdin); // citeste sintagma
	fflush(stdin);
	scanf("%d", &n);								  // folosesc calloc in loc de malloc
	dictionar *vector = calloc(n, sizeof(dictionar)); // alocare dinamica pentru vector,
	fgets(aux, 100, stdin);							  // citire newline inutil
	for (i = 0; i < n; i++)
	{
		fgets(aux, 100, stdin);
		fflush(stdin);
		vector[i].gresit = calloc(1, sizeof(char));
		vector[i].corect = calloc(1, sizeof(char));
		s1 = strtok(aux, " ");	  // despartirea celor doua cuvinte introduse
		s2 = strtok(NULL, " \n"); // si introducerea in vector
		strcpy(vector[i].gresit, s1);
		strcpy(vector[i].corect, s2);
	}
	autocorect(&vector, sintagma, n); // printeaza fraza corectata, codificata
	for (i = 0; i < n; i++)
	{ // eliberarea memorie
		free(vector[i].gresit);
		free(vector[i].corect);
	}
	free(vector); // eliberare memorie
	// task4
	char mesaj[255];
	long long int *componente; // vector de long long int
	fgets(mesaj, 255, stdin);  // citirea mesajului
	fflush(stdin);
	printf("%d\n", nrcomponente(mesaj));				  // numar componente
	transfer(mesaj, &componente, nrcomponente(mesaj));	  // transfera sirul mesaj in n componente
	printarecomponente(&componente, nrcomponente(mesaj)); // printeaza componente
	printf("\n");
	cmmcmppoz(&componente, nrcomponente(mesaj));			// cea mai mare componenta si pozitia ei
	printf("%d\n", prim(&componente, nrcomponente(mesaj))); // daca este prim sau nu
	free(componente);
	printf("\n"); // aici trebuie sa fie ultimul subpunct
	return 0;	  // nu putem sa le facem chiar pe toate, ¯\_(ツ)_/¯
}
