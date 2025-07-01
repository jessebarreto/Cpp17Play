#ifndef __DESIGN_PATTERN_ABSTRACTFACTORY_H__
#define __DESIGN_PATTERN_ABSTRACTFACTORY_H__

#include <memory>

namespace cpp17Play {

template <typename Type, typename EnumType>
class AbstractFactory {
 protected:
  AbstractFactory() noexcept = default;  //!

 public:
  AbstractFactory(AbstractFactory& other) = delete;
  AbstractFactory(AbstractFactory&& other) noexcept = delete;
  AbstractFactory& operator=(AbstractFactory& other) = delete;
  AbstractFactory& operator=(AbstractFactory&& other) = delete;
  virtual ~AbstractFactory() = default;

  virtual std::unique_ptr<Type> create(EnumType enumerate) const = 0;
};

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_ABSTRACTFACTORY_H__ */