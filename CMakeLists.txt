cmake_minimum_required(VERSION 3.16)

project(HoodQuest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HoodQuest

    main.cpp

    Models/Edge.cpp
    Models/Vertex.cpp

    DataStructures/Graph.cpp

    Algorithms/BFS.cpp
)