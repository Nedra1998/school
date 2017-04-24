#ifndef CLASS_CORE_HPP
#define CLASS_CORE_HPP
#include <map>
#include <string>
namespace classcore {
  struct Semester {
    Semester(std::string na, std::map<std::string, void (*)(std::string)> cl) {
      name = na;
      classes = cl;
    }
    std::string name;
    std::map<std::string, void (*)(std::string)> classes;
  };
  void Null(std::string str);
  void ClassSelection();
}
#endif
