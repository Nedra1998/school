#ifndef THEORY_GRAMMAR_HPP
#define THEORY_GRAMMAR_HPP
#include <string>
#include <vector>
namespace grammar {
  struct GrammarInst {
    GrammarInst(std::string str) {
      bool first = true;
      for (int i = 0; i < str.size(); i++) {
        if (str[i] == '-' && str[i + 1] == '>') {
          i++;
          first = false;
        } else if (first == true) {
          left += str[i];
        } else if (first == false) {
          right += str[i];
        }
      }
    }
    std::string String() { return (left + "->" + right); }
    std::string left, right;
  };
  void Grammar();
  int RunGrammar(std::string start, std::vector<GrammarInst> production);
}
#endif
