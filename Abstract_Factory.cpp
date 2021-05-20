#include <iostream>

using namespace std;

class AbstractEnemyFactory {
 public:
  virtual Soldier* MakeSoldier() = 0;
  virtual Monster* MakeMonter() = 0;
  virtual SuperMonster* MakeSuperMonster() = 0;
};

class EasyLevelEnemyFactory : public AbstractEnemyFactory {
 public:
  Soldier* MakeSoldier() { return new SillySoldier(); }
  Monster* MakeMonter() { return new Monster(); }
  SuperMonster* MakeSuperMonster() { return new SuperMonster(); }
};

class DieHardLevelEnemyFactory : public AbstractEnemyFactory {
 public:
  Soldier* MakeSoldier() { return new FurrySoldier(); }
  Monster* MakeMonter() { return new FurryMonter(); }
  SuperMonster* MakeSuperMonster() { return new FurrySuperMonster(); }
};
int main() { return 0; }
