#include "src/cclass.h"
#include "src/create_functions.h"
#include "src/csplit.h"
#include "src/initcpi.h"
#include "src/loc_tool.h"
#include "src/setup.h"
#include "src/util.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << RANG_EXPR(rang::fg::red) << "At least 1 argument required.\n";
    return 1;
  }

  std::string user_choice = argv[1];
  cpi::ToolChoice tool_choice = [&user_choice] {
    std::map<std::string, cpi::ToolChoice> tool_mapping{
        {"setup", cpi::ToolChoice::SETUP},
        {"initcpi", cpi::ToolChoice::INITCPI},
        {"cclass", cpi::ToolChoice::CCLASS},
        {"csplit", cpi::ToolChoice::CSPLIT},
        {"loc", cpi::ToolChoice::LOC}};

    if (auto search = tool_mapping.find(user_choice);
        search != tool_mapping.end()) {
      return tool_mapping[user_choice];
    }
    return cpi::ToolChoice::NONE;
  }();

  switch (tool_choice) {
  case cpi::ToolChoice::SETUP: {
    cpi::setup_cpp_project();
  } break;
  case cpi::ToolChoice::INITCPI: {
    cpi::init_cpi();
  } break;
  case cpi::ToolChoice::CSPLIT: {
    cpi::split_fn_execute(cpi::csplit, argc, argv, "csplit");
  } break;
  case cpi::ToolChoice::CCLASS: {
    cpi::split_fn_execute(cpi::cclass, argc, argv, "cclass");
  } break;
  case cpi::ToolChoice::LOC: {
    // BIG PROBLEM WITH THIS TOOL: WONT BE ABLE TO HANDLE OVERLAPS (between
    // directories, since the search is recursive). It does handle it if the
    // directories are exactly the same though.
    try {

      auto config = toml::parse_file("cpi/cpi.toml");
      std::cout << RANG_EXPR(rang::style::reset)
                << "Lines of code count: " << RANG_EXPR(rang::style::bold)
                << cpi::get_project_loc(config);

    }

    catch (const toml::parse_error &err) {
      std::cout << "Could not find toml file." << std::endl;
      return 1;
    }
  } break;
  case cpi::ToolChoice::NONE:

  default:
    std::cout << RANG_EXPR(rang::fg::red) << "Option not found.\n";

    return 1;
  }

  return 0;
}
