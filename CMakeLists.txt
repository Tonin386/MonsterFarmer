cmake_minimum_required(VERSION 3.0.0)
project(MonsterFarmer VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCES 
    game/entities/items/Item.hpp 
    game/entities/monsters/Team.hpp 
    game/entities/monsters/Monster.hpp 
    game/entities/Players/Player.hpp 
    game/scenarios/Farm.hpp 
    game/scenarios/Fight.hpp 
    views/TextInterface.hpp 
    game/Game.hpp

    game/entities/items/Item.cpp 
    game/entities/monsters/Team.cpp 
    game/entities/monsters/Monster.cpp 
    game/entities/Players/Player.cpp 
    game/scenarios/Farm.cpp 
    game/scenarios/Fight.cpp 
    views/TextInterface.cpp 
    game/Game.cpp 
    main.cpp
)

add_executable(MonsterFarmer ${SOURCES})
set_target_properties(MonsterFarmer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../ )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
