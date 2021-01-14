#include <iostream>
#include <fstream>


int main () {
  std::ifstream myfile;

  myfile.open ("../tomls/treem.toml", 'r');

  std::string tmp;

  myfile >> tmp;
  std::cout << tmp;


  myfile.close();
  return 0;
}