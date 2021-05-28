#ifndef SERVER_BASE_H_INCLUDED
#define SERVER_BASE_H_INCLUDED

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iostream>
#include <lua.hpp>

#define HW_TRACE BOOST_LOG_SEV(lg, boost::log::trivial::trace)
#define HW_DEBUG BOOST_LOG_SEV(lg, boost::log::trivial::debug)
#define HW_INFO BOOST_LOG_SEV(lg, boost::log::trivial::info)
#define HW_WARN BOOST_LOG_SEV(lg, boost::log::trivial::warning)
#define HW_ERROR BOOST_LOG_SEV(lg, boost::log::trivial::error)
#define HW_FATAL BOOST_LOG_SEV(lg, boost::log::trivial::fatal)

namespace Server {
class server_base {
  public:
    server_base();
    virtual ~server_base();

  private:
    lua_State *                                                               L;
    boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;
    bool                                                                      init_config();
    bool                                                                      init_log();
    bool                                                                      init_lua();
    bool                                                                      init_socket();
};
} // namespace Server

#endif // SERVER_BASE_H_INCLUDED
