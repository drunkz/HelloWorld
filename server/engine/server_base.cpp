#include "server_base.h"
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <fstream>
namespace Server {
server_base::server_base() {
    boost::log::add_file_log(boost::log::keywords::file_name =
                                 "/home/dkz/ttt/aaa/sample_%Y-%m-%d_%H-%M-%S.txt",
                             boost::log::keywords::rotation_size = 10 << 20,
                             boost::log::keywords::format        = "[%TimeStamp%]: %Message%");
    boost::log::add_console_log();
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    boost::log::add_common_attributes();
    HW_TRACE << "A trace severity messagea";
    HW_DEBUG << "A debug severity message";
    HW_INFO << "An informational severity message";
    HW_WARN << "A warning severity message";
    HW_ERROR << "An error severity messagea";
    HW_DEBUG << "A fatal severity message";
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
