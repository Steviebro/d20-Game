cmake_minimum_required(VERSION 3.27)
project(345Project)


set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(catchTests)

#cpp files only
add_executable(345Project
        src/main.cpp
        src/Static/Functions.cpp
        src/Static/Dice.cpp
        src/Components/Character.cpp
        src/Components/Item.cpp
        src/Components/Weapon.cpp
        src/Components/Armor.cpp
        src/Components/ItemBag.cpp
        src/Components/Equipment.cpp
        src/Controller/GameManager.cpp
        src/Components/MapGeneration.cpp
        src/Components/MapEditor.cpp
        #src/Components/MapDirector.cpp
        #src/Components/MapBuilder.cpp
        #src/Components/MapConcreteBuilder.cpp
        src/Components/Subject.cpp
        src/Components/Observer.cpp
)

#[[
add_executable(TestExecutable
        

)
]]

