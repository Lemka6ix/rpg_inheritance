#ifndef RPG_CHARACTERS_HPP
#define RPG_CHARACTERS_HPP

#include <string>
#include <iostream>


/**
 * @brief Абстрактный базовый класс для всех игровых персонажей
 * 
 * Класс Character определяет общий интерфейс для всех типов персонажей
 * в RPG-системе. Является абстрактным классом с чисто виртуальными методами.
 */
class Character {
private:
    bool alive;                           ///< Статус жизни персонажа
    std::string name;                     ///< Имя персонажа
    static int totalDamageDealt;          ///< Общий нанесенный урон всеми персонажами
    static Character* topDamageDealer;    ///< Указатель на персонажа с максимальным уроном
    int personalDamageDealt;              ///< Персональный нанесенный урон

protected:
    int damage;                           ///< Базовый урон персонажа

public:
    /**
     * @brief Конструктор базового персонажа
     * @param name_p Имя персонажа
     * @param alive_p Статус жизни (по умолчанию true)
     * @param damage_p Базовый урон (по умолчанию 0)
     */
    Character(const std::string& name_p, bool alive_p = true, int damage_p = 0)
        : name(name_p), alive(alive_p), damage(damage_p), personalDamageDealt(0) {}
    
    /**
     * @brief Конструктор копирования
     * @param c Объект для копирования
     */
    Character(const Character &c)
        : name(c.name), alive(c.alive), damage(c.damage), personalDamageDealt(c.personalDamageDealt)
    {
        std::cout << "Character copy constructor called" << std::endl;
    }

    /**
     * @brief Оператор присваивания
     * @param c Объект для копирования
     * @return Ссылка на текущий объект
     */
    Character& operator=(const Character &c) {
        if (this != &c) {
            name = c.name;
            alive = c.alive;
            damage = c.damage;
            personalDamageDealt = c.personalDamageDealt;
        }
        return *this;
    }

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Character() {
        std::cout << "Character destructor called" << std::endl;
    }

    /**
     * @brief Чисто виртуальная функция атаки
     * @return Количество нанесенного урона
     */
    virtual int attack() = 0;

    /**
     * @brief Чисто виртуальная функция получения урона
     * @param damage Полученный урон
     */
    virtual void takeDamage(int damage) = 0;

    /**
     * @brief Чисто виртуальная функция проверки жизни
     * @return true если персонаж жив, false если мертв
     */
    virtual bool isAlive() const = 0;

    /**
     * @brief Получить имя класса
     * @return Строка с именем класса
     */
    virtual std::string getClassName() const {return "Character";}

    /**
     * @brief Получить имя персонажа
     * @return Имя персонажа
     */
    std::string getName() const { return name; }

    /**
     * @brief Получить персональный нанесенный урон
     * @return Количество нанесенного урона
     */
    int getPersonalDamageDealt() const { return personalDamageDealt; }

    /**
     * @brief Статический метод получения общего урона
     * @return Суммарный урон всех персонажей
     */
    static int getTotalDamageDealt() { return totalDamageDealt; }

    /**
     * @brief Статический метод получения лучшего бойца
     * @return Указатель на персонажа с максимальным уроном
     */
    static Character* getTopDamageDealer() { return topDamageDealer; }

protected:
    /**
     * @brief Добавить урон к статистике
     * @param amount Количество урона для добавления
     */
    void addDamage(int amount){
        personalDamageDealt += amount;
        totalDamageDealt += amount;
        if(!topDamageDealer || personalDamageDealt > topDamageDealer->personalDamageDealt){
            topDamageDealer = this;
        }
    }
};


/**
 * @brief Класс живых персонажей с системой здоровья
 * 
 * Наследуется от Character и добавляет систему здоровья,
 * максимального здоровья и механику получения урона.
 */
