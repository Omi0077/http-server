#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "socket.hpp"

using json = nlohmann::json;

int main(){
  // std::ifstream f("sample_json.json");
  // if(!f.is_open()){
  //   std::cerr << "could not open file\n";
  //   return 1;
  // }
  // json j = json::parse(f);
  // std::cout << j.dump(2) <<"\n";

  server s = server();
  s.init(8000, "0.0.0.0");
  s.start();
  return 0;
}