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

namespace Server {
class server_base {
  public:
    server_base();
    virtual ~server_base();

  private:
    lua_State *L;
    bool       init_config();
    bool       init_log();
    bool       init_lua();
    bool       init_socket();
};
} // namespace Server

#endif // SERVER_BASE_H_INCLUDED
