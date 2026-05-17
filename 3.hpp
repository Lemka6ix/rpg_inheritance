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


    LivingCharacter(const LivingCharacter %lc)
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

    
#endif // RPG_CHARACTERS_HPP