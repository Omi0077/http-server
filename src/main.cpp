#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(){
  json j = {
    {"name","om shankar"},
    {"age", 21},
    {"gender", "male"},
    {"language", {"hindi","english","telgu"}}
  };
  std::cout << j <<"\n";
  return 0;
}