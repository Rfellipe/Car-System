#include <fstream>
#include <string>
#include <iostream>

void readtxt() {
  std::string txt;
  std::ifstream readme("readme.md");

  for (int i = 0; i < 49; i++)
  {
    getline(readme, txt);
    std::cout << txt << std::endl;
  }
  
  readme.close();
}