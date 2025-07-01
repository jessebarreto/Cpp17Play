#ifndef __DESIGN_PATTERN_PROTOTYPE_H__
#define __DESIGN_PATTERN_PROTOTYPE_H__

#include <string>
#include <unordered_map>

namespace cpp17Play {

class Prototype {
 protected:
  Prototype() = default;

 public:
  virtual ~Prototype() = default;

  Prototype(Prototype&) = delete;
  Prototype& operator=(Prototype&) = delete;
  Prototype(Prototype&&) = default;
  Prototype& operator=(Prototype&&) = default;

  [[nodiscard]] virtual Prototype& clone() const = 0;
};

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_PROTOTYPE_H__ */