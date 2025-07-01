#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "../BuilderDirector.hpp"

using namespace cpp17Play;

class Car {
  std::string _carType;

 public:
  Car() noexcept = default;

  void setCarType(const std::string& carType) { _carType = carType; }

  std::string carType() { return _carType; }
};

class Manual {
  std::string _manualContent;

 public:
  Manual() = default;

  void setContent(const std::string& content) { _manualContent = content; }

  std::string manualContent() { return _manualContent; }
};

class BaseBuilder : public AbstractBuilder {
 protected:
  BaseBuilder() = default;

 public:
  virtual void makeSUV() = 0;

  virtual void makeHatch() = 0;
};

class CarBuilder : public BaseBuilder {
  std::unique_ptr<Car> _car{nullptr};

 public:
  CarBuilder() = default;

  void reset() override { _car = nullptr; }

  void makeSUV() override {
    if (!_car) {
      _car = std::make_unique<Car>();
    }
    _car->setCarType("SUV");
  }

  void makeHatch() override {
    if (!_car) {
      _car = std::make_unique<Car>();
    }
    _car->setCarType("Hatch");
  }

  Car getResult() { return *_car; }
};

class ManualBuilder : public BaseBuilder {
  std::unique_ptr<Manual> _manual{nullptr};

 public:
  ManualBuilder() noexcept = default;

  void reset() override { _manual = nullptr; }

  void makeSUV() override {
    if (!_manual) {
      _manual = std::make_unique<Manual>();
    }
    _manual->setContent("SUV Manual Content");
  }

  void makeHatch() override {
    if (!_manual) {
      _manual = std::make_unique<Manual>();
    }
    _manual->setContent("Hatch Manual Content");
  }

  Manual getResult() { return *_manual; }
};

class CarDirector : public AbstractDirector {
  std::unique_ptr<BaseBuilder> _builder;

 public:
  explicit CarDirector(std::unique_ptr<BaseBuilder> builder)
      : _builder(std::move(builder)) {}

  void buildSUV() {
    _builder->reset();
    _builder->makeSUV();
  }

  void buildHatch() {
    _builder->reset();
    _builder->makeHatch();
  }

  std::unique_ptr<BaseBuilder> getBuilder() { return std::move(_builder); }
};

TEST(BuilderDirectorTest,
     Given_BuildDirector_When_CreatingCar_Then_CreatesCar) {
  auto director = CarDirector(std::make_unique<CarBuilder>());
  director.buildSUV();

  auto builder = director.getBuilder();

  auto* carBuilder = dynamic_cast<CarBuilder*>(builder.get());
  ASSERT_TRUE(carBuilder != nullptr);
  EXPECT_EQ(carBuilder->getResult().carType(), "SUV");
}

TEST(BuilderDirectorTest,
     Given_BuildDirector_When_CreatingCar_Then_CreatesManual) {
  auto director = CarDirector(std::make_unique<ManualBuilder>());
  director.buildHatch();

  auto builder = director.getBuilder();

  auto* manualBuilder = dynamic_cast<ManualBuilder*>(builder.get());
  ASSERT_TRUE(manualBuilder != nullptr);
  EXPECT_EQ(manualBuilder->getResult().manualContent(), "Hatch Manual Content");
}