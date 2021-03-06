#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h> 
#include <vector>
#include <queue>
#include <conio.h>

using namespace std;

class Pole
{
public:
	int x;
	int y;
	bool czy_zajete;
	char znak;
};


void generuj(Pole **temp, int r, int px, int py)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (i == 0 || i == r - 1) { temp[i][j].znak = 'X'; }
			else if (j == 0 || j == r - 1) { temp[i][j].znak = 'X'; }
			else if (i == px && j == py) { temp[i][j].znak = 'O'; }
			else { temp[i][j].znak = ' '; }
			temp[i][j].x = i;
			temp[i][j].y = j;
		}
	}
}


void wyswietl(Pole **temp, int r)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (i == 0 || i == r - 1) { cout << "-[ ]-"; }
			else if (j == 0 || j == r - 1) { cout << " [ ] "; }
			else { cout << "  " << temp[i][j].znak << "  "; }
		}
		cout << endl << endl;
	}
}

void wyswietl(queue<Pole>temp)
{
	Pole frontT, backT;
	frontT = temp.front();
	backT = temp.back();

	cout << " Glowa weza : [" << frontT.x << "] [" << frontT.y << "] " << endl;
	cout << " Koniec weza : [" << backT.x << "] [" << backT.y << "] " << endl;
}


int losowanie(int zakres)
{
	int k;
	k = rand() % zakres;
	k += 1;
	return k;
}


int sterowanie(int ruch)
{

	int p = ruch;
	char w;
	int licznik = 0;
	while (true)
	{
		licznik++;
		if (_kbhit())
		{
			w = _getch();
			p = w - '0';
			if (p == 8 && ruch != 3)//w gore
			{
				p = 1;
				for (int l = licznik; l < 9000; l++) {}
				break;
			}
			else if (p == 2 && ruch != 1)//w dol
			{
				p = 3;
				for (int l = licznik; l < 9000; l++) {}
				break;
			}
			else if (p == 6 && ruch != 4)//w prawo
			{
				p = 2;
				for (int l = licznik; l < 9000; l++) {}
				break;
			}
			else if (p == 4 && ruch != 2)//w lewo
			{
				p = 4;
				for (int l = licznik; l < 9000; l++) {}
				break;
			}
		}
		else if (licznik > 9000)
		{
			p = ruch;
			break;
		}
	}
	return p;
}


void umiescOwoc(Pole **temp, int rozmiar, char owoc)
{
	int x, y;
	x = losowanie(rozmiar);
	y = losowanie(rozmiar);
	if (temp[x][y].znak == ' ') { temp[x][y].znak = owoc; }
}


