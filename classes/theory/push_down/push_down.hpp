#ifndef THEORY_PUSH_DOWN_HPP
#define THEORY_PUSH_DOWN_HPP
#include <pessum.h>
#include <string>
#include <vector>
namespace theory {
  struct PushDownInst {
    PushDownInst(std::string str) {
      std::string sub_str = "";
      int pos = 0;
      for (int i = 0; i < str.size(); i++) {
        if (str[i] == ',') {
          if (pos == 0) {
            start_state = sub_str;
            pos = 1;
          } else if (pos == 1) {
            read = sub_str[0];
            pos = 2;
          } else if (pos == 3) {
            end_state = sub_str;
            pos = 4;
          }
          sub_str = "";
        } else if (str[i] == '-' && str[i + 1] == '>') {
          if (pos == 2) {
            pop = sub_str[0];
            pos = 3;
          }
          sub_str = "";
          i++;
        } else {
          sub_str += str[i];
        }
      }
      push = sub_str[0];
    }
    std::string String() {
      return (start_state + "," + read + "," + pop + "->" + end_state + "," +
              push);
    }
    std::string start_state, end_state;
    char read, pop, push;
  };
  void PushDown();
  int RunPushDown(std::string start, std::vector<std::string> accept,
                  std::vector<PushDownInst> transitions, bool empty);
}
#endif
