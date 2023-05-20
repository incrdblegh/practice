#include <iostream>
#include <memory>

class Car final {
  public:
    void setMake(const std::string_view make) { m_make = make; }
    void setModel(const std::string_view model) { m_model = model; }
    void setColor(const std::string_view color) { m_color = color; }
    void setYear(const int year) { m_year = year; }
    void printSpecs() const {
        std::cout << "Make: " << m_make << "\nModel: " << m_model << "\nColor: " << m_color
                  << "\nYear: " << m_year << "\n\n";
    }

  private:
    std::string m_make{};
    std::string m_model{};
    std::string m_color{};
    int m_year{};
};

class CarBuilder {
  public:
    virtual CarBuilder& newCar() {
        m_car = std::make_unique<Car>();
        return *this;
    }
    virtual std::unique_ptr<Car> getCar() { return std::move(m_car); }
    virtual CarBuilder& buildMake() = 0;
    virtual CarBuilder& buildModel() = 0;
    virtual CarBuilder& buildColor() = 0;
    virtual CarBuilder& buildYear() = 0;

  protected:
    std::unique_ptr<Car> m_car{};
};

class PorscheCarBuilder : public CarBuilder {
  public:
    // return a reference to the object to allow for create a fluent interface (call chaining). make use of
    // covariant return types, i.e. a base builder type can be replaced with a derived builder type
    PorscheCarBuilder& buildMake() override {
        m_car->setMake("Porsche");
        return *this;
    }
    PorscheCarBuilder& buildModel() override {
        m_car->setModel("Taycan");
        return *this;
    }
    PorscheCarBuilder& buildColor() override {
        m_car->setColor("White");
        return *this;
    }
    PorscheCarBuilder& buildYear() override {
        m_car->setYear(2023);
        return *this;
    }
};

class HondaCarBuilder : public CarBuilder {
  public:
    HondaCarBuilder& buildMake() override {
        m_car->setMake("Honda");
        return *this;
    }
    HondaCarBuilder& buildModel() override {
        m_car->setModel("Civic Type R");
        return *this;
    }
    HondaCarBuilder& buildColor() override {
        m_car->setColor("Gray");
        return *this;
    }
    HondaCarBuilder& buildYear() override {
        m_car->setYear(2022);
        return *this;
    }
};

class CarBuilderDirector final {
  public:
    void setBuilder(std::shared_ptr<CarBuilder> builder) { m_builder = builder; }
    void buildCar() { m_builder->newCar().buildMake().buildModel().buildColor().buildYear(); }

  private:
    std::shared_ptr<CarBuilder> m_builder;
};

void client(std::shared_ptr<CarBuilder> builder) {
    CarBuilderDirector director;
    director.setBuilder(builder);
    director.buildCar();
    auto car = builder->getCar();
    car->printSpecs();
}

int main() {
    auto builder1 = std::make_shared<PorscheCarBuilder>();
    auto builder2 = std::make_shared<HondaCarBuilder>();
    client(builder1);
    client(builder2);
}
