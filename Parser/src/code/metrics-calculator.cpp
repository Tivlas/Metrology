#include "../include/metrics-calculator.h"

return_type ParserHalstead::parse(int argc, char const *argv[])
{
  clang::tooling::CommonOptionsParser optionsParser(argc, argv, myToolCategory);

  clang::tooling::ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

  MyRecursiveASTVisitor::sourcepathlist = optionsParser.getSourcePathList();

  int res = tool.run(clang::tooling::newFrontendActionFactory<MetricsCalculatorAction>().get());

  unsigned int N1, N2, n1, n2, N, n;
  int V;

  N1 = 0; // общее число операторов
  std::vector<std::pair<std::string, int>> operator_number;
  for (auto op : MyRecursiveASTVisitor::operators)
  {
    N1 += op.second;
    operator_number.push_back(std::make_pair(op.first, op.second));
  }

  N2 = 0; // общее число операндов
  std::vector<std::pair<std::string, int>> operand_number;
  for (auto op : MyRecursiveASTVisitor::operands)
  {
    N2 += op.second;
    operand_number.push_back(std::make_pair(op.first, op.second));
  }

  n1 = MyRecursiveASTVisitor::operators.size(); // число уникальных операторов
  n2 = MyRecursiveASTVisitor::operands.size();  // число уникальных операндов

  N = N1 + N2;           // длина программы
  n = n1 + n2;           // словарь программы
  V = N * std::log2f(n); // объем программы
  return std::make_tuple(operator_number, operand_number, n1, n2, N1, N2, n, N, V);
}