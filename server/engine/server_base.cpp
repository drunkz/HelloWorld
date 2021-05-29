#include "server_base.h"

namespace Server {

server_base::server_base() {
    init_log();
    for (size_t i = 0; i < 500; i++) {
        LOG_DEBUG << "aaaa" << i;
    }
    L = luaL_newstate();
    if (L == nullptr) {
    } else {
        luaL_openlibs(L);
        luaL_dostring(L, "print('hello,world')");
    }
}

void coloring_formatter(logging::record_view const &rec, logging::formatting_ostream &strm) {
    auto severity = rec[logging::trivial::severity];
    if (severity) {
        // Set the color
        switch (severity.get()) {
            case 0:
                strm << "\033[32m";
                break;
            case 1:
                strm << "\033[33m";
                break;
            case 2:
            case 3:
                strm << "\033[31m";
                break;
            default:
                break;
        }
    }
    strm << rec[logging::expressions::smessage];
    if (severity) {
        strm << "\033[0m";
    }
}

void server_base::init_log() {
    typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_ostream_sink;
    boost::shared_ptr<text_ostream_sink>                          ostream_sink = boost::make_shared<text_ostream_sink>();
    ostream_sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
    // ostream_sink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
    //                                          << expr::format_named_scope("Scope", logging::keywords::format = "[%f:%l]") <<
    //                                          logging::trivial::severity
    //                                          << expr::smessage);
    // ostream_sink->set_formatter();
    logging::core::get()->add_sink(ostream_sink);

    typedef sinks::asynchronous_sink<sinks::text_file_backend> text_file_sink;
    boost::shared_ptr<text_file_sink>                          file_sink = boost::make_shared<text_file_sink>();
    file_sink->locked_backend()->set_file_name_pattern("/home/dkz/ttt/aaa/sample_%Y-%m-%d_%H-%M-%S.txt");
    file_sink->locked_backend()->set_rotation_size(10 << 20);
    file_sink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                                          << expr::format_named_scope("Scope", logging::keywords::format = "[%f:%l]") << logging::trivial::severity
                                          << expr::smessage);
    logging::core::get()->add_sink(file_sink);
    logging::add_common_attributes();
    // logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
}

server_base::~server_base() {
    lua_close(L);
    logging::core::get()->flush();
}

} // namespace Server
