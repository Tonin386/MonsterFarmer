#include "Game.hpp"

#include <thread>
#include <functional>

using namespace std;

void test()
{
    Game *game = new Game();
    // Monster(id, atk, maxHp, speed, maxStamina, stamina, name, rarity);
    Monster *m1 = new Monster(0, 60, 15000, 85, 1000, 0, "King's Knight", 2);
    Monster *m2 = new Monster(1, 60, 15000, 85, 1000, 0, "King's Knight", 2);
    Monster *m3 = new Monster(2, 135, 8000, 100, 1000, 0, "King's Archer", 2);
    Monster *m4 = new Monster(3, 135, 8000, 100, 1000, 0, "King's Archer", 2);
    Monster *m5 = new Monster(4, 72, 11000, 70, 1000, 0, "Big Orc", 1);
    Monster *m6 = new Monster(5, 72, 11000, 70, 1000, 0, "Big Orc", 1);
    Monster *m7 = new Monster(6, 100, 7500, 120, 1000, 0, "Small gobelin", 1);
    Monster *m8 = new Monster(7, 100, 7500, 120, 1000, 0, "Small gobelin", 1);

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
