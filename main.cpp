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


void testBattlemageAttacks() {
    std::cout << "\ntestBattlemageAttacks" << std::endl;
    
    Battlemage bm("coolBattlemage", 100, 15, 25, 60, 10);

    bm.physicalAttack();
    bm.physicalAttack();

    bm.magicAttack();
    bm.magicAttack();

    bm.attack();

    Character* character = &bm;
    character->attack();
    
    std::cout << "Battlemage attack test passed!" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "\ntestCopyAndAssignment" << std::endl;
    
    Warrior originalWarrior("OriginalWarrior", 100, 15);
    originalWarrior.attack();
    Warrior copiedWarrior = originalWarrior;
    
    std::cout << "Original warrior damage dealt: " << originalWarrior.getPersonalDamageDealt() << std::endl;
    std::cout << "Copied warrior damage dealt: " << copiedWarrior.getPersonalDamageDealt() << std::endl;

    Mage mage1("Mage1", 80, 25, 100, 10);
    mage1.attack();
    Mage mage2("Mage2", 90, 30, 120, 15);
    mage2 = mage1;
    
    std::cout << "Mage1 mana: " << mage1.getMana() << std::endl;
    std::cout << "Mage2 mana: " << mage2.getMana() << std::endl;
    
    std::cout << "Copy and assignment test passed!" << std::endl << std::endl;
}

void testMultipleInheritance() {
    std::cout << "\ntestMultipleInheritance" << std::endl;
    
    Battlemage bm("TestBattlemage", 100, 15, 20, 50, 8);
    
    std::cout << "Battlemage health: " << bm.getHealth() << std::endl;
    std::cout << "Battlemage mana: " << bm.getMana() << std::endl;
    
    bm.attack();
    std::cout << "Mana after attack: " << bm.getMana() << std::endl;
    
    Warrior& warriorRef = bm;
    Mage& mageRef = bm;
    
    warriorRef.attack();
    mageRef.attack();
    
    std::cout << "Multiple inheritance test passed!" << std::endl << std::endl;
}

void testAbstractClass() {
    std::cout << "\ntestAbstractClass" << std::endl;
    
    Character* character = new Warrior("TestWarrior", 100, 15);
    character->attack();
    delete character;
    
    std::cout << "Abstract class test passed!" << std::endl << std::endl;
}

int main() {
    try {
        testBasicCreation();
        testPolymorphism();
        testCombat();
        testStaticMembers();
        testBattlemageAttacks();
        testCopyAndAssignment();
        testMultipleInheritance();
        testAbstractClass();
        
        std::cout << "All tests passed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}