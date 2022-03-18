#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{ // Structura nivelelor
	char intrebare[150];
	char optiunea[150];
	char optiuneb[150];
	char optiunec[150];
	char optiuned[150];
	char optiunecorecta[150];
} nivel;

int citire(nivel *vector, int *argc, char **argv)
{
	int j = 0;
	int size = 1; // Dimensiunea curenta a vectorului de nivele
	FILE *f;
	for (int i = 1; i < *argc; i++)
	{
		f = fopen(argv[i], "r");							 // deschiderea streamului
		while (fgets((vector)[j].intrebare, 150, f) != NULL) // verifica daca s-a a juns la EOF
		{
			fgets((vector)[j].optiunea, 150, f); // se citeste linie cu linie
			fgets((vector)[j].optiuneb, 150, f);
			fgets((vector)[j].optiunec, 150, f);
			fgets((vector)[j].optiuned, 150, f);
			fgets((vector)[j].optiunecorecta, 150, f);
			j++; // cate nivele au fost parcurse din fisiere
		}
		fclose(f);			 // inchiderea streamului
		if (j + 1 == (size)) // verifica daca s-a ajuns la dimensiunea maxima alocata
		{
			size = size + size;
			vector = (nivel *)realloc(vector, size); // dubleaza
		}
	}
	return j; // returneaza numarul de nivele
}

void logo(int ymax, int xmax) // printarea logo-ului
{
	WINDOW *logo = newwin(7, 30, 1, (xmax - 50) / 2);
	refresh();
	mvwprintw(logo, 0, 0, "  _______   _       _       ");
	mvwprintw(logo, 1, 0, " |__   __| (_)     (_)      ");
	mvwprintw(logo, 2, 0, "    | |_ __ ___   ___  __ _ ");
	mvwprintw(logo, 3, 0, "    | | '__| \\ \\ / / |/ _` |");
	mvwprintw(logo, 4, 0, "    | | |  | |\\ V /| | (_| |");
	mvwprintw(logo, 5, 0, "    |_|_|  |_| \\_/ |_|\\__,_| "); //#fancy
	wrefresh(logo);
}

int mainmenu(int ymax, int xmax) // CERINTA 1 ,meniul principal
{
	int choice;
	int i;
	int highlight = 0;
	clear();											  // curatarea ecranulu, in cazul iesirii din joc si intrarii
	refresh();											  // din nou in meniul principal
	logo(ymax, xmax);									  // printare logo
	WINDOW *menu = newwin(7, 20, 7, (xmax - 50) / 2 + 4); // initializare
	refresh();
	keypad(menu, true); // initializare sagetilor de la tastatura
	char *menuchoice[] = {"New game", "Resume Game", "Quit"};
	box(menu, 0, 0); // bordura in jurul cutiei
	wrefresh(menu);
	while (1)
	{
		for (i = 0; i < 3; i++)
		{
			if (i == highlight) // reverseaza culorile la optiunea selectata
			{
				wattron(menu, A_REVERSE);
			}
			mvwprintw(menu, i + 1, 3, menuchoice[i]);
			wattroff(menu, A_REVERSE);
		}
		choice = wgetch(menu);
		switch (choice) // parcurgerea meniului
		{
		case KEY_UP:
			highlight--;
			if (highlight == -1)
			{
				highlight = 0;
			}
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 3)
			{
				highlight = 2;
			}
			break;
		default:
			break;
		}
		if (choice == 10) // selectare ENTER
		{
			wclear(menu);
			wrefresh(menu);
			return highlight; // returneaza 0,1,2 un functie de ce a fost selectat
			break;
		}
		if (choice == 113) // apasare q
		{
			return 2;
			break;
		}
	}
}