void rozgrywka(Pole **temp, int rozmiarP, int px, int py)
{
	int lattency = 250;
	int licznik = 1;
	char owoc = '*';
	int snakeSize = 3;//rozmiar snakea
	queue<Pole> KompletnyWonsz;
	Pole snake = temp[px][py];

	KompletnyWonsz.push(snake);

	int ruch = 1;
	while (true)
	{

		if ((temp[snake.x - 1][snake.y].znak == 'O' || temp[snake.x - 1][snake.y].znak == 'D' || temp[snake.x - 1][snake.y].znak == 'X') &&
			(temp[snake.x + 1][snake.y].znak == 'O' || temp[snake.x + 1][snake.y].znak == 'D' || temp[snake.x + 1][snake.y].znak == 'X') &&
			(temp[snake.x][snake.y - 1].znak == 'O' || temp[snake.x][snake.y - 1].znak == 'D' || temp[snake.x][snake.y - 1].znak == 'X') &&
			(temp[snake.x][snake.y + 1].znak == 'O' || temp[snake.x][snake.y + 1].znak == 'D' || temp[snake.x][snake.y + 1].znak == 'X'))// sprawdza czy zostaly wolne pola przy glowie
		{
			break;
		}

		else
		{
			//ruch = losowanie(4);
			ruch = sterowanie(ruch);

			if (ruch == 1)
			{
				if (temp[snake.x - 1][snake.y].znak == 'X')
				{
					break;
				}
				else if (temp[snake.x - 1][snake.y].znak == 'O' || temp[snake.x - 1][snake.y].znak == 'D') {}

				else if (temp[snake.x - 1][snake.y].znak == owoc)//czy owoc
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x - 1][snake.y].znak = 'D';
					snake = temp[snake.x - 1][snake.y];
					snakeSize++;
					KompletnyWonsz.push(snake);
				}

				else
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x - 1][snake.y].znak = 'D';
					snake = temp[snake.x - 1][snake.y];
					KompletnyWonsz.push(snake);
				}
			}

			else if (ruch == 2)
			{
				if (temp[snake.x][snake.y + 1].znak == 'X')
				{
					break;
				}
				else if (temp[snake.x][snake.y + 1].znak == 'O' || temp[snake.x][snake.y + 1].znak == 'D') {}

				else if (temp[snake.x][snake.y + 1].znak == owoc)//czy owoc
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x][snake.y + 1].znak = 'D';
					snake = temp[snake.x][snake.y + 1];
					snakeSize++;
					KompletnyWonsz.push(snake);
				}

				else
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x][snake.y + 1].znak = 'D';
					snake = temp[snake.x][snake.y + 1];
					KompletnyWonsz.push(snake);
				}
			}

			else if (ruch == 3)
			{
				if (temp[snake.x + 1][snake.y].znak == 'X')
				{
					break;
				}
				else if (temp[snake.x + 1][snake.y].znak == 'O' || temp[snake.x + 1][snake.y].znak == 'D') {}

				else if (temp[snake.x + 1][snake.y].znak == owoc)//czy owoc
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x + 1][snake.y].znak = 'D';
					snake = temp[snake.x + 1][snake.y];
					snakeSize++;
					KompletnyWonsz.push(snake);
				}
				else
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x + 1][snake.y].znak = 'D';
					snake = temp[snake.x + 1][snake.y];
					KompletnyWonsz.push(snake);
				}
			}

			else if (ruch == 4)
			{
				if (temp[snake.x][snake.y - 1].znak == 'X')
				{
					break;
				}
				else if (temp[snake.x][snake.y - 1].znak == 'O' || temp[snake.x][snake.y - 1].znak == 'D') {}
				else if (temp[snake.x][snake.y - 1].znak == owoc)//czy owoc
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x][snake.y - 1].znak = 'D';
					snake = temp[snake.x][snake.y - 1];
					snakeSize++;
					KompletnyWonsz.push(snake);
				}
				else
				{
					Sleep(lattency);
					temp[snake.x][snake.y].znak = 'O';
					temp[snake.x][snake.y - 1].znak = 'D';
					snake = temp[snake.x][snake.y - 1];
					KompletnyWonsz.push(snake);
				}
			}


			if (KompletnyWonsz.size() > snakeSize)
			{
				temp[KompletnyWonsz.front().x][KompletnyWonsz.front().y].znak = ' ';
				KompletnyWonsz.pop();
			}


			system("cls");
			wyswietl(temp, rozmiarP);
			licznik++;

			if (licznik % 5 == 0) { umiescOwoc(temp, rozmiarP - 2, owoc); }//umieszczanie owocow
		}
	}

	cout << "=   Koniec   =     Wynik :" << snakeSize << "                                 Wcisnij  ENTER !" << endl;
}


int main()
{
	srand(time(NULL));

	char w;
	int poczatekx, poczateky;

	int r = 16; //rozmiar Planszy
	int r2 = r - 2;
	Pole **Plansza = new Pole *[r];
	for (int i = 0; i < r; i++) { Plansza[i] = new Pole[r]; }

	while (true)
	{
		cout << "Type anything to start" << endl;
		getchar();
		system("cls");
		poczatekx = (rand() % r2) + 1;
		poczateky = (rand() % r2) + 1;

		generuj(Plansza, r, poczatekx, poczateky);
		rozgrywka(Plansza, r, poczatekx, poczateky);
		getchar();
		system("cls");
		cout << "=   WAIT!   =     ";

	}


	getchar(); getchar();
}

