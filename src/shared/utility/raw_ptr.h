/*
** Created by Christian Howard on 10/12/22.
*/
#ifndef TENTPITCH_SDG_SRC_SHARED_UTILITY_RAW_PTR_H_
#define TENTPITCH_SDG_SRC_SHARED_UTILITY_RAW_PTR_H_

namespace tp_sdg::shared::util {

template<typename T>
class raw_ptr {
 public:
  raw_ptr(T *ptr = nullptr) : internal_ptr_(ptr) {}
  raw_ptr(raw_ptr &r_ptr) {
    internal_ptr_ = r_ptr.internal_ptr_;
  }
  ~raw_ptr() = default;
  raw_ptr &operator=(T *ptr) {
    internal_ptr_ = ptr;
    return *this;
  }
  raw_ptr &operator=(const raw_ptr &r_ptr) {
    internal_ptr_ = r_ptr.internal_ptr_;
    return *this;
  }

  bool IsNull() const { return internal_ptr_ == nullptr; }
  bool IsNotNull() const { return !IsNull(); }

 private:
  T *internal_ptr_;
};

int dummy_func(int a);

} // end namespace

#endif //TENTPITCH_SDG_SRC_SHARED_UTILITY_RAW_PTR_H_
