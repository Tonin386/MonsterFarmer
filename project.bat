g++ -c "entities/items/Item.hpp"
g++ -c "entities/items/Item.cpp"
g++ -c "entities/Monster.hpp"
g++ -c "entities/Monster.cpp"
g++ -c "gameMethods/Farm.hpp"
g++ -c "gameMethods/Farm.cpp"
g++ -c "gameMethods/Fight.hpp"
g++ -c "gameMethods/Fight.cpp"
g++ -c "frontend/TextInterface.hpp"
g++ -c "frontend/TextInterface.cpp"
g++ -c "Game.hpp"
g++ -c "Game.cpp"
g++ -c main.cpp
g++ Item.o Monster.o Farm.o Fight.o TextInterface.o Game.o main.o -o MonsterFarmer
MonsterFarmer.exe