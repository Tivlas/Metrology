#include <iostream>
#include <vector>

#include <llvm/Support/CommandLine.h>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include "../include/MetricsCalculatorAction.hpp"
#include <tuple>

using return_type = std::tuple<unsigned long long, double, unsigned long long>;

class JilbMetricsCalculator
{
  llvm::cl::OptionCategory myToolCategory{"my-tool options"};

public:
  JilbMetricsCalculator() {}

  return_type parse(int argc, char const *argv[]);
};
