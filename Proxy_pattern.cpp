/* Proxy is a structure design pattern, that lets you provide a substitude or placeholder for another object.
A proxy control access to the original object, allow you to perform something either before or after the
request gets through to the original object 
Pros: can be used at cache, allow to do some access control.
Cons: the proxy object should be used to perfom all the required operations on the resource it represents.
The benefit of the proxy pattern are useless if clients can bypass the surrogate and use the underlying 
types directly.
Useful link: http://www.vincehuston.org/dp/proxy.html 
*/

#include <iostream>
#include <memory>

using namespace std;

class Payment
{
    public:
         virtual void Pay(const unsigned amount) = 0;
};

//Real object
class FundAccount : public Payment
{
    public:
        FundAccount(const unsigned int balance)
        :m_balance(balance) {}
        FundAccount() = default;
        ~FundAccount() = default;
        
        void Pay(const unsigned int amount) override
        {
            if(m_balance > amount)
                m_balance = m_balance - amount;
            std::cout << "Payment is completed, your account balance is: " << m_balance << std::endl;
        }
        
    private:
        unsigned int m_balance;
};

//Proxy object
class ProxyCheck : public Payment
{
    public:
        ProxyCheck(const unsigned int balance)
        :m_balance(balance){};
        ProxyCheck() = default;
        ~ProxyCheck() = default;
        
        void Pay(const unsigned int amount) override
        {
            /*This is called lazy initialization, ProxyCheck is created but Real onject only created
            when Pay method is invoked */
            if(!m_realAccount)
                m_realAccount = std::make_shared<FundAccount>(m_balance);
            
            if(m_balance > amount)
                m_realAccount->Pay(amount);
            else    
                std::cout << "Unable to pay, pls topup your account" << std::endl;
        }
        
    private:
        unsigned int m_balance;
        std::shared_ptr<FundAccount> m_realAccount;
};

int main()
{
    
    ProxyCheck paycheck(1000);
    paycheck.Pay(50000);
    paycheck.Pay(500);
    
    return 0;
}

