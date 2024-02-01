/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_SHARED_UTILITY_RAW_PTR_H_
#define TENTPITCH_SDG_SRC_SHARED_UTILITY_RAW_PTR_H_

#include <cstddef>

namespace tp_sdg::shared::util {

template<typename T>
class RawPtr {
 public:
  RawPtr(): internal_ptr_(nullptr){}
  explicit RawPtr(T *ptr) : internal_ptr_(ptr) {}
  RawPtr(RawPtr &r_ptr) {
    internal_ptr_ = r_ptr.internal_ptr_;
  }
  RawPtr(const RawPtr<T>& raw_ptr):internal_ptr_(raw_ptr.internal_ptr_) {

  }
  ~RawPtr() = default;
  RawPtr &operator=(T *ptr) {
    internal_ptr_ = ptr;
    return *this;
  }
  RawPtr &operator=(const RawPtr &r_ptr) {
    if(this != &r_ptr)
      internal_ptr_ = r_ptr.internal_ptr_;
    return *this;
  }
  RawPtr &operator=(RawPtr &&r_ptr) noexcept {
    internal_ptr_ = r_ptr.internal_ptr_;
    return *this;
  }
  bool operator==(const RawPtr &r) const { return (internal_ptr_ == r.internal_ptr_); }
  bool operator!=(const RawPtr &r) const { return (internal_ptr_ != r.internal_ptr_); }
  bool operator!=(std::nullptr_t) const { return (internal_ptr_ != nullptr); }
  bool operator==(std::nullptr_t) const { return (internal_ptr_ == nullptr); }
  T *operator->() {
    return internal_ptr_;
  }
  const T *operator->() const {
    return internal_ptr_;
  }
  T &operator*() {
    return *internal_ptr_;
  }
  const T &operator*() const {
    return *internal_ptr_;
  }
  operator T *() { return internal_ptr_; }
  operator T *() const { return internal_ptr_; }

  bool IsNull() const { return internal_ptr_ == nullptr; }
  bool IsNotNull() const { return !IsNull(); }

 private:
  T *internal_ptr_;
};

} // end namespace

#endif //TENTPITCH_SDG_SRC_SHARED_UTILITY_RAW_PTR_H_
