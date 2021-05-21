#include "server_base.h"

namespace Server {
server_base::server_base() {
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
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
