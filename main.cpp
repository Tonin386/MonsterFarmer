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
    int loadedItemTemplates = game->loadItemTemplates();

    Player *p1 = new Player("Fiddle");

    game->setPlayer(p1);
    game->loadActiveItems();
    game->loadActiveMonsters();
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

    delete game;

    return 0;
}
