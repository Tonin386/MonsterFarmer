#include "views/TextInterface.hpp"
#include "game/Game.hpp"
#include "game/entities/players/Player.hpp"
#include "game/entities/monsters/Monster.hpp"

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
    cout << "Loaded " << loadedMonsterTemplates << " monster templates." << endl;
    vector<Monster *> monsters = game->getMonsterTemplates();
    
    sort(monsters.begin(), monsters.end(), [](const Monster *a, const Monster *b)
         { return a->getRating() > b->getRating(); });
         
    for (int i = 0; i < monsters.size(); i++)
    {
        TextInterface::log(monsters[i]);
    }

    Player *p1 = new Player("Fiddle");

    game->setPlayer(p1);
    game->loadActiveMonsters();
    p1->generateTeams();

    p1->saveState();

    TextInterface::log(p1);

    return 0;
}
