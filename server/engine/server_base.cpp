#include "server_base.h"

namespace Server {
server_base::server_base() {
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<sinks::text_file_backend>                  backend = boost::make_shared<sinks::text_file_backend>(
        logging::keywords::file_name = "/home/dkz/ttt/aaa/sample_%Y-%m-%d_%H-%M-%S.txt", logging::keywords::rotation_size = 10 << 20);
    boost::shared_ptr<text_sink>    sink = boost::make_shared<text_sink>();
    boost::shared_ptr<std::ostream> stream(&std::clog, boost::null_deleter());
    // sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>("/home/dkz/ttt/aaa/sample.log"));
    sink->locked_backend()->add_stream(stream);
    sink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                                     << expr::format_named_scope("Scope", logging::keywords::format = "[%f:%l]") << logging::trivial::severity
                                     << expr::smessage);
    logging::core::get()->add_sink(sink);
    typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
    boost::shared_ptr<sink_t>                                 ssink(new sink_t(backend));
    ssink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                                      << expr::format_named_scope("Scope", logging::keywords::format = "[%f:%l]") << logging::trivial::severity
                                      << expr::smessage);
    logging::core::get()->add_sink(ssink);
    // boost::shared_ptr<text_sink> ssink(new text_sink(backend));
    // logging::core::get()->add_sink(ssink);
    // logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    // logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
    logging::add_common_attributes();
    logging::core::get()->add_global_attribute("Scope", attrs::named_scope());
    LOG_ERROR << "aaaaa!";
    LOG_DEBUG << "bbbb";
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