int trivia(nivel *vector, int i, int *corect, int *gresite, int *score, int ymax, int xmax) // CERINTA 2 si 3, joc propriu zis
{
	char answer;
	WINDOW *wscore = newwin(3, 20, 4, (xmax) / 2 + 5);	  // intializare
	WINDOW *winq = newwin(5, 50, 1 + 7, (xmax - 50) / 2); // se foloseste xmax si ymax
	WINDOW *wina = newwin(4, 25, 6 + 7, (xmax - 50) / 2); // pentru centrarea pe ecran
	WINDOW *winb = newwin(4, 25, 6 + 7, xmax / 2);
	WINDOW *winc = newwin(4, 25, 10 + 7, (xmax - 50) / 2);
	WINDOW *wind = newwin(4, 25, 10 + 7, xmax / 2);
	WINDOW *answr = newwin(3, 42, ymax - 3, (xmax - 50) / 2);
	refresh();
	box(wscore, 0, 0);
	mvwprintw(wscore, 1, 2, "Score:");
	mvwprintw(wscore, 1, 10, "%d", *score);
	box(winq, 0, 0);
	mvwprintw(winq, 0, 0, "QUESTION");
	mvwprintw(winq, 1, 2, (vector)[i].intrebare); // printarea intrebarilor
	box(wina, 0, 0);
	mvwprintw(wina, 0, 0, "A");
	mvwprintw(wina, 1, 2, (vector)[i].optiunea); // printarea optiuni
	box(winb, 0, 0);
	mvwprintw(winb, 0, 0, "B");
	mvwprintw(winb, 1, 2, (vector)[i].optiuneb);
	box(winc, 0, 0);
	mvwprintw(winc, 0, 0, "C");
	mvwprintw(winc, 1, 2, (vector)[i].optiunec);
	box(wind, 0, 0);
	mvwprintw(wind, 0, 0, "D");
	mvwprintw(wind, 1, 2, (vector)[i].optiuned);
	box(answr, 0, 0);
	mvwprintw(answr, 1, 2, "Raspunsul tau este:");
	wrefresh(wscore);
	wrefresh(winq);
	wrefresh(wina);
	wrefresh(winb);
	wrefresh(winc);
	wrefresh(wind);
	wrefresh(answr);
	while (1)
	{
		answer = getch(); // input de la tastatur
		if (answer == 'a')
		{
			if (strcmp((vector)[i].optiunea, (vector)[i].optiunecorecta) == 0) // verifica daca este corect
			{
				*score = *score + 10; // marirea scorului
				mvwprintw(answr, 1, 22, "Raspuns Corect A!");
				*corect = *corect + 1; // numara intrebarile corecte
				break;
			}
			else
			{
				*score = *score - 5; // micsorarea scorului
				mvwprintw(answr, 1, 22, "Raspuns Gresit!");
				*gresite = *gresite + 1; // numara intrebarile gresite
				break;
			}
		}
		if (answer == 'b')
		{
			if (strcmp((vector)[i].optiuneb, (vector)[i].optiunecorecta) == 0)
			{
				*score = *score + 10;
				mvwprintw(answr, 1, 22, "Raspuns Corect B!");
				*corect = *corect + 1;
				break;
			}
			else
			{
				*score = *score - 5;
				mvwprintw(answr, 1, 22, "Raspuns Gresit!");
				*gresite = *gresite + 1;
				break;
			}
		}
		if (answer == 'c')
		{
			if (strcmp((vector)[i].optiunec, (vector)[i].optiunecorecta) == 0)
			{
				*score = *score + 10;
				mvwprintw(answr, 1, 22, "Raspuns Corect C!");
				*corect = *corect + 1;
				break;
			}
			else
			{
				*score = *score - 5;
				mvwprintw(answr, 1, 22, "Raspuns Gresit!");
				*gresite = *gresite + 1;
				break;
			}
		}
		if (answer == 'd')
		{
			if (strcmp((vector)[i].optiuned, (vector)[i].optiunecorecta) == 0)
			{
				*score = *score + 10;
				mvwprintw(answr, 1, 22, "Raspuns Corect D!");
				*corect = *corect + 1;
				break;
			}
			else
			{
				*score = *score - 5;
				mvwprintw(answr, 1, 22, "Raspuns Gresit!");
				*gresite = *gresite + 1;
				break;
			}
		}
		if (answer == 's') // CERINTA 4, optiunea skip
		{
			mvwprintw(answr, 1, 22, "Skipped!");
			break;
		}
		if (answer == 'q') // iesire in meniul principal
		{
			wclear(wscore);
			wclear(winq);
			wclear(wina);
			wclear(winb);
			wclear(winc);
			wclear(wind);
			wrefresh(wscore);
			wrefresh(winq);
			wrefresh(wina);
			wrefresh(winb);
			wrefresh(winc);
			wrefresh(wind);
			return 1;
		}
	}
	wclear(wscore);
	box(wscore, 0, 0);
	mvwprintw(wscore, 1, 2, "Score:");
	mvwprintw(wscore, 1, 10, "%d", *score); // updatare scor
	wrefresh(wscore);
	wrefresh(winq);
	wrefresh(wina);
	wrefresh(winb);
	wrefresh(winc);
	wrefresh(wind);
	wrefresh(answr);
	getch();
	wclear(answr);
	wrefresh(answr);
}

