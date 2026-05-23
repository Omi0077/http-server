#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>

struct server{
  int server_fd{}, client_fd{};
  sockaddr_in server_addr{}, client_addr{}; 
  socklen_t client_addr_len = sizeof(client_addr);

  bool keep_running = false;

  server();

  void init(const int& port, const char* addr = "0.0.0.0");

  void handle_get(const std::string &path);
  void handle_post(const std::string &path,
                   const std::string &req
                  );
  void send_response(const std::string &status,
                             const std::string &content_type,
                             const std::string &body
                            );

  void handle_request(const std::string &req);

  void start();
};

#endif