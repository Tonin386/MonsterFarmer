#include "Game.hpp"

using namespace std;

Game::Game(/* args */) 
{
    _farm = new Farm();
}

Game::Game(vector<Monster *> m, vector<Item *> i) : _monsters(m), _items(i)
{
    _farm = new Farm();
}

vector<Monster *> Game::getMonsters() const
{
    return _monsters;
}

vector<Item *> Game::getItems() const
{
    return _items;
}

void Game::addMonster(Monster *m)
{
    _monsters.push_back(m);
}

void Game::addItem(Item *i)
{
    _items.push_back(i);
}

void Game::startFight(Team *attackers, Team *defenders)
{
    Fight *f = new Fight(attackers, defenders);
    _fights.push_back(f);

    console.log("New fight has started between two monsters.");

    while (f->playTurn())
    {
        int i = 0;
        //console.log("Monster1 HP:" + to_string(m1->getHp()) + " Stam: " + to_string(m1->getStamina()) + "/" + to_string(m1->getMaxStamina()) + " | Monster2 HP: " + to_string(m2->getHp())  + " Stam: " + to_string(m2->getStamina()) + "/" + to_string(m2->getMaxStamina()));
    }

    console.log("Done.");
}

void Game::startSummoning(int count)
{
    for (int i = 0; i < count; i++)
    {
        int tier = _farm->summonMonster();
        if (tier < 10)
        {
            console.log("***** Legendary monster summoned! *****");
        }
        else if (tier > 10 && tier <= 60)
        {
            console.log("**** Epic monster summoned! ****");
        }
        else if (tier > 60 && tier <= 170)
        {
            console.log("*** Rare monster summoned! ***");
        }
        else if (tier > 170 && tier <= 400)
        {
            console.log("** Uncommon monster summoned! **");
        }
        else
        {
            console.log("* Common monster summoned! *");
        }
    }
}

Game::~Game()
{
}
