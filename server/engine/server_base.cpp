#include "server_base.h"
#include "client/linux/handler/exception_handler.h"
#include "config.hpp"
#include <boost/stacktrace.hpp>

namespace Server {

void my_terminate_handler() {
    try {
        std::cerr << boost::stacktrace::stacktrace();
    } catch (...) {
    }
    std::abort();
}

server_base::server_base() {
    init_log();
    // LOG_TRACE << "aaa";
    // LOG_INFO << "aaa";
    // LOG_DEBUG << "aaaa";
    // LOG_WARN << "ccc";
    // LOG_ERROR << "bbb";
    // LOG_FATAL << "ccc";
    // std::cout << boost::stacktrace::stacktrace();
    google_breakpad::MinidumpDescriptor descriptor("/home/dkz/Videos");
    google_breakpad::ExceptionHandler eh(descriptor, NULL, NULL, NULL, true, -1);
    // std::set_terminate(&my_terminate_handler);
    config cfg;
    // cfg.load("aabb.cc");
    int b = 3 / 0;
    L     = luaL_newstate();
    if (L == nullptr) {
    } else {
        luaL_openlibs(L);
        luaL_dostring(L, "print('hello,world')");
    }
}

void my_formatter(logging::record_view const &rec, logging::formatting_ostream &strm) {
    auto severity = rec[logging::trivial::severity];
    // #ifdef __linux__
    if (severity) {
        switch (severity.get()) {
            case boost::log::trivial::trace:
                strm << "\033[36m";
                break;
            case boost::log::trivial::debug:
                strm << "\033[34m";
                break;
            case boost::log::trivial::info:
                strm << "\033[32m";
                break;
            case boost::log::trivial::warning:
                strm << "\033[33m";
                break;
            case boost::log::trivial::error:
            case boost::log::trivial::fatal:
                strm << "\033[31m";
                break;
            default:
                break;
        }
    }
    // #endif
    strm << rec[expr::smessage];
    if (severity) {
        strm << "\033[0m";
    }
}

void server_base::init_log() {
    // boost::log::core::get()->set_exception_handler(boost::log::make_exception_suppressor());
    typedef sinks::asynchronous_sink<sinks::text_ostream_backend> t_text_ostream;
    boost::shared_ptr<t_text_ostream> ostream_sink = boost::make_shared<t_text_ostream>();
    ostream_sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
    // ostream_sink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
    //                                          << expr::format_named_scope("Scope", logging::keywords::format = "[%f:%l]") <<
    //                                          logging::trivial::severity
    //                                          << expr::smessage);
    ostream_sink->set_formatter(&my_formatter);
    logging::core::get()->add_sink(ostream_sink);

    typedef sinks::asynchronous_sink<sinks::text_file_backend> t_text_file;
    boost::shared_ptr<t_text_file> file_sink = boost::make_shared<t_text_file>();
    file_sink->locked_backend()->set_file_name_pattern("/home/dkz/ttt/aaa/sample_%Y-%m-%d_%H-%M-%S.txt");
    file_sink->locked_backend()->set_rotation_size(10 << 20);
    file_sink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                                          << expr::format_named_scope("Scope", logging::keywords::format = "[%f:%l]") << logging::trivial::severity
                                          << expr::smessage);
    file_sink->locked_backend()->set_file_collector(
        boost::log::sinks::file::make_collector(keywords::target = "aaa", keywords::max_size = 3 * 1024, keywords::max_files = 10));
    file_sink->locked_backend()->scan_for_files(boost::log::sinks::file::scan_method::scan_matching, true);
    file_sink->locked_backend()->auto_flush(true);
    logging::core::get()->add_sink(file_sink);
    logging::add_common_attributes();
    // logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
}

server_base::~server_base() {
    lua_close(L);
    logging::core::get()->flush();
}

} // namespace Server
