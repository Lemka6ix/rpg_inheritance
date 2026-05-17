#include "3.hpp"

void testBasicCreation() {
    std::cout << "\ntestBasicCreation" << std::endl;

    Warrior warrior1("Warrior", 100, 15);
    Mage mage1("Mage", 80, 25, 100, 10);
    Battlemage battlemage1("Battlemage", 120, 12, 20, 80, 15);

    std::cout << "Basic creation test passed!" << std::endl << std::endl;
}

void testPolymorphism() {
    std::cout << "\ntestPolymorphism" << std::endl;
    
    Warrior warrior2("Warrior", 100, 15);
    Mage mage2("Mage", 80, 25, 100, 10);
    Battlemage battlemage2("Battlemage", 120, 12, 20, 80, 15);
    
    Character* characters[] = {&warrior2, &mage2, &battlemage2};
    
    for (int i = 0; i < 3; ++i) {
        std::cout << characters[i]->getClassName() << " " << characters[i]->getName() << " attacks: ";
        characters[i]->attack();
    }
    
    std::cout << "Polymorphism test passed!" << std::endl << std::endl;
}

void testCombat() {
    std::cout << "\ntestCombat" << std::endl;
    
    Warrior warrior3("Warrior", 100, 15);
    Mage mage3("Mage", 80, 25, 100, 10);

    int damage = warrior3.attack();
    mage3.takeDamage(damage);
    
    damage = mage3.attack();
    warrior3.takeDamage(damage);

    for (int i = 0; i < 10 && mage3.isAlive(); ++i) {
        mage3.attack();
    }
    
    std::cout << "Combat test completed!" << std::endl << std::endl;
}

void testStaticMembers() {
    std::cout << "\ntestStaticMembers" << std::endl;

    Character* oldTop = Character::getTopDamageDealer();
    
    Warrior warrior4("Warrior", 100, 15);
    Mage mage4("Mage", 80, 25, 100, 10);

    warrior4.attack();
    warrior4.attack();
    mage4.attack();
    
    std::cout << "Total damage dealt by all characters: " << Character::getTotalDamageDealt() << std::endl;
    
    Character* topDealer = Character::getTopDamageDealer();
    if (topDealer) {
        std::cout << "Top damage dealer: " << topDealer->getName() 
                  << " with " << topDealer->getPersonalDamageDealt() << " damage" << std::endl;
    }
    
    std::cout << "Static members test passed!" << std::endl << std::endl;
}