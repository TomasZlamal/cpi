#include "libs/rang/rang.hpp"
#include <filesystem>
#include <fstream>
#include <map>
#include <streambuf>

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

enum class ToolChoice { NONE, SETUP };

void get_project_name(SetupState &state) {
  std::cout << rang::style::bold << "Project name?" << rang::style::reset
            << "\n> ";
  std::getline(std::cin, state.project_name);
  std::cout << "\n";
}

void get_package_manager(SetupState &state) {
  std::cout << rang::style::bold
            << "Which package manager do you want to use?\n"
            << rang::style::reset << "[0] None (default)\n"
            << "[1] Vcpkg\n> ";
  std::string temp;

  std::getline(std::cin, temp);

  if (temp == "1") {
    state.package_manager = PackageManager::VCPKG;
  } else {
    state.package_manager = PackageManager::NONE;
  }

  std::cout << "\n";
}
void get_project_type(SetupState &state) {
  std::cout << rang::style::bold << "What is the output of your project?\n"
            << rang::style::reset << "[0] Executable program (default)\n"
            << "[1] Library\n> ";
  std::string temp;

  std::getline(std::cin, temp);

  if (temp == "1") {
    state.project_type = ProjectType::LIBRARY;

  } else {
    state.project_type = ProjectType::EXECUTABLE;
  }

  std::cout << "\n";
}
void get_build_system(SetupState &state) {

  std::cout << rang::style::bold << "Which build system do you want to use?\n"
            << rang::style::reset << "[0] CMake (default)\n"
            << "[1] None\n> ";
  std::string temp;

  std::getline(std::cin, temp);

  if (temp == "1") {
    state.build_system = BuildSystem::NONE;
  } else {
    state.build_system = BuildSystem::CMAKE;
  }

  std::cout << "\n";
}

void handle_build_system(const SetupState &state) {
  if (state.build_system == BuildSystem::CMAKE) {
    std::ofstream outfile("CMakeLists.txt");

    outfile << "cmake_minimum_required(VERSION 3.15)\nproject("
            << state.project_name << " VERSION 0.1)" << std::endl;

    outfile.close();
    std::filesystem::create_directory("build");
  }
}

void handle_package_manager(const SetupState &state) {
  if (state.package_manager == PackageManager::VCPKG) {
    system("vcpkg new --application");
    std::ofstream outfile("CMakePresets.json");
    std::string presets_out = R"(
{
  "version": 2,
  "configurePresets": [
    {
      "name": "vcpkg",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      }
    }
  ]
})";
    std::string vcpkg_dir = "";

    std::cout << rang::style::bold
              << "In which directory is your vcpkg installation?\n> "
              << rang::style::reset;

    std::getline(std::cin, vcpkg_dir);
    std::cout << "\n";
    std::string user_presets_out = std::string(R"(
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": ")") + vcpkg_dir +
                                   R"("
      }
    }
  ]
}
    )";

    outfile << presets_out << std::endl;

    outfile.close();

    std::ofstream outfile2("CMakeUserPresets.json");

    outfile2 << user_presets_out << std::endl;

    outfile2.close();

    std::ofstream gitignore_file(".gitignore");

    gitignore_file << "CMakeUserPresets.json\nbuild/\nvcpkg_installed/"
                   << std::endl;

    gitignore_file.close();

    system("cmake --preset=default");
  }
}
void generate_readme(const SetupState &state) {
  std::ofstream readme_file("README.md");

  readme_file << "# " << state.project_name << "\n";
  readme_file << "## Next steps\n";
  readme_file << "### Adding a main function\nCreate a `main.cc` file. Add "
                 "`add_executable("
              << state.project_name
              << " main.cc)` into your CMakeLists.txt\nRun this to verify that "
                 "your build system works:\n```bash\ncd build\ncmake "
                 "..\ncmake --build .\n./"
              << state.project_name << "\n```\n";
  readme_file << "### Adding VCPKG dependencies\n"
              << "Add dependencies via `vcpkg add port PACKAGE`\nThen, go to "
                 "your CMakeLists.txt and type these two lines:\n"
              << "```cmake\nfind_package(PACKAGE_NAME CONFIG "
                 "REQUIRED)\ntarget_link_libraries("
              << state.project_name
              << " PRIVATE PACKAGE_NAME::PACKAGE_NAME)\n```\n";
  readme_file.close();
}
void setup_tool() {
  SetupState state;
  get_project_name(state);
  get_package_manager(state);
  get_build_system(state);

  handle_build_system(state);
  handle_package_manager(state);

  generate_readme(state);

  std::cout << rang::style::bold << rang::fg::green
            << "\nDone generating project " << state.project_name << "."
            << "\nRead the " << rang::fg::blue << "README.md" << rang::fg::green
            << " file for further instructions.";
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << rang::fg::red << "At least 1 argument required.\n";
    return 1;
  }
  std::map<std::string, ToolChoice> m{{"setup", ToolChoice::SETUP}};
  std::string user_choice = argv[1];
  ToolChoice choice = ToolChoice::NONE;
  if (auto search = m.find(user_choice); search != m.end()) {
    choice = m[user_choice];
  }
  switch (choice) {
  case ToolChoice::SETUP: {
    setup_tool();
  } break;
  case ToolChoice::NONE:

  default:
    std::cout << rang::fg::red << "Option not found.\n";
  }
}
