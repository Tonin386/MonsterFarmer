g++ -c "game/entities/items/Item.hpp"
g++ -c "game/entities/items/Item.cpp"
g++ -c "game/entities/monsters/Team.hpp"
g++ -c "game/entities/monsters/Team.cpp"
g++ -c "game/entities/monsters/Monster.hpp"
g++ -c "game/entities/monsters/Monster.cpp"
g++ -c "game/entities/Players/Player.hpp"
g++ -c "game/entities/Players/Player.cpp"
g++ -c "game/scenarios/Farm.hpp"
g++ -c "game/scenarios/Farm.cpp"
g++ -c "game/scenarios/Fight.hpp"
g++ -c "game/scenarios/Fight.cpp"
g++ -c "views/TextInterface.hpp"
g++ -c "views/TextInterface.cpp"
g++ -c "game/Game.hpp"
g++ -c "game/Game.cpp"
g++ -c "main.cpp"
g++ "Item.o" "Team.o" "Monster.o" "Player.o" "Farm.o" "Fight.o" "TextInterface.o" "Game.o" "main.o" -o MonsterFarmer
MonsterFarmer.exe