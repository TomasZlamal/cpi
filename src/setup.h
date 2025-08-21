#pragma once
#include "util.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <streambuf>
namespace cpi {
namespace setup {
enum class PackageManager { VCPKG, NONE };
enum class BuildSystem { CMAKE, NONE };
enum class ProjectType { EXECUTABLE, LIBRARY };

struct SetupState {
  std::string project_name;
  PackageManager package_manager;
  BuildSystem build_system;
  ProjectType project_type;
  bool generate_entrypoint;
};

void get_project_name(SetupState &state);
void get_package_manager(SetupState &state);
void get_project_type(SetupState &state);
void get_build_system(SetupState &state);
void handle_build_system(const SetupState &state);
void handle_package_manager(const SetupState &state);
void generate_readme(const SetupState &state);
} // namespace setup
void setup_cpp_project();
} // namespace cpi
