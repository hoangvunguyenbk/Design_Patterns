/*Ensure 1 and only 1 instance of a class exist at any point in time
Pros: Useful when exactly one object need to coodinate actions across the system
Cons: Problem with tesability` - Have to deal with real data, and when these data changed,
      Unit test will start failling as unit test not updated yet and this going to be continous 
      problem.
      To Avoid: Supply an alternative to the singleton implementation with some dummy data.
               -> Make an interface and make singleton implemented that inteface
reference: http://www.vishalchovatiya.com/singleton-design-pattern-in-modern-cpp/                
*/

#include <iostream>


//Interface class
class DataBase {
    public:
       virtual void CommondFunction() = 0;
};
class SingletonDataBase : public DataBase {
    public:
        SingletonDataBase(SingletonDataBase const &) = delete; 
        SingletonDataBase& operator = (SingletonDataBase const &) = delete
        
        static SingletonDataBase* Instance() {
            if(m_instance == nullptr) {
                std::cout << "Creating database object...\n"
                m_instance = new SingletonDataBase();
            }
            std::cout << "database object is existing\n";
            return m_instance;
        }
        
        void CommondFunction() {}
    private:
        static SingletonDataBase* m_instance;
        SingletonDataBase() = default;
};
SingletonDataBase* SingletonDataBase::m_instance = nullptr;

class DummyDataBase : public DataBase {
    public:
        DummyDataBase() = default;
        void CommondFunction() {};
};

int main() {
    
    SingletonDataBase* db = SingletonDataBase::Instance();
    return 0;
}