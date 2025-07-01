#ifndef __DESIGN_PATTERN_ADAPTER_H__
#define __DESIGN_PATTERN_ADAPTER_H__

namespace cpp17Play {

template <typename InputT, typename OutputT>
class Adapter {
 protected:
  Adapter() = default;

 public:
  virtual ~Adapter() = default;

  Adapter(Adapter&) = delete;
  Adapter& operator=(Adapter&) = delete;
  Adapter(Adapter&&) = delete;
  Adapter& operator=(Adapter&&) = delete;

  [[nodiscard]] virtual OutputT adapt(InputT& input) const = 0;
};

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_ADAPTER_H__ */