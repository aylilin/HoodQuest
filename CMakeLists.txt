cmake_minimum_required(VERSION 3.16)

project(HoodQuest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HoodQuest

    main.cpp

    Models/Edge.cpp
    Models/Vertex.cpp
    Models/Player.cpp
    Models/Wolf.cpp
    Models/GameState.cpp
    Models/Dice.cpp
    Models/Item.cpp

    DataStructures/Graph.cpp

    Algorithms/BFS.cpp
    Algorithms/Dijkstra.cpp
    Algorithms/AStar.cpp

    Game/GameEngine.cpp
    Game/Menu.cpp
)
