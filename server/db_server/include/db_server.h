#ifndef DB_SERVER_H_INCLUDED
#define DB_SERVER_H_INCLUDED

#include "../../engine/server_base.h"

namespace server {
class db_server : public server_base {
  public:
    db_server();
    virtual ~db_server();
};
} // namespace server

#endif // DB_SERVER_H_INCLUDED
