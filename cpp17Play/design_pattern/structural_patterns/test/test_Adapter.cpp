#include <gtest/gtest.h>

#include "../Adapter.hpp"

using namespace cpp17Play;

class Circle {
  double _radius;

 public:
  explicit Circle(double radius) : _radius(radius) {}

  double radius() const { return _radius; }
};

class Square {
  double _side;

 public:
  explicit Square(double side) : _side(side) {}

  double side() const { return _side; }
};

class CircleSquareAdapter : public Adapter<Circle, Square> {
 public:
  Square adapt(Circle& circle) const { return Square(2 * circle.radius()); }
};

TEST(AdapterTest, WHEN_Adapting_THEN_SuccessfullyAdapts) {
  Circle circle(1.0);

  CircleSquareAdapter adapter;
  auto square = adapter.adapt(circle);

  EXPECT_EQ(square.side(), 2.0);
}