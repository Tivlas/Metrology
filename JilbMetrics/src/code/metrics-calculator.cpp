#include "../include/metrics-calculator.h"

return_type JilbMetricsCalculator::parse(int argc, char const *argv[])
{
  clang::tooling::CommonOptionsParser optionsParser(argc, argv, myToolCategory);

  clang::tooling::ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

  MyRecursiveASTVisitor::sourcepathlist = optionsParser.getSourcePathList();

  int res = tool.run(clang::tooling::newFrontendActionFactory<MetricsCalculatorAction>().get());

  return {MyRecursiveASTVisitor::branches_count,
            static_cast<double>(MyRecursiveASTVisitor::branches_count) /
                static_cast<double>(MyRecursiveASTVisitor::operators_count),
            MyRecursiveASTVisitor::max_depth};
}