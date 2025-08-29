#include "util.h"
#include <iostream>
#include <string>
#include <toml++/toml.hpp>
#pragma once

namespace cpi {
int split_fn_execute(int (*fn)(std::string_view, const toml::table &), int argc,
                     char **argv, std::string_view fn_name);

}
