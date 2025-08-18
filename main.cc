#include "src/initcpi.h"
#include "src/setup.h"
#include "src/util.h"
#include <toml++/toml.hpp>

int create_class(std::string_view class_name, const toml::table &config) {
  std::string impl_dir = config["Implementator"]["impl"].value_or("");
  if (impl_dir == "") {
    std::cout << rang::fg::red << "No implementation directory provided.\n";
    return 1;
  }
  std::string header_dir = config["Implementator"]["header"].value_or("");
  if (header_dir == "") {
    std::cout << rang::fg::red << "No header directory provided.\n";
    return 1;
  }

  // create directories, if they dont exist
  if (!std::filesystem::is_directory(impl_dir))
    std::filesystem::create_directory(impl_dir);

  if (!std::filesystem::is_directory(header_dir))
    std::filesystem::create_directory(header_dir);

  std::string_view impl_extension =
      config["Implementator"]["impl_extension"].value_or(".cc");
  std::string_view header_extension =
      config["Implementator"]["header_extension"].value_or(".h");

  std::string namespace_value =
      config["Implementator"]["namespace"].value_or("");
  bool hasNamespace = namespace_value != "";

  // default behaviour - select the .cc
  // file extension; same with header extension with .h

  impl_dir += class_name;
  impl_dir += impl_extension;

  header_dir += class_name;
  header_dir += header_extension;
  /*std::cout << rang::style::bold << "IMPL: " << impl_dir
            << "\nHEADER: " << header_dir;*/
  std::ofstream header_file(header_dir);
  header_file << "#pragma once\n";
  if (hasNamespace)
    header_file << "namespace " << namespace_value << " {\n";
  header_file << "class " << class_name << " {};\n";
  if (hasNamespace)
    header_file << "} // namespace " << namespace_value << "\n";
  header_file.close();
  std::ofstream implementation_file(impl_dir);

  implementation_file << "#include \"../" << header_dir << "\"\n";
  if (hasNamespace)
    implementation_file << "namespace " << namespace_value << " {}\n";

  implementation_file.close();
  return 0;
}

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

    using namespace std::literals;
    try {
      auto config = toml::parse_file("cpi/cpi.toml");
      int ccfailed = create_class(argv[2], config);
      if (ccfailed) {
        std::cout << rang::fg::red << "'cclass' failed.\n";
        return 1;
      }

      std::cout << rang::fg::green << "'cclass' executed succesfully\n"
                << rang::fg::reset;

    } catch (const toml::parse_error &err) {

      std::cout << rang::fg::red
                << "Something went wrong with reading your cpi.toml file.\n";
      return 1;
    }

  } break;
  case cpi::ToolChoice::NONE:

  default:
    std::cout << rang::fg::red << "Option not found.\n";

    return 1;
  }

  return 0;
}
