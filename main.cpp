#include "views/TextInterface.hpp"
#include "game/Game.hpp"
#include "game/entities/players/Player.hpp"
#include "game/entities/monsters/Monster.hpp"
#include "game/scenarios/Fight.hpp"
#include "game/entities/monsters/Team.hpp"

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
    if (p1->getMonsters().size() < 4)
        p1->summonMonsters(15);

    bool stop = false;

    thread fights(
        [](Game *g, Player *p, bool *stop) -> void
        {
            TextInterface::log("Starting fights");
            while (!*stop)
            {
                int nbTeams = p->generateTeams();
                for (int i = 0; i < nbTeams; i++)
                {
                    Team *attackers = p->getTeam(i);
                    Team *defenders = g->generateTeam(attackers->getAverageLevel());
                    g->startFight(attackers, defenders);
                    if(*stop) return;
                }
            }
        },
        game, p1, &stop);

    thread stopExec(
        [](bool *stop, Player *p1) -> void
        {
            while (!*stop)
            {
                TextInterface::log("Waiting for user input to end the execution.");
                cin >> *stop;
            }
            TextInterface::log("Quitting game.");
            TextInterface::clear();
        },
        &stop, p1);

    stopExec.join();
    fights.join();

    p1->generateTeams();
    TextInterface::log(p1);

    p1->saveState();
    delete game;

    return 0;
}
