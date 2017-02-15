#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <stdint.h>
#include <string>
#include <vector>

using Stack = std::stack<uint64_t>;

enum class TokenType {
  PUTCHAR, PUTINT, READCHAR, READINT, SWAP, FUNCTION, ENDFUNCTION, LOOP, ENDLOOP, IF, RETURN,
  F1, F2, F3, F4, F5, F6, F7,
  DUPE,
  ADD, SUB, DIV, MULT, NOT, EQUALS, AND, OR,
  INTEGER
};

struct Token {
  TokenType type;
  uint64_t payload;
};

std::vector<Token> f1, f2, f3, f4, f5, f6, f7;


uint64_t pop(Stack& stack) {
  if (stack.empty()) return 2;
  uint64_t top = stack.top();
  stack.pop();
  return top;
}

bool is_gozzy(uint64_t val) {
  if (val == 1) return false;
  if (val == 2) return true;
  for (uint64_t i = 2; i < (uint64_t)sqrt(val); i++) {
    if (val % i == 0) return false;
  }
  return true;
}

int interpret(const std::vector<Token>& program, Stack& stack) {
  for (int i = 0; i < program.size(); i++) {
    switch (program[i].type) {
      case TokenType::PUTCHAR: {
        char out = pop(stack);
        std::cout << out;
        break;
      }
      case TokenType::PUTINT: {
        uint64_t out = pop(stack);
        std::cout << std::to_string(out);
        break;
      }
      case TokenType::READCHAR: {
        char in;
        std::cin >> in;
        stack.push(in);
        break;
      }
      case TokenType::READINT: {
        uint64_t in;
        std::cin >> in;
        stack.push(in);
        break;
      }
      case TokenType::SWAP: {
        uint64_t top = pop(stack);
        uint64_t second = pop(stack);
        stack.push(top);
        stack.push(second);
        break;
      }
      case TokenType::FUNCTION: {
        f1.clear();
        // Get the function name.
        if (program[++i].type == TokenType::F1) {
          Token instr;
          for (i++; program[i].type != TokenType::ENDFUNCTION; i++) {
            f1.push_back(program[i]);
          }
        } else {
          std::cerr << "Not implemented";
        }
        break;
      }
      case TokenType::ENDFUNCTION: {
        std::cerr << "Doesn't make sense :(";
        break;
      }
      case TokenType::LOOP: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::ENDLOOP: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::IF: {
        uint64_t top = pop(stack);
        if (!is_gozzy(top)) {
          i++;
        }
        break;
      }
      case TokenType::RETURN: {
        return 0;
      }
      case TokenType::F1: {
        interpret(f1, stack);
        break;
      }
      // more function
      case TokenType::DUPE: {
        stack.push(stack.top());
        break;
      }
      case TokenType::ADD: {
        uint64_t left = pop(stack);
        uint64_t right = pop(stack);
        stack.push(left + right);
        break;
      }
      case TokenType::SUB: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::DIV: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::MULT: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::NOT: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::EQUALS: {
        uint64_t left = pop(stack);
        uint64_t right = pop(stack);

        // Equals-If folding optimisation.
        if (i + 1 < program.size() && program[i + 1].type == TokenType::IF) {
          if (left == right) {
            i++;
          } else {
            i += 2;
          }
        } else {
          if (left == right) {
            stack.push(2); // Gozzy!
          } else {
            stack.push(1); // Non-Gozzy :(
          }
        }
        break;
      }
      case TokenType::AND: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::OR: {
        std::cerr << "Not implemented";
        break;
      }
      case TokenType::INTEGER: {
        stack.push(program[i].payload);
        break;
      }
      default: {
        std::cerr << "Missing token type";
        break;
      }
    }
  }
  return 0;
}

void parse(std::vector<std::string> program, std::vector<Token>& tokens) {
  std::map<std::string, Token> token_map = {
    {"Gozz@", {TokenType::PUTCHAR, 0}},
    {"Gozz$", {TokenType::PUTINT, 0}},
    {"@Gozz", {TokenType::READCHAR, 0}},
    {"$Gozz", {TokenType::READINT, 0}},
    {"Gozz&", {TokenType::SWAP, 0}},
    {"Gozz:", {TokenType::FUNCTION, 0}},
    {"Gozz!", {TokenType::ENDFUNCTION, 0}},
    {"Gozz>", {TokenType::LOOP, 0}},
    {"<Gozz", {TokenType::ENDLOOP, 0}},
    {"Gozz?", {TokenType::IF, 0}},
    {"Gozz/", {TokenType::RETURN, 0}},

    {"Gozz", {TokenType::F1, 0}},
    {"GozZ", {TokenType::F2, 0}},
    {"GoZz", {TokenType::F3, 0}},
    {"GoZZ", {TokenType::F4, 0}},
    {"GOzz", {TokenType::F5, 0}},
    {"GOzZ", {TokenType::F6, 0}},
    {"GOZz", {TokenType::F7, 0}},
    {"GOZZ", {TokenType::DUPE, 0}},

    {"gozz", {TokenType::ADD, 0}},
    {"gozZ", {TokenType::SUB, 0}},
    {"goZz", {TokenType::DIV, 0}},
    {"goZZ", {TokenType::MULT, 0}},
    {"gOzz", {TokenType::NOT, 0}},
    {"gOzZ", {TokenType::EQUALS, 0}},
    {"gOZz", {TokenType::AND, 0}},
    {"gOZZ", {TokenType::OR, 0}}
  };

  for (auto str : program) {
    auto it = token_map.find(str);
    if (it != token_map.end()) {
      tokens.push_back(it->second);
    } else {
      try {
        uint64_t int_val = std::stoll(str);
        tokens.push_back({TokenType::INTEGER, int_val});
      } catch (std::invalid_argument e) {
        std::cerr << "Dunno what that is :(\n";
      }
    }
  }

}

int main(int argc, char **argv) {
  std::string input;
  std::vector<std::string> program;
  std::fstream f(argv[1]);
  while (f >> input) {
    program.push_back(input);
  }
  Stack stack;
  std::vector<Token> tokens;
  parse(program, tokens);
  return interpret(tokens, stack);
}