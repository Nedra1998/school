#include <ostendo.h>
#include <pessum.h>
#include "classes/class_headers.hpp"

int main(int argc, char const* argv[]) {
  ostendo::InitOstendo(true, 1);
  classcore::ClassSelection();
  ostendo::TermOstendo();
  pessum::SaveLog("out.log");
  return 0;
}
