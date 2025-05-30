cmake_minimum_required(VERSION 3.31)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp
        include/common/GameConstants.h
        include/utils/Utils.h
        src/utils/Utils.cpp
        include/core/Map.h
        src/core/Map.cpp
        include/entities/GameObject.h
        src/entities/GameObject.cpp
        include/entities/Obstacle.h
        src/entities/Obstacle.cpp
        include/entities/Vehicle.h
        src/entities/Vehicle.cpp
        include/entities/Car.h
        src/entities/Car.cpp
        include/entities/Moto.h
        src/entities/Moto.cpp
        include/entities/Frog.h
        src/entities/Frog.cpp
        include/core/Controller.h
        src/core/Controller.cpp
)
