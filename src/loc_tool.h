#include "cpi_toml.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#pragma once
namespace cpi {
namespace loc {
bool isSubPath(const std::string &base, const std::string &destination);
}
int get_project_loc(const toml::table &config);
} // namespace cpi
