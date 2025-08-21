#include "util.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <toml++/toml.hpp>

namespace cpi {
namespace config {
struct ImplementationValues {
  bool valid_values;
  std::string implementation_dir;
  std::string header_dir;
  std::string file_namespace;
  std::string implementation_ext;
  std::string header_ext;
};
ImplementationValues getImplValuesFromToml(const toml::table &config);
} // namespace config
} // namespace cpi
