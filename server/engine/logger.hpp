#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include "singleton.hpp"
namespace server {
class logger : public singleton<logger> {
    friend class singleton<logger>;

  public:
  private:
    logger() noexcept = default;
    virtual ~logger() = default;
};
} // namespace server

#endif // LOGGER_HPP_INCLUDED