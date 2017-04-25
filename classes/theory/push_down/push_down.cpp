#include "push_down.hpp"
#include <ostendo.h>
#include <fstream>

using namespace ostendo;

void theory::PushDown() {
  bool running = true, new_machine = true, edit_path = true, empty = false;
  std::vector<std::string> transitions = {""};
  std::vector<std::string> accept_states = {"qaccept"};
  std::string start_state = "q0";
  std::vector<PushDownInst> instructions;
  while (running == true) {
    if (new_machine == true) {
      Window entry_win(0.5, 0.5, 0.25, 0.25);
      entry_win.ToggleBorder();
      entry_win.ToggleTitle("New Push Down Automata");
      std::string accept_state_str = "";
      for (int i = 0; i < accept_states.size(); i++) {
        accept_state_str += accept_states[i];
        if (i != accept_states.size() - 1) {
          accept_state_str += ",";
        }
      }
      std::vector<Var> fields = {Var("Start State", start_state),
                                 Var("Accept States", accept_state_str),
                                 Var("Empty Stack", empty)};
      fields = Form(entry_win, fields);
      entry_win.DelWin();
      new_machine = false;
      edit_path = true;
      start_state = fields[0].String();
      accept_state_str = fields[1].String();
      accept_states.clear();
      std::string sub = "";
      for (int i = 0; i < accept_state_str.size(); i++) {
        if (accept_state_str[i] == ',') {
          accept_states.push_back(sub);
          sub = "";
        } else {
          sub += accept_state_str[i];
        }
      }
      if (sub != "") {
        accept_states.push_back(sub);
      }
      empty = fields[2].Bool();
    }
    if (edit_path == true) {
      Window entry_win(0.5, 0.5, 0.25, 0.25);
      entry_win.ToggleBorder();
      entry_win.ToggleTitle("Transitions");
      transitions = VTextBox(entry_win, transitions);
      entry_win.DelWin();
      edit_path = false;
      instructions.clear();
      for (int i = 0; i < transitions.size(); i++) {
        if (transitions[i].find("$load:") == 0) {
          std::string file_path = transitions[i];
          file_path.erase(file_path.begin(), file_path.begin() + 6);
          std::ifstream load(file_path.c_str());
          if (load.is_open()) {
            std::string line = "";
            bool first = true;
            while (getline(load, line)) {
              if (first == true) {
                transitions[i] = line;
                first = false;
              } else {
                transitions.insert(transitions.begin() + i + 1, line);
              }
            }
            load.close();
          }
        }
        if (transitions[i].find("$save:") == 0) {
          std::string file_path = transitions[i];
          file_path.erase(file_path.begin(), file_path.begin() + 6);
          std::ofstream save(file_path.c_str());
          if (save.is_open()) {
            for (int j = 0; j < transitions.size(); j++) {
              if (j != i) {
                save << transitions[i] << "\n";
              }
            }
            save.close();
          }
        }
        if (transitions[i].find("$") != 0) {
          instructions.push_back(PushDownInst(transitions[i]));
        }
      }
    }
    int ret = RunPushDown(start_state, accept_states, instructions, empty);
    if (ret == 0) {
      running = false;
    } else if (ret == 1) {
      new_machine = true;
    } else if (ret == 2) {
      edit_path = true;
    }
  }
}

int theory::RunPushDown(std::string start, std::vector<std::string> accept,
                        std::vector<PushDownInst> transitions,
                        bool empty_stack) {
  std::string str = "";
  std::string stack = "";
  Window enter(std_scr.w, 3, 0.0, 0.5);
  enter.ToggleBorder();
  enter.ToggleTitle("Enter String");
  str = Form(enter, std::vector<Var>{Var(str)})[0].String();
  enter.DelWin();

  Window str_win(std_scr.w, 3, 0, (int)(0.25 * std_scr.h));
  str_win.ToggleBorder();
  str_win.ToggleTitle("Push Down Automata");
  Window stack_win(std_scr.w, 3, 0, (int)(0.25 * std_scr.h) + 3);
  stack_win.ToggleBorder();
  stack_win.ToggleTitle("Stack");
  Window data_win((int)(0.5 * std_scr.w), (int)(0.5 * std_scr.h) - 6,
                  (int)(0.25 * std_scr.w), (int)(0.25 * std_scr.h) + 6);
  data_win.ToggleBorder();
  bool running = true, fast = false, update = true;

  int accepted = -1;

  std::string current_state = start;
  int position = 0, last_trans = -1;
  int steps = 0;
  int ret = 0;
  int pause_counter = 0;
  while (running == true) {
    if (update == true) {
      update = false;
      stack_win.Clear();
      stack_win.Print("#c%s", stack.c_str());
      str_win.Clear();
      int start_pos = (str_win.window_space.w - str.size()) / 2;
      str_win.Print("%*c", start_pos, ' ');
      for (int i = 0; i < str.size(); i++) {
        if (i == position) {
          str_win.Print("#o10%c#f10", str[i]);
        } else if (i != position) {
          str_win.Print("%c", str[i]);
        }
      }
      data_win.Clear();
      data_win.SetCurs(1, 1);
      std::string acc = "...";
      if (accepted == 0) {
        acc = "Rejected";
      } else if (accepted == 1) {
        acc = "Accepted";
      }
      if (last_trans != -1) {
        data_win.Print(
            "Accepted: %s\nCurrent State: %s\nLast Transition: %s\nCurrent "
            "Character:%c\nString Position: %i\nTop of Stack: %c\nTotal Steps: "
            "%i",
            acc.c_str(), current_state.c_str(),
            transitions[last_trans].String().c_str(), str[position], position,
            stack.end(), steps);
      } else {
        data_win.Print(
            "Accepted: %s\nCurrent State: %s\nLast Transition: NONE\nCurrent "
            "Character:%c\nTape Position: %i\nTop of Stack: %c\nTotal Steps: "
            "%i",
            acc.c_str(), current_state.c_str(), str[position], position, stack.end(),
            steps);
      }
    }
    int in = getch();
    if (fast == true) {
      pause_counter++;
    }
    if (pause_counter >= 10 || in == int(' ')) {
      pause_counter = 0;
    }
    if (in == int(' ')) {
      fast = !fast;
    } else if (in == KEY_RIGHT || (fast == true && pause_counter == 0)) {
      update = true;
      bool trans = false;
      for (int i = 0; i < transitions.size() && trans == false; i++) {
        if (current_state == transitions[i].start_state &&
            str[position] == transitions[i].read &&
            (transitions[i].pop == '_' || transitions[i].pop == stack.back())) {
          steps++;
          current_state = transitions[i].end_state;
          if(transitions[i].pop != '_'){
            stack.pop_back();
          }
          if(transitions[i].push != '_'){
            stack.push_back(transitions[i].push);
          }
          position++;
          trans = true;
          last_trans = i;
        }
      }
      for (int i = 0; i < accept.size(); i++) {
        if (current_state == accept[i]) {
          accepted = 1;
          fast = false;
        }
      }
      if (trans == false && accepted == -1) {
        accepted = 0;
        fast = false;
      }
    } else if (in == int('q')) {
      running = false;
    } else if (in == int('e')) {
      running = false;
      ret = 2;
    } else if (in == int('n')) {
      running = false;
      ret = 1;
    } else if (in == int('s')) {
      running = false;
      ret = 3;
    }
  }
  data_win.DelWin();
  str_win.DelWin();
  stack_win.DelWin();
  return (ret);
}
