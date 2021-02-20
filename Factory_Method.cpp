#include <iostream>
#include <memory>
#include <utility>

using namespace std;

enum class Investment_Type { stock, bond, real_estate };

/*
        Base Class
*/
class IFInvestment {
 public:
  IFInvestment() {}
  virtual ~IFInvestment() {}

  virtual void Buy(const int &price) = 0;
  virtual void Sell(const int &price) = 0;

 protected:
  int m_price;
  string m_sticker;
};

/*
        Stock
*/

class Stock : public IFInvestment {
 public:
  Stock(const std::string &sticker) {
    m_sticker = sticker;
    m_price = 0;
  }

  virtual ~Stock() {}

  void Buy(const int &price) {
    m_price = price;
    std::cout << "buying " << m_sticker << " with price: " << m_price
              << std::endl;
  }

  void Sell(const int &price) {
    m_price = price;
    std::cout << "selling " << m_sticker << " with price: " << m_price
              << std::endl;
  }
};

/*
        Bond
*/

class Bond : public IFInvestment {
 public:
  Bond(const std::string &sticker) {
    m_sticker = sticker;
    m_price = 0;
  }
  virtual ~Bond() {}

  void Buy(const int &price) {
    std::cout << "buying " << m_sticker << " with price: " << price
              << std::endl;
    m_price = price;
  }

  void Sell(const int &price) {
    std::cout << "selling " << m_sticker << " with price: " << price
              << std::endl;
    m_price = price;
  }
};

/*
        RealEstate
*/
class RealEstate : public IFInvestment {
 public:
  RealEstate(std::string sticker) {
    m_sticker = sticker;
    m_price = 0;
  }
  virtual ~RealEstate() {}

  void Buy(const int &price) {
    std::cout << "buying " << m_sticker << " with price: " << price
              << std::endl;
    m_price = price;
  }

  void Sell(const int &price) {
    std::cout << "selling " << m_sticker << " with price: " << price
              << std::endl;
    m_price = price;
  }
};

class TradingFactory {
 public:
  static std::unique_ptr<IFInvestment> MakeInvestment(
      const Investment_Type &type, const std::string &sticker) {
    switch (type) {
      case Investment_Type::stock:
        return std::make_unique<Stock>(sticker);

      case Investment_Type::bond:
        return std::make_unique<Bond>(sticker);

      default:
        return std::make_unique<RealEstate>(sticker);
    }
  }
};

int main() {
  std::unique_ptr<IFInvestment> ptr =
      TradingFactory::MakeInvestment(Investment_Type::stock, "AAPL");
  ptr->Buy(200);

  return 0;
}
