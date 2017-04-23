#include <ostendo.h>
#include <pessum.h>
#include <map>
#include <string>
#include <vector>
#include "class_core.hpp"
#include "class_headers.hpp"

void classcore::ClassSelection() {
  std::map<std::string, void (*)()> classes;
  classes["CS Theory (465)"] = theory::ProjectSelection;
  std::vector<std::string> options;
  for (std::map<std::string, void (*)()>::iterator it = classes.begin();
       it != classes.end(); ++it) {
    options.push_back(it->first);
  }
  options.push_back("Quit");
  std::string input = "";
  while (input != "Quit") {
    ostendo::Window win(0.5, 0.5, 0.25, 0.25);
    win.ToggleBorder();
    win.ToggleTitle("Classes");
    input = ostendo::Menu(win, options);
    win.DelWin();
    std::map<std::string, void (*)()>::iterator it = classes.find(input);
    if (it != classes.end()) {
      it->second();
    }
  }
}
