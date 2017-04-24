#ifndef CLASS_CORE_HPP
#define CLASS_CORE_HPP
#include <map>
#include <string>
namespace classcore {
  struct Semester {
    Semester(std::string na, std::map<std::string, void (*)()> cl) {
      name = na;
      classes = cl;
    }
    std::string name;
    std::map<std::string, void (*)()> classes;
  };
  void ClassSelection();
}
#endif
