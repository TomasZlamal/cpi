#include "cclass.h"

namespace cpi {
namespace cc {}

int cclass(std::string_view class_name, const toml::table &config) {
  config::ImplementationValues values = config::getImplValuesFromToml(config);
  if (!values.valid_values) {
    return 1;
  }
  bool hasNamespace = values.file_namespace != "";

  std::string impl_dir = "";
  impl_dir += values.implementation_dir;
  impl_dir += class_name;
  impl_dir += values.implementation_ext;

  std::string header_dir = "";
  header_dir += values.header_dir;
  header_dir += class_name;
  header_dir += values.header_ext;

  // Should be independent behaiviour from HERE ____
  /*std::cout << rang::style::bold << "IMPL: " << impl_dir
            << "\nHEADER: " << header_dir;*/
  std::ofstream header_file(header_dir);
  header_file << "#pragma once\n";
  if (hasNamespace)
    header_file << "namespace " << values.file_namespace << " {\n";
  header_file << "class " << class_name << " {};\n";
  if (hasNamespace)
    header_file << "} // namespace " << values.file_namespace << "\n";
  header_file.close();
  std::ofstream implementation_file(impl_dir);

  implementation_file << "#include \"../" << header_dir << "\"\n";
  if (hasNamespace)
    implementation_file << "namespace " << values.file_namespace << " {}\n";

  implementation_file.close();
  return 0;
}

} // namespace cpi
