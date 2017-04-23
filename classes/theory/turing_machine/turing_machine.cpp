#include <ostendo.h>
#include <pessum.h>
#include "turing_machine.hpp"

using namespace ostendo;

namespace theory {
  ostendo::Window tape_win, data_win, table_win, run_win;
}
void theory::TuringMachine() {
  bool running = true;
  std::vector<Var> fields = {Var("Tapes", 1)};
  while (running == true) {
    Window win(0.5, 0.2, 0.25, 0.4);
    win.ToggleBorder();
    win.ToggleTitle("Turing Machine");
    fields = Form(win, fields);
    win.DelWin();
    running = CreateTuringMachine(fields[0].Int());
  }
}

bool theory::CreateTuringMachine(int tapes) {
  tape_win = Window(std_scr.w, tapes + 3, 0, 0);
  table_win = Window(std_scr.w, std_scr.h - (tapes + 6), 0, tapes + 3);
  run_win = Window(std_scr.w, 3, 0, std_scr.h - 3);
  tape_win.ToggleBorder();
  table_win.ToggleBorder();
  run_win.ToggleBorder();
  std::vector<std::string> instructions = {""};
  int selected_win = 0;
  bool running = true, return_val = false;
  while (running == true) {
    int in = getch();
    if (in == int('q')) {
      running = false;
    } else if (in == int(' ')) {
      running = false;
      return_val = true;
    } else if (in == KEY_UP) {
      if (selected_win == 1) {
        selected_win = 0;
      }
    } else if (in == KEY_DOWN) {
      if (selected_win == 0) {
        selected_win = 1;
      }
    }
    if (selected_win == 0) {
      instructions = VTextBox(table_win, instructions);
      int temp = 0;
      DisplayLines(table_win, instructions, -1, temp);
      selected_win = 1;
    }
  }
  tape_win.DelWin();
  table_win.DelWin();
  run_win.DelWin();
  return (return_val);
}

void theory::SimulateTuringMachine() {}
