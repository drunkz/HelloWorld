#include "include/db_server.h"

namespace server {
db_server::db_server() {
    std::cout << "start" << std::endl;
}
db_server::~db_server() {
    std::cout << "end" << std::endl;
}
} // namespace server

int main(int argc, char **argv) {
    using namespace server;
    using namespace std;
    server_base *db = new db_server;
    delete db;
}
