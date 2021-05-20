/* The command pattern encapsulates a request as an object, thereby letting you
parameterize other objects with different requests, queue or log requests, and
support undoable operations. Pros:
        - Decouple the classes that invoke the operation from the object that
knows how to execute the operation.
        - Allow to create a sequence commands by providing a queue system.
        - Add new command is easy  and can be done without changing existing
code.
        - Can design a rollback system.
Cons:
        - Each command will be separated into 1 class.
        - High number of classes and object working together. */

#include <iostream>

using namespace std;
enum class eLIGHT_STATE { ON, OFF };

// Base Command class
class Command {
 public:
  virtual void execute() const {}
  virtual void undo() const {}
};

// Receiver base class
class Device {
 public:
  virtual string GetDeviceName() const = 0;
  virtual void SetDeviceName(string) = 0;
  virtual void TurnOn() = 0;
  virtual void TurnOff() = 0;
};

class Light : public Device {
 public:
  Light(string name, eLIGHT_STATE state) : m_name(name), m_state(state) {}

  virtual ~Light() = default;

  void TurnOn() {
    if (m_state != eLIGHT_STATE::ON) {
      m_state = eLIGHT_STATE::ON;
      cout << "Light is On\n";
    }
  }

  void TurnOff() {
    if (m_state != eLIGHT_STATE::OFF) {
      m_state = eLIGHT_STATE::OFF;
      cout << "Light is Off\n";
    }
  }

  string GetDeviceName() const { return m_name; }

  void SetDeviceName(string name) { m_name = name; }

 private:
  string m_name;
  eLIGHT_STATE m_state;
};

class CeilingFan : public Device {
 public:
  CeilingFan(string name, eLIGHT_STATE state) : m_name(name), m_state(state) {}
  virtual ~CeilingFan() = default;

  void TurnOn() {
    if (m_state != eLIGHT_STATE::ON) {
      m_state = eLIGHT_STATE::ON;
      cout << "CeilingFan is On\n";
    }
  }

  void TurnOff() {
    if (m_state != eLIGHT_STATE::OFF) {
      m_state = eLIGHT_STATE::OFF;
      cout << "CeilingFan is Off\n";
    }
  }

  string GetDeviceName() const { return m_name; }

  void SetDeviceName(string name) { m_name = name; }

 private:
  string m_name;
  eLIGHT_STATE m_state;
};

// Concrete Command classes
class LightOnCommand : public Command {
 public:
  LightOnCommand(Light* light) : m_light(light) {}

  ~LightOnCommand() {
    delete m_light;
    m_light = nullptr;
  }

  LightOnCommand(const LightOnCommand& obj) { this->m_light = obj.m_light; }

  LightOnCommand& operator=(const LightOnCommand& obj) {
    this->m_light = obj.m_light;
    return *this;
  }

  void execute() const override { m_light->TurnOn(); }

  void undo() const override { m_light->TurnOff(); }

 private:
  Light* m_light;
};

class LightOffCommand : public Command {
 public:
  LightOffCommand(Light* light) : m_light(light) {}

  LightOffCommand(const LightOffCommand& obj) { this->m_light = obj.m_light; }

  LightOffCommand& operator=(const LightOffCommand& obj) {
    this->m_light = obj.m_light;
    return *this;
  }

  ~LightOffCommand() {
    delete m_light;
    m_light = nullptr;
  }

  void execute() const override { m_light->TurnOff(); }

  void undo() const override { m_light->TurnOn(); }

 private:
  Light* m_light;
};

class CeilingFanOnCommand : public Command {
 public:
  CeilingFanOnCommand(CeilingFan* fan) : m_ceiling(fan) {}

  ~CeilingFanOnCommand() {
    delete m_ceiling;
    m_ceiling = nullptr;
  }

  CeilingFanOnCommand(const CeilingFanOnCommand& obj) {
    this->m_ceiling = obj.m_ceiling;
  }

  CeilingFanOnCommand& operator=(const CeilingFanOnCommand& obj) {
    this->m_ceiling = obj.m_ceiling;
    return *this;
  }

  void execute() const override { m_ceiling->TurnOn(); }

  void undo() const override { m_ceiling->TurnOff(); }

 private:
  CeilingFan* m_ceiling;
};

class CeilingFanOffCommand : public Command {
 public:
  CeilingFanOffCommand(CeilingFan* fan) : m_ceiling(fan) {}

  ~CeilingFanOffCommand() {
    delete m_ceiling;
    m_ceiling = nullptr;
  }

  CeilingFanOffCommand(const CeilingFanOffCommand& obj) {
    this->m_ceiling = obj.m_ceiling;
  }

  CeilingFanOffCommand& operator=(const CeilingFanOffCommand& obj) {
    this->m_ceiling = obj.m_ceiling;
    return *this;
  }

  void execute() const override { m_ceiling->TurnOff(); }

  void undo() const override { m_ceiling->TurnOn(); }

 private:
  CeilingFan* m_ceiling;
};

// Invoker class
class SimpleRemoteControl {
 public:
  SimpleRemoteControl() {
    onCommand = new Command*[2];
    offCommand = new Command*[2];
    undoCommand = nullptr;
  }

  virtual ~SimpleRemoteControl() {
    delete[] onCommand;
    delete[] offCommand;
  }

  void SetCommand(int slot, Command* on_cmd, Command* off_cmd) {
    onCommand[slot] = on_cmd;
    offCommand[slot] = off_cmd;
  }

  void onButtonPressed(int slot) {
    onCommand[slot]->execute();
    undoCommand = onCommand[slot];
  }

  void offButtonPressed(int slot) {
    offCommand[slot]->execute();
    undoCommand = offCommand[slot];
  }

  void undoButtonPressed() const { undoCommand->undo(); }

 private:
  Command** onCommand;
  Command** offCommand;
  Command* undoCommand;
};

// Act as client role
int main() {
  SimpleRemoteControl* remote = new SimpleRemoteControl();
  Device* light = new Light("Kitchen Light", eLIGHT_STATE::OFF);
  Device* fan = new CeilingFan("Ceiling Fan", eLIGHT_STATE::OFF);
  Command* light_on_cmd = new LightOnCommand(dynamic_cast<Light*>(light));
  Command* light_off_cmd = new LightOffCommand(dynamic_cast<Light*>(light));
  Command* fan_on_cmd = new CeilingFanOnCommand(dynamic_cast<CeilingFan*>(fan));
  Command* fan_off_cmd = new CeilingFanOffCommand(dynamic_cast<CeilingFan*>(fan));

  remote->SetCommand(0, dynamic_cast<Command*>(light_on_cmd),
                     dynamic_cast<Command*>(light_off_cmd));
  remote->SetCommand(1, dynamic_cast<Command*>(fan_on_cmd),
                     dynamic_cast<Command*>(fan_off_cmd));

  remote->onButtonPressed(0);  // light on
  remote->onButtonPressed(1);  // fan on

  remote->offButtonPressed(0);  // light off
  remote->undoButtonPressed();  // light on

  return 0;
}
