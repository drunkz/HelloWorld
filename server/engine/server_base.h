#ifndef SERVER_BASE_H_INCLUDED
#define SERVER_BASE_H_INCLUDED

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <lua.hpp>

namespace logging = boost::log;
namespace sinks   = boost::log::sinks;
namespace src     = boost::log::sources;
// namespace expr = boost::log::expressions;
// namespace attrs = boost::log::attributes;
// namespace keywords = boost::log::keywords;

#define HW_TRACE BOOST_LOG_SEV(lg, logging::trivial::trace)
#define HW_DEBUG BOOST_LOG_SEV(lg, logging::trivial::debug)
#define HW_INFO BOOST_LOG_SEV(lg, logging::trivial::info)
#define HW_WARN BOOST_LOG_SEV(lg, logging::trivial::warning)
#define HW_ERROR BOOST_LOG_SEV(lg, logging::trivial::error)
#define HW_FATAL BOOST_LOG_SEV(lg, logging::trivial::fatal)

namespace Server {
class server_base {
  public:
    server_base();
    virtual ~server_base();

  private:
    lua_State *L;
    // logging::sources::severity_logger<logging::trivial::severity_level> lg;
    bool init_config();
    bool init_log();
    bool init_lua();
    bool init_socket();
};
} // namespace Server

#endif // SERVER_BASE_H_INCLUDED
