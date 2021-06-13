/* Provide an interface for creating families of related or dependent objects without specifying their concrete classes*
The main disavantage of Abstract Factory is the type intensive: The abstract factory base class must know
about every abstract product that to be created. 
Pros: Can create the objects without knowing its type. Client no need to deal with new operator
      Decouple the creation part from the usage of the client.
      
Cons: The abstract factory class need to know about every abstract product type that created.
      Support new kinds of product is difficult, which involves changing the AbstractFactory class and 
      all it subclasses.
      Avoid this: TODO?
*/

#include <iostream>

using namespace std;

enum class Level {
    EASY,
    HARD
};
// Abstract product classes
class Soldier {};

class Monster {};

class SuperMonster {};

// Concrete product classes

class SillySoldier : public Soldier {
};

class SillyMonster : public Monster {
};

class SillySuperMonster : public SuperMonster {
};

class FurrySoldier : public Soldier {
};

class FurryMonster : public Monster {
};

class FurrySuperMonster : public SuperMonster {
};

// Abstract factory base class
class AbstractEnemyFactory {
    public:
        virtual Soldier* MakeSoldier() const = 0;
        virtual Monster* MakeMonster() const = 0;
        virtual SuperMonster* MakeSuperMonster() const = 0;
};

// Concrete Factory classes
class EasyLevelEnemyFactory : public AbstractEnemyFactory {
    public:
        Soldier* MakeSoldier() const override { 
            return new SillySoldier(); 
        }
        Monster* MakeMonster() const override { 
            return new SillyMonster(); 
        }
        SuperMonster* MakeSuperMonster() const override { 
            return new SillySuperMonster(); 
        }
};

class DieHardLevelEnemyFactory : public AbstractEnemyFactory {
    public:
        Soldier* MakeSoldier() const override { 
            return new FurrySoldier(); 
        }
        Monster* MakeMonster() const override { 
            return new FurryMonster(); 
        }
        SuperMonster* MakeSuperMonster() const override { 
            return new FurrySuperMonster(); 
        }
};

class GameApp {
    public:
        void  SelectLevel(Level lev) {
            if(lev == Level::EASY) {
                pFactory = new EasyLevelEnemyFactory();
            }else {
                pFactory = new DieHardLevelEnemyFactory();
            }
        }
        
        void CreateEnemy() const {
            if(pFactory != nullptr) {
                pFactory->MakeSoldier();
                pFactory->MakeMonster();
                pFactory->MakeSuperMonster();
            }
        }
        
    private:
        AbstractEnemyFactory* pFactory;
};

int main() {

    GameApp app;
    app.SelectLevel(Level::EASY);
    app.CreateEnemy();

    return 0; 
}
