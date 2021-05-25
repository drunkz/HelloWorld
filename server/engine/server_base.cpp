#include "server_base.h"

namespace Server {
server_base::server_base() {
    boost::log::add_file_log(boost::log::keywords::file_name = "/home/dkz/ttt/aaa/sample_%N.log",
                             boost::log::keywords::open_mode =
                                 std::ios_base::out | std::ios_base::app,
                             boost::log::keywords::rotation_size = 10 << 20,
                             boost::log::keywords::format        = "[%TimeStamp%]: %Message%");
    boost::log::add_console_log();
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    boost::log::add_common_attributes();
    using namespace boost::log::trivial;
    boost::log::sources::severity_logger<severity_level> lg;
    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
    L = luaL_newstate();
    if (L == nullptr) {
    } else {
        luaL_openlibs(L);
        luaL_dostring(L, "print('hello,world')");
    }
}
server_base::~server_base() {
    lua_close(L);
    L = nullptr;
}
} // namespace Server
