#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

using Stack = std::stack<uint64_t>;

std::vector<std::string> f1;

uint64_t pop(Stack& stack) {
  if (stack.empty()) return 2;
  uint64_t top = stack.top();
  stack.pop();
  return top;
}

int interpret(std::vector<std::string> program, Stack& stack) {
  for (int i = 0; i < program.size(); i++) {
    // std::cout << program[i] << "\n";
    // Convert string to int.
    uint64_t int_val = 0;
    bool valid_int = true;
    try {
      int_val = std::stoll(program[i]);
    } catch (std::invalid_argument e) {
      valid_int = false;
    }
    if (program[i] == "@Gozz") {
      char in;
      std::cin >> in;
      stack.push(in);
    } else if (program[i] == "Gozz@") {
      char out = pop(stack);
      std::cout << out;
    } else if (valid_int) {
      stack.push(int_val);
    } else if (program[i] == "Gozz$") {
      uint64_t out = pop(stack);
      std::cout << std::to_string(out);
    } else if (program[i] == "gozz") {
      uint64_t left = pop(stack);
      uint64_t right = pop(stack);
      stack.push(left + right);
    } else if (program[i] == "Gozz:") {
      f1.clear();
      // Function definition.
      // Get the function name.
      if (program[++i] == "Gozz") {
        std::string instr;
        while ((instr = program[++i]) != "Gozz!") {
          f1.push_back(instr);
        }
      } else {
        std::cerr << "Not implemented";
      }
    } else if (program[i] == "Gozz") {
      // Function call.
      interpret(f1, stack);
    } else {
      std::cerr << "Dunno what that is :(\n";
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  std::string input;
  std::vector<std::string> program;
  std::fstream f(argv[1]);
  while (f >> input) {
    program.push_back(input);
  }
  Stack stack;
  return interpret(program, stack);
}