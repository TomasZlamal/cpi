#pragma once
#include "cpi_toml.h"
#include "util.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace cpi {

int csplit(std::string_view file_name, const toml::table &config);
} // namespace cpi
