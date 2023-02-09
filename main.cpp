#include "Game.hpp"
#include "frontend/TextInterface.hpp"

#include <thread>
#include <functional>
#include <iostream>

using namespace std;

void test()
{
    Game *game = new Game();
    int loadedMonsterTemplates = game->loadMonsterTemplates();
    cout << "Loaded " << loadedMonsterTemplates << " monster templates." << endl;
    Monster *m1 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m2 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m3 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m4 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m5 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m6 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m7 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    Monster *m8 = new Monster(game->getMonsterTemplates()[rand() % loadedMonsterTemplates]);
    game->addActiveMonster(m1);
    game->addActiveMonster(m2);
    game->addActiveMonster(m3);
    game->addActiveMonster(m4);
    game->addActiveMonster(m5);
    game->addActiveMonster(m6);
    game->addActiveMonster(m7);
    game->addActiveMonster(m8);
    TextInterface::showStats(m1);
    TextInterface::showStats(m2);
    TextInterface::showStats(m3);
    TextInterface::showStats(m4);
    TextInterface::showStats(m5);
    TextInterface::showStats(m6);
    TextInterface::showStats(m7);
    TextInterface::showStats(m8);

    Team *t1 = new Team();
    t1->addMonster(m1);
    t1->addMonster(m2);
    t1->addMonster(m3);
    t1->addMonster(m4);

    Team *t2 = new Team();
    t2->addMonster(m5);
    t2->addMonster(m6);
    t2->addMonster(m7);
    t2->addMonster(m8);

    thread fight1(
        [](Game *g, Team *t1, Team *t2) -> void
        {
            g->startFight(t1, t2);
        },
        game, t1, t2);

    fight1.join();
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    test();

    return 0;
}
