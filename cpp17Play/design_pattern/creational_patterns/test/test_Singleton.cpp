#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "../Singleton.hpp"

using namespace cpp17Play;

namespace {

class Sphere {
  float _radius{0.0};
  static constexpr float _PI{3.14159};

 public:
  explicit Sphere(float radius = 1.0) : _radius{radius} {}

  void setRadius(float radius) { _radius = radius; }

  float volume() const { return _radius * _radius * _radius * _PI * 4 / 3; }

  float radius() const noexcept { return _radius; }
};

void threadFooA() {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
  auto& singleton = Singleton<Sphere>::instance();
  singleton.setRadius(3);
  EXPECT_FLOAT_EQ(singleton.radius(), 3.0);
}

void threadFooB() {
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  auto& singleton = Singleton<Sphere>::instance();
  singleton.setRadius(2);
  EXPECT_FLOAT_EQ(singleton.radius(), 2.0);
}

TEST(SingletonTests, Given__When__Then_) {
  auto single_sphere = Singleton<Sphere>::instance(2.5);
  // single_sphere.setRadius(2.5);
  // auto single_sphere = Singleton<Sphere>::instance();

  EXPECT_FLOAT_EQ(single_sphere.radius(), 2.5);
  // EXPECT_EQ(1, 0);
}

TEST(SingletonTests, Given_Threads_When__Then_) {
  std::thread threadA(threadFooA);
  std::thread threadB(threadFooB);

  threadA.join();
  threadB.join();
}

}  // namespace
