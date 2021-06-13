/* State pattern : the behavioral design pattern that lets an object alter its behavior when its internal
state changes. It appears as if the object changed it class
Pros: get rid of alot if/else, switch/case, nested loops compare to naive implementation,
      easy to extend/reuse
Cons: big memory footprint -  use heap allocates states, created once, never destroy.
      write more code required
      perfomance a bit slow compare to table approach

Useful link: https://www.youtube.com/watch?v=yZVby-PuXM0 (Cppcon2018)
             http://www.vishalchovatiya.com/state-design-pattern-in-modern-cpp/
*/

#include <iostream>

using namespace std;

/*-----------Model beharvior approach GoF implemntation ------------------*/
class TCPOctetStream; //forward declaration
class TCPState; 

//Contex class
class TCPConnection {
    public:
        TCPConnection() {
            m_state = TCPClosed::Instance();
        }
        virtual ~TCPConnection() {
            delete m_state;
        }
        void ActiveOpen() {
            if(m_state != nullptr)
                m_state->ActiveOpen(this);
        }
        void PassiveOpen() {
            if(m_state != nullptr)
                m_state->PassiveOpen(this);
        }
        void Close() {
            if(m_state != nullptr)
                m_state->Close(this);
        }
        void Send() {
            if(m_state != nullptr)
                m_state->Send(this);
        }
        void Acknowledge() {
            if(m_state != nullptr)
                m_state->Acknowledge();
        }
        void Synchronize() {
            if(m_state != nullptr)
                m_state->Synchronize();            
        }
        void ProcessOctet(TCPOctetStream* ) {
            if(m_state != nullptr)
                m_state->ProcessOctet();            
        }
        
    private:
        friend class TCPState;
        void ChangeState(TCPState* );
        TCPState* m_state;
};

//Abstract State class
class TCPState {
    public:
        virtual void Transmit(TCPConnection*, TCPOctetStream* ) = 0;
        virtual void ActiveOpen(TCPConnection*) = 0;
        virtual void PassiveOpen(TCPConnection*) = 0;
        virtual void Close(TCPConnection*) = 0;
        virtual void Synchronize(TCPConnection*) = 0;
        virtual void Acknowledge(TCPConnection*) = 0;
        virtual void Send(TCPConnection*) = 0;
    protected:
        void ChangeState(TCPConnection*, TCPState*);
};

//Concrete State classes
class TCPEstablished : public TCPState {
    public:
        static TCPState* Instance(); // Each state is unique so make use of singleton pattern
        void Transmit(TCPConnection*, TCPOctetStream* ) override;
        void ActiveOpen(TCPConnection*)override;
        void PassiveOpen(TCPConnection*)override;
        void Close(TCPConnection*) override;
        void Synchronize(TCPConnection*) override;
        void Acknowledge(TCPConnection*) override;
        void Send(TCPConnection*) override;
        virtual ~TCPEstablished() = default;
        
    private:
        TCPEstablished() = default;
        static TCPState* m_instance;
};

class TCPListen : public TCPState {
    public:
        static TCPState* Instance(); // Each state is unique so make use of singleton pattern
        void Transmit(TCPConnection*, TCPOctetStream* ) override;
        void ActiveOpen(TCPConnection*)override;
        void PassiveOpen(TCPConnection*)override;
        void Close(TCPConnection*) override;
        void Synchronize(TCPConnection*) override;
        void Acknowledge(TCPConnection*) override;
        void Send(TCPConnection*) override;
        virtual ~TCPListen() = default;
        
    private:
        TCPListen() = default;
        static TCPState* m_instance;
};

class TCPClosed : public TCPState {
    public:
        static TCPState* Instance(); // Each state is unique so make use of singleton pattern
        void Transmit(TCPConnection*, TCPOctetStream* ) override;
        void ActiveOpen(TCPConnection*)override;
        void PassiveOpen(TCPConnection*)override;
        void Close(TCPConnection*) override;
        void Synchronize(TCPConnection*) override;
        void Acknowledge(TCPConnection*) override;
        void Send(TCPConnection*) override;
        virtual ~TCPClosed() = default;
        
    private:
        TCPClosed() = default;
        static TCPState* m_instance;
};

//Some more TCPStates...
/*--------------------------------------------------------------*/

int main() {
    
    TCPConnection* connection = new TCPConnection();
    TCPState* establised = TCPEstablished::Instance();
    TCPState* establised = TCPEstablished::Instance();
    TCPState* establised = TCPEstablished::Instance();
    
    connection->ActiveOpen();
    connection->Send();
    ...
    
    return 0;
}

