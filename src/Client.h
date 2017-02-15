#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
  public:
    Client(std::string addr_ip);
    ~Client();
    int join_connection();

  private:
    std::string ip;
};

#endif