class LivingCharacter : public Character {
protected:
    unsigned health;     ///< Текущее здоровье персонажа
    unsigned maxHealth;  ///< Максимальное здоровье персонажа
    
public:
    /**
     * @brief Конструктор живого персонажа
     * @param name_p Имя персонажа
     * @param health_p Текущее здоровье
     * @param max_health_p Максимальное здоровье
     * @param dmg Базовый урон
     */
    LivingCharacter(const std::string& name_p, unsigned health_p, unsigned max_health_p, int dmg)
        : Character(name_p, true, dmg), health(health_p), maxHealth(max_health_p)
    {}


    /**
     * @brief Конструктор копирования
     * @param lc Объект для копирования
     */
    LivingCharacter(const LivingCharacter &lc)
        : Character(lc), health(lc.health), maxHealth(lc.maxHealth)
    {
        std::cout << "LivingCharacter copy constructor called" << std::endl;
    }


    /**
     * @brief Оператор присваивания
     * @param lc Объект для копирования
     * @return Ссылка на текущий объект
     */
    LivingCharacter& operator=(const LivingCharacter &lc) {
        if (this != &lc) {
            Character::operator=(lc);
            health = lc.health;
            maxHealth = lc.maxHealth;
        }
        return *this;
    }

    /**
     * @brief Проверка, жив ли персонаж
     * @return true если здоровье > 0, иначе false
     */
    bool isAlive() const override {
        return health > 0;
    }

    /**
     * @brief Получение урона персонажем
     * @param damage Количество получаемого урона
     */
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


    /**
     * @brief Получить текущее здоровье
     * @return Текущее значение здоровья
     */
    unsigned getHealth() const { return health; }

    /**
     * @brief Получить максимальное здоровье
     * @return Максимальное значение здоровья
     */
    unsigned getMaxHealth() const { return maxHealth; }

    /**
     * @brief Получить имя класса
     * @return Строка "LivingCharacter"
     */
    std::string getClassName() const override {return "LivingCharacter"; }
};


/**
 * @brief Класс воина - специализируется на физических атаках
 * 
 * Наследуется от LivingCharacter, представляет персонажа
 * который наносит физический урон без затрат ресурсов.
 */
class Warrior : virtual public LivingCharacter
{
public:
    /**
     * @brief Конструктор воина
     * @param name_p Имя воина
     * @param health_p Здоровье воина
     * @param physical_damage_p Физический урон
     */
    Warrior(const std::string& name_p, unsigned health_p, unsigned physical_damage_p)
        : LivingCharacter(name_p, health_p, health_p, physical_damage_p){
            std::cout << "Warrior " << name_p << " has been created" << std::endl;
        }
    
    /**
     * @brief Конструктор копирования
     * @param w Объект для копирования
     */
    Warrior(const Warrior &w) : LivingCharacter(w){
        std::cout << "Warrior copy constructor called" << std::endl;
    }

    /**
     * @brief Оператор присваивания
     * @param w Объект для копирования
     * @return Ссылка на текущий объект
     */
    Warrior& operator=(const Warrior &w) {
        if (this != &w) {
            LivingCharacter::operator=(w);
        }
        return *this;
    }

    /**
     * @brief Выполнить физическую атаку
     * @return Количество нанесенного физического урона
     */
    int attack() override {
        if (!isAlive()) {
            std::cout << getName() << " is dead and cannot attack!" << std::endl;
            return 0;
        }

        std::cout << getName() << " deals physical damage: " << damage << std::endl;
        addDamage(damage);
        return damage;
    }
    
    /**
     * @brief Получить имя класса
     * @return Строка "Warrior"
     */
    std::string getClassName() const override { return "Warrior"; }
};


/**
 * @brief Класс мага - специализируется на магических атаках
 * 
 * Наследуется от LivingCharacter, представляет персонажа
 * который наносит магический урон с затратами маны.
 */
