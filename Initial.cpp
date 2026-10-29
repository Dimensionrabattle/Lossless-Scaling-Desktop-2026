#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Character {
public:
    string name;
    int level;
    int experience;
    int health;
    int attack;

    Character(string name, int health, int attack)
        : name(name), level(1), experience(0),
          health(health), attack(attack) {}

    void gainExperience(int amount) {
        experience += amount;

        while (experience >= level * 100) {
            experience -= level * 100;
            level++;
            health += 20;
            attack += 5;

            cout << name << " reached level " << level << "!\n";
        }
    }

    void display() const {
        cout << name
             << " | Level: " << level
             << " | XP: " << experience
             << " | Health: " << health
             << " | Attack: " << attack << '\n';
    }
};

class CharacterManager {
private:
    vector<Character> characters;

public:
    void addCharacter(const Character& character) {
        characters.push_back(character);
    }

    Character* findCharacter(const string& name) {
        for (auto& character : characters) {
            if (character.name == name) {
                return &character;
            }
        }

        return nullptr;
    }

    void showAll() const {
        cout << "\nCharacter Roster\n";
        cout << "================\n";

        for (const auto& character : characters) {
            character.display();
        }
    }

    void sortByLevel() {
        sort(characters.begin(), characters.end(),
            [](const Character& a, const Character& b) {
                return a.level > b.level;
            });
    }
};

int main() {
    CharacterManager manager;

    manager.addCharacter(Character("Knight", 150, 25));
    manager.addCharacter(Character("Mage", 90, 40));
    manager.addCharacter(Character("Rogue", 110, 32));

    if (Character* knight = manager.findCharacter("Knight")) {
        knight->gainExperience(250);
    }

    if (Character* mage = manager.findCharacter("Mage")) {
        mage->gainExperience(450);
    }

    manager.sortByLevel();
    manager.showAll();

    return 0;
}