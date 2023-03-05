#include <iostream>
#include <vector>

#include <llvm/Support/CommandLine.h>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include "../include/MetricsCalculatorAction.hpp"
#include <tuple>

using return_type = std::tuple<std::vector<std::pair<std::string, int>>, std::vector<std::pair<std::string, int>>, int, int, int, int, int, int, int>;

class ParserHalstead
{
  llvm::cl::OptionCategory myToolCategory{"my-tool options"};

public:
  ParserHalstead() {}

  return_type parse(int argc, char const *argv[]);
};
