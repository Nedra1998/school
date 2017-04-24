#ifndef THEORY_TURING_MACHINE_HPP
#define THEORY_TURING_MACHINE_HPP
#include <string>
#include <vector>
namespace theory {
  struct TuringInst {
    TuringInst(std::string str) {
      std::string sub_str = "";
      int pos = 0;
      for (int i = 0; i < str.size(); i++) {
        if (str[i] == ',') {
          if (pos == 0) {
            start_state = sub_str;
            pos = 1;
          } else if (pos == 2) {
            end_state = sub_str;
            pos = 3;
          } else if (pos == 3) {
            write = sub_str[0];
            pos = 4;
          } else if (pos == 4) {
            if (sub_str[0] == 'S' || sub_str[0] == 's') {
              move = 0;
            } else if (sub_str[0] == 'R' || sub_str[0] == 'r') {
              move = 1;
            } else if (sub_str[0] == 'L' || sub_str[0] == 'l') {
              move = -1;
            }
          }
          sub_str = "";
        } else if (str[i] == '-' && str[i + 1] == '>') {
          if (pos == 1) {
            read = sub_str[0];
            sub_str = "";
            pos = 2;
          }
          i++;
          sub_str = "";
        } else {
          sub_str += str[i];
        }
      }
      if (pos == 0) {
        start_state = sub_str;
        pos = 1;
      } else if (pos == 2) {
        end_state = sub_str;
        pos = 3;
      } else if (pos == 3) {
        write = sub_str[0];
        pos = 4;
      } else if (pos == 4) {
        if (sub_str[0] == 'S' || sub_str[0] == 's') {
          move = 0;
        } else if (sub_str[0] == 'R' || sub_str[0] == 'r') {
          move = 1;
        } else if (sub_str[0] == 'L' || sub_str[0] == 'l') {
          move = -1;
        }
      }
    }
    std::string String() {
      if (move == 1) {
        return (start_state + "," + read + "->" + end_state + "," + write +
                ",R");
      } else if (move == 0) {
        return (start_state + "," + read + "->" + end_state + "," + write +
                ",S");
      } else if (move == -1) {
        return (start_state + "," + read + "->" + end_state + "," + write +
                ",L");
      }
      return ("");
    }
    std::string start_state, end_state;
    char read, write;
    int move;
  };
  void TuringMachine();
  int RunTuring(std::string start, std::vector<std::string> accept,
                std::vector<TuringInst> transitions, bool last);
}
#endif
