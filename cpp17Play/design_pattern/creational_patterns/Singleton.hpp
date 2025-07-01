#ifndef __DESIGN_PATTERN_SINGLETON_H__
#define __DESIGN_PATTERN_SINGLETON_H__

#include <memory>
#include <mutex>

namespace cpp17Play {

template <typename T>
class Singleton {
  static std::mutex _mutex;

 protected:
  Singleton() noexcept = default;

 public:
  Singleton(Singleton&) = delete;
  Singleton& operator=(Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;
  ~Singleton() = default;

  template <typename... Args>
  static T& instance(Args&&... args) {
    static std::unique_ptr<T> _instance = nullptr;
    std::lock_guard<std::mutex> lock(_mutex);
    if (!_instance) {
      _instance = std::make_unique<T>(std::forward<Args>(args)...);
    }

    return *_instance;
  }
};

template <typename T>
std::mutex Singleton<T>::_mutex;

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_SINGLETON_H__ */