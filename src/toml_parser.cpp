#include <iostream>
#include <fstream>


int main () {
  std::ifstream myfile;

  myfile.open("../tomls/tree.toml");
  if (myfile.fail())
  	std::cout << "bitckou mater" << std::endl;

  std::string tmpl, spc, tmpr, tmp;

  //std::getline(myfile, tmp);
  std::getline(myfile, tmp);
   std::getline(myfile, tmp);
    std::getline(myfile, tmp);
  std::getline(myfile, tmp);
  std::cout << "first line :" << tmp << std::endl ;


  myfile.close();
  return 0;
}