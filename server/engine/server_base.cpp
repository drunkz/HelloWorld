#include "server_base.h"

namespace Server {
server_base::server_base() {
    // logging::add_file_log(
    //     logging::keywords::file_name     = "/home/dkz/ttt/aaa/sample_%Y-%m-%d_%H-%M-%S.txt",
    //     logging::keywords::rotation_size = 10 << 20,
    //     logging::keywords::format =
    //         (logging::expressions::stream
    //          << logging::expressions::format_date_time<boost::posix_time::ptime>(
    //                 "TimeStamp", "%Y-%m-%d %H:%M:%S")
    //          << ": [" << logging::trivial::severity << "] " << logging::expressions::smessage));
    // logging::add_console_log(
    //     std::cout,
    //     logging::keywords::format =
    //         (logging::expressions::stream
    //          << logging::expressions::format_date_time<boost::posix_time::ptime>(
    //                 "TimeStamp", "%Y-%m-%d %H:%M:%S")
    //          << ": [" << logging::trivial::severity << "] " << logging::expressions::smessage));
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    sink->locked_backend()->add_stream(
        boost::make_shared<std::ofstream>("/home/dkz/ttt/aaa/sample.log"));
    logging::core::get()->add_sink(sink);
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    // logging::add_common_attributes();
    // HW_TRACE << "A trace severity messagea";
    // HW_DEBUG << "A debug severity message";
    // HW_INFO << "An informational severity message";
    // HW_WARN << "A warning severity message";
    // HW_ERROR << "An error severity messagea";
    // HW_DEBUG << "A fatal severity message";
    src::logger lg;
    BOOST_LOG(lg) << "aaaaa!";
    BOOST_LOG(lg) << "aaaaa!";
    BOOST_LOG(lg) << "aaaaa!";
    BOOST_LOG(lg) << "aaaaa!";
    BOOST_LOG(lg) << "aaaaa!";
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
