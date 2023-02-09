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
    game->startSummoning(4 * 4);

    Team *t1 = new Team();
    Team *t2 = new Team();
    Team *t3 = new Team();
    Team *t4 = new Team();

    for(int i = 0; i<4; i++)
    {
        t1->addMonster(game->getActiveMonsters()[i * 4 + 0]);
        t2->addMonster(game->getActiveMonsters()[i * 4 + 1]);
        t3->addMonster(game->getActiveMonsters()[i * 4 + 2]);
        t4->addMonster(game->getActiveMonsters()[i * 4 + 3]);
    }

    thread fight1(
        [](Game *g, Team *t1, Team *t2) -> void
        {
            g->startFight(t1, t2);
        },
        game, t1, t2);
        
    thread fight2(
        [](Game *g, Team *t1, Team *t2) -> void
        {
            g->startFight(t1, t2);
        },
        game, t3, t4);

    fight1.join();
    fight2.join();
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    test();

    return 0;
}
