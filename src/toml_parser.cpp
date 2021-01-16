#include <iostream>
#include <string>
#include <fstream>
#include <map>

int main () {
  std::ifstream myfile;

  myfile.open("../tomls/tree.toml");
  if (myfile.fail())
  	std::cout << "not found" << std::endl;

  std::string s;
  std::map < std::string, std::map <std::string,std::string> > res;
  std::string header;

  while(getline(myfile,s)){
    if (s.find(" = ") != std::string::npos){
      int val = s.find(" = ");
      res[header][s.substr(0,val-1)] = s.substr(val+3);
    }
    else if (s[0]=='['){
      header = s.substr(1,s.size()-2);
    }
    else{
      continue;
    }
  }
  std::cout<<res.size();
  myfile.close();
  return 0;
}