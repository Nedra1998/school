#include <ostendo.h>
#include <pessum.h>
#include <map>
#include <string>
#include <vector>
#include "class_core.hpp"
#include "class_headers.hpp"

void test() {}

void classcore::ClassSelection() {
  std::vector<Semester> semesters;
  std::map<std::string, void (*)()> classes;
  /*Spring 2017*/
  classes["Exploration and Discovery II (CORE-107-25)"] = test;
  classes["Linear Algebra (MATH-225-F1)"] = test;
  classes["Physics II: Waves and Matter (PHYS-152-01)"] = test;
  classes["Theory of Computation (CS-456-01)"] = theory::ProjectSelection;
  semesters.push_back(Semester("Spring 2017", classes));
  classes.clear();
  /*Fall 2016*/
  classes["Exploration and Discovery I (CORE-106-19)"] = test;
  classes["Calculus III (Math-233-F1)"] = test;
  classes["Physics I: Motion (PHYS-151-01)"] = test;
  classes["Intermediate Spanish I (SPAN-201-F5)"] = test;
  semesters.push_back(Semester("Fall 2016", classes));
  classes.clear();

  int selected_semester = -1;
  std::vector<std::string> options;
  std::string input = "";
  while (input != "Quit") {
    options.clear();
    if (selected_semester != -1) {
      for (std::map<std::string, void (*)()>::iterator it =
               semesters[selected_semester].classes.begin();
           it != semesters[selected_semester].classes.end(); ++it) {
        options.push_back(it->first);
      }
      options.push_back("Back");
    } else {
      for (int i = 0; i < semesters.size(); i++) {
        options.push_back(semesters[i].name);
      }
      options.push_back("Quit");
    }
    ostendo::Window win(0.75, 0.5, 0.125, 0.25);
    win.ToggleBorder();
    win.ToggleTitle("Classes");
    input = ostendo::Menu(win, options);
    win.DelWin();
    if (selected_semester != -1 && input != "Back") {
      std::map<std::string, void (*)()>::iterator it =
          semesters[selected_semester].classes.find(input);
      if (it != semesters[selected_semester].classes.end()) {
        it->second();
      }
    } else if (selected_semester != -1 && input == "Back") {
      selected_semester = -1;
    } else if (selected_semester == -1 && input != "Quit") {
      for (int i = 0; i < semesters.size(); i++) {
        if (semesters[i].name == input) {
          selected_semester = i;
        }
      }
    }
  }
}
