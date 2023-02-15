#include "views/TextInterface.hpp"
#include "game/Game.hpp"
#include "game/entities/players/Player.hpp"
#include "game/entities/monsters/Monster.hpp"
#include "game/scenarios/Fight.hpp"

#include <thread>
#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(0));

    Game *game = new Game();
    int loadedMonsterTemplates = game->loadMonsterTemplates();
    cout << "Here 1 " << endl;
    int loadedItemTemplates = game->loadItemTemplates();
    cout << "Here 2 " << endl;

    Player *p1 = new Player("Fiddle");

    game->setPlayer(p1);
    cout << "Here 3 " << endl;
    game->loadActiveItems();
    cout << "Here 4" << endl;
    game->loadActiveMonsters();
    cout << "here 5" << endl;
    if(p1->getMonsters().size() < 10)
        p1->summonMonsters(10);
        
    p1->generateTeams();
    
    TextInterface::log(p1->getTeam(0));

    for(int i = 0; i < 10; i++)
    {
        game->startFight(p1->getTeam(0), game->generateTeam());
    }

    p1->saveState();

    TextInterface::log(p1->getTeam(0));

    return 0;
}
