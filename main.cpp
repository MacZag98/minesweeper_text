#include <iostream>

#include "Board.h"
#define NUMBER_OF_MINES 10

int main()
{
    int number_of_mines = NUMBER_OF_MINES;
    int x;
    int y;
    int menu;

    std::cout<<"\
Start game. Choose coordinates:\n\
x: ";
    std::cin>>x;
    std::cout<<"\
y: ";
    std::cin>>y;

    Board NewGame = Board(x, y, number_of_mines); //creates a new board with certain number of mines

    while (!NewGame.display(NUMBER_OF_MINES))
    {
    std::cout<<"\
0 - discover\n\
other character - flag or deflag a field\n\
What do you want to do?: \n";
    std::cin>>menu;
    std::cout<<"\
Choose coordinates:\n\
x: ";
    std::cin>>x;
    std::cout<<"\
y: ";
    std::cin>>y;
    if (menu==0)
    {
        if(!NewGame.discover_field(x,y))
        {
            NewGame.discover_all_mines();
            std::cin>>menu;
            return 0;
        }
    }
    else
        NewGame.flag_or_deflag_field(x, y);
    //NewGame.debug_display();
    }
    std::cout<<"You won";
    std::cin>>menu;
    return 0;
}
