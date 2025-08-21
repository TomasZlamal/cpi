#include "cpi_toml.h"

namespace cpi {
namespace config {

ImplementationValues getImplValuesFromToml(const toml::table &config) {
  ImplementationValues out;
  std::string impl_dir = config["Implementator"]["impl"].value_or("");
  if (impl_dir == "") {
    out.valid_values = false;
    std::cout << RANG_EXPR(rang::fg::red)
              << "No implementation directory provided.\n";
    return out;
  }
  std::string header_dir = config["Implementator"]["header"].value_or("");
  if (header_dir == "") {

    out.valid_values = false;
    std::cout << RANG_EXPR(rang::fg::red) << "No header directory provided.\n";
    return out;
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
  // default behaviour - select the .cc
  // file extension; same with header extension with .h

  std::string namespace_value =
      config["Implementator"]["namespace"].value_or("");
  out.valid_values = true;
  out.implementation_dir = impl_dir;
  out.header_dir = header_dir;
  out.implementation_ext = impl_extension;
  out.header_ext = header_extension;
  out.file_namespace = namespace_value;
  return out;
}
} // namespace config
} // namespace cpi
