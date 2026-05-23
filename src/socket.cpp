#include "socket.hpp"

  server::server(){
    server_fd = socket(AF_INET, SOCK_STREAM,0);
    if(server_fd == -1){
      std::cerr << "socket failed\n";
      exit(1);
    }
  }

  void server::init(const int& port, const char* addr){
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(addr);

    if(bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0){
      std::cerr << "binding failed\n";
      close(server_fd);
      exit(1);
    }

    if(listen(server_fd, 1) < 0){
      std::cerr << "listen failed\n";
      close(server_fd);
      exit(1);
    }
    
    keep_running = true;

    std::cout << "server listening on http://" <<addr<< ":" <<port <<"\n"; 
  }

  void server::handle_get(const std::string &path){
    send_response("200 OK", "text/html", "<h1>GET request received</h1>");
  }
  void server::handle_post(const std::string &path,
                           const std::string &req
                          )
  {
    send_response("200 OK", "text/plain", "POST request received");
  }
  void server::send_response(const std::string &status,
                             const std::string &content_type,
                             const std::string &body
                            )
  {
    std::string response = "HTTP/1.1 " + status + "\r\nContent-Type: "+ content_type +"\r\n\r\n" + body;
    send(client_fd, response.c_str(), response.length(), 0);
  }

  void server::handle_request(const std::string &req){
    std::istringstream iss(req);
    std::string method, path, version;

    iss >> method >> path >> version;

    std::cout << "Method: " << method << ", Path: " << path << ", Version: " << version << "\n";

    if(method == "GET"){
      handle_get(path);
    }
    else if(method == "POST"){
      handle_post(path, req);
    }
    else{
      send_response("405 Method Not Allowed", "text/plain", "Method Not Allowed");
    }
  }

  void server::start(){
    while (keep_running){
      client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_addr_len);
      if(client_fd < 0){
        std::cerr << "accept failed\n";
        close(server_fd);
        exit(1);
      }

      char buffer[4096] = {0};
      read(client_fd, buffer, sizeof(buffer)-1);

      // std::cout << buffer << "\n";
      std::string req(buffer);
      handle_request(req);

      close(client_fd);
    }
  }