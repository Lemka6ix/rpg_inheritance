#ifndef RPG_CHARACTERS_HPP
#define RPG_CHARACTERS_HPP

#include <string>
#include <iostream>


class Character {
private:
    bool alive;
    std::string name;
    static int totalDamageDealt;
    static Character* topDamageDealer;
    int personalDamageDealt;

protected:
    int damage;

public:
    Character(const std::string& name_p, bool alive_p = true, int damage_p = 0)
        : name(name_p), alive(alive_p), damage(damage_p), personalDamageDealt(0) {}
    
    Character(const Character &c)
        : name(c.name), alive(c.alive), damage(c.damage), personalDamageDealt(c.personalDamageDealt)
    {
        std::cout << "Character copy constructor called" << std::endl;
    }

    Character& operator=(const Character &c) {
        if (this != &c) {
            name = c.name;
            alive = c.alive;
            damage = c.damage;
            personalDamageDealt = c.personalDamageDealt;
        }
        return *this;
    }

    virtual ~Character() {
        std::cout << "Character destructor called" << std::endl;
    }

    virtual int attack() = 0;

    virtual void takeDamage(int damage) = 0;

    virtual bool isAlive() const = 0;

    virtual std::string getClassName() const {return "Character";}

    std::string getName() const { return name; }

    int getPersonalDamageDealt() const { return personalDamageDealt; }

    static int getTotalDamageDealt() { return totalDamageDealt; }

    static Character* getTopDamageDealer() { return topDamageDealer; }

protected:
    void addDamage(int amount){
        personalDamageDealt += amount;
        totalDamageDealt += amount;
        if(!topDamageDealer || personalDamageDealt > topDamageDealer->personalDamageDealt){
            topDamageDealer = this;
        }
    }
};


class LivingCharacter : public Character {
protected:
    unsigned health;
    unsigned maxHealth;
    
public:
    LivingCharacter(const std::string& name_p, unsigned health_p, unsigned max_health_p, int dmg)
        : Character(name_p, true, dmg), health(health_p), maxHealth(max_health_p)
    {}


    LivingCharacter(const LivingCharacter &lc)
        : Character(lc), health(lc.health), maxHealth(lc.maxHealth)
    {
        std::cout << "LivingCharacter copy constructor called" << std::endl;
    }


    LivingCharacter& operator=(const LivingCharacter &lc) {
        if (this != &lc) {
            Character::operator=(lc);
            health = lc.health;
            maxHealth = lc.maxHealth;
        }
        return *this;
    }

    bool isAlive() const override {
        return health > 0;
    }

    void takeDamage(int damage) override {
        if (damage > 0 && health > 0) {
            if (damage > static_cast<int>(health)) {
                health = 0;
            } else {
                health -= damage;
            }
            std::cout << getName() << " took " << damage << " damage. HP: " << health << std::endl;

            if (health == 0) {
                std::cout << getName() << " died :(" << std::endl;
            }
        }
    }


    unsigned getHealth() const { return health; }

    unsigned getMaxHealth() const { return maxHealth; }

    std::string getClassName() const override {return "LivingCharacter"; }
};


class Warrior : virtual public LivingCharacter
{
public:
    Warrior(const std::string& name_p, unsigned health_p, unsigned physical_damage_p)
        : LivingCharacter(name_p, health_p, health_p, physical_damage_p){
            std::cout << "Warrior " << name_p << " has been created" << std::endl;
        }
    

    Warrior(const Warrior &w) : LivingCharacter(w){
        std::cout << "Warrior copy constructor called" << std::endl;
    }

    Warrior& operator=(const Warrior &w) {
        if (this != &w) {
            LivingCharacter::operator=(w);
        }
        return *this;
    }

    int attack() override {
        if (!isAlive()) {
            std::cout << getName() << " is dead and cannot attack!" << std::endl;
            return 0;
        }

        std::cout << getName() << " deals physical damage: " << damage << std::endl;
        addDamage(damage);
        return damage;
    }

