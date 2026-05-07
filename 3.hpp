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