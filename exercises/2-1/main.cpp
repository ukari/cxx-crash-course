#include <iostream>

enum class Operation {
  Add,
  Subtract,
  Multiply,
  Divide
};

int main() {
  Operation op{Operation::Add};
  switch(op) {
  case Operation::Add:
    {
      std::cout << "add" << std::endl;
    }
    break;
  case Operation::Subtract:
    {
      std::cout << "subtract" << std::endl;
    }
    break;
  case Operation::Multiply:
    {
      std::cout << "multiply" << std::endl;
    }
    break;
  case Operation::Divide:
    {
      std::cout << "divide" << std::endl;
    }
    break;
  default:
    break;
  }
  return 0;
}
