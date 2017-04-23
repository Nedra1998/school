#ifndef THEORY_TURING_MACHINE_HPP
#define THEORY_TURING_MACHINE_HPP
#include <ostendo.h>
namespace theory {
  extern ostendo::Window tape_win, table_win, run_win;
  void TuringMachine();
  bool CreateTuringMachine(int tapes);
  void SimulateTuringMachine();
}
#endif
