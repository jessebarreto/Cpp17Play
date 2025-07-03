#ifndef __DESIGN_PATTERN_CHAINOFRESPONSIBILITY_H__
#define __DESIGN_PATTERN_CHAINOFRESPONSIBILITY_H__

#include <functional>

namespace cpp17Play {

template <typename RequestT>
class AbstractHandler {
 protected:
  AbstractHandler() noexcept = default;

 public:
  AbstractHandler(AbstractHandler& other) = delete;
  AbstractHandler(AbstractHandler&& other) noexcept = default;
  AbstractHandler& operator=(AbstractHandler& other) = delete;
  AbstractHandler& operator=(AbstractHandler&& other) = default;
  virtual ~AbstractHandler() = default;

  virtual void setNext(AbstractHandler& handler) = 0;
  virtual void handle(RequestT& request) = 0;
};

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_CHAINOFRESPONSIBILITY_H__ */