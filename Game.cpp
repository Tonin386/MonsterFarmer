#include "Game.hpp"

using namespace std;

Game::Game()
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

    TextInterface::log("New fight has started between two monsters.");

    while (f->playTurn())
    {
        // TextInterface::log("Turn ended.");
    }

    TextInterface::log("Done.");
    TextInterface::showStats(f);
}

void Game::startSummoning(int count)
{
    for (int i = 0; i < count; i++)
    {
        int tier = _farm->summonMonster();
        if (tier < 10)
        {
            TextInterface::log("***** Legendary monster summoned! *****");
        }
        else if (tier > 10 && tier <= 60)
        {
            TextInterface::log("**** Epic monster summoned! ****");
        }
        else if (tier > 60 && tier <= 170)
        {
            TextInterface::log("*** Rare monster summoned! ***");
        }
        else if (tier > 170 && tier <= 400)
        {
            TextInterface::log("** Uncommon monster summoned! **");
        }
        else
        {
            TextInterface::log("* Common monster summoned! *");
        }
    }
}

Game::~Game()
{
}
