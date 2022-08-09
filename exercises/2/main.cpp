#include <iostream>

enum class Operation {
  Add,
  Subtract,
  Multiply,
  Divide
};

struct Calculator {

  Operation operation;
  
  Calculator(Operation op) {
    operation = op;
  }

  int calculate(int a, int b) {
    int result;
    switch(operation) {
    case Operation::Add:
      {
        result = a + b;
      }
      break;
    case Operation::Subtract:
      {
        result = a - b;
      }
      break;
    case Operation::Multiply:
      {
        result = a * b;
      }
      break;
    case Operation::Divide:
      {
        result = a / b;
      }
      break;
    default:
      break;
    }
    return result;
  }
};

int main() {
  Calculator cal1 = {Operation::Add};
  Calculator cal2{Operation::Subtract};
  Calculator cal3(Operation::Multiply);
  Calculator cal4 = {Operation::Divide};;

  std::cout << cal1.calculate(1, 2) << std::endl;
  std::cout << cal2.calculate(1, 2) << std::endl;
  std::cout << cal3.calculate(1, 2) << std::endl;
  std::cout << cal4.calculate(6, 2) << std::endl;
  return 0;
}
