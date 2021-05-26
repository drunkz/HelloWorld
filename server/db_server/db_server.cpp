#include "include/db_server.h"

namespace Server {
db_server::db_server() {
    std::cout << "start" << std::endl;
}
db_server::~db_server() {
    std::cout << "end" << std::endl;
}
} // namespace Server

int main(int argc, char **argv) {
    using namespace Server;
    using namespace std;
    server_base *db = new db_server;
    delete db;
}