void finishscreen(int i, int *corect, int *gresite, int *score, int ymax, int xmax) // CERINTA 5, dupa terminarea intrebarilor
{
	clear();
	refresh();
	logo(ymax, xmax);
	WINDOW *endscr = newwin(5, 45, 8, (xmax - 50) / 2);
	refresh();
	box(endscr, 0, 0);
	mvwprintw(endscr, 1, 2, "Final Score:");
	mvwprintw(endscr, 1, 15, "%d", *score);
	mvwprintw(endscr, 2, 2, "Intrebari corecte:");
	mvwprintw(endscr, 2, 21, "%d", *corect);
	mvwprintw(endscr, 3, 2, "Intrebari gresite:");
	mvwprintw(endscr, 3, 21, "%d", *gresite);
	wrefresh(endscr);
	getch();
}

int main(int argc, char *argv[])
{
	int i = 0;
	int corect = 0;
	int gresite = 0;
	int score = 0;
	int size = 10;
	int actualsize;
	;
	nivel *vector = malloc(sizeof(nivel) * size); // allocare dinamica
	if (argc == 1)
	{
		printf("[Eroare]: Nu s-au dat argumente in linia de comanda.\n");
		return 1;
	}
	else
	{
		actualsize = citire(vector, &argc, argv); // numarul de nivele
	}
	initscr(); // initializare ecran
	noecho();
	keypad(stdscr, TRUE); // initializare keypad
	cbreak();
	curs_set(0); // ascunderea cursorului
	int ymax, xmax;
	int chce;
	getmaxyx(stdscr, ymax, xmax);
	while (1)
	{
		int i;
		chce = mainmenu(ymax, xmax); // primirea alegerii din meniul principal
		if (chce == 0)				 // pornire joc
		{
			score = 0;
			corect = 0;
			gresite = 0;
			for (i = 0; i < actualsize; i++) // parcurgerea nivelelor
			{
				if (trivia(vector, i, &corect, &gresite, &score, ymax, xmax) == 1) // daca s-a apasat q
				{
					break;
				}
			}
		}
		if (chce == 1) // continuare joc
		{
			for (i; i < actualsize; i++)
			{
				if (trivia(vector, i, &corect, &gresite, &score, ymax, xmax) == 1)
				{
					break;
				}
			}
		}
		if (i == actualsize) // terminarea nivelelor
			finishscreen(i, &corect, &gresite, &score, ymax, xmax);
		if (chce == 2) // iesire din progra,
		{
			endwin();
			free(vector);
			return 0;
		}
	}
	getch();
	endwin();	  // inchidere ecran
	free(vector); // eliberare de memorie
	return 0;
}
