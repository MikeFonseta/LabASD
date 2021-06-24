
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {

  uint choice=0;

  while(choice!=6)
  {
    std::cout << std::endl << "===================== My Test Menu =====================" << std::endl;
    SelectOption(choice);
    switch (choice) {
      case 1:
      SelectDataStructure(choice);
      break;
      case 2:
      SelectDataStructure(choice);
      break;
      case 3:
      SelectType(choice,3);
      break;
      case 4:
      SelectType(choice,4);
      break;
      case 5:
      std::cout << "Lasd Libraries 2020" << std::endl;
      lasdtest();
      break;
    }
  }
  return 0;
}