class Mage : virtual public LivingCharacter
{
private:
    unsigned maxMana;      ///< Максимальное количество маны

protected:
    unsigned mana;         ///< Текущее количество маны
    unsigned spellCost;    ///< Стоимость заклинания в мане

public:
    /**
     * @brief Конструктор мага
     * @param name_p Имя мага
     * @param health_p Здоровье мага
     * @param magic_damage_p Магический урон
     * @param mana_p Количество маны
     * @param spell_cost_p Стоимость заклинания
     */
    Mage(const std::string& name_p, unsigned health_p, unsigned magic_damage_p,
        unsigned mana_p, unsigned spell_cost_p)
        : LivingCharacter(name_p, health_p, health_p, magic_damage_p),
        mana(mana_p), maxMana(mana_p), spellCost(spell_cost_p)
        {
            std::cout << "Mage " << name_p << " has been created" << std::endl;
        }
    
    /**
     * @brief Конструктор копирования
     * @param m Объект для копирования
     */
    Mage(const Mage &m) : LivingCharacter(m), mana(m.mana), maxMana(m.maxMana), spellCost(m.spellCost)
    {
        std::cout << "Mage copy constructor called" << std::endl;
    }

    /**
     * @brief Оператор присваивания
     * @param m Объект для копирования
     * @return Ссылка на текущий объект
     */
    Mage& operator=(const Mage &m) {
        if (this != &m) {
            LivingCharacter::operator=(m);
            mana = m.mana;
            maxMana = m.maxMana;
            spellCost = m.spellCost;
        }
        return *this;
    }

    /**
     * @brief Проверить, хватает ли маны для заклинания
     * @return true если маны достаточно, иначе false
     */
    bool hasEnoughMana() const {
        return mana >= spellCost;
    }

    /**
     * @brief Выполнить магическую атаку
     * @return Количество нанесенного магического урона
     */
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

    /**
     * @brief Получить текущее количество маны
     * @return Текущая мана
     */
    unsigned getMana() const { return mana; }

    /**
     * @brief Получить максимальное количество маны
     * @return Максимальная мана
     */
    unsigned getMaxMana() const {return maxMana; }

    /**
     * @brief Получить имя класса
     * @return Строка "Mage"
     */
    std::string getClassName() const override { return "Mage"; }
};


/**
 * @brief Класс боевого мага - гибрид воина и мага
 * 
 * Множественное наследование от Warrior и Mage.
 * Позволяет выбирать между физическими и магическими атаками.
 */
class Battlemage : public Warrior, public Mage
{
public:
    /**
     * @brief Конструктор боевого мага
     * @param name_p Имя боевого мага
     * @param health_p Здоровье
     * @param physical_damage_p Физический урон
     * @param magic_damage_p Магический урон
     * @param mana_p Количество маны
     * @param spell_cost_p Стоимость заклинания
     */
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

    /**
     * @brief Конструктор копирования
     * @param bm Объект для копирования
     */
    Battlemage(const Battlemage &bm)
        : LivingCharacter(bm), Warrior(bm), Mage(bm)
    {
        std::cout << "Battlemage copy constructor called" << std::endl;
    }

    /**
     * @brief Оператор присваивания
     * @param bm Объект для копирования
     * @return Ссылка на текущий объект
     */
    Battlemage& operator=(const Battlemage &bm) {
        if (this != &bm) {
            Warrior::operator=(bm);
            Mage::operator=(bm);
        }
        return *this;
    }

    /**
     * @brief Базовая атака (физическая по умолчанию)
     * @return Количество нанесенного урона
     */
    int attack() override {
        return physicalAttack();
    }

    /**
     * @brief Физическая атака
     * @return Количество нанесенного физического урона
     */
    int physicalAttack() {
        if (!isAlive()) {
            std::cout << getName() << " is dead and cannot attack!" << std::endl;
            return 0;
        }
        std::cout << getName() << " deals physical damage: " << Warrior::damage << std::endl;
        addDamage(Warrior::damage);
        return Warrior::damage;
    }

    /**
     * @brief Магическая атака
     * @return Количество нанесенного магического урона
     */
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

    /**
     * @brief Получить имя класса
     * @return Строка "Battlemage"
     */
    std::string getClassName() const override { return "Battlemage"; }
};


// Инициализация статических членов
int Character::totalDamageDealt = 0;                ///< Инициализация общего урона
Character* Character::topDamageDealer = nullptr;    ///< Инициализация указателя на лучшего бойца

#endif