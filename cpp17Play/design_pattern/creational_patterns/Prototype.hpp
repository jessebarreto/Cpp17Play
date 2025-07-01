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

// class PrototypeRegitry {
//   std::unordered_map<std::string, Prototype> _prototypes;

//  public:
//   void registerPrototype(const std::string& prototypeName,
//                          const Prototype& prototype) {
//     _prototypes.emplace(prototypeName, prototype.clone());
//   }

//   const Prototype& getByName(const std::string& prototypeName) {
//     return _prototypes.at(prototypeName);
//   }
// }

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_PROTOTYPE_H__ */