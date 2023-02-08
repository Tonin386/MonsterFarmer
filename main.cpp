#include "Game.hpp"

#include <thread>
#include <functional>

using namespace std;

// void oldMain()
// {
//     Game *game = new Game();
//     Monster *m1 = new Monster();
//     Monster *m2 = new Monster();

//     game->addMonster(m1);
//     game->addMonster(m2);

//     thread fight1(
//         [](Game *g, Monster *m1, Monster *m2) -> void
//         {
//             g->startFight(m1, m2);
//         },
//         game, m1, m2);

//     thread farm1(
//         [](Game *g) -> void
//         {
//             g->startSummoning(10);
//         },
//         game);

//     fight1.join();
//     farm1.join();
// }

void test()
{
    Game *game = new Game();
    Monster *m1 = new Monster(1, 1, 1, 1000, 1, "Slow monster", 1);
    Monster *m2 = new Monster(1, 1, 2, 1000, 2, "Fast Monster", 2);

    Team *t1 = new Team();

    *((*t1)[0]) = *m1;
    ((*t1)[0])[0] = *m1;
    *(t1[0][0]) = *m1;
    *(t1->operator[](0)) = *m1;

    t1[0] = *t1;

    cout << t1->getMonster(0)->getName() << endl;

    cout << (m1 > m2) << endl;
    cout << (m1 < m2) << endl;
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    test();

    return 0;
}