    std::string getClassName() const override { return "Warrior"; }
};


class Mage : virtual public LivingCharacter
{
private:
    unsigned maxMana;

protected:
    unsigned mana;
    unsigned spellCost;

public:
    Mage(const std::string& name_p, unsigned health_p, unsigned magic_damage_p,
        unsigned mana_p, unsigned spell_cost_p)
        : LivingCharacter(name_p, health_p, health_p, magic_damage_p),
        mana(mana_p), maxMana(mana_p), spellCost(spell_cost_p)
        {
            std::cout << "Mage " << name_p << " has been created" << std::endl;
        }

    Mage(const Mage &m) : LivingCharacter(m), mana(m.mana), maxMana(m.maxMana), spellCost(m.spellCost)
    {
        std::cout << "Mage copy constructor called" << std::endl;
    }

    Mage& operator=(const Mage &m) {
        if (this != &m) {
            LivingCharacter::operator=(m);
            mana = m.mana;
            maxMana = m.maxMana;
            spellCost = m.spellCost;
        }
        return *this;
    }

    bool hasEnoughMana() const {
        return mana >= spellCost;
    }

    int attack() override {
        if(!isAlive()) {
            std::cout << getName() << " is dead and cannot attack!" << std::endl;
            return 0;
        }

        if (!hasEnoughMana()) {
            std::cout << getName() << " doesn't have enough mana!" << std::endl;
            return 0;
        }

        mana -= spellCost;
        std::cout << getName() << " casts a spell for " << damage << " magic damage! Mana left: " << mana << std::endl;
        addDamage(damage);
        return damage;
    }

    unsigned getMana() const { return mana; }

    unsigned getMaxMana() const {return maxMana; }

    std::string getClassName() const override { return "Mage"; }
};


class Battlemage : public Warrior, public Mage
{
public:
    Battlemage(const std::string& name_p, unsigned health_p, unsigned physical_damage_p, 
               unsigned magic_damage_p, unsigned mana_p, unsigned spell_cost_p) 
        : LivingCharacter(name_p, health_p, health_p, 0),
          Warrior(name_p, health_p, physical_damage_p),
          Mage(name_p, health_p, magic_damage_p, mana_p, spell_cost_p)
    {
        Warrior::damage = physical_damage_p;
        Mage::damage = magic_damage_p;
        std::cout << "Battlemage " << name_p << " has been created" << std::endl;
    }

    Battlemage(const Battlemage &bm)
        : LivingCharacter(bm), Warrior(bm), Mage(bm)
    {
        std::cout << "Battlemage copy constructor called" << std::endl;
    }

    Battlemage& operator=(const Battlemage &bm) {
        if (this != &bm) {
            Warrior::operator=(bm);
            Mage::operator=(bm);
        }
        return *this;
    }

    int attack() override {
        return physicalAttack();
    }

    int physicalAttack() {
        if (!isAlive()) {
            std::cout << getName() << " is dead and cannot attack!" << std::endl;
            return 0;
        }
        std::cout << getName() << " deals physical damage: " << Warrior::damage << std::endl;
        addDamage(Warrior::damage);
        return Warrior::damage;
    }

    int magicAttack() {
        if (!isAlive()) {
            std::cout << getName() << " is dead and cannot attack!" << std::endl;
            return 0;
        }

        if (!hasEnoughMana()) {
            std::cout << getName() << " doesn't have enough mana!" << std::endl;
            return 0;
        }

        mana -= spellCost;
        std::cout << getName() << " casts a spell for " << Mage::damage << " magic damage! Mana left: " << mana << std::endl;
        addDamage(Mage::damage);
        return Mage::damage;
    }

    std::string getClassName() const override { return "Battlemage"; }
};

int Character::totalDamageDealt = 0;
Character* Character::topDamageDealer = nullptr;

#endif // RPG_CHARACTERS_HPP