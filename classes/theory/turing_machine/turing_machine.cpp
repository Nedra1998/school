#include "turing_machine.hpp"
#include <ostendo.h>

using namespace ostendo;

void theory::TuringMachine() {
  bool running = true, new_machine = true, edit_path = true, run = true;
  std::vector<std::string> transitions = {""};
  std::vector<std::string> accept_states = {"qaccept"};
  std::string start_state = "q0";
  std::vector<TuringInst> instructions;
  while (running == true) {
    if (new_machine == true) {
      Window entry_win(0.5, 0.5, 0.25, 0.25);
      entry_win.ToggleBorder();
      entry_win.ToggleTitle("New Turing Machine");
      std::string accept_state_str = "";
      for (int i = 0; i < accept_states.size(); i++) {
        accept_state_str += accept_states[i];
        if (i != accept_states.size() - 1) {
          accept_state_str += ",";
        }
      }
      std::vector<Var> fields = {Var("Number of Tapes", 1),
                                 Var("Start State", start_state),
                                 Var("Accept States", accept_state_str)};
      fields = Form(entry_win, fields);
      entry_win.DelWin();
      new_machine = false;
      edit_path = true;
    }
    if (edit_path == true) {
      Window entry_win(0.5, 0.5, 0.25, 0.25);
      entry_win.ToggleBorder();
      entry_win.ToggleTitle("Transitions");
      transitions = VTextBox(entry_win, transitions);
      entry_win.DelWin();
      edit_path = false;
      instructions.clear();
      for(int i = 0; i < transitions.size(); i++){
        instructions.push_back(TuringInst(transitions[i]));
      }
    }
    int ret = RunTuring(start_state, accept_states, instructions);
    if(ret == 0){
      running = false;
    } else if(ret == 1){
      new_machine = true;
    } else if(ret == 2){
      edit_path = true;
    }
  }
}

int theory::RunTuring(std::string start, std::vector<std::string> accept, std::vector<TuringInst> transitions){
  std::string tape = "";
  Window enter(1.0, 0.1, 0.0, 0.45);
  enter.ToggleBorder();
  enter.ToggleTitle("Enter String");
  tape = Form(enter, std::vector<Var>{Var(tape)})[0].String();
  enter.DelWin();
  
  Window tape_win(1.0, 0.1, 0.0, 0.3);
  tape_win.ToggleBorder();
  tape_win.ToggleTitle("Turing Machine");
  bool running = true, fast = false;
  int ret = 0;
  while(running == true){
    int in = getch();
    if(in == int(' ')){
      fast = true;
    } else if(in == KEY_RIGHT || fast == true){
      
    } else if(in == int('q')){
      running = false;
    } else if(in == int('e')){
      running = false;
      ret = 2;
    } else if(in == int('n')){
      running = false;
      ret = 1;
    } else if (in == int('s')) {
      running = false;
      ret = 3;
    }
  } 
  tape_win.DelWin();
  return(ret);
}
