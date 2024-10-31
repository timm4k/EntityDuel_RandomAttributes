#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

enum class MonsterType
{
    Ogre,
    Goblin,
    Skeleton,
    Orc,
    Troll
};

struct Monster
{
    MonsterType type;
    std::string name;
    int health;
    int attackPower;

    bool isAlive() const { return health > 0; }
};

std::string getMonsterTypeName(MonsterType type)
{
    switch (type)
    {
    case MonsterType::Ogre: return "Ogre";
    case MonsterType::Goblin: return "Goblin";
    case MonsterType::Skeleton: return "Skeleton";
    case MonsterType::Orc: return "Orc";
    case MonsterType::Troll: return "Troll";
    default: return "Unknown";
    }
}

void printMonster(const Monster& monster)
{
    std::cout << "This " << getMonsterTypeName(monster.type) << " named " << monster.name
        << ", has " << monster.health << " health and "
        << monster.attackPower << " atc power\n";
}

void attack(Monster& attacker, Monster& defender)
{
    if (!attacker.isAlive())
    {
        std::cout << attacker.name << " is defeated and cannot attack\n";
        return;
    }
    if (!defender.isAlive())
    {
        std::cout << defender.name << " is already defeated\n";
        return;
    }

    int damage = std::rand() % attacker.attackPower + 1;
    defender.health -= damage;

    std::cout << attacker.name << " attacks " << defender.name
        << " for " << damage << " damage\n";

    if (defender.health <= 0)
    {
        defender.health = 0;
        std::cout << defender.name << " has been defeated\n";
    }
    else
    {
        std::cout << defender.name << " has " << defender.health << " health remaining\n";
    }
}

Monster createRandomMonster(MonsterType type, const std::string& name)
{
    int health = std::rand() % 101 + 50;
    int attackPower = std::rand() % 41 + 10;
    return Monster{ type, name, health, attackPower };
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::vector<Monster> monsters = {
        createRandomMonster(MonsterType::Goblin, "Lari"),
        createRandomMonster(MonsterType::Orc, "Yoru"),
        createRandomMonster(MonsterType::Skeleton, "Emz"),
        createRandomMonster(MonsterType::Troll, "Warlord"),
        createRandomMonster(MonsterType::Ogre, "Karim")
    };

    std::cout << "All monsters:\n";
    for (const auto& monster : monsters)
    {
        printMonster(monster);
    }

    std::cout << "\nBattle begins\n\n";

    int firstIndex = std::rand() % monsters.size();
    int secondIndex;
    do {
        secondIndex = std::rand() % monsters.size();
    } while (secondIndex == firstIndex);

    Monster& fighter1 = monsters[firstIndex];
    Monster& fighter2 = monsters[secondIndex];

    std::cout << fighter1.name << " the " << getMonsterTypeName(fighter1.type)
        << " vs " << fighter2.name << " the " << getMonsterTypeName(fighter2.type) << "\n\n";

    while (fighter1.isAlive() && fighter2.isAlive())
    {
        attack(fighter1, fighter2);
        if (fighter2.isAlive())
        {
            attack(fighter2, fighter1);
        }
        std::cout << "\n";
    }

    if (fighter1.isAlive())
        std::cout << fighter1.name << " wins\n";
    else
        std::cout << fighter2.name << " wins\n";

    return 0;
}
