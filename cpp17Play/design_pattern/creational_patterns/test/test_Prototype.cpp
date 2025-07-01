#include <utility>

#include <gtest/gtest.h>

#include "../Prototype.hpp"

using namespace cpp17Play;

class Shape : public Prototype {
    double _x;
    double _y;

protected:
    Shape(double x, double y) : _x{x}, _y{y} {}

public:
    virtual ~Shape() = default;

    std::pair<double, double> position() const {
        return std::make_pair(_x, _y);
    }
};

class Rectangle : public Shape {
    double _width;
    double _height;

public:
    Rectangle(double width, double height) : Shape(0.0, 0.0), _width{width}, _height{height} {}

    [[nodiscard]]
    Prototype& clone() const override {
        return *(new Rectangle(_width, _height));
    }
};

class Circle : public Shape {
    double _radius;

public:
    Circle(double radius) : Shape(0.0, 0.0), _radius(radius) {}

    Prototype& clone() const override {
        return *(new Circle(_radius));
    }
};

TEST(PrototypeTest, GIVEN_DerivedInstanceOfPrototype_When_CloningPrototype_Then_SuccessfullyClone) {
    Circle circle(3.14);

    auto& shape = circle.clone();

    auto* newCircle = dynamic_cast<Circle*>(&shape);
    ASSERT_TRUE(newCircle);
    EXPECT_NE(newCircle, &circle);
}