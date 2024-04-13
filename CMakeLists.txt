cmake_minimum_required(VERSION 3.27)
project(345Project)


set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(catchTests)

#cpp files only
add_executable(d20Game
        src/main.cpp
        src/Static/Functions.cpp
        src/Static/Dice.cpp
        src/Controller/GameManager.cpp
        src/Controller/GameEngine.cpp
        src/Components/Character.cpp
        src/Components/Item.cpp
        src/Components/Weapon.cpp
        src/Components/Armor.cpp
        src/Components/ItemBag.cpp
        src/Components/Equipment.cpp
        
        src/Components/MapGeneration.cpp
        src/Components/MapEditor.cpp
        #src/Components/MapDirector.cpp
        #src/Components/MapBuilder.cpp
        #src/Components/MapConcreteBuilder.cpp
        src/Components/Subject.cpp
        src/Components/Observer.cpp
        src/Controller/Combat.cpp
        src/Components/Potion.cpp
        src/Controller/ObjectEditor.cpp
)

#[[
add_executable(TestExecutable
        

)
]]

