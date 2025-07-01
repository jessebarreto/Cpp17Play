#include <gtest/gtest.h>

#include "../AbstractFactory.hpp"

using namespace cpp17Play;

namespace {

class AbstractGeometry {
 protected:
  AbstractGeometry(){};

 public:
  virtual ~AbstractGeometry(){};
};

class AbstractShape : public AbstractGeometry {
 protected:
  AbstractShape(){};

 public:
  virtual float area() const = 0;

  virtual ~AbstractShape(){};
};

class Rectangle : public AbstractShape {
  float _width{0.0};
  float _height{0.0};

 public:
  Rectangle(float width = 0.0, float height = 0.0)
      : _width(width), _height(height) {}

  float area() const override { return _width * _height; }
};

class Circle : public AbstractShape {
  float _radius{0.0};
  static constexpr float _PI{3.14159};

 public:
  explicit Circle(float radius = 0.0) : _radius(radius) {}

  float area() const override { return _PI * _radius * _radius; }
};

class AbstractSolid : public AbstractGeometry {
 protected:
  AbstractSolid(){};

 public:
  virtual float volume() const = 0;

  virtual ~AbstractSolid(){};
};

class Cuboid : public AbstractSolid {
  Rectangle _base;
  float _height{0.0};

 public:
  Cuboid(const Rectangle& base, float height) : _base(base), _height(height) {}

  float volume() const override { return _base.area() * _height; }
};

class Sphere : public AbstractSolid {
  float _radius{0.0};
  static constexpr float _PI{3.14159};

 public:
  explicit Sphere(float radius) : _radius{radius} {}

  float volume() const override {
    return _radius * _radius * _radius * _PI * 4 / 3;
  }
};

enum ShapeEnum {
  CircleT,
  RectangleT,
};

class GeometryFactory : public AbstractFactory<AbstractGeometry, ShapeEnum> {
 public:
  std::unique_ptr<AbstractGeometry> create(ShapeEnum enumerate) const {
    if (enumerate == ShapeEnum::CircleT) {
      return std::make_unique<Sphere>(1.0);
    }
    return std::make_unique<Cuboid>(Rectangle(1.0, 1.0), 1.0);
  }
};

class ShapeFactory : public AbstractFactory<AbstractGeometry, ShapeEnum> {
 public:
  std::unique_ptr<AbstractGeometry> create(ShapeEnum enumerate) const {
    if (enumerate == ShapeEnum::CircleT) {
      return std::make_unique<Circle>(1.0);
    }
    return std::make_unique<Rectangle>(1.0, 1.0);
  }
};

TEST(
    AbstractFactoryTests,
    GIVEN_Inheriting_AbstractFactory_For_Shape_WHEN_Calling_Create_Method_THEN_Corretly_Apply_Factory) {
  std::unique_ptr<AbstractFactory<AbstractGeometry, ShapeEnum>> factory =
      nullptr;

  factory = std::make_unique<ShapeFactory>();
  auto shape = factory->create(ShapeEnum::CircleT);

  EXPECT_TRUE(dynamic_cast<Circle*>(shape.get()));
}

TEST(
    AbstractFactoryTests,
    GIVEN_Inheriting_AbstractFactory_For_Solid_WHEN_Calling_Create_Method_THEN_Corretly_Apply_Factory) {
  std::unique_ptr<AbstractFactory<AbstractGeometry, ShapeEnum>> factory =
      nullptr;

  factory = std::make_unique<GeometryFactory>();
  auto solid = factory->create(ShapeEnum::CircleT);

  EXPECT_TRUE(dynamic_cast<Sphere*>(solid.get()));
}

}  // namespace
