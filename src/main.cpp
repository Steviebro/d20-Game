#include "../include/Components/Character.h"
#include "../include/Static/Functions.h"

#include <iostream>

int main() {
    Character c1(1, "BULLY");
    c1.printCharacter();

    Character c2(12, "NImble");
    c2.printCharacter();
    
    Character c3(21, "taNk");
    c3.printCharacter();

    Character c4(-1000, "bullY");
    c4.printCharacter();
    
    

}