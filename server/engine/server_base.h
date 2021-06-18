#ifndef SERVER_BASE_H_INCLUDED
#define SERVER_BASE_H_INCLUDED

#include <boost/core/null_deleter.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <lua.hpp>

namespace logging  = boost::log;
namespace sinks    = boost::log::sinks;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace attrs    = boost::log::attributes;
namespace keywords = boost::log::keywords;

#define HW_LOG(severity) BOOST_LOG_SEV(lg, boost::log::trivial::severity) << "[" << __FILE__ << ":" << __LINE__ << "]"
#define LOG_TRACE HW_LOG(trace)
#define LOG_DEBUG HW_LOG(debug)
#define LOG_INFO HW_LOG(info)
#define LOG_WARN HW_LOG(warning)
#define LOG_ERROR HW_LOG(error)
#define LOG_FATAL HW_LOG(fatal)

namespace server {
class server_base {
  public:
    server_base();
    virtual ~server_base();

  private:
    lua_State *L;
    src::severity_logger<logging::trivial::severity_level> lg;
    bool init();
    bool init_config();
    void init_log();
    bool init_lua();
    bool init_network();
};

} // namespace server

#endif // SERVER_BASE_H_INCLUDED
