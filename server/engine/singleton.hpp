#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

namespace server {

template <typename T> class singleton {
  public:
    static T &Get() noexcept(std::is_nothrow_constructible<T>::value) {
        static T instance;
        return instance;
    }

  protected:
    singleton() noexcept         = default;
    virtual ~singleton()         = default;
    singleton(const singleton &) = delete;
    singleton &operator=(const singleton &) = delete;
};

} // namespace server

#endif // SINGLETON_HPP_INCLUDED