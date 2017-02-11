#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

using Stack = std::stack<uint64_t>;

int interpret(std::vector<std::string> program, Stack stack) {
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
      char out = stack.top();
      stack.pop();
      std::cout << out;
    } else if (valid_int) {
      stack.push(int_val);
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