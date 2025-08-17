#include "src/initcpi.h"
#include "src/setup.h"
#include "src/util.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << rang::fg::red << "At least 1 argument required.\n";
    return 1;
  }
  std::map<std::string, cpi::ToolChoice> m{
      {"setup", cpi::ToolChoice::SETUP},
      {"initcpi", cpi::ToolChoice::INITCPI},
      {"cclass", cpi::ToolChoice::CCLASS}};
  std::string user_choice = argv[1];
  auto choice = cpi::ToolChoice::NONE;
  if (auto search = m.find(user_choice); search != m.end()) {
    choice = m[user_choice];
  }
  switch (choice) {
  case cpi::ToolChoice::SETUP: {
    cpi::setup_cpp_project();
  } break;
  case cpi::ToolChoice::INITCPI: {
    cpi::init_cpi();
  } break;
  case cpi::ToolChoice::CCLASS: {

    if (argc < 3) {
      std::cout << rang::fg::red << "'cclass' needs atleast 1 argument.\n";
      return 1;
    }

    std::cout << rang::fg::green << "run 'cclass'";
  } break;
  case cpi::ToolChoice::NONE:

  default:
    std::cout << rang::fg::red << "Option not found.\n";

    return 1;
  }

  return 0;
}
