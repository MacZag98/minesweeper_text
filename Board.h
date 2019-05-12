#ifndef BOARD_H
#define BOARD_H

#define HEIGHT 10
#define WIDTH 10

#include <iostream>
#include <ctime>
#include <cstdlib>

class Board
{
public:
	Board() {} //pusty konstruktor
	
	Board(int x_start, int y_start, int number_of_mines) //konstruktor z podaniem liczby min
	{
		int x;
		int y;
		game_field[x_start][y_start].if_discovered=1;
		srand( time( NULL ) ); //ustawia ziarno
		while (number_of_mines!=0) //wybiera pola i umieszcza na nich miny
		{
			x=rand()%HEIGHT; //wybiera pierwsza wspolrzedna
			y=rand()%WIDTH; //wybiera druga wspolrzedna
			if (game_field[x][y].if_mined==0 && !game_field[x][y].if_discovered) //jesli na polu nie ma miny i jest nieodkryte
			{
				game_field[x][y].if_discovered=0;
				game_field[x][y].if_flaged=0;
				game_field[x][y].if_mined=1; //dodaje mine
				number_of_mines--;
			}
		}
		discover_adjacent_0(x_start, y_start);
	}

	~Board() //destruktor
	{
	delete game_field;
	}

	bool discover_field(int x, int y) //odkrywa wybrane pole zwraca falsz jesli zostanie odkryte pole z mina
	{
    	if (game_lost(x,y)) //sprawdza czy jest mina
        	{
            	std::cout<<"\nYou lost!\n";
	            return false;
    	    }
    	else if (!game_field[x][y].if_flaged) //sprawdza czy pole nie jest oflagowane, jesli jest to nie mozna odkryc
        {
        	game_field[x][y].if_discovered=1;
        	discover_adjacent_0 (x, y);
        }
    	else
        	std::cout<<"\nField is already flagged!\n";
    	return true;
	}
	
	void discover_adjacent_0 (int x, int y) //odkrywa sasiadujace pola z 0
	{
		if (count_adjacent_mines(x, y)==0)
		{
			for (int i1=-1; i1<2; i1++)
				for (int j1=-1; j1<2; j1++)
					if (-1<x+i1 && x+i1<HEIGHT && -1<y+j1 && y+j1<WIDTH && //pole musi byc sasiadujace
						!game_field[x+i1][y+j1].if_discovered && //pole musi byc nieodkryte
						(count_adjacent_mines(x+i1,y+j1)==0 || //sasiadujace pole musi zawierac 0
					 	(!game_field[x+i1][y+j1].if_mined && count_adjacent_mines(x+i1,y+j1)>0))) //lub musi byc niezaminowanym polem na ktorym powinna pojawic sie liczba
							
							discover_field(x+i1,y+j1); //w takim wypadku odkrywa pole
		}
	}

	void discover_all_mines() //odkrywa pozycje min na planszy po przegranej grze
	{
		for (int i=0; i<WIDTH; i++)
		{
			for (int j=0; j<HEIGHT; j++)
				{
					if (!game_field[j][i].if_discovered && !game_field[j][i].if_flaged)
						if (game_field[j][i].if_mined)
							std::cout << "x";
						else
							std::cout << "_";
					if (!game_field[j][i].if_discovered && game_field[j][i].if_flaged)
						if (game_field[j][i].if_mined)
							std::cout << "x";
						else
							std::cout << "F";
					if (game_field[j][i].if_discovered)
						if (count_adjacent_mines(j,i)==0)
							std::cout << " ";
						else
							std::cout << count_adjacent_mines(j,i);
				}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void flag_or_deflag_field (int x, int y) //flaguje lub odflagowuje pole
	{
		if (!game_field[x][y].if_flaged)
			game_field[x][y].if_flaged=1;
		else
			game_field[x][y].if_flaged=0;
	}
	
	bool game_lost(int x, int y) //sprawdza czy pole wybrane do odkrycia jest zaminowane
	{
		if (game_field[x][y].if_mined) 
			return true; 
		return false;
	}
	
	int count_adjacent_mines(int x, int y) //funkcja zlicza ile pol z minami sasiaduje z wybranym
	{
		int counter=0;
		for (int i1=-1; i1<2; i1++)
			for (int j1=-1; j1<2; j1++)
				if (-1<x+i1 && x+i1<HEIGHT && -1<y+j1 && y+j1<WIDTH && //pole musi byc sasiadujace
					!game_field[x+i1][y+j1].if_discovered && //pole musi byc nieodkryte
					game_field[x+i1][y+j1].if_mined) //pole musi byc zaminowane
						counter++; //zwieksza licznik min
		return counter; //zwraca licznik min
	}

	bool display(int number_of_mines) //wyswietla plansze i sprawdzaczy gra zostala wygrana
	{
		int do_I_win=0;
		for (int i=0; i<WIDTH; ++i)
		{
			for (int j=0; j<HEIGHT; ++j)
				{
					if (!game_field[j][i].if_discovered && !game_field[j][i].if_flaged)
					{
						std::cout << "_";
						++do_I_win;
					}
					if (!game_field[j][i].if_discovered && game_field[j][i].if_flaged)
					{
						std::cout << "F";
						++do_I_win;
					}
					if (game_field[j][i].if_discovered)
						if (count_adjacent_mines(j,i)==0)
							std::cout << " ";
						else
							std::cout << count_adjacent_mines(j,i);
				}
			std::cout << "\n";
		}
		std::cout << "\n";
		if (do_I_win==number_of_mines)
			return true;
		return false;
	}

	void debug_display()
	{
		for (int i=0; i<WIDTH; i++)
		{
			for (int j=0; j<HEIGHT; j++)
				{
					std::cout << "[" << game_field[j][i].if_discovered;
					std::cout << "," << game_field[j][i].if_flaged;
					std::cout << "," << game_field[j][i].if_mined << "]";
				}
			std::cout << "\n";
		}
		std::cout << "\n";
		for (int i=0; i<WIDTH; i++)
		{
			for (int j=0; j<HEIGHT; j++)
				{
					std::cout<<count_adjacent_mines(j,i);
				}
			std::cout << "\n";
		}
	}
private:
	struct Field
	{
		bool if_mined=0; //czy zaminowane
		bool if_discovered=0; //czy odkryte
		bool if_flaged=0; //czy oflagowane
	};
	Field game_field[HEIGHT][WIDTH];
	int height;
	int width;
};


#endif // BOARD_H