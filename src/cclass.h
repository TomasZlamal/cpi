#include "cpi_toml.h"
#include "util.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace cpi {
namespace cc {}

int cclass(std::string_view class_name, const toml::table &config);
} // namespace cpi
