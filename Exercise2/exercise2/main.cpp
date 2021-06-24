
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"
#include "queue/vec/queuevec.hpp"
/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {

  uint choice=0;

  while(choice!=4)
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
      std::cout << "Lasd Libraries 2020" << std::endl;
      lasdtest();
      break;
    }
  }
  return 0;
  lasdtest();

}
