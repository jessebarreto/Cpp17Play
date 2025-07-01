#ifndef __DESIGN_PATTERN_BUILDER_H__
#define __DESIGN_PATTERN_BUILDER_H__

namespace cpp17Play {

class AbstractBuilder {
 protected:
  AbstractBuilder() noexcept = default;

 public:
  AbstractBuilder(AbstractBuilder&) = delete;
  AbstractBuilder& operator=(AbstractBuilder&) = delete;
  AbstractBuilder(AbstractBuilder&&) = delete;
  AbstractBuilder& operator=(AbstractBuilder&&) = delete;
  virtual ~AbstractBuilder() = default;

  virtual void reset() = 0;
};

class AbstractDirector {
 protected:
  AbstractDirector() noexcept = default;

 public:
  AbstractDirector(AbstractDirector&) = delete;
  AbstractDirector& operator=(AbstractDirector&) = delete;
  AbstractDirector(AbstractDirector&&) = delete;
  AbstractDirector& operator=(AbstractDirector&&) = delete;
  virtual ~AbstractDirector() = default;
};

}  // namespace cpp17Play

#endif /* __DESIGN_PATTERN_BUILDER_H__ */