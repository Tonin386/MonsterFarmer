#include "Game.hpp"

#include <thread>
#include <functional>

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(0));
    Game *game = new Game();
    Monster *m1 = new Monster(10, 100, 100);
    Monster *m2 = new Monster(8, 110, 110);

    game->addMonster(m1);
    game->addMonster(m2);

    thread fight1(
        [](Game *g, Monster *m1, Monster *m2) -> void
        {
            g->startFight(m1, m2);
        },
        game, m1, m2);

    thread farm1(
        [](Game *g) -> void
        {
            g->startSummoning(10);
        },
        game);

    fight1.join();
    farm1.join();

    return 0;
}
