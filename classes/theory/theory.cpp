#include <ostendo.h>
#include <pessum.h>
#include <map>
#include <string>
#include <vector>
#include "theory.hpp"
#include "theory_headers.hpp"

void theory::ProjectSelection(std::string str) {
  std::map<std::string, void (*)()> projects;
  projects["Turing Machine"] = TuringMachine;
  projects["Push Down Automata"] = PushDown;
  std::vector<std::string> options;
  for (std::map<std::string, void (*)()>::iterator it = projects.begin();
       it != projects.end(); ++it) {
    options.push_back(it->first);
  }
  options.push_back("Back");
  std::string input = "";
  while (input != "Back") {
    ostendo::Window win(0.75, 0.5, 0.125, 0.25);
    win.ToggleBorder();
    win.ToggleTitle(str);
    input = ostendo::Menu(win, options);
    win.DelWin();
    std::map<std::string, void (*)()>::iterator it = projects.find(input);
    if (it != projects.end()) {
      it->second();
    }
  }
}
